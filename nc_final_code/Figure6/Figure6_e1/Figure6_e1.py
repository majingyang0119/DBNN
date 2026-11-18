from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure6" / "Figure6_e1"
plt.rcParams.update({"font.family": "sans-serif", "font.sans-serif": ["Liberation Sans", "DejaVu Sans"], "pdf.fonttype": 42, "pdf.compression": 0})






def main():
    events = np.load(DATA_DIR / "cifar_events.npy", allow_pickle=False)
    boundaries = np.linspace(events["t"].min(), events["t"].max(), 4)
    frames = []
    for i in range(3):
        selected = events[(events["t"] >= boundaries[i]) & (events["t"] < boundaries[i + 1])]
        frame = np.zeros((128, 128), dtype=np.float32)
        np.add.at(frame, (selected["y"], selected["x"]), np.where(selected["on"], 1, -1))
        frames.append(np.abs(frame))

    left, right, top, bottom = 435.0, 573.0, 395.0, 592.0
    width, height = right - left, bottom - top
    fig = plt.figure(figsize=(width / 72, height / 72))
    ax = fig.add_axes([0, 0, 1, 1])
    ax.set_xlim(left, right)
    ax.set_ylim(bottom, top)
    ax.axis("off")
    ax.text(511.87, 405.98, "DVS-CIFAR10", ha="center", va="center", fontsize=14, fontweight="bold")
    ax.annotate("", xy=(510, 582.5), xytext=(444.2, 457.5), arrowprops={"arrowstyle": "->", "lw": 1.2, "mutation_scale": 8, "shrinkA": 0, "shrinkB": 0})
    ax.text(494.3, 580.85, "t", ha="center", va="center", fontsize=16, fontweight="bold")
    positions = [(457.6, 416.4727, 48.0, 48.0), (485.5273, 470.8, 47.782, 48.0), (513.4546, 526.8728, 48.0, 48.0)]
    for frame, (x, y, w, h) in zip(frames, positions):
        frame_ax = fig.add_axes([(x - left) / width, (bottom - y - h) / height, w / width, h / height])
        frame_ax.imshow(frame, cmap="gray", aspect="auto")
        frame_ax.axis("off")
    fig.savefig(SCRIPT_DIR / "Figure6_e1.pdf", dpi=300)
    plt.close(fig)


if __name__ == "__main__":
    main()
