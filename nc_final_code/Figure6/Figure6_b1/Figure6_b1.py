from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure6" / "Figure6_b1"
plt.rcParams.update({"font.family": "sans-serif", "font.sans-serif": ["Liberation Sans", "DejaVu Sans"], "pdf.fonttype": 42, "pdf.compression": 0})






def main():
    frames = np.load(DATA_DIR / "gait_frames.npy", allow_pickle=False)
    left, right, top, bottom = 15.0, 156.0, 194.0, 377.0
    width, height = right - left, bottom - top
    fig = plt.figure(figsize=(width / 72, height / 72))
    ax = fig.add_axes([0, 0, 1, 1])
    ax.set_xlim(left, right)
    ax.set_ylim(bottom, top)
    ax.axis("off")
    ax.text(96.72, 205.47, "Gait recognition", ha="center", va="center", fontsize=14, fontweight="bold")
    ax.annotate("", xy=(89, 367), xytext=(23.2, 242), arrowprops={"arrowstyle": "->", "lw": 1.2, "mutation_scale": 8, "shrinkA": 0, "shrinkB": 0})
    ax.text(73.25, 365.3, "t", ha="center", va="center", fontsize=16, fontweight="bold")
    positions = [(40.6546, 214.4363, 46.036, 51.055), (69.0182, 268.3272, 49.091, 51.055), (103.0546, 322.0, 49.091, 51.055)]
    for frame, (x, y, w, h) in zip(frames, positions):
        frame_ax = fig.add_axes([(x - left) / width, (bottom - y - h) / height, w / width, h / height])
        frame_ax.imshow(frame, cmap="gray", vmin=0, vmax=255, aspect="auto")
        frame_ax.axis("off")
    fig.savefig(SCRIPT_DIR / "Figure6_b1.pdf", dpi=300)
    plt.close(fig)


if __name__ == "__main__":
    main()
