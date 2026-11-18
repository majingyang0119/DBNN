import csv
import os
from pathlib import Path
import argparse

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
import torch


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
GROUP = "d"
METRIC = "ve"
DATA_DIR = ROOT / "nc_final_data" / "FigureS3" / f"FigureS3_{GROUP}"
SOURCE_DIR = ROOT / "nc_final_source_data" / "FigureS3" / f"FigureS3_{GROUP}"
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
    amplitude = torch.abs(state["reset_amp"])
    threshold = state["v_th"]
    voltage = torch.empty_like(drive)
    powers = alpha.pow(torch.arange(steps, dtype=drive.dtype, device=device))
    start = 0
    reset = torch.zeros((), dtype=drive.dtype, device=device)
    while start < steps:
        decay = powers[:steps - start]
        segment = drive[0, start:] + reset * decay
        above = torch.nonzero(segment >= threshold, as_tuple=False)
        if above.numel() == 0:
            voltage[0, start:] = segment
            break
        first = int(above[0, 0].item())
        end = start + first
        voltage[0, start:end + 1] = segment[:first + 1]
        reset = alpha * reset * decay[first] - amplitude
        start = end + 1
    return voltage.cpu().numpy()[0]


def spike_counts(truth, prediction, threshold):
    above = prediction >= threshold
    predicted = np.flatnonzero(above[1:] & ~above[:-1]) + 1
    if above[0]:
        predicted = np.r_[0, predicted]
    used = np.zeros(len(predicted), dtype=bool)
    matched = 0
    for spike in truth:
        available = np.flatnonzero((~used) & (np.abs(predicted - spike) <= 10.0))
        if len(available):
            nearest = available[np.argmin(np.abs(predicted[available] - spike))]
            used[nearest] = True
            matched += 1
    return matched, int((~used).sum()), len(truth) - matched


def evaluate(folder, state, device):
    inputs = np.load(folder / "test_ip.npy", mmap_mode="r", allow_pickle=False)
    voltage = np.load(folder / "test_op.npy", mmap_mode="r", allow_pickle=False)
    spikes = np.load(folder / "test_spike_times.npy", allow_pickle=False)
    offsets = np.load(folder / "test_spike_offsets.npy", allow_pickle=False)
    if len(inputs) != len(voltage) or len(offsets) != len(inputs) + 1:
        raise ValueError("Input, voltage and spike arrays have inconsistent sample counts")
    if offsets[0] != 0 or offsets[-1] != len(spikes) or np.any(np.diff(offsets) < 0):
        raise ValueError("Invalid spike-time offsets")
    nr = sr = ssr = nt = st = sst = 0.0
    tp = fp = fn = 0
    with torch.inference_mode():
        for index, (raster, row) in enumerate(zip(inputs, voltage)):
            truth_spikes = spikes[offsets[index]:offsets[index + 1]]
            prediction = predict(raster, state, device)
            target = np.asarray(row, dtype=np.float64)
            keep = np.ones(len(target), dtype=bool)
            for spike in truth_spikes:
                if np.isfinite(spike):
                    keep[max(0, int(np.floor(spike - 10))):min(len(keep), int(np.ceil(spike + 10)) + 1)] = False
            residual = (target - prediction)[keep]
            nr += len(residual)
            sr += residual.sum()
            ssr += residual @ residual
            nt += len(target)
            st += target.sum()
            sst += target @ target
            a, b, c = spike_counts(truth_spikes, prediction, float(state["v_th"]))
            tp += a
            fp += b
            fn += c
    if not nr or not nt:
        raise ValueError("No samples or no unmasked time points")
    residual_variance = ssr / nr - (sr / nr) ** 2
    target_variance = sst / nt - (st / nt) ** 2
    if target_variance <= 0:
        raise ValueError("True voltage variance must be positive")
    f1 = 2 * tp / (2 * tp + fp + fn) if 2 * tp + fp + fn else 0.0
    return 1 - residual_variance / target_variance, f1


def evaluate_test(device):
    values = np.empty((len(CONDITIONS), 5, 2), dtype=np.float64)
    for condition_index, condition in enumerate(CONDITIONS):
        folder = DATA_DIR / condition
        for run in range(1, 6):
            saved = torch.load(folder / f"dbnn_checkpoint_{run}.pt", map_location=device, weights_only=True)
            if set(saved) != {"model_state"}:
                raise ValueError("Checkpoint must contain only model_state")
            values[condition_index, run - 1] = evaluate(folder, saved["model_state"], device)
            print("test", condition, run, *values[condition_index, run - 1], flush=True)
    return values




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
    parser = argparse.ArgumentParser()
    parser.add_argument("--device", default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    torch.set_num_threads(4)
    torch.backends.cuda.matmul.allow_tf32 = False
    torch.backends.cudnn.allow_tf32 = False
    device = torch.device(args.device)
    values = evaluate_test(device)
    means = values.mean(axis=1)
    stds = values.std(axis=1, ddof=0)
    metric_index = 0 if METRIC == "ve" else 1
    columns = [f"{condition}_{metric}" for condition in CONDITIONS for metric in ("VE", "F1")]
    runs = values.transpose(0, 2, 1).reshape(len(columns), 5)
    write_table(SOURCE_DIR / f"FigureS3_{GROUP}.csv", columns, runs, means.reshape(-1), stds.reshape(-1))
    with plt.rc_context({"font.size": 32, "pdf.fonttype": 42, "ps.fonttype": 42}):
        fig, ax = plt.subplots(figsize=(8.0, 8.0))
        ax.bar(np.arange(len(CONDITIONS)), means[:, metric_index], yerr=stds[:, metric_index],
               color=COLORS, edgecolor="black", linewidth=1.5, width=0.72,
               error_kw={"elinewidth": 4, "ecolor": "black", "capsize": 10, "capthick": 4})
        offsets = np.linspace(-0.22, 0.22, values.shape[1])
        for index in range(len(CONDITIONS)):
            ax.scatter(index + offsets, values[index, :, metric_index], s=120, facecolors="white", edgecolors="black", linewidths=1.5, zorder=5)
        ax.set_ylim(0.0, 1.05)
        ax.set_ylabel("VE" if METRIC == "ve" else "F1 score")
        ax.set_xticks(np.arange(len(CONDITIONS)))
        ax.set_xticklabels(LABELS)
        ax.tick_params(axis="x", labelsize=23, pad=8)
        plt.setp(ax.get_xticklabels(), rotation=25, ha="right", rotation_mode="anchor")
        ax.tick_params(axis="y", width=1.5, length=6)
        ax.spines["right"].set_visible(False)
        ax.spines["top"].set_visible(False)
        ax.spines["left"].set_linewidth(1.5)
        ax.spines["bottom"].set_linewidth(1.5)
        fig.subplots_adjust(left=0.17, right=0.98, bottom=0.23, top=0.98)
        fig.savefig(SCRIPT_DIR / f"FigureS3_{GROUP}{1 if METRIC == 've' else 2}.pdf",
                    format="pdf", bbox_inches="tight")
        plt.close(fig)


if __name__ == "__main__":
    main()
