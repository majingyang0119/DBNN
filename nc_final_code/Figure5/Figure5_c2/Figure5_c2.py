import csv
import os
from itertools import zip_longest
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import ListedColormap

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure5" / "Figure5_c2"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure5" / "Figure5_c2"
LABELS = ("0", "1/3", "2/3", "3/3")




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
    neuron = np.load(DATA_DIR / "neuron_output.npy", allow_pickle=False)
    dbnn = np.load(DATA_DIR / "dbnn_output.npy", allow_pickle=False)
    if neuron.shape != (4, 4) or dbnn.shape != (4, 4):
        raise ValueError("Unexpected figure data")
    columns = ("pathway_Y_gain",) + tuple(f"{model}_X_{gain}" for gain in LABELS for model in ("NEURON", "DBNN"))
    values = [LABELS] + [series[:, index] for index in range(4) for series in (neuron, dbnn)]
    write_columns(SOURCE_DIR / "Figure5_c2.csv", columns, values)
    fig, axes = plt.subplots(1, 2, figsize=(5.2, 3.6))
    fig.subplots_adjust(left=0.13, right=0.98, bottom=0.20, top=0.88, wspace=0.35)
    edges = np.arange(5) - 0.5
    for ax, values, title, color in ((axes[0], neuron, "NEURON", "black"), (axes[1], dbnn, "DBNN", "#00A6A6")):
        ax.pcolormesh(edges, edges, values, cmap=ListedColormap(["white", color]), vmin=0, vmax=1,
                      shading="flat", edgecolors="black", linewidth=0.8)
        ax.set_aspect("equal")
        ax.set_xlim(-0.5, 3.5)
        ax.set_ylim(-0.5, 3.5)
        ax.set_xticks(range(4), LABELS)
        ax.set_yticks(range(4), LABELS)
        ax.tick_params(axis="both", labelsize=13)
        ax.set_xlabel("Pathway X gain", fontsize=14)
        ax.set_ylabel("Pathway Y gain", fontsize=14)
        ax.set_title(title, fontsize=13)
        for y_index in range(4):
            for x_index in range(4):
                active = int(values[y_index, x_index])
                ax.text(x_index, y_index, str(active), ha="center", va="center", fontsize=13,
                        color="white" if active else "black")
    fig.savefig(SCRIPT_DIR / "Figure5_c2.pdf")
    plt.close(fig)


if __name__ == "__main__":
    main()
