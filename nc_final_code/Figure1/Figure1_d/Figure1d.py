import csv
import os
from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
import torch


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure1" / "Figure1_d"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure1" / "Figure1_d"
CONDITIONS = ("all_ampa", "ampa_nmda_2to1", "ampa_nmda_1to1", "ampa_nmda_1to2")
LABELS = ("all AMPA", "AMPA:NMDA 2:1", "AMPA:NMDA 1:1", "AMPA:NMDA 1:2")
COLORS = ("#B24A4A", "#D1844F", "#A6AD55", "#4AB27E")


def predict(raster, state, device):
    x = torch.as_tensor(np.array(raster[None]), dtype=torch.float32, device=device)
    steps = x.shape[-1]
    lag = (torch.arange(steps, dtype=torch.float32, device=device) - 0.5).clamp_min(0)
    kernels = state["omega"][:, None] * (1 - torch.exp(-lag / state["tau_rise"][:, None])) * torch.exp(-lag / state["tau_decay"][:, None])
    size = 1 << (2 * steps - 2).bit_length()
    filtered = torch.fft.irfft(torch.fft.rfft(x, n=size) * torch.fft.rfft(kernels, n=size)[None], n=size)[..., :steps].transpose(1, 2)
    weight = state["bilinear.weight"][0].clone()
    weight.fill_diagonal_(0)
    drive = torch.einsum("...i,ij,...j->...", filtered, weight, filtered) + state["bilinear.bias"] + filtered.sum(-1)
    tau = torch.clamp(torch.abs(state["tau_reset"]), min=1e-4)
    alpha = torch.exp(-torch.ones((), dtype=drive.dtype, device=device) / tau)
    amp = torch.abs(state["reset_amp"])
    threshold = state["v_th"]
    result = torch.empty_like(drive)
    alpha_powers = alpha.pow(torch.arange(steps, dtype=drive.dtype, device=device))
    start = 0
    reset = torch.zeros((), dtype=drive.dtype, device=device)
    while start < steps:
        decay = alpha_powers[:steps - start]
        segment = drive[0, start:] + reset * decay
        above = torch.nonzero(segment >= threshold, as_tuple=False)
        if above.numel() == 0:
            result[0, start:] = segment
            break
        first = int(above[0, 0].item())
        end = start + first
        result[0, start:end + 1] = segment[:first + 1]
        at_spike = reset * decay[first]
        reset = alpha * at_spike - amp
        start = end + 1
    return result.cpu().numpy()[0]


def spike_counts(truth, prediction, threshold):
    above = prediction >= threshold
    predicted = np.flatnonzero(above[1:] & ~above[:-1]) + 1
    if above[0]:
        predicted = np.r_[0, predicted]
    used = np.zeros(len(predicted), dtype=bool)
    matched = 0
    for spike in np.asarray(truth, dtype=float):
        available = np.flatnonzero((~used) & (np.abs(predicted - spike) <= 10.0))
        if len(available):
            nearest = available[np.argmin(np.abs(predicted[available] - spike))]
            used[nearest] = True
            matched += 1
    return matched, int((~used).sum()), len(truth) - matched


def evaluate(folder, state, device):
    inputs = np.load(folder / "test_ip.npy", mmap_mode="r", allow_pickle=False)
    voltage = np.load(folder / "test_op.npy", mmap_mode="r", allow_pickle=False)
    spikes = np.load(folder / "test_spike_time.npy", allow_pickle=True)
    if len(inputs) != len(voltage) or len(inputs) != len(spikes):
        raise ValueError("Input, voltage and spike arrays have inconsistent sample counts")
    nr = sr = ssr = nt = st = sst = 0.0
    tp = fp = fn = 0
    with torch.inference_mode():
        for raster, row, true_spikes in zip(inputs, voltage, spikes):
            prediction = predict(raster, state, device)
            target = np.asarray(row, dtype=np.float64)
            mask = np.ones(len(target), dtype=bool)
            for spike in true_spikes:
                if np.isfinite(spike):
                    mask[max(0, int(np.floor(spike - 10))):min(len(mask), int(np.ceil(spike + 10)) + 1)] = False
            residual = (target - prediction)[mask]
            nr += len(residual)
            sr += residual.sum()
            ssr += residual @ residual
            nt += len(target)
            st += target.sum()
            sst += target @ target
            a, b, c = spike_counts(true_spikes, prediction, float(state["v_th"]))
            tp += a
            fp += b
            fn += c
    residual_variance = ssr / nr - (sr / nr) ** 2
    target_variance = sst / nt - (st / nt) ** 2
    f1 = 2 * tp / (2 * tp + fp + fn) if 2 * tp + fp + fn else 0.0
    return 1 - residual_variance / target_variance, f1


def draw_metric(ax, means, stds, ylabel, repeats):
    x = np.arange(len(CONDITIONS), dtype=float)
    ax.bar(x, means, yerr=stds, color=COLORS, edgecolor="black", linewidth=1.5, width=0.72,
           error_kw={"elinewidth": 4, "ecolor": "black", "capsize": 10, "capthick": 4})
    offsets = np.linspace(-0.22, 0.22, repeats.shape[1])
    for index in range(len(CONDITIONS)):
        ax.scatter(x[index] + offsets, repeats[index], s=120, facecolors="white", edgecolors="black", linewidths=1.5, zorder=5)
    ax.set_ylim(0.0, 1.05)
    ax.set_ylabel(ylabel)
    ax.set_xticks(x)
    ax.set_xticklabels(LABELS)
    ax.tick_params(axis="x", labelsize=23, pad=8)
    plt.setp(ax.get_xticklabels(), rotation=25, ha="right", rotation_mode="anchor")
    ax.tick_params(axis="y", width=1.5, length=6)
    ax.spines["right"].set_visible(False)
    ax.spines["top"].set_visible(False)
    ax.spines["left"].set_linewidth(1.5)
    ax.spines["bottom"].set_linewidth(1.5)




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
    values = np.empty((4, 5, 2), dtype=np.float64)
    for condition_index, condition in enumerate(CONDITIONS):
        folder = DATA_DIR / condition
        for run in range(1, 6):
            saved = torch.load(folder / f"dbnn_checkpoint_{run}.pt", map_location=device, weights_only=True)
            values[condition_index, run - 1] = evaluate(folder, saved["model_state"], device)
            print(condition, run, *values[condition_index, run - 1], flush=True)
    mean = values.mean(axis=1)
    std = values.std(axis=1, ddof=0)
    columns = [f"{condition}_{metric}" for condition in CONDITIONS for metric in ("VE", "F1")]
    runs = values.transpose(0, 2, 1).reshape(len(columns), 5)
    write_table(SOURCE_DIR / "Figure1_d.csv", columns, runs, mean.reshape(-1), std.reshape(-1))
    with plt.rc_context({"font.size": 32}):
        fig, axes = plt.subplots(1, 2, figsize=(16.0, 8.0))
        draw_metric(axes[0], mean[:, 0], std[:, 0], "VE", values[:, :, 0])
        draw_metric(axes[1], mean[:, 1], std[:, 1], "F1 score", values[:, :, 1])
        fig.subplots_adjust(left=0.055, right=0.99, bottom=0.23, top=0.98, wspace=0.22)
        fig.savefig(SCRIPT_DIR / "Figure1_d.pdf", format="pdf", bbox_inches="tight")
        plt.close(fig)


if __name__ == "__main__":
    main()
