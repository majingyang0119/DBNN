import csv
import os
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np

ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "nc_final_data" / "FigureS1" / "FigureS1_abc"
SOURCE = ROOT / "nc_final_source_data" / "FigureS1" / "FigureS1_abc"
PANELS = [2]
LABELS = ("Dendritic spike", "Calcium spike", "Plateau")
COLORS = ("#B24A4A", "#D1844F", "#A6AD55", "#4AB27E")
EXAMPLE_VOLTAGE_LIMITS_MV = ((-67.86488494873046, -35.24535980224609), (-75.51710395812988, -38.308709335327116), (-69.33568363189697, -3.072042655944824))

def load_probabilities():
    names = ("bar_mean.npy", "bar_std.npy")
    values = tuple(np.load(DATA / name, allow_pickle=False) for name in names)
    if any(value.shape != (3, 4) or not np.isfinite(value).all() for value in values):
        raise ValueError("Invalid bar data")
    repeats = np.load(DATA / "bar_repeats.npy", allow_pickle=False)
    if repeats.shape != (3, 4, 3) or not np.array_equal(repeats.mean(axis=2), values[0]) or not np.array_equal(repeats.std(axis=2, ddof=0), values[1]):
        raise ValueError("Individual probabilities do not match bar data")
    events = ("sodium_spike", "calcium_spike", "plateau")
    conditions = ("all_ampa", "ampa_nmda_2to1", "ampa_nmda_1to1", "ampa_nmda_1to2")
    columns = [f"{condition}_{event}_probability" for condition in conditions for event in events]
    runs = repeats.transpose(1, 0, 2).reshape(len(columns), 3)
    write_table(SOURCE / "FigureS1_bars.csv", columns, runs, values[0].T.reshape(-1), values[1].T.reshape(-1))
    return (*values, repeats)


def load_example(panel):
    suffixes = ("time_ms", "voltage_mv", "sodium_inward", "calcium_inward")
    names = tuple("FigureS1_" + "abc"[panel] + "_" + suffix + ".npy" for suffix in suffixes)
    values = tuple(np.load(DATA / name, allow_pickle=False) for name in names)
    if any(value.ndim != 1 or value.size < 2 or value.shape != values[0].shape or not np.isfinite(value).all() for value in values):
        raise ValueError("Invalid example data")
    write_curves(SOURCE / ("FigureS1_" + "abc"[panel] + "_curves.csv"),
                 ("time_ms", "voltage_mv", "sodium_inward", "calcium_inward"), values)
    return values


def draw(axes, panel, mean, std, repeats, example):
    voltage_ax, current_ax, bar_ax = axes
    t, voltage, sodium, calcium = example
    for ax in (voltage_ax, current_ax):
        ax.spines["right"].set_visible(False)
        ax.spines["top"].set_visible(False)
    voltage_ax.plot(t, voltage, color="black", linewidth=2.8)
    voltage_ax.set_ylim(*EXAMPLE_VOLTAGE_LIMITS_MV[panel])
    voltage_ax.set_ylabel("Local V (mV)")
    voltage_ax.tick_params(axis="x", labelbottom=False)
    current_ax.plot(t, sodium, color="#F58518", linewidth=2.3, label=r"$-I_{Na}$")
    current_ax.plot(t, calcium, color="#54A24B", linewidth=2.3, label=r"$-I_{Ca}$")
    current_ax.set_ylabel("Inward current")
    current_ax.set_xlabel("Time (ms)")
    current_ax.legend(frameon=False, loc="upper right", fontsize=15)
    voltage_ax.set_xlim(0.0, float(t[-1]))
    tick_step = 20.0 if t[-1] <= 200.0 else 50.0
    current_ax.set_xticks(np.arange(0.0, float(t[-1]) + 1e-9, tick_step))
    x = np.arange(4)
    bar_ax.bar(x, 100 * mean[panel], yerr=100 * std[panel], color=COLORS, width=0.68,
               edgecolor="black", linewidth=1.2,
               error_kw={"elinewidth": 2.0, "ecolor": "black", "capsize": 5, "capthick": 2.0})
    offsets = np.linspace(-0.20, 0.20, repeats.shape[2])
    for index in range(len(x)):
        bar_ax.scatter(x[index] + offsets, 100 * repeats[panel, index], s=44, facecolors="white", edgecolors="black", linewidths=1.0, zorder=5)
    bar_ax.set_xticks(x, ("all AMPA", "2:1", "1:1", "1:2"))
    bar_ax.set_xlabel("AMPA:NMDA ratio")
    bar_ax.set_ylabel("Event probability (%)")
    bar_ax.set_ylim(0, 50 if panel == 1 else 20)
    bar_ax.set_yticks(np.arange(0.0, 51.0, 10.0) if panel == 1 else np.arange(0.0, 21.0, 5.0))
    for ax in axes:
        ax.spines["top"].set_visible(False)
        ax.spines["right"].set_visible(False)
        ax.yaxis.set_label_coords(-0.11, 0.5)
    bar_ax.spines["left"].set_linewidth(1.5)
    bar_ax.spines["bottom"].set_linewidth(1.5)
    bar_ax.tick_params(axis="both", width=1.3, length=5)




def write_table(path, columns, runs, means, stds):
    values = np.asarray(runs)
    if values.ndim != 2 or values.shape[0] != len(columns) or len(means) != len(columns) or len(stds) != len(columns):
        raise ValueError("Unexpected source table shape")
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.{os.getpid()}.tmp")
    try:
        with temporary.open("w", encoding="utf-8", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(["run", *columns])
            for index in range(values.shape[1]):
                writer.writerow([f"run_{index + 1}", *values[:, index]])
            writer.writerow(["mean", *means])
            writer.writerow(["std", *stds])
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


def write_curves(path, columns, values):
    if any(len(value) != len(values[0]) for value in values):
        raise ValueError("Inconsistent curve lengths")
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(f".{path.name}.{os.getpid()}.tmp")
    try:
        with temporary.open("w", encoding="utf-8", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(columns)
            writer.writerows(zip(*values))
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


def main():
    mean, std, repeats = load_probabilities()
    style = {"font.size": 17, "axes.grid": False, "axes.linewidth": 1.5, "xtick.major.width": 1.3,
             "ytick.major.width": 1.3, "pdf.fonttype": 42, "ps.fonttype": 42}
    with plt.rc_context(style):
        if len(PANELS) == 1:
            panel = PANELS[0]
            fig = plt.figure(figsize=(8.8, 8.6))
            grid = fig.add_gridspec(3, 1, height_ratios=(1.45, 1.0, 1.25))
            voltage_ax = fig.add_subplot(grid[0, 0])
            current_ax = fig.add_subplot(grid[1, 0], sharex=voltage_ax)
            bar_ax = fig.add_subplot(grid[2, 0])
            draw((voltage_ax, current_ax, bar_ax), panel, mean, std, repeats, load_example(panel))
            fig.suptitle(LABELS[panel], x=0.54, y=0.975, fontsize=20)
            fig.subplots_adjust(left=0.13, right=0.95, bottom=0.09, top=0.93, hspace=0.38)
        else:
            fig = plt.figure(figsize=(26.4, 8.6))
            grid = fig.add_gridspec(3, 3, height_ratios=(1.45, 1.0, 1.25))
            for panel in PANELS:
                voltage_ax = fig.add_subplot(grid[0, panel])
                current_ax = fig.add_subplot(grid[1, panel], sharex=voltage_ax)
                bar_ax = fig.add_subplot(grid[2, panel])
                draw((voltage_ax, current_ax, bar_ax), panel, mean, std, repeats, load_example(panel))
                for ax in (voltage_ax, current_ax, bar_ax):
                    ax.yaxis.set_label_coords(-0.18, 0.5)
                voltage_ax.set_title(LABELS[panel], fontsize=20, pad=20)
                voltage_ax.text(-0.14, 1.2, "abc"[panel], transform=voltage_ax.transAxes,
                                fontsize=20, fontweight="bold")
            fig.subplots_adjust(left=0.07, right=0.98, bottom=0.09, top=0.90, hspace=0.38, wspace=0.4)
        fig.savefig(Path(__file__).with_suffix(".pdf"), format="pdf")
        plt.close(fig)


if __name__ == "__main__":
    main()
