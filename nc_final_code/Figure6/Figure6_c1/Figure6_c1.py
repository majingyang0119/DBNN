from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure6" / "Figure6_c1"
plt.rcParams.update({"font.family": "sans-serif", "font.sans-serif": ["Liberation Sans", "DejaVu Sans"], "pdf.fonttype": 42, "pdf.compression": 0})






def main():
    events = np.load(DATA_DIR / "nmnist_events.npy", allow_pickle=False)
    boundaries = np.linspace(events["t"].min(), events["t"].max(), 4)
    frames = []
    for i in range(3):
        selected = events[(events["t"] >= boundaries[i]) & (events["t"] < boundaries[i + 1])]
        frame = np.zeros((34, 34), dtype=np.float32)
        np.add.at(frame, (selected["y"], selected["x"]), np.where(selected["p"] == 0, -1, 1))
        frames.append(np.abs(frame))

    left, right, top, bottom = 435.0, 574.0, 194.0, 377.0
    width, height = right - left, bottom - top
    fig = plt.figure(figsize=(width / 72, height / 72))
    ax = fig.add_axes([0, 0, 1, 1])
    ax.set_xlim(left, right)
    ax.set_ylim(bottom, top)
    ax.axis("off")
    ax.text(514.78, 205.47, "N-MNIST", ha="center", va="center", fontsize=14, fontweight="bold")
    ax.annotate("", xy=(510, 367), xytext=(444.2, 242), arrowprops={"arrowstyle": "->", "lw": 1.2, "mutation_scale": 8, "shrinkA": 0, "shrinkB": 0})
    ax.text(494.3, 365.3, "t", ha="center", va="center", fontsize=16, fontweight="bold")
    positions = [(461.9636, 214.6545, 51.491, 50.837), (488.8, 268.5454, 51.273, 51.055), (517.1636, 322.6545, 51.491, 51.055)]
    for frame, (x, y, w, h) in zip(frames, positions):
        frame_ax = fig.add_axes([(x - left) / width, (bottom - y - h) / height, w / width, h / height])
        frame_ax.imshow(frame, cmap="gray", origin="lower", interpolation="nearest", aspect="auto")
        frame_ax.axis("off")
    fig.savefig(SCRIPT_DIR / "Figure6_c1.pdf", dpi=300)
    plt.close(fig)


if __name__ == "__main__":
    main()
