import csv
import os
from itertools import zip_longest
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Patch

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure5" / "Figure5_a"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure5" / "Figure5_a"
COLORS = ("#0072B2", "#E69F00", "#CC79A7", "#009E73")




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
    velocities = np.load(DATA_DIR / "velocity_um_per_ms.npy", allow_pickle=False)
    reported = np.load(DATA_DIR / "spacing_um.npy", allow_pickle=False)
    neuron_dsi = np.load(DATA_DIR / "neuron_dsi.npy", allow_pickle=False)
    dbnn_dsi = np.load(DATA_DIR / "dbnn_dsi.npy", allow_pickle=False)
    if reported.shape != (4,) or velocities.shape != (6,) or neuron_dsi.shape != (4, 6) or dbnn_dsi.shape != (4, 6):
        raise ValueError("Unexpected figure data")
    columns = ["velocity_um_per_ms"] + [f"spacing_{spacing:g}_{model}" for spacing in reported for model in ("NEURON", "DBNN")]
    values = [velocities] + [series for index in range(len(reported)) for series in (neuron_dsi[index], dbnn_dsi[index])]
    write_columns(SOURCE_DIR / "Figure5_a.csv", columns, values)
    fig, ax = plt.subplots(figsize=(4.6, 3.6))
    fig.subplots_adjust(left=0.17, right=0.97, bottom=0.18, top=0.96)
    x = np.arange(len(velocities), dtype=float)
    cluster_width = 0.88
    spacing_width = cluster_width / len(reported)
    bar_width = spacing_width * 0.42
    for index, color in enumerate(COLORS):
        center = x - cluster_width / 2.0 + (index + 0.5) * spacing_width
        ax.bar(center - bar_width / 2.0, neuron_dsi[index], width=bar_width, color=color, edgecolor=color, linewidth=0.9, zorder=2)
        ax.bar(center + bar_width / 2.0, dbnn_dsi[index], width=bar_width, color="white", edgecolor=color, linewidth=1.2, hatch="///", zorder=3)
    ax.set_xticks(x, [f"{value:g}" for value in velocities])
    ax.set_xlim(-0.55, len(velocities) - 0.45)
    ax.set_xlabel(r"Velocity ($\mu$m/ms)", fontsize=14)
    ax.set_ylabel("Direction selectivity index", fontsize=14)
    ax.tick_params(axis="both", labelsize=13)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    model_handles = [Patch(facecolor="0.35", edgecolor="0.35", label="NEURON"),
                     Patch(facecolor="white", edgecolor="0.25", hatch="///", label="DBNN")]
    blank_handles = [Patch(facecolor="none", edgecolor="none", label=""), Patch(facecolor="none", edgecolor="none", label="")]
    spacing_handles = [Patch(facecolor=color, edgecolor=color, label=fr"{spacing:d} $\mu$m") for color, spacing in zip(COLORS, reported)]
    ax.legend(handles=model_handles + blank_handles + spacing_handles, frameon=False, loc="upper left",
              bbox_to_anchor=(0.02, 1.0), borderaxespad=0.0, fontsize=13, ncol=2,
              columnspacing=0.8, handlelength=1.8, handletextpad=0.6)
    fig.savefig(SCRIPT_DIR / "Figure5_a.pdf")
    plt.close(fig)


if __name__ == "__main__":
    main()
