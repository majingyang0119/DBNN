from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure1" / "Figure1_b"
OUTPUT = SCRIPT_DIR / "Figure1_b2.pdf"
EXCITATORY_CHANNELS = 250
TOTAL_CHANNELS = 500
SAMPLE_INTERVAL_MS = 1.0


def build_plot_data():
    raster = np.load(DATA_DIR / "display_raster.npy", allow_pickle=False)
    voltage = np.load(DATA_DIR / "voltage.npy", allow_pickle=False).astype(float)
    spike_times = np.load(DATA_DIR / "spike_times.npy", allow_pickle=False)
    if raster.shape[0] != TOTAL_CHANNELS:
        raise ValueError(f"Expected {TOTAL_CHANNELS} synapse channels.")
    channel_type = np.where(
        np.arange(TOTAL_CHANNELS) < EXCITATORY_CHANNELS, "exc", "inh"
    )
    interval_ms = SAMPLE_INTERVAL_MS

    displayed_events = {}
    for kind in ("inh", "exc"):
        local_channel, time_index = np.nonzero(raster[channel_type == kind])
        channel_index = np.flatnonzero(channel_type == kind)[local_channel]
        dtype = np.uint16 if max(raster.shape) <= np.iinfo(np.uint16).max else np.uint32
        displayed_events[kind] = np.column_stack((time_index, channel_index)).astype(dtype)

    spike_indices = np.rint(spike_times / interval_ms).astype(int)
    spike_indices = spike_indices[(spike_indices >= 0) & (spike_indices < len(voltage))]
    voltage[spike_indices] = 0.0
    return displayed_events["exc"], displayed_events["inh"], voltage, interval_ms, channel_type


def main():
    excitatory, inhibitory, voltage, interval_ms, channel_type = build_plot_data()

    time_seconds = np.arange(len(voltage), dtype=float) * interval_ms / 1000.0
    fig, (raster_ax, voltage_ax) = plt.subplots(
        2,
        1,
        figsize=(8.5, 6.0),
        sharex=True,
        gridspec_kw={"height_ratios": (2.1, 1.5), "hspace": 0.32},
    )

    for events, color, zorder in (
        (inhibitory, "#000000", 2),
        (excitatory, "#e41a1c", 3),
    ):
        event_times = events[:, 0].astype(float) * interval_ms / 1000.0
        raster_ax.scatter(
            event_times,
            events[:, 1],
            s=6.0,
            c=color,
            marker=".",
            alpha=1.0,
            linewidths=0,
            zorder=zorder,
        )

    raster_ax.axhline(
        y=int(np.sum(channel_type == "exc")),
        color="0.85",
        linestyle="--",
        linewidth=0.8,
        zorder=1,
    )
    raster_ax.set_ylim(len(channel_type) + 5, -5)
    raster_ax.axis("off")

    voltage_ax.plot(time_seconds, voltage, color="#000000", linewidth=2.4)
    voltage_ax.set_xlim(time_seconds[0], time_seconds[-1])
    voltage_ax.axis("off")

    fig.subplots_adjust(left=0.12, right=0.99, bottom=0.12, top=0.99)
    fig.savefig(OUTPUT, format="pdf", bbox_inches="tight", pad_inches=0.02)
    plt.close(fig)


if __name__ == "__main__":
    main()
