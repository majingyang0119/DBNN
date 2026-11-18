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
DATA_DIR = ROOT / "nc_final_data" / "Figure4" / "Figure4_f"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure4" / "Figure4_f"




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
    baseline = states[0]["bilinear.weight"].numpy().astype(np.float64)
    scale = np.sqrt(np.mean(baseline * baseline))
    errors = np.concatenate([100 * (state["bilinear.weight"].numpy().astype(np.float64) - baseline).ravel() / scale for state in states[1:]])
    edges = np.load(DATA_DIR / "a_bin_edges.npy", allow_pickle=False)
    density, _ = np.histogram(errors, bins=edges, density=True)
    centers = (edges[:-1] + edges[1:]) / 2
    smooth = gaussian_filter1d(density, sigma=1.0, mode="nearest")
    curve_x = np.linspace(edges[0], edges[-1], 800)
    curve_y = np.clip(PchipInterpolator(np.r_[edges[0], centers, edges[-1]], np.r_[0, smooth, 0])(curve_x), 0.0, None)
    SOURCE_DIR.mkdir(parents=True, exist_ok=True)
    collect_source(SOURCE_DIR / "curve_x.npy", curve_x, allow_pickle=False)
    collect_source(SOURCE_DIR / "curve_y.npy", curve_y, allow_pickle=False)
    plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 18, "axes.linewidth": 1.2,
                         "xtick.major.width": 1.2, "ytick.major.width": 1.2, "xtick.major.size": 5, "ytick.major.size": 5})
    fig, ax = plt.subplots(figsize=(5.24, 3.91))
    ax.fill_between(curve_x, curve_y, 0.0, color="#3C5488", alpha=0.22)
    ax.plot(curve_x, curve_y, color="#3C5488", linewidth=2.5, label=r"$a_{ij}$")
    ax.set_xlabel("Relative error (%)")
    ax.set_ylabel("Density")
    ax.set_xlim(edges[0], edges[-1])
    ax.spines["right"].set_visible(False)
    ax.spines["top"].set_visible(False)
    ax.legend(frameon=False, fontsize=18, loc="upper right")
    fig.tight_layout()
    fig.savefig(SCRIPT_DIR / "Figure4_f.pdf", format="pdf", bbox_inches="tight")
    plt.close(fig)


def main():
    _SOURCE_COLUMNS.clear()
    draw_figure()
    write_columns(SOURCE_DIR / f"{SCRIPT_DIR.name}.csv", tuple(_SOURCE_COLUMNS), tuple(_SOURCE_COLUMNS.values()))


if __name__ == "__main__":
    main()
