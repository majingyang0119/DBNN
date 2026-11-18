from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure4" / "Figure4_a1"


def main():
    image = np.load(DATA_DIR / "morphology_rgb.npy", allow_pickle=False)
    if image.shape != (1600, 626, 3) or image.dtype != np.uint8:
        raise ValueError("Expected the 1600×626 RGB morphology image")
    padded = np.pad(image, ((1, 1), (1, 1), (0, 0)), mode="constant", constant_values=255)
    nearby = np.minimum.reduce((image, padded[:-2, 1:-1], padded[2:, 1:-1],
                                padded[1:-1, :-2], padded[1:-1, 2:]))
    displayed = np.rint(0.35 * image.astype(np.float32) + 0.65 * nearby.astype(np.float32)).astype(np.uint8)
    height, width = image.shape[:2]
    fig = plt.figure(figsize=(width / 200.0, height / 200.0), dpi=200)
    ax = fig.add_axes([0.0, 0.0, 1.0, 1.0])
    ax.imshow(displayed, interpolation="none", aspect="equal")
    ax.axis("off")
    fig.savefig(SCRIPT_DIR / "Figure4_a1.pdf", format="pdf", dpi=200, pad_inches=0)
    plt.close(fig)


if __name__ == "__main__":
    main()
