import csv
import os
from itertools import zip_longest
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np

ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "nc_final_data" / "FigureS2" / "FigureS2_abc"
SOURCE = ROOT / "nc_final_source_data" / "FigureS2" / "FigureS2_abc"
PANELS = ['a2']
EVENTS = {"a": "Dendritic spike", "b": "Calcium spike", "c": "Plateau"}
PAIRS = {"1": "AMPA+AMPA", "2": "AMPA+NMDA", "3": "NMDA+NMDA"}


def calculate(panel):
    curves = np.load(DATA / ("FigureS2_" + panel) / "curves.npy", allow_pickle=False)
    if curves.ndim != 2 or curves.shape[1] != 4 or not np.isfinite(curves).all():
        raise ValueError("Unexpected plotted curve data")
    time, observed, linear, fit = (np.ascontiguousarray(curves[:, i]) for i in range(4))
    total = float(np.sum((observed - np.mean(observed)) ** 2))
    if total <= 0:
        raise ValueError("Degenerate response variance")
    error = observed - fit
    r2 = float(1.0 - np.sum(error * error) / total)
    result = {"time_ms": time, "ssp_mv": observed, "sum_mv": linear, "fit_mv": fit, "r2": r2}
    output = SOURCE / ("FigureS2_" + panel)
    columns = ("time_ms", "SSP_mV", "EPSP1_plus_EPSP2_mV", "fit_mV")
    write_columns(output / ("FigureS2_" + panel + ".csv"), columns, (time, observed, linear, fit))
    return result


def draw(ax, panel, result):
    time = result["time_ms"]
    ax.plot(time, result["ssp_mv"], color="black", lw=1.2, label="SSP")
    ax.plot(time, result["sum_mv"], color="blue", lw=1.2, label="EPSP1+EPSP2")
    ax.plot(time, result["fit_mv"], color="red", ls="--", lw=1.2, label=f"fit (VE={float(result['r2']):.3f})")
    ax.set_title(EVENTS[panel[0]] + ", " + PAIRS[panel[1]], fontsize=9)
    ax.set_xlabel("Time from input (ms)")
    ax.set_ylabel("Somatic response (mV)")
    ax.legend(frameon=False, fontsize=6)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)




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
    if len(PANELS) == 1:
        fig, ax = plt.subplots(figsize=(4.1, 2.6))
        draw(ax, PANELS[0], calculate(PANELS[0]))
    else:
        fig, axes = plt.subplots(3, 3, figsize=(12.4, 7.6))
        for i, panel in enumerate(PANELS):
            draw(axes.flat[i], panel, calculate(panel))
        for y, label in zip((0.965, 0.635, 0.305), ("a", "b", "c")):
            fig.text(0.005, y, label, fontsize=14, fontweight="bold")
    fig.tight_layout()
    fig.savefig(Path(__file__).with_suffix(".pdf"), bbox_inches="tight")
    plt.close(fig)


if __name__ == "__main__":
    main()
