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
DATA_DIR = ROOT / "nc_final_data" / "Figure4" / "Figure4_d4"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure4" / "Figure4_d4"




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
    names = ("epsp_voltage", "ipsp_voltage", "ssp_voltage")
    voltages = [np.load(DATA_DIR / (name + ".npy"), allow_pickle=False) for name in names]
    if any(v.shape != (2001,) or not np.isfinite(v).all() for v in voltages):
        raise ValueError("Expected three finite 2001-sample voltage traces")
    if not np.allclose([v[0] for v in voltages], voltages[0][0], rtol=0, atol=1e-12):
        raise ValueError("The three traces must share the same baseline")
    time_ms = np.arange(2001, dtype=np.float64) * 0.1
    epsp, ipsp, ssp = (v - v[0] for v in voltages)
    sc = ssp - (epsp + ipsp)
    SOURCE_DIR.mkdir(parents=True, exist_ok=True)
    collect_source(SOURCE_DIR / "time_ms.npy", time_ms, allow_pickle=False)
    collect_source(SOURCE_DIR / "sc_mV.npy", sc, allow_pickle=False)
    with plt.rc_context({"pdf.fonttype": 42}):
        fig, ax = plt.subplots(figsize=(10, 5))
        ax.plot(time_ms, sc, color="orange", linewidth=10)
        ax.set_ylim(-0.5, 0.4)
        ax.axis("off")
        fig.savefig(SCRIPT_DIR / "Figure4_d4.pdf", bbox_inches="tight")
        plt.close(fig)


def main():
    _SOURCE_COLUMNS.clear()
    draw_figure()
    write_columns(SOURCE_DIR / f"{SCRIPT_DIR.name}.csv", tuple(_SOURCE_COLUMNS), tuple(_SOURCE_COLUMNS.values()))


if __name__ == "__main__":
    main()
