import csv
import os
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
        if variant != "dbnn":
            raise ValueError(variant)
        self.dt = float(dt)
        for name in ("tau_rise", "tau_decay", "omega"):
            self.register_parameter(name, nn.Parameter(torch.empty(500), requires_grad=False))
        for name in ("v_th", "reset_amp", "tau_reset"):
            self.register_parameter(name, nn.Parameter(torch.empty(()), requires_grad=False))
        self.bilinear = FixedBilinear()

    def forward(self, inputs):
        steps = inputs.shape[-1]
        lag = (torch.arange(steps, dtype=inputs.dtype, device=inputs.device) * self.dt - 0.5).clamp_min(0)
        kernels = self.omega[:, None] * (1.0 - torch.exp(-lag / self.tau_rise[:, None])) * torch.exp(-lag / self.tau_decay[:, None])
        size = 1 << (2 * steps - 2).bit_length()
        filtered = torch.fft.irfft(torch.fft.rfft(inputs, n=size, dim=-1) * torch.fft.rfft(kernels, n=size, dim=-1)[None], n=size, dim=-1)[..., :steps].transpose(1, 2)
        drive = filtered.sum(dim=-1) + self.bilinear.bias
        weight = self.bilinear.weight[0].to(filtered.dtype)
        weight = weight - torch.diag_embed(weight.diagonal())
        drive = drive + torch.einsum("bti,ij,btj->bt", filtered, weight, filtered)
        if bool(torch.all(drive < self.v_th)):
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
DATA_DIR = ROOT / "nc_final_data/FigureS5/FigureS5"
SOURCE_DIR = ROOT / "nc_final_source_data/FigureS5/FigureS5"
DATASETS = (("gait_recognition", "Gait"), ("nmnist", "N-MNIST"), ("dvs_gesture", "DVS-Gesture"), ("dvs_cifar10", "DVS-CIFAR10"))


def plot(means, stds, run_accuracies):
    with plt.rc_context({"font.size": 22, "axes.linewidth": 1.5, "pdf.fonttype": 42, "ps.fonttype": 42}):
        fig, ax = plt.subplots(figsize=(8.8, 5.8))
        positions = np.arange(len(DATASETS), dtype=float)
        width = 0.34
        style = {"elinewidth": 2.3, "ecolor": "black", "capsize": 6, "capthick": 2.3}
        ax.bar(positions - width / 2, means[:, 0], width=width, yerr=stds[:, 0], color="#4AB27E", edgecolor="black", linewidth=1.3, error_kw=style, label="Structured")
        ax.bar(positions + width / 2, means[:, 1], width=width, yerr=stds[:, 1], color="#5679BA", edgecolor="black", linewidth=1.3, error_kw=style, label="Random")
        offsets = np.linspace(-0.11, 0.11, run_accuracies.shape[2])
        for dataset in range(len(DATASETS)):
            for group in range(2):
                center = positions[dataset] + (-width / 2 if group == 0 else width / 2)
                ax.scatter(center + offsets, run_accuracies[dataset, group], s=25, facecolors="white", edgecolors="black", linewidths=.8, zorder=5)
        ax.set_ylim(0.0, 100.0)
        ax.set_yticks(np.arange(0.0, 101.0, 20.0))
        ax.set_ylabel("Accuracy (%)")
        ax.set_xticks(positions)
        ax.set_xticklabels([label for _, label in DATASETS], fontsize=19)
        ax.tick_params(axis="both", width=1.5, length=6)
        ax.spines["top"].set_visible(False)
        ax.spines["right"].set_visible(False)
        ax.legend(frameon=False, loc="upper right", fontsize=20)
        fig.subplots_adjust(left=0.13, right=0.97, bottom=0.16, top=0.97)
        fig.savefig(SCRIPT_DIR / "FigureS5.pdf", format="pdf")
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
    means = np.empty((len(DATASETS), 2), dtype=np.float64)
    stds = np.empty_like(means)
    run_accuracies = np.empty((len(DATASETS), 2, 5), dtype=np.float64)
    for dataset_index, (dataset, _) in enumerate(DATASETS):
        folder = DATA_DIR / dataset
        inputs = torch.from_numpy(np.load(folder / "test_input.npy", allow_pickle=False)).to(device)
        labels = torch.from_numpy(np.load(folder / "test_label.npy", allow_pickle=False)).long().to(device)
        counts = np.empty((2, 5), dtype=np.int64)
        with torch.inference_mode():
            for group, name in enumerate(("structured", "random")):
                for run in range(1, 6):
                    checkpoint = torch.load(folder / name / f"checkpoint_{run}.pt", map_location="cpu", weights_only=True)
                    if set(checkpoint) != {"model_state"}:
                        raise ValueError("Unexpected checkpoint fields")
                    model = LocalDBNN(dataset).to(device).eval()
                    model.load_state_dict(checkpoint["model_state"], strict=True)
                    for start in range(0, len(labels), 32):
                        prediction = model(inputs[start:start + 32].float()).argmax(dim=1)
                        counts[group, run - 1] = 0 if start == 0 else counts[group, run - 1]
                        counts[group, run - 1] += int((prediction == labels[start:start + 32]).sum())
                    print(dataset, name, run, counts[group, run - 1], len(labels), flush=True)
        values = counts.astype(np.float64) / len(labels)
        run_accuracies[dataset_index] = values * 100.0
        means[dataset_index] = values.mean(axis=1) * 100.0
        stds[dataset_index] = values.std(axis=1, ddof=1) * 100.0
    columns = [f"{dataset}_{mapping}_accuracy_percent" for dataset, _ in DATASETS for mapping in ("structured", "random")]
    write_table(SOURCE_DIR / "FigureS5.csv", columns, run_accuracies.reshape(len(columns), 5), means.reshape(-1), stds.reshape(-1))
    plot(means, stds, run_accuracies)


if __name__ == "__main__":
    main()
