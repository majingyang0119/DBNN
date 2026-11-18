import csv
import os
from itertools import zip_longest
from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
import torch
from scipy.interpolate import PchipInterpolator
from scipy.ndimage import gaussian_filter1d


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure4" / "Figure4_c"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure4" / "Figure4_c"
PARAMETERS = (("tau_rise", r"$\tau_{\mathrm{rise}}$", "#B24A4A"),
              ("tau_decay", r"$\tau_{\mathrm{decay}}$", "#5679BA"),
              ("omega", r"$\omega$", "#4AB27E"))




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


_SOURCE_COLUMNS = {}


_SOURCE_COLUMNS = {}


def collect_source(path, value, allow_pickle=False):
    name = Path(path).stem
    name = {"neuron_psp": "NEURON", "dbnn_kernel": "DBNN"}.get(name, name)
    _SOURCE_COLUMNS[name] = np.asarray(value)


def draw_figure():
    states = [torch.load(DATA_DIR / f"dbnn_checkpoint_{i}.pt", map_location="cpu", weights_only=True)["model_state"] for i in range(1, 6)]
    SOURCE_DIR.mkdir(parents=True, exist_ok=True)
    plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 18, "axes.linewidth": 1.2,
                         "xtick.major.width": 1.2, "ytick.major.width": 1.2, "xtick.major.size": 5, "ytick.major.size": 5})
    fig, ax = plt.subplots(figsize=(5.24, 3.91))
    limits = []
    for name, label, color in PARAMETERS:
        baseline = states[0][name].numpy().astype(np.float64)
        errors = np.concatenate([100 * (state[name].numpy().astype(np.float64) - baseline)
                                 / np.maximum(np.abs(baseline), np.finfo(float).eps) for state in states[1:]])
        edges = np.load(DATA_DIR / f"{name}_bin_edges.npy", allow_pickle=False)
        density, _ = np.histogram(errors, bins=edges, density=True)
        centers = (edges[:-1] + edges[1:]) / 2
        smooth = gaussian_filter1d(density, sigma=1.0, mode="nearest")
        curve_x = np.linspace(edges[0], edges[-1], 800)
        curve_y = np.clip(PchipInterpolator(np.r_[edges[0], centers, edges[-1]], np.r_[0, smooth, 0])(curve_x), 0.0, None)
        collect_source(SOURCE_DIR / f"{name}_x.npy", curve_x, allow_pickle=False)
        collect_source(SOURCE_DIR / f"{name}_y.npy", curve_y, allow_pickle=False)
        limits.extend((edges[0], edges[-1]))
        ax.fill_between(curve_x, curve_y, 0.0, color=color, alpha=0.10)
        ax.plot(curve_x, curve_y, color=color, linewidth=2.5, label=label)
    ax.set_xlabel("Relative error (%)")
    ax.set_ylabel("Density")
    ax.set_xlim(min(limits), max(limits))
    ax.set_ylim(bottom=0.0)
    ax.spines["right"].set_visible(False)
    ax.spines["top"].set_visible(False)
    ax.legend(frameon=False, fontsize=18, loc="upper right")
    fig.tight_layout()
    fig.savefig(SCRIPT_DIR / "Figure4_c.pdf", format="pdf", bbox_inches="tight")
    plt.close(fig)


def main():
    _SOURCE_COLUMNS.clear()
    draw_figure()
    write_columns(SOURCE_DIR / f"{SCRIPT_DIR.name}.csv", tuple(_SOURCE_COLUMNS), tuple(_SOURCE_COLUMNS.values()))


if __name__ == "__main__":
    main()
