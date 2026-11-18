from itertools import zip_longest
import csv
import os
import argparse
from pathlib import Path
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1.inset_locator import mark_inset

ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "nc_final_data" / "FigureS4" / "FigureS4_abc"
SOURCE = ROOT / "nc_final_source_data" / "FigureS4"
VARIANTS = ("dbnn", "relu", "sigmoid", "linear", "diagonal_quadratic")
LABELS = ("DBNN", "ReLU", "Sigmoid", "Linear", "Diagonal\nquadratic")
COLORS = ("#B24A4A", "#D1844F", "#A6AD55", "#4AB27E", "#4C78A8")

class Bilinear(nn.Module):
    def __init__(self, device):
        super().__init__()
        self.weight = nn.Parameter(torch.zeros((1, 500, 500), device=device))
        self.register_buffer("bias", torch.tensor([-70.0], device=device))

    def forward(self, x):
        with torch.no_grad():
            index = torch.arange(500, device=self.weight.device)
            self.weight[:, index, index] = 0
        return torch.einsum("...i,ij,...j->...", x, self.weight[0], x).unsqueeze(-1) + self.bias


class Model(nn.Module):
    def __init__(self, variant, device):
        super().__init__()
        self.variant = variant
        self.tau_rise = nn.Parameter(torch.ones(500, device=device) * 5)
        self.tau_decay = nn.Parameter(torch.ones(500, device=device) * 20)
        self.omega = nn.Parameter(torch.ones(500, device=device) * 0.3)
        self.bilinear = Bilinear(device)
        self.v_th = nn.Parameter(torch.tensor(-55.0, device=device))
        self.reset_amp = nn.Parameter(torch.tensor(15.0, device=device))
        self.tau_reset = nn.Parameter(torch.tensor(10.0, device=device))
        if variant != "dbnn":
            self.nonlinear_weight = nn.Parameter(torch.zeros(500, device=device))
            self.nonlinear_bias = nn.Parameter(torch.zeros((), device=device))
            self.nonlinear_scale = nn.Parameter(torch.zeros((), device=device))
            self.diagonal_quadratic_weight = nn.Parameter(torch.zeros(500, device=device))

    def forward_drive(self, x):
        steps = x.shape[-1]
        time = torch.arange(steps, device=x.device)
        kernels = self.omega[:, None] * (1 - torch.exp(-time / self.tau_rise[:, None])) * torch.exp(-time / self.tau_decay[:, None])
        fft_size = 1 << (2 * steps - 2).bit_length()
        spectrum = torch.fft.rfft(x, n=fft_size, dim=2)
        transfer = torch.fft.rfft(kernels, n=fft_size, dim=1)
        y = torch.fft.irfft(spectrum * transfer[None], n=fft_size, dim=2)[..., :steps].permute(0, 2, 1)
        linear = y.sum(dim=2)
        if self.variant == "dbnn":
            return linear + self.bilinear(y).squeeze(-1)
        base = linear + self.bilinear.bias.view(1, 1)
        if self.variant == "linear":
            return base
        if self.variant == "diagonal_quadratic":
            return base + (y.square() * self.diagonal_quadratic_weight.view(1, 1, -1)).sum(dim=2)
        projection = (y * self.nonlinear_weight.view(1, 1, -1)).sum(dim=2) + self.nonlinear_bias
        nonlinear = torch.sigmoid(projection) if self.variant == "sigmoid" else F.relu(projection)
        return base + self.nonlinear_scale * nonlinear

    def forward(self, x):
        drive = self.forward_drive(x)
        steps = drive.shape[1]
        alpha = torch.exp(-torch.ones((), device=drive.device, dtype=drive.dtype) / torch.clamp(torch.abs(self.tau_reset), min=1e-4))
        amplitude = torch.abs(self.reset_amp).to(dtype=drive.dtype)
        decay = alpha.pow(torch.arange(steps, device=drive.device, dtype=drive.dtype))
        result = torch.empty_like(drive)
        state = torch.zeros((), device=drive.device, dtype=drive.dtype)
        start = 0
        while start < steps:
            values = drive[0, start:] + state * decay[:steps - start]
            indices = torch.nonzero(values >= self.v_th, as_tuple=False)
            if indices.numel() == 0:
                result[0, start:] = values
                break
            offset = int(indices[0, 0].item())
            end = start + offset
            result[0, start:end + 1] = values[:offset + 1]
            state_at_spike = state * decay[offset]
            state = alpha * state_at_spike - amplitude
            start = end + 1
        return result


def model_for(variant, index, device):
    model = Model(variant, device)
    checkpoint = torch.load(DATA / variant / f"checkpoint_{index}.pt", map_location="cpu", weights_only=True)
    if set(checkpoint) != {"model_state"}:
        raise ValueError("Unexpected checkpoint contents")
    model.load_state_dict(checkpoint["model_state"], strict=True)
    return model.eval()


def prediction(model, raster, device):
    value = np.asarray(raster, dtype=np.float32).copy()
    value[250:] *= -1
    with torch.inference_mode():
        return model(torch.as_tensor(value[None], device=device)).cpu().numpy()[0]


def spike_times(trace, threshold):
    above = trace >= threshold
    rising = np.flatnonzero(above[1:] & ~above[:-1]) + 1
    if above[0]:
        rising = np.r_[0, rising]
    return rising.astype(np.int32)


def load_spikes(split):
    values = np.load(DATA / f"{split}_spike_times.npy", allow_pickle=False)
    offsets = np.load(DATA / f"{split}_spike_offsets.npy", allow_pickle=False)
    return [values[offsets[i]:offsets[i + 1]] for i in range(len(offsets) - 1)]


def verify_events(split, inputs, rows):
    bins = np.load(DATA / f"{split}_event_bins.npy", mmap_mode="r", allow_pickle=False)
    offsets = np.load(DATA / f"{split}_event_offsets.npy", mmap_mode="r", allow_pickle=False)
    if len(offsets) != len(inputs) * 500 + 1:
        raise ValueError("Incorrect event offsets")
    for row in rows:
        rebuilt = np.zeros((500, 6001), dtype=np.uint8)
        for channel in range(500):
            start, stop = offsets[row * 500 + channel:row * 500 + channel + 2]
            events = np.asarray(bins[start:stop], dtype=np.int64)
            rebuilt[channel, events + events % 2] = 1
        if not np.array_equal(rebuilt, inputs[row]):
            raise ValueError(f"Input does not match physical event bins: {split} {row}")


def setup():
    parser = argparse.ArgumentParser()
    parser.add_argument("--device", default="auto")
    parser.add_argument("--output", type=Path, default=Path(__file__).resolve().with_suffix(".pdf"))
    args = parser.parse_args()
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu") if args.device == "auto" else torch.device(args.device)
    torch.set_num_threads(4)
    torch.backends.cuda.matmul.allow_tf32 = False
    torch.backends.cudnn.allow_tf32 = False
    plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 24, "pdf.fonttype": 42, "ps.fonttype": 42})
    return args, device

def matching_counts(true_spikes, predicted_spikes):
    used = np.zeros(len(predicted_spikes), dtype=bool)
    matched = 0
    for true in true_spikes:
        best, distance = -1, 11.0
        for index, predicted in enumerate(predicted_spikes):
            delta = abs(predicted - true)
            if not used[index] and delta <= 10 and delta < distance:
                best, distance = index, delta
        if best >= 0:
            used[best] = True
            matched += 1
    return matched, int((~used).sum()), len(true_spikes) - matched


def keep_mask(spikes, size):
    keep = np.ones(size, dtype=bool)
    for spike in spikes:
        start = max(0, int(np.floor(spike - 10)))
        stop = min(size, int(np.ceil(spike + 10)) + 1)
        keep[start:stop] = False
    return keep


def evaluate(model, inputs, truth, spikes, device):
    residual_n = residual_sum = residual_square = 0.0
    truth_n = truth_sum = truth_square = 0.0
    tp = fp = fn = 0
    threshold = float(model.v_th.detach().cpu())
    for row in range(len(inputs)):
        predicted = prediction(model, inputs[row], device)
        keep = keep_mask(spikes[row], truth.shape[1])
        residual = truth[row, keep].astype(np.float64) - predicted[keep].astype(np.float64)
        actual = truth[row].astype(np.float64)
        residual_n += len(residual)
        residual_sum += residual.sum()
        residual_square += np.dot(residual, residual)
        truth_n += len(actual)
        truth_sum += actual.sum()
        truth_square += np.dot(actual, actual)
        a, b, c = matching_counts(spikes[row], spike_times(predicted, threshold))
        tp, fp, fn = tp + a, fp + b, fn + c
    variance = residual_square / residual_n - (residual_sum / residual_n) ** 2
    reference = truth_square / truth_n - (truth_sum / truth_n) ** 2
    f1 = 2 * tp / (2 * tp + fp + fn) if 2 * tp + fp + fn else 0.0
    return 1 - variance / reference, f1


def compute_bars(device):
    inputs = np.load(DATA / "test_ip.npy", mmap_mode="r", allow_pickle=False)
    truth = np.load(DATA / "test_op.npy", allow_pickle=False)
    spikes = load_spikes("test")
    if inputs.shape != (100, 500, 6001) or truth.shape != (100, 6001) or len(spikes) != 100:
        raise ValueError("Expected the shared 100-sample test dataset")
    verify_events("test", inputs, range(100))
    values = np.empty((5, 5, 2), dtype=np.float64)
    for i, variant in enumerate(VARIANTS):
        for j in range(5):
            model = model_for(variant, j + 1, device)
            values[i, j] = evaluate(model, inputs, truth, spikes, device)
            print(variant, j + 1, values[i, j].tolist(), flush=True)
    return values, values.mean(axis=1), values.std(axis=1, ddof=0)


def save_bar_data(means, stds, values):
    columns = [f"{variant}_{metric}" for variant in VARIANTS for metric in ("VE", "F1")]
    runs = values.transpose(0, 2, 1).reshape(len(columns), 5)
    write_table(SOURCE / "FigureS4_bc" / "FigureS4_bc.csv", columns, runs, means.reshape(-1), stds.reshape(-1))


def draw_bar(ax, metric, means, stds, values):
    index = 0 if metric == "ve" else 1
    x = np.arange(5, dtype=float)
    ax.bar(x, means[:, index], yerr=stds[:, index], width=0.68, color=COLORS, edgecolor="black", linewidth=1.2,
           error_kw={"elinewidth": 2, "ecolor": "black", "capsize": 5, "capthick": 2})
    offsets = np.linspace(-0.21, 0.21, values.shape[1])
    for variant in range(len(x)):
        ax.scatter(x[variant] + offsets, values[variant, :, index], s=48, facecolors="white", edgecolors="black", linewidths=1.0, zorder=5)
    ax.set_xticks(x, LABELS)
    ax.tick_params(axis="x", labelsize=18, pad=7)
    ax.set_ylabel("VE" if metric == "ve" else "F1 score")
    ax.set_ylim(0, 1)
    ax.set_yticks(np.linspace(0, 1, 6))
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)

def compute_trace(device):
    inputs = np.load(DATA / "train_ip.npy", mmap_mode="r", allow_pickle=False)
    truth = np.load(DATA / "train_op.npy", mmap_mode="r", allow_pickle=False)
    spikes = load_spikes("train")
    if inputs.ndim != 3 or inputs.shape[1:] != (500, 6001) or len(inputs) < 1 or truth.shape != (len(inputs), 6001) or len(spikes) != len(inputs):
        raise ValueError("Expected matching training inputs, voltages and spike records")
    target = np.asarray(truth[0], dtype=np.float32).copy()
    displayed = target.copy()
    for spike in spikes[0]:
        center = int(np.clip(np.rint(spike), 0, len(target) - 1))
        start, stop = max(0, center - 3), min(len(target), center + 4)
        displayed[start + int(np.argmax(target[start:stop]))] = 20.0
    predictions = []
    segments = []
    for variant in VARIANTS:
        model = model_for(variant, 1, device)
        trace = prediction(model, inputs[0], device)
        times = spike_times(trace, float(model.v_th.detach().cpu()))
        plotted = trace.copy()
        for spike in times:
            plotted[int(np.clip(np.rint(spike), 0, len(trace) - 1))] = 20.0
        if variant == "dbnn":
            for spike in times:
                index = int(np.clip(np.rint(spike), 0, len(trace) - 1))
                start, stop = max(0, index - 3), min(len(trace), index + 4)
                segments.append([float(spike), float(np.median(plotted[start:stop])), float(plotted[index])])
        predictions.append(plotted)
    return displayed, predictions, np.asarray(segments, dtype=np.float64).reshape(-1, 3)


def save_trace_data(target, predictions, segments):
    columns = ("time_ms", "NEURON") + tuple(variant.upper() for variant in VARIANTS)
    arrays = (np.arange(len(target), dtype=np.float64), target, *predictions)
    write_columns(SOURCE / "FigureS4_a" / "FigureS4_a.csv", columns, arrays)


def draw_trace(ax, target, predictions, segments):
    time = np.arange(len(target), dtype=float)
    ax.plot(time, target, color="#111111", linewidth=2.2, label="Neuron", zorder=7)
    for i, (trace, label, color) in enumerate(zip(predictions, LABELS, COLORS)):
        ax.plot(time, trace, color=color, linewidth=2.0 if i == 0 else 1.35, alpha=1.0 if i == 0 else 0.9,
                label=label.replace("\n", " "), zorder=6 if i == 0 else 3)
    for timepoint, baseline, peak in segments:
        ax.vlines(timepoint, ymin=baseline, ymax=peak, color=COLORS[0], linewidth=2.4, linestyles="--", zorder=10)
    ax.set_xlim(0, 6100)
    ax.set_ylim(-97, 25)
    ax.axis("off")
    ax.legend(frameon=False, ncol=2, fontsize=16, loc="upper right")
    inset = ax.inset_axes([0.35, 0.49, 0.30, 0.44])
    inset.plot(time, target, color="#111111", linewidth=1.8, zorder=7)
    for i, (trace, color) in enumerate(zip(predictions, COLORS)):
        inset.plot(time, trace, color=color, linewidth=1.7 if i == 0 else 1.15,
                   alpha=1.0 if i == 0 else 0.9, zorder=6 if i == 0 else 3)
    start, stop = 4500, 4800
    values = [target[start:stop]] + [trace[start:stop] for trace in predictions]
    low = min(float(value.min()) for value in values)
    high = max(float(value.max()) for value in values)
    padding = max(0.5, 0.08 * (high - low))
    inset.set_xlim(start, stop)
    inset.set_ylim(low - padding, high + padding)
    inset.set_xticks([])
    inset.set_yticks([])
    inset.tick_params(length=0)
    for spine in inset.spines.values():
        spine.set_visible(True)
        spine.set_color("black")
        spine.set_linewidth(0.9)
    mark_inset(ax, inset, loc1=3, loc2=4, facecolor="none", edgecolor="0.35", alpha=0.8)



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




def write_columns(path, columns, arrays):
    values = [np.asarray(value) for value in arrays]
    if any(value.ndim != 1 for value in values) or len(columns) != len(values):
        raise ValueError("Unexpected source data shape")
    values = [value.astype(np.float64) if value.dtype == np.float32 else value for value in values]
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.{os.getpid()}.tmp")
    try:
        with temporary.open("w", encoding="utf-8", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(columns)
            writer.writerows(zip_longest(*values, fillvalue=""))
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


def main():
    args, device = setup()
    target, predictions, segments = compute_trace(device)
    values, means, stds = compute_bars(device)
    save_trace_data(target, predictions, segments)
    save_bar_data(means, stds, values)
    figure = plt.figure(figsize=(16, 11))
    grid = figure.add_gridspec(2, 2, height_ratios=(1.0, 1.05), hspace=0.42, wspace=0.28)
    trace_ax = figure.add_subplot(grid[0, :])
    ve_ax = figure.add_subplot(grid[1, 0])
    f1_ax = figure.add_subplot(grid[1, 1])
    draw_trace(trace_ax, target, predictions, segments)
    draw_bar(ve_ax, "ve", means, stds, values)
    draw_bar(f1_ax, "f1", means, stds, values)
    figure.subplots_adjust(left=0.075, right=0.985, bottom=0.10, top=0.985)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    figure.savefig(args.output, format="pdf")
    plt.close(figure)


if __name__ == "__main__":
    main()
