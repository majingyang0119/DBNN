import csv
import os
from itertools import zip_longest
from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
PANEL = SCRIPT_DIR.name
DATA_DIR = ROOT / "nc_final_data" / "Figure2" / PANEL
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure2" / PANEL




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
    neuron = np.load(DATA_DIR / "neuron_displayed_voltage.npy", allow_pickle=False)
    dbnn = np.load(DATA_DIR / "dbnn_displayed_voltage.npy", allow_pickle=False)
    if neuron.shape != (6001,) or dbnn.shape != neuron.shape:
        raise ValueError("Unexpected voltage shape")
    if not np.isfinite(neuron).all() or not np.isfinite(dbnn).all():
        raise ValueError("Voltage data must be finite")
    threshold = -43.0
    above_threshold = dbnn >= threshold
    spike_indices = np.flatnonzero(above_threshold[1:] & ~above_threshold[:-1]) + 1
    if above_threshold[0]:
        spike_indices = np.concatenate(([0], spike_indices))
    spike_times = spike_indices.astype(float)
    height = float(np.max(neuron))
    time = np.arange(neuron.size, dtype=float)
    limits = (-79.49019065766525, 87.29700672860345)
    write_columns(SOURCE_DIR / f"{PANEL}.csv", ("time_ms", "NEURON", "DBNN"), (time, neuron, dbnn))
    fig, ax = plt.subplots(figsize=(14.0, 8.0))
    ax.plot(time, neuron, color="black", linewidth=3.0)
    ax.plot(time, dbnn, color="c", linewidth=4.0)
    for spike in spike_times:
        index = int(np.clip(np.rint(spike), 0, len(time) - 1))
        ax.vlines(spike, ymin=float(dbnn[index]), ymax=height,
                  color="c", linestyle="--", linewidth=4.0)
    ax.axhline(threshold, color="red", linestyle="--", linewidth=1.0)
    ax.set_xlim(0.0, 6000.0)
    ax.set_ylim(*limits)
    ax.axis("off")
    fig.subplots_adjust(left=0.01, right=0.99, bottom=0.02, top=0.98)
    fig.savefig(SCRIPT_DIR / f"{PANEL}.pdf", format="pdf", bbox_inches="tight", pad_inches=0.02)
    plt.close(fig)


if __name__ == "__main__":
    main()
