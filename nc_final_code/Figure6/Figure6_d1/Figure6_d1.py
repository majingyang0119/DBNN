from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure6" / "Figure6_d1"
plt.rcParams.update({"font.family": "sans-serif", "font.sans-serif": ["Liberation Sans", "DejaVu Sans"], "pdf.fonttype": 42, "pdf.compression": 0})






def main():
    events = np.load(DATA_DIR / "gesture_events.npy", allow_pickle=False)
    start = events["t"].min()
    duration = events["t"].max() - start
    boundaries = np.linspace(start + 0.25 * duration, start + 0.75 * duration, 4)
    frames = []
    for i in range(3):
        selected = events[(events["t"] >= boundaries[i]) & (events["t"] < boundaries[i + 1])]
        frame = np.zeros((128, 128), dtype=np.float32)
        np.add.at(frame, (selected["y"], selected["x"]), 1)
        frames.append(frame)

    left, right, top, bottom = 15.0, 155.0, 395.0, 592.0
    width, height = right - left, bottom - top
    fig = plt.figure(figsize=(width / 72, height / 72))
    ax = fig.add_axes([0, 0, 1, 1])
    ax.set_xlim(left, right)
    ax.set_ylim(bottom, top)
    ax.axis("off")
    ax.text(97.2, 405.98, "DVS-Gesture", ha="center", va="center", fontsize=14, fontweight="bold")
    ax.annotate("", xy=(89, 582.5), xytext=(23.2, 457.5), arrowprops={"arrowstyle": "->", "lw": 1.2, "mutation_scale": 8, "shrinkA": 0, "shrinkB": 0})
    ax.text(73.25, 580.85, "t", ha="center", va="center", fontsize=16, fontweight="bold")
    positions = [(37.3818, 416.4727, 47.782, 48.0), (65.0909, 470.8, 48.0, 48.0), (93.0182, 526.8728, 48.0, 48.0)]
    for frame, (x, y, w, h) in zip(frames, positions):
        frame_ax = fig.add_axes([(x - left) / width, (bottom - y - h) / height, w / width, h / height])
        frame_ax.imshow(frame, cmap="gray", vmax=5, aspect="auto")
        frame_ax.axis("off")
    fig.savefig(SCRIPT_DIR / "Figure6_d1.pdf", dpi=300)
    plt.close(fig)


if __name__ == "__main__":
    main()
