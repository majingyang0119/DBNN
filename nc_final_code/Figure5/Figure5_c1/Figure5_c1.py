import csv
import os
from itertools import zip_longest
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.lines import Line2D

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure5" / "Figure5_c1"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure5" / "Figure5_c1"
LABELS = ("00", "X", "Y", "XY", "XY+inhib")
TEXT = {
    "00": "Background",
    "X": "Background + X",
    "Y": "Background + Y",
    "XY": "Background + X + Y",
    "XY+inhib": "Background + X + Y\n+ inhibition",
}
COLORS = {"00": "#5F5F5F", "X": "#FF2138", "Y": "#1615FF", "XY": "#8F3FB0", "XY+inhib": "#009E73"}
STYLES = (
    {"label": "Background ", "color": "#A7A7A7", "marker": "o", "size": 20, "zorder": 3},
    {"label": "Pathway X ", "color": "#FF2138", "marker": "o", "size": 39, "zorder": 5},
    {"label": "Pathway Y", "color": "#1615FF", "marker": "o", "size": 39, "zorder": 5},
    {"label": "Inhibition", "color": "#111111", "marker": "^", "size": 46, "zorder": 6},
)
PEAK_THRESHOLD_MV = -20.0




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
    segments = np.load(DATA_DIR / "segments.npy", allow_pickle=False)
    offsets = np.load(DATA_DIR / "section_segment_offsets.npy", allow_pickle=False)
    section_widths = np.load(DATA_DIR / "section_widths.npy", allow_pickle=False)
    synapse_xy = np.load(DATA_DIR / "synapse_xy.npy", allow_pickle=False)
    soma_xy = np.load(DATA_DIR / "soma_xy.npy", allow_pickle=False)
    display = np.load(DATA_DIR / "dbnn_displayed_voltage.npy", allow_pickle=False)
    if segments.shape != (6787, 2, 2) or offsets.shape != (184,) or section_widths.shape != (183,):
        raise ValueError("Unexpected displayed morphology format")
    if offsets[0] != 0 or offsets[-1] != len(segments) or np.any(np.diff(offsets) < 1):
        raise ValueError("Unexpected displayed morphology offsets")
    if display.shape != (5, 3801) or synapse_xy.shape != (170, 2) or soma_xy.shape != (2,):
        raise ValueError("Unexpected displayed figure data")
    widths = np.repeat(section_widths, np.diff(offsets))
    time_s = np.arange(200, 4001, dtype=np.float64) / 1000.0
    columns = ("time_s", "DBNN_background", "DBNN_background_X", "DBNN_background_Y", "DBNN_background_X_Y", "DBNN_background_X_Y_inhibition")
    write_columns(SOURCE_DIR / "Figure5_c1.csv", columns, (time_s, *display))
    plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 13, "pdf.fonttype": 42,
                         "ps.fonttype": 42, "axes.linewidth": 0.9})
    fig = plt.figure(figsize=(16.0, 6.4))
    outer = fig.add_gridspec(1, 4, width_ratios=(0.60, 0.50, 1.2325, 0.045), left=0.015,
                             right=0.985, bottom=0.10, top=0.96, wspace=0.01)
    morphology_ax = fig.add_subplot(outer[0, 0])
    label_grid = outer[0, 1].subgridspec(5, 1, hspace=0.13)
    trace_grid = outer[0, 2].subgridspec(5, 1, hspace=0.13)
    label_axes = [fig.add_subplot(label_grid[index, 0]) for index in range(5)]
    trace_axes = [fig.add_subplot(trace_grid[index, 0]) for index in range(5)]
    for index, (start, stop) in enumerate(zip(offsets[:-1], offsets[1:])):
        xy = np.vstack((segments[start, 0], segments[start:stop, 1]))
        morphology_ax.plot(xy[:, 0], xy[:, 1], color="#111111" if index == 0 else "#5A5A5A", linewidth=section_widths[index], zorder=1)
        if index == 0:
            morphology_ax.scatter([soma_xy[0]], [soma_xy[1]], s=24, color="#111111", linewidths=0, zorder=2)
    for group, (selected, style) in enumerate(zip(np.split(synapse_xy, (100, 125, 150)), STYLES)):
        morphology_ax.scatter(selected[:, 0], selected[:, 1], s=style["size"], marker=style["marker"],
                              color=style["color"], edgecolors="none" if group == 0 else "white",
                              linewidths=0.35, alpha=0.72 if group == 0 else 0.95, zorder=style["zorder"])
    handles = [Line2D([0], [0], linestyle="none", marker=style["marker"], markersize=5.5,
                      markerfacecolor=style["color"], markeredgecolor="none", label=style["label"]) for style in STYLES]
    morphology_ax.legend(handles=handles, frameon=False, fontsize=13.5, loc="upper left",
                         bbox_to_anchor=(0.85, 1.0), ncol=1, columnspacing=0.0, handletextpad=0.35)
    xy = segments.reshape(-1, 2)
    morphology_ax.set_xlim(float(np.min(xy[:, 0])), float(np.max(xy[:, 0])))
    morphology_ax.set_ylim(float(np.min(xy[:, 1])), float(np.max(xy[:, 1])))
    morphology_ax.margins(0)
    morphology_ax.set_aspect("equal", adjustable="box")
    morphology_ax.set_anchor("W")
    morphology_ax.axis("off")
    for index, label in enumerate(LABELS):
        label_axes[index].axis("off")
        label_axes[index].text(0.03, 0.5, TEXT[label], transform=label_axes[index].transAxes,
                               ha="left", va="center", fontsize=19, fontweight="bold", color=COLORS[label], wrap=True)
        trace_axes[index].plot(time_s, display[index], color=COLORS[label], linewidth=1.7)
        trace_axes[index].axhline(PEAK_THRESHOLD_MV, color="#D62728", linestyle="--", linewidth=0.9, dashes=(4, 3), zorder=0)
        trace_axes[index].set_xlim(0.2, 4.0)
        trace_axes[index].set_ylim(-75.0, 60.0)
        trace_axes[index].axis("off")
    fig.savefig(SCRIPT_DIR / "Figure5_c1.pdf")
    plt.close(fig)


if __name__ == "__main__":
    main()
