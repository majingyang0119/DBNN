import csv
import os
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.transforms import ScaledTranslation
import numpy as np

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "FigureS7" / "FigureS7_b"
SOURCE_DIR = ROOT / "nc_final_source_data" / "FigureS7" / "FigureS7_b"

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


def write_runtime_table(path, x, shown, plotted_means, plotted_stds):
    columns, runs, means, stds = [], [], [], []
    for condition_index, condition in enumerate(x):
        for engine_index, engine in enumerate(("NEURON", "DBNN")):
            columns.append(f"{condition:g}_{engine}_plotted_s")
            runs.append(shown[condition_index, engine_index])
            means.append(plotted_means[condition_index, engine_index])
            stds.append(plotted_stds[condition_index, engine_index])
    write_table(path, columns, runs, means, stds)


def main():
    x = np.load(DATA_DIR / "synapse_counts.npy", allow_pickle=False)
    means = np.load(DATA_DIR / "runtime_mean_s.npy", allow_pickle=False)
    if x.shape != (8,) or means.shape != (8, 2) or not np.isfinite(means).all() or np.any(means <= 0):
        raise ValueError("Unexpected figure data")
    runs = np.load(DATA_DIR / "runtime_runs_s.npy", allow_pickle=False)
    if runs.shape != (8, 2, 5) or not np.isfinite(runs).all() or np.any(runs <= 0):
        raise ValueError("Unexpected individual timing data")
    if not np.allclose(runs.mean(axis=2), means, rtol=1e-12, atol=1e-12):
        raise ValueError("Individual times do not match plotted means")
    stds = runs.std(axis=2, ddof=1)
    write_runtime_table(SOURCE_DIR / "FigureS7_b.csv", x, runs, means, stds)
    plt.rcParams.update({"font.family": "Arial", "font.size": 19, "axes.labelsize": 21, "xtick.labelsize": 17, "ytick.labelsize": 17, "legend.fontsize": 18, "axes.linewidth": 1.3, "pdf.fonttype": 42, "ps.fonttype": 42})
    fig, ax = plt.subplots(figsize=(7.4, 5.7))
    ax.plot(x, means[:, 0], color="#202020", marker="o", linewidth=2.8, markersize=8.5, markeredgewidth=1.0, label="NEURON", clip_on=False)
    ax.plot(x, means[:, 1], color="#00AFC1", marker="s", linewidth=2.8, markersize=8.5, markeredgewidth=1.0, label="DBNN", clip_on=False)
    offsets = np.linspace(-9.0, 9.0, runs.shape[2])
    for engine, color in enumerate(("#202020", "#00AFC1")):
        ax.errorbar(x, means[:, engine], yerr=stds[:, engine], fmt="none", ecolor=color,
                    elinewidth=1.5, capsize=4, capthick=1.5, zorder=2)
        for repeat, offset in enumerate(offsets):
            shift = ScaledTranslation(offset / 72.0, 0.0, fig.dpi_scale_trans)
            ax.scatter(x, runs[:, engine, repeat], s=20, facecolors="white", edgecolors=color, linewidths=.9,
                       transform=ax.transData + shift, clip_on=False, zorder=5)
    ax.set_xscale("log", base=10)
    ax.set_yscale("log")
    ax.set_xlabel("Number of synapses", labelpad=8)
    ax.set_ylabel("Runtime(s)", labelpad=8)
    ax.set_xlim(10, 2000)
    ax.set_ylim(min(2.5e-4, float(np.min(means - stds)) * 0.9), max(18, float(np.max(means + stds)) * 1.1))
    ax.legend(loc="center left", frameon=False, handlelength=2.2, borderaxespad=0.3)
    fig.subplots_adjust(left=0.17, right=0.97, bottom=0.24, top=0.97)
    ax.tick_params(axis="both", which="major", width=1.3, length=6)
    ax.tick_params(axis="y", which="minor", width=0.8, length=3)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    fig.savefig(SCRIPT_DIR / "FigureS7_b.pdf", format="pdf")
    plt.close(fig)


if __name__ == "__main__":
    main()
