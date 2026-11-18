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
DATA_DIR = ROOT / "nc_final_data" / "Figure5" / "Figure5_b"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure5" / "Figure5_b"




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
    x = np.load(DATA_DIR / "offset_ms.npy", allow_pickle=False)
    neuron_curves = np.stack((np.load(DATA_DIR / "neuron_different.npy", allow_pickle=False),
                              np.load(DATA_DIR / "neuron_same.npy", allow_pickle=False)))
    dbnn_curves = np.stack((np.load(DATA_DIR / "dbnn_different.npy", allow_pickle=False),
                            np.load(DATA_DIR / "dbnn_same.npy", allow_pickle=False)))
    if x.shape != (11,) or neuron_curves.shape != (2, 11) or dbnn_curves.shape != (2, 11):
        raise ValueError("Unexpected figure data")
    columns = ("offset_ms", "different_NEURON", "different_DBNN", "same_NEURON", "same_DBNN")
    values = (x, neuron_curves[0], dbnn_curves[0], neuron_curves[1], dbnn_curves[1])
    write_columns(SOURCE_DIR / "Figure5_b.csv", columns, values)
    fig, ax = plt.subplots(figsize=(4.6, 3.6))
    fig.subplots_adjust(left=0.17, right=0.97, bottom=0.18, top=0.96)
    for curves, color in ((neuron_curves, "black"), (dbnn_curves, "#00A6A6")):
        for index, linestyle in ((0, "-"), (1, "--")):
            ax.plot(x, curves[index], color=color, ls=linestyle, lw=2.0)
    ax.set_xlabel(r"Absolute timing offset $|\Delta t|$ (ms)", fontsize=14)
    ax.set_ylabel("Normalized response", fontsize=14)
    ax.tick_params(axis="both", labelsize=13)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    handles = [Line2D([0], [0], color="black", lw=2.0, ls="-", label="NEURON (dif)"),
               Line2D([0], [0], color="black", lw=2.0, ls="--", label="NEURON (same)"),
               Line2D([0], [0], color="#00A6A6", lw=2.0, ls="--", label="DBNN (same)"),
               Line2D([0], [0], color="#00A6A6", lw=2.0, ls="-", label="DBNN (dif)")]
    ax.legend(handles=handles, frameon=False, fontsize=13, loc="upper right")
    fig.savefig(SCRIPT_DIR / "Figure5_b.pdf")
    plt.close(fig)


if __name__ == "__main__":
    main()
