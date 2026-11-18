import csv
import os
from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure4" / "Figure4_e"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure4" / "Figure4_e"


def write_columns(path, x, y):
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.{os.getpid()}.tmp")
    try:
        with temporary.open("w", encoding="utf-8", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(("a", "kappa"))
            writer.writerows(zip(x, y))
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


def main():
    points = np.load(DATA_DIR / "scatter_points.npy", allow_pickle=False)
    if points.ndim != 2 or points.shape[1] != 2 or not np.isfinite(points).all():
        raise ValueError("Expected finite scatter points with two coordinates")
    x, y = points[:, 0], points[:, 1]
    limits = np.asarray((-0.3534199666976929, 0.4056056809425354))
    plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 18, "axes.linewidth": 1.2,
                         "xtick.major.width": 1.2, "ytick.major.width": 1.2, "xtick.major.size": 5, "ytick.major.size": 5})
    fig, ax = plt.subplots(figsize=(5.24, 3.91))
    ax.scatter(x, y, s=14.0, color="0.45", alpha=0.3, edgecolors="0.30", linewidths=0.1, zorder=2)
    ax.plot(limits, limits, color="0.70", linewidth=0.8, zorder=1)
    ax.set_xlim(limits)
    ax.set_ylim(limits)
    ax.set_xticks([-0.3, 0.0, 0.3])
    ax.set_yticks([-0.3, 0.0, 0.3])
    ax.set_aspect("equal", adjustable="box")
    ax.set_xlabel(r"$a_{ij}$ in DBNN ($\mathrm{mV}^{-1}$)")
    ax.set_ylabel(r"$\kappa_{ij}$ in biophysical" + "\n" + r"neuron ($\mathrm{mV}^{-1}$)")
    ax.spines["right"].set_visible(False)
    ax.spines["top"].set_visible(False)
    fig.tight_layout()
    fig.savefig(SCRIPT_DIR / "Figure4_e.pdf", format="pdf", dpi=600, bbox_inches="tight")
    plt.close(fig)
    write_columns(SOURCE_DIR / f"{SCRIPT_DIR.name}.csv", x, y)


if __name__ == "__main__":
    main()
