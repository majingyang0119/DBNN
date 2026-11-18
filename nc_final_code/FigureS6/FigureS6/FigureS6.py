import csv
import os
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

ROOT = Path(__file__).resolve().parents[3]
SCRIPT_DIR = Path(__file__).resolve().parent
DATA_DIR = ROOT / "nc_final_data/FigureS6/FigureS6"
SOURCE_DIR = ROOT / "nc_final_source_data/FigureS6/FigureS6"
DATASETS = ("gait_recognition", "nmnist", "dvs_gesture", "dvs_cifar10")
NAMES = ("dbnn", "tcn", "mlp", "lstm", "snn")
LABELS = ("DBNN", "TCN", "MLP", "LSTM", "SNN")
COLORS = ("#B24A4A", "#5679BA", "#4AB27E", "#D1844F", "#A6AD55")
DATASET_LABELS = ("Gait recognition", "N-MNIST", "DVS-Gesture", "DVS-CIFAR10")


def create_figure(labels_by_dataset, coordinates, means, stds, runs, output):
    plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 16, "axes.titlesize": 19, "axes.labelsize": 16, "xtick.labelsize": 14, "ytick.labelsize": 14, "axes.linewidth": 1.2, "pdf.fonttype": 42, "ps.fonttype": 42})
    fig = plt.figure(figsize=(21.2, 14.8))
    grid = fig.add_gridspec(4, 7, width_ratios=(1.0, 1.0, 1.0, 1.0, 1.0, 0.14, 1.28), wspace=0.12, hspace=0.18)
    class_colors = plt.get_cmap("tab20")(np.linspace(0.0, 0.95, 20))
    for row, dataset in enumerate(DATASETS):
        labels = labels_by_dataset[dataset]
        for column, name in enumerate(NAMES):
            ax = fig.add_subplot(grid[row, column])
            xy = coordinates[(dataset, name)]
            for class_id in np.unique(labels):
                selected = labels == class_id
                ax.scatter(xy[selected, 0], xy[selected, 1], s=10 if dataset == "dvs_gesture" else 5, color=class_colors[int(class_id) % len(class_colors)], alpha=0.72, linewidths=0, rasterized=True)
            ax.set_aspect("equal", adjustable="datalim")
            ax.axis("off")
            if row == 0:
                ax.set_title(LABELS[column], pad=4)
        ax = fig.add_subplot(grid[row, 6])
        ax.bar(np.arange(5, dtype=float), means[row], yerr=stds[row], width=0.68, color=COLORS, edgecolor="black", linewidth=1.0, error_kw={"elinewidth": 1.4, "ecolor": "black", "capsize": 4, "capthick": 1.4}, zorder=2)
        offsets = np.linspace(-0.26, 0.26, runs.shape[2])
        for model in range(len(NAMES)):
            ax.scatter(model + offsets, 100.0 * runs[row, model], s=9, facecolors="white", edgecolors="black", linewidths=.5, zorder=5)
        low, high = float(np.min(means[row] - stds[row])), float(np.max(means[row] + stds[row]))
        span = max(1.0, high - low)
        lower, upper = max(0.0, low - 0.18 * span), high + 0.18 * span
        lower = min(lower, max(0.0, float(np.min(runs[row]) * 100.0) - 0.04 * span))
        upper = max(upper, float(np.max(runs[row]) * 100.0) + 0.04 * span)
        ax.set_ylim(lower, upper)
        ax.set_xticks(np.arange(5, dtype=float), LABELS)
        ax.tick_params(axis="x", labelrotation=25)
        ax.set_ylabel("5-NN accuracy (%)")
        ax.spines["top"].set_visible(False)
        ax.spines["right"].set_visible(False)
        ax.tick_params(width=1.2, length=5)
        if row == 0:
            ax.set_title("Class neighborhood", pad=4)
        position = ax.get_position()
        fig.text(0.022, (position.y0 + position.y1) / 2.0, DATASET_LABELS[row], rotation=90, ha="center", va="center", fontsize=19, fontweight="bold")
    fig.subplots_adjust(left=0.065, right=0.992, bottom=0.04, top=0.965)
    fig.savefig(output, format="pdf", dpi=300)
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


def write_curves(path, columns, values):
    if any(len(value) != len(values[0]) for value in values):
        raise ValueError("Inconsistent curve lengths")
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.{os.getpid()}.tmp")
    try:
        with temporary.open("w", encoding="utf-8", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(columns)
            writer.writerows(zip(*values))
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


def main():
    labels_by_dataset = {}
    coordinates = {}
    for dataset in DATASETS:
        label_name = f"{dataset}_labels.npy"
        labels = np.load(DATA_DIR / label_name, allow_pickle=False)
        if labels.ndim != 1:
            raise ValueError("Unexpected label shape")
        labels_by_dataset[dataset] = labels
        for name in NAMES:
            filename = f"{dataset}_{name}_embedding.npy"
            xy = np.load(DATA_DIR / filename, allow_pickle=False)
            if xy.shape != (len(labels), 2) or not np.isfinite(xy).all():
                raise ValueError("Unexpected embedding data")
            coordinates[(dataset, name)] = xy
    means = np.load(DATA_DIR / "knn_mean.npy", allow_pickle=False)
    stds = np.load(DATA_DIR / "knn_std.npy", allow_pickle=False)
    if means.shape != (len(DATASETS), len(NAMES)) or stds.shape != means.shape or not np.isfinite(means).all() or not np.isfinite(stds).all():
        raise ValueError("Unexpected summary data")
    runs = np.load(DATA_DIR / "knn_runs.npy", allow_pickle=False)
    if runs.shape != (len(DATASETS), len(NAMES), 9) or not np.isfinite(runs).all():
        raise ValueError("Unexpected individual accuracy data")
    if not np.allclose(runs.mean(axis=2) * 100.0, means, rtol=0, atol=1e-10) or not np.allclose(runs.std(axis=2, ddof=1) * 100.0, stds, rtol=0, atol=1e-10):
        raise ValueError("Individual accuracies do not match bar data")
    for dataset in DATASETS:
        columns = ["label"] + [f"{name}_{axis}" for name in NAMES for axis in ("x", "y")]
        arrays = [labels_by_dataset[dataset]] + [coordinates[(dataset, name)][:, axis] for name in NAMES for axis in (0, 1)]
        write_curves(SOURCE_DIR / f"FigureS6_{dataset}_scatter.csv", columns, arrays)
    columns = [f"{dataset}_{name}_5NN_percent" for dataset in DATASETS for name in NAMES]
    write_table(SOURCE_DIR / "FigureS6_5NN.csv", columns, (runs * 100.0).reshape(len(columns), 9), means.reshape(-1), stds.reshape(-1))
    create_figure(labels_by_dataset, coordinates, means, stds, runs, SCRIPT_DIR / "FigureS6.pdf")


if __name__ == "__main__":
    main()
