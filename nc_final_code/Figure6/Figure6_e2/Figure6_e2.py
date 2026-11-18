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


class TemporalTCN(nn.Module):
    def __init__(self, features, classes, width):
        super().__init__()
        self.net = nn.Sequential(nn.Conv1d(features, width, 3, padding=1), nn.GELU(), nn.Dropout(0.1), nn.Conv1d(width, width, 3, padding=2, dilation=2), nn.GELU(), nn.Dropout(0.1))
        self.classifier = nn.Linear(width, classes)

    def features_before_classifier(self, inputs):
        return self.net(inputs.transpose(1, 2)).mean(dim=2)

    def forward(self, inputs):
        return self.classifier(self.features_before_classifier(inputs))


class TemporalMLP(nn.Module):
    def __init__(self, features, steps, classes, width):
        super().__init__()
        self.net = nn.Sequential(nn.Flatten(), nn.Linear(features * steps, width), nn.GELU(), nn.Dropout(0.1), nn.Linear(width, classes))

    def features_before_classifier(self, inputs):
        return self.net[:4](inputs)

    def forward(self, inputs):
        return self.net(inputs)


class TemporalLSTM(nn.Module):
    def __init__(self, features, classes, projection, hidden):
        super().__init__()
        self.input_projection = nn.Linear(features, projection)
        self.lstm = nn.LSTM(projection, hidden, batch_first=True)
        self.dropout = nn.Dropout(0.1)
        self.classifier = nn.Linear(hidden, classes)

    def features_before_classifier(self, inputs):
        _, (hidden, _) = self.lstm(self.input_projection(inputs))
        return self.dropout(hidden[-1])

    def forward(self, inputs):
        return self.classifier(self.features_before_classifier(inputs))


class TemporalSNN(nn.Module):
    def __init__(self, features, classes, hidden):
        super().__init__()
        self.input_gain_raw = nn.Parameter(torch.empty(()))
        self.hidden_layer = nn.Linear(features, hidden)
        self.output_layer = nn.Linear(hidden, classes)

    def simulate(self, inputs):
        hidden = inputs.new_zeros((inputs.shape[0], self.hidden_layer.out_features))
        output = inputs.new_zeros((inputs.shape[0], self.output_layer.out_features))
        logits = torch.zeros_like(output)
        hidden_sum = torch.zeros_like(hidden)
        gain = F.softplus(self.input_gain_raw)
        for step in range(inputs.shape[1]):
            hidden = 0.2 * hidden + self.hidden_layer(gain * inputs[:, step])
            hidden_spikes = (hidden >= 1.0).to(hidden.dtype)
            hidden = hidden - hidden_spikes
            output = 0.2 * output + self.output_layer(hidden_spikes)
            output_spikes = (output >= 1.0).to(output.dtype)
            output = output - output_spikes
            logits = logits + output
            hidden_sum = hidden_sum + hidden_spikes
        return logits / inputs.shape[1], hidden_sum / inputs.shape[1]

    def features_before_classifier(self, inputs):
        return self.simulate(inputs)[1]

    def forward(self, inputs):
        return self.simulate(inputs)[0]


def make_model(dataset, name, variant="dbnn"):
    gait = dataset == "gait_recognition"
    features = 18 if gait else 98
    steps = 50 if gait else 20
    classes = 11 if dataset == "dvs_gesture" else 10
    if name == "dbnn":
        return LocalDBNN(dataset, variant)
    if name == "tcn":
        return TemporalTCN(features, classes, 64 if gait else 24)
    if name == "mlp":
        return TemporalMLP(features, steps, classes, 80 if gait else 5)
    if name == "lstm":
        return TemporalLSTM(features, classes, 64 if gait else 54, 64 if gait else 13)
    if name == "snn":
        return TemporalSNN(features, classes, 400 if gait else 83)
    raise ValueError(name)


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = Path(__file__).resolve().parents[3]
DATA_DIR = ROOT / "nc_final_data/Figure6/Figure6_e2"
SOURCE_DIR = ROOT / "nc_final_source_data/Figure6/Figure6_e2"
DATASET = "dvs_cifar10"
NAMES = ("dbnn", "tcn", "mlp", "lstm", "snn")
COLORS = ("#B24A4A", "#5679BA", "#4AB27E", "#D1844F", "#A6AD55")




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
    inputs = torch.from_numpy(np.load(DATA_DIR / "test_input.npy", allow_pickle=False)).to(device)
    labels = torch.from_numpy(np.load(DATA_DIR / "test_label.npy", allow_pickle=False)).long().to(device)
    dbnn_inputs = torch.from_numpy(np.load(DATA_DIR / "test_frames.npy", allow_pickle=False)).to(device) if DATASET == "gait_recognition" else inputs
    accuracy = np.empty((len(NAMES), 5), dtype=np.float64)
    with torch.inference_mode():
        for model_index, name in enumerate(NAMES):
            x = dbnn_inputs if name == "dbnn" else inputs
            for run in range(1, 6):
                checkpoint = torch.load(DATA_DIR / name / f"checkpoint_{run}.pt", map_location="cpu", weights_only=True)
                if set(checkpoint) != {"model_state"}:
                    raise ValueError("Unexpected checkpoint fields")
                model = make_model(DATASET, name).to(device).eval()
                model.load_state_dict(checkpoint["model_state"], strict=True)
                correct = 0
                for start in range(0, len(labels), 32):
                    prediction = model(x[start:start + 32].float()).argmax(dim=1)
                    correct += int((prediction == labels[start:start + 32]).sum())
                accuracy[model_index, run - 1] = correct / len(labels)
                print(name, run, correct, len(labels), flush=True)
    means = accuracy.mean(axis=1) * 100.0
    stds = accuracy.std(axis=1, ddof=1) * 100.0
    columns = [f"{name}_accuracy_percent" for name in NAMES]
    write_table(SOURCE_DIR / f"{SCRIPT_DIR.name}.csv", columns, accuracy * 100.0, means, stds)
    plot_accuracy(accuracy, means, stds)


def plot_accuracy(accuracy, means, stds):
    with plt.rc_context({"font.size": 32, "pdf.fonttype": 42, "ps.fonttype": 42}):
        fig, ax = plt.subplots(figsize=(8, 6))
        ax.bar(np.arange(len(NAMES)), means, width=0.8, color=COLORS, edgecolor="black", linewidth=1.2,
               yerr=stds, error_kw={"elinewidth": 2, "ecolor": "black", "capsize": 5, "capthick": 2})
        offsets = np.linspace(-0.24, 0.24, accuracy.shape[1])
        for index in range(len(NAMES)):
            ax.scatter(index + offsets, accuracy[index] * 100.0, s=58, facecolors="white", edgecolors="black", linewidths=1.0, zorder=5)
        ax.set_xticks(np.arange(len(NAMES)), ["DBNN", "TCN", "MLP", "LSTM", "SNN"])
        ax.set_ylabel("Accuracy (%)")
        ymin = max(0.0, float(np.min(means - stds)) - 5.0)
        ymax = min(100.0, float(np.max(means + stds)) + 5.0)
        step = 5.0 if ymax - ymin <= 25.0 else 10.0
        start = step * round(((ymin + ymax) / 2.0 - 1.5 * step) / step)
        ticks = start + step * np.arange(4)
        ax.set_ylim(min(ymin, float(ticks[0])), max(ymax, float(ticks[-1])))
        ax.set_yticks(ticks)
        lower, upper = ax.get_ylim()
        minimum, maximum = float(np.min(accuracy) * 100.0), float(np.max(accuracy) * 100.0)
        if minimum < lower or maximum > upper:
            lower = min(lower, max(0.0, 5.0 * np.floor((minimum - 0.5) / 5.0)))
            upper = max(upper, min(100.0, 5.0 * np.ceil((maximum + 0.5) / 5.0)))
            ax.set_ylim(lower, upper)
            step = 5.0 if upper - lower <= 25.0 else 10.0
            ax.set_yticks(np.arange(step * np.ceil(lower / step), upper + 0.1 * step, step))
        ax.spines["top"].set_visible(False)
        ax.spines["right"].set_visible(False)
        fig.subplots_adjust(left=0.20, right=0.97, bottom=0.18, top=0.97)
        fig.savefig(SCRIPT_DIR / "Figure6_e2.pdf", format="pdf")
        plt.close(fig)


if __name__ == "__main__":
    main()
