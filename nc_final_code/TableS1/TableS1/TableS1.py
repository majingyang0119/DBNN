import csv
import os
from decimal import Decimal, ROUND_HALF_UP
from pathlib import Path
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

import numpy as np
import torch
from torch import nn
import torch.nn.functional as F


class FixedBilinear(nn.Module):
    def __init__(self):
        super().__init__()
        self.weight = nn.Parameter(torch.empty(1, 500, 500), requires_grad=False)
        self.register_buffer("bias", torch.empty(1))


class FixedCore(nn.Module):
    def __init__(self, variant, dt):
        super().__init__()
        self.variant = variant
        self.dt = float(dt)
        for name in ("tau_rise", "tau_decay", "omega"):
            self.register_parameter(name, nn.Parameter(torch.empty(500), requires_grad=False))
        for name in ("v_th", "reset_amp", "tau_reset"):
            self.register_parameter(name, nn.Parameter(torch.empty(()), requires_grad=False))
        self.bilinear = FixedBilinear()
        if variant in ("relu", "sigmoid", "linear", "diagonal_quadratic"):
            self.nonlinear_weight = nn.Parameter(torch.empty(500), requires_grad=False)
            self.nonlinear_bias = nn.Parameter(torch.empty(()), requires_grad=False)
            self.nonlinear_scale = nn.Parameter(torch.empty(()), requires_grad=False)
            self.diagonal_quadratic_weight = nn.Parameter(torch.empty(500), requires_grad=False)

    def forward(self, inputs):
        steps = inputs.shape[-1]
        lag = (torch.arange(steps, dtype=inputs.dtype, device=inputs.device) * self.dt - 0.5).clamp_min(0)
        kernels = self.omega[:, None] * (1.0 - torch.exp(-lag / self.tau_rise[:, None])) * torch.exp(-lag / self.tau_decay[:, None])
        size = 1 << (2 * steps - 2).bit_length()
        filtered = torch.fft.irfft(torch.fft.rfft(inputs, n=size, dim=-1) * torch.fft.rfft(kernels, n=size, dim=-1)[None], n=size, dim=-1)[..., :steps].transpose(1, 2)
        drive = filtered.sum(dim=-1) + self.bilinear.bias
        if self.variant in ("dbnn", "uniform_tau", "no_reset"):
            weight = self.bilinear.weight[0].to(filtered.dtype)
            weight = weight - torch.diag_embed(weight.diagonal())
            drive = drive + torch.einsum("bti,ij,btj->bt", filtered, weight, filtered)
        elif self.variant == "diagonal_quadratic":
            drive = drive + (filtered.square() * self.diagonal_quadratic_weight).sum(dim=-1)
        elif self.variant in ("relu", "sigmoid"):
            projection = (filtered * self.nonlinear_weight).sum(dim=-1) + self.nonlinear_bias
            drive = drive + self.nonlinear_scale * (F.relu(projection) if self.variant == "relu" else torch.sigmoid(projection))
        elif self.variant != "linear":
            raise ValueError(self.variant)
        if self.variant == "no_reset" or bool(torch.all(drive < self.v_th)):
            return drive
        alpha = torch.exp(-torch.tensor(self.dt, dtype=drive.dtype, device=drive.device) / self.tau_reset.abs().clamp_min(1e-4))
        reset = torch.zeros(inputs.shape[0], device=inputs.device, dtype=inputs.dtype)
        values = []
        for step in range(steps):
            voltage = drive[:, step] + reset
            spike = (voltage >= self.v_th).to(voltage.dtype)
            reset = alpha * reset - self.reset_amp.abs() * spike
            values.append(voltage)
        return torch.stack(values, dim=-1)


class LocalEncoder(nn.Module):
    def __init__(self, dataset):
        super().__init__()
        self.dataset = dataset
        self.feature_maps = 8
        self.convolutions = nn.Sequential(nn.Conv2d(2, 96, 3, padding=1, groups=2), nn.GELU(), nn.Conv2d(96, 128, 3, padding=1, groups=2), nn.GELU(), nn.Conv2d(128, 16, 1, groups=2))
        self.node_mix_logits = nn.Parameter(torch.empty(2, 250, 8))
        self.log_input_gain = nn.Parameter(torch.empty(2))
        self.register_buffer("synapse_to_node", torch.empty(500, dtype=torch.int64))

    def forward(self, inputs):
        batch, steps = inputs.shape[:2]
        if self.dataset == "gait_recognition":
            frames = inputs.float().reshape(batch * steps, 1, 48, 30) / 255.0
            frames = F.adaptive_avg_pool2d(frames, (16, 16)).repeat(1, 2, 1, 1)
        else:
            frames = inputs.float().reshape(batch * steps, 2, 7, 7)[:, [1, 0]]
        frames = torch.sigmoid(self.convolutions(frames))
        if frames.shape[-2:] != (16, 16):
            frames = F.interpolate(frames, size=(16, 16), mode="bilinear", align_corners=False)
        frames = frames.reshape(batch * steps, 2, self.feature_maps, 256)[..., :250]
        weights = self.node_mix_logits.softmax(dim=-1)
        nodes = torch.einsum("bpkm,pmk->bpm", frames, weights)
        gains = self.log_input_gain.exp().clamp(1e-7, 0.2)
        nodes = (nodes * gains[None, :, None]).reshape(batch, steps, 500)
        return nodes[:, :, self.synapse_to_node].transpose(1, 2)


class LocalDBNN(nn.Module):
    def __init__(self, dataset, variant="dbnn"):
        super().__init__()
        self.dataset = dataset
        self.phases = 20 if dataset == "gait_recognition" else 49
        self.front = LocalEncoder(dataset)
        dt = 2.0 if dataset == "gait_recognition" else 1.0 if dataset == "dvs_gesture" else 10.0
        self.core = FixedCore(variant, dt)
        output_steps = 1000 if dataset == "gait_recognition" else 980
        classes = 11 if dataset == "dvs_gesture" else 10
        self.classifier = nn.Linear(output_steps, classes)
        self.logit_gain = nn.Parameter(torch.empty(()))

    def features_before_classifier(self, inputs):
        encoded = self.front(inputs)
        node_phase = torch.div(torch.arange(250, device=encoded.device) * self.phases, 250, rounding_mode="floor").repeat(2)
        synapse_phase = node_phase[self.front.synapse_to_node]
        phase_mask = F.one_hot(synapse_phase, num_classes=self.phases).to(encoded.dtype)
        encoded = (encoded.unsqueeze(-1) * phase_mask[None, :, None, :]).reshape(encoded.shape[0], 500, -1)
        if encoded.shape[-1] != self.classifier.in_features:
            encoded = F.interpolate(encoded, size=self.classifier.in_features, mode="linear", align_corners=False)
        trace = self.core(encoded)
        return (trace - self.core.bilinear.bias) / 0.3

    def forward(self, inputs):
        return self.classifier(self.features_before_classifier(inputs)) * self.logit_gain




SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "nc_final_data/TableS1/TableS1"
SOURCE = ROOT / "nc_final_source_data/TableS1/TableS1"
DATASETS = ("gait_recognition", "nmnist", "dvs_gesture", "dvs_cifar10")
DATASET_LABELS = ("Gait recognition", "N-MNIST", "DVS-Gesture", "DVS-CIFAR10")
VARIANTS = ("dbnn", "relu", "sigmoid", "linear", "diagonal_quadratic", "uniform_tau", "no_reset")
VARIANT_LABELS = ("DBNN", "ReLU", "Sigmoid", "Linear", "Diagonal\nquadratic", "Uniform time\nconstant", "No\nreset")


def draw_table(strings):
    plt.rcParams.update({"font.family": "DejaVu Serif"})
    fig, ax = plt.subplots(figsize=(12.3, 2.75))
    ax.set_axis_off()
    ax.text(0.02, 0.96, "Table S1   Classification accuracy (%) in the DBNN ablation studies.", transform=ax.transAxes, fontsize=14, va="top")
    cells = [[label, *row] for label, row in zip(DATASET_LABELS, strings)]
    table = ax.table(cellText=cells, colLabels=["", *VARIANT_LABELS], cellLoc="center", colWidths=[0.20, 0.095, 0.095, 0.095, 0.095, 0.14, 0.15, 0.09], bbox=[0.02, 0.15, 0.96, 0.63])
    table.auto_set_font_size(False)
    table.set_fontsize(12)
    for (row, column), cell in table.get_celld().items():
        cell.visible_edges = ""
        if row == 0:
            cell.set_height(cell.get_height() * 1.55)
            cell.visible_edges = "TB"
            cell.set_linewidth(0.9)
        elif row == len(DATASETS):
            cell.visible_edges = "B"
            cell.set_linewidth(0.9)
        if row > 0 and column == 0:
            cell.get_text().set_ha("left")
        if row > 0 and column == 1:
            cell.get_text().set_weight("bold")
    fig.savefig(SCRIPT_DIR / "TableS1.pdf", format="pdf", bbox_inches="tight")
    plt.close(fig)






def write_table(path, columns, runs, means, stds):
    values = np.asarray(runs)
    if values.ndim != 2 or values.shape[0] != len(columns) or len(means) != len(columns) or len(stds) != len(columns):
        raise ValueError("Unexpected source table shape")
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.{os.getpid()}.tmp")
    try:
        with temporary.open("w", encoding="utf-8", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(["run", *columns])
            for index in range(values.shape[1]):
                writer.writerow([f"run_{index + 1}", *values[:, index]])
            writer.writerow(["mean", *means])
            writer.writerow(["std", *stds])
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


def main():
    torch.set_num_threads(4)
    torch.backends.cuda.matmul.allow_tf32 = False
    torch.backends.cudnn.allow_tf32 = False
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    means = np.empty((len(DATASETS), len(VARIANTS)), dtype=np.float64)
    run_accuracies = np.empty((len(DATASETS), len(VARIANTS), 5), dtype=np.float64)
    texts = []
    for dataset_index, dataset in enumerate(DATASETS):
        folder = DATA / dataset
        inputs = torch.from_numpy(np.load(folder / "test_input.npy", allow_pickle=False)).to(device)
        labels = torch.from_numpy(np.load(folder / "test_label.npy", allow_pickle=False)).long().to(device)
        row = []
        with torch.inference_mode():
            for variant_index, variant in enumerate(VARIANTS):
                counts = []
                for run in range(1, 6):
                    checkpoint = torch.load(folder / variant / f"checkpoint_{run}.pt", map_location="cpu", weights_only=True)
                    if set(checkpoint) != {"model_state"}:
                        raise ValueError("Unexpected checkpoint fields")
                    model = LocalDBNN(dataset, variant).to(device).eval()
                    model.load_state_dict(checkpoint["model_state"], strict=True)
                    correct = 0
                    for start in range(0, len(labels), 32):
                        predictions = model(inputs[start:start + 32].float()).argmax(dim=1)
                        correct += int((predictions == labels[start:start + 32]).sum())
                    counts.append(correct)
                    print(dataset, variant, run, correct, len(labels), flush=True)
                run_accuracies[dataset_index, variant_index] = np.asarray(counts, dtype=np.float64) * 100.0 / len(labels)
                value = Decimal(100) * Decimal(sum(counts)) / Decimal(5 * len(labels))
                means[dataset_index, variant_index] = float(value)
                row.append(str(value.quantize(Decimal("0.1"), rounding=ROUND_HALF_UP)))
        texts.append(row)
    columns = [f"{dataset}_{variant}_accuracy_percent" for dataset in DATASETS for variant in VARIANTS]
    stds = run_accuracies.std(axis=2, ddof=1)
    write_table(SOURCE / "TableS1.csv", columns, run_accuracies.reshape(len(columns), 5), means.reshape(-1), stds.reshape(-1))
    draw_table(texts)


if __name__ == "__main__":
    main()
