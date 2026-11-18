import csv
import os
from itertools import zip_longest
from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
import torch


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure4" / "Figure4_b2"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure4" / "Figure4_b2"




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
    response = np.load(DATA_DIR / "IPSP2.npy", allow_pickle=False).astype(np.float64)
    response -= response[0]
    state = torch.load(DATA_DIR / "dbnn_checkpoint.pt", map_location="cpu", weights_only=True)["model_state"]
    time_ms = np.arange(response.size, dtype=np.float64) * 0.1
    lag = np.maximum(time_ms - 0.5, 0.0)
    kernel = float(state["omega"][488]) * (-np.expm1(-lag / float(state["tau_rise"][488]))) * np.exp(-lag / float(state["tau_decay"][488]))
    SOURCE_DIR.mkdir(parents=True, exist_ok=True)
    for name, value in (("time_ms.npy", time_ms), ("neuron_psp.npy", response), ("dbnn_kernel.npy", kernel)):
        collect_source(SOURCE_DIR / name, value, allow_pickle=False)
    with plt.rc_context({"font.size": 16, "axes.linewidth": 1.0, "pdf.fonttype": 42}):
        fig, ax = plt.subplots(figsize=(6.5, 4.4), constrained_layout=True)
        ax.plot(time_ms, response, color="black", linewidth=2.8, label="IPSP of neuron")
        ax.plot(time_ms, kernel, color="#00bfc4", linewidth=2.5, label="kernel of DBNN")
        ax.set_xlim(-5, time_ms[-1])
        ax.set_xlabel("t (ms)", fontsize=24)
        ax.set_ylabel("MP (mV)", fontsize=24)
        ax.tick_params(axis="both", labelsize=24)
        ax.set_yticks([-0.15, -0.10, -0.05, 0])
        if np.isclose(time_ms[-1], 200):
            ax.set_xticks([0, 50, 100, 150, 200])
        ax.spines[["top", "right"]].set_visible(False)
        ax.legend(loc="lower right", fontsize=20)
        fig.savefig(SCRIPT_DIR / "Figure4_b2.pdf", dpi=250, bbox_inches="tight", pad_inches=0.08)
        plt.close(fig)


def main():
    _SOURCE_COLUMNS.clear()
    draw_figure()
    write_columns(SOURCE_DIR / f"{SCRIPT_DIR.name}.csv", tuple(_SOURCE_COLUMNS), tuple(_SOURCE_COLUMNS.values()))


if __name__ == "__main__":
    main()
