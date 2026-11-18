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
DATA_DIR = ROOT / "nc_final_data" / "Figure4" / "Figure4_d5"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure4" / "Figure4_d5"




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
    x = np.load(DATA_DIR / "negative_ve_vi_mV2.npy", allow_pickle=False)
    y = np.load(DATA_DIR / "negative_vsc_mV.npy", allow_pickle=False)
    if x.shape != (12,) or y.shape != x.shape or not np.isfinite(x).all() or not np.isfinite(y).all():
        raise ValueError("Expected twelve finite illustrative points")
    reference_x = np.linspace(0.0, 12.0, 100)
    reference_y = 0.25 * reference_x
    SOURCE_DIR.mkdir(parents=True, exist_ok=True)
    for name, value in (("negative_ve_vi_mV2.npy", x), ("negative_vsc_mV.npy", y),
                        ("reference_x_mV2.npy", reference_x), ("reference_y_mV.npy", reference_y)):
        collect_source(SOURCE_DIR / name, value, allow_pickle=False)
    with plt.rc_context({"font.size": 32, "pdf.fonttype": 42}):
        fig, ax = plt.subplots(figsize=(6, 6))
        ax.scatter(x, y, color="black", s=100)
        ax.plot(reference_x, reference_y, color="black", linestyle="--")
        ax.set_xlabel(r"$-V_{E}V_I(mV^2)$")
        ax.set_ylabel(r"$-V_{SC}(mV)$")
        ax.set_xticks([0, 4, 8, 12])
        ax.spines["right"].set_visible(False)
        ax.spines["top"].set_visible(False)
        fig.savefig(SCRIPT_DIR / "Figure4_d5.pdf", bbox_inches="tight")
        plt.close(fig)


def main():
    _SOURCE_COLUMNS.clear()
    draw_figure()
    write_columns(SOURCE_DIR / f"{SCRIPT_DIR.name}.csv", tuple(_SOURCE_COLUMNS), tuple(_SOURCE_COLUMNS.values()))


if __name__ == "__main__":
    main()
