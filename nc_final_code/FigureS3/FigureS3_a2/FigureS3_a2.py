from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.collections import LineCollection


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "FigureS3" / "FigureS3_a2"
GEOMETRY_DIR = ROOT / "nc_final_data" / "FigureS3" / "FigureS3_a"
OUTPUT = SCRIPT_DIR / "FigureS3_a2.pdf"
EXCITATORY_CHANNELS = 250
TOTAL_CHANNELS = 500


def project_point_to_segment(px, py, x0, y0, x1, y1):
    dx = x1 - x0
    dy = y1 - y0
    length_sq = dx * dx + dy * dy
    if length_sq <= 1e-12:
        return x0, y0, 0.0
    t = ((px - x0) * dx + (py - y0) * dy) / length_sq
    t = min(1.0, max(0.0, t))
    return x0 + t * dx, y0 + t * dy, t


def nearest_point(points, px, py, axis1, axis2):
    polyline = [
        (float(p[axis1]), float(p[axis2]), float(p[3])) for p in points
    ]
    best = None
    for i in range(1, len(polyline)):
        x0, y0, d0 = polyline[i - 1]
        x1, y1, d1 = polyline[i]
        x, y, t = project_point_to_segment(px, py, x0, y0, x1, y1)
        distance = float(np.hypot(x - px, y - py))
        diameter = float((1.0 - t) * d0 + t * d1)
        candidate = (distance, x, y, diameter)
        if best is None or candidate[0] < best[0]:
            best = candidate
    if best is None:
        return polyline[0]
    return best[1:]


def build_plot_data():
    points = np.load(GEOMETRY_DIR / "section_points.npy", allow_pickle=False)
    names = np.load(GEOMETRY_DIR / "section_names.npy", allow_pickle=False).astype(str)
    offsets = np.load(GEOMETRY_DIR / "section_offsets.npy", allow_pickle=False)
    parents = np.load(GEOMETRY_DIR / "section_parents.npy", allow_pickle=False)
    synapse_sections = np.load(DATA_DIR / "synapse_section.npy", allow_pickle=False).astype(str)
    synapse_locations = np.load(DATA_DIR / "synapse_location.npy", allow_pickle=False).astype(float)
    cluster_ids = np.load(DATA_DIR / "synapse_cluster_id.npy", allow_pickle=False).astype(int)
    if len(synapse_sections) != TOTAL_CHANNELS:
        raise ValueError(f"Expected {TOTAL_CHANNELS} synapse sites.")
    synapse_type = np.where(
        np.arange(TOTAL_CHANNELS) < EXCITATORY_CHANNELS, "exc", "inh"
    )

    ranges = {
        name: float(points[:, i].max() - points[:, i].min())
        for i, name in enumerate(("x", "y", "z"))
    }
    axes = sorted(ranges, key=lambda name: ranges[name], reverse=True)
    axis1, axis2 = [("x", "y", "z").index(name) for name in axes[:2]]
    sections = [points[offsets[i]:offsets[i + 1]] for i in range(len(names))]
    section_map = {name: i for i, name in enumerate(names)}

    segments = []
    is_soma = []
    for name, section in zip(names, sections):
        for i in range(1, len(section)):
            previous, current = section[i - 1], section[i]
            segments.append((
                float(previous[axis1]), float(current[axis1]),
                float(previous[axis2]), float(current[axis2]),
                float(previous[3]), float(current[3]),
            ))
            is_soma.append("soma" in name)

    for section, parent_index in zip(sections, parents):
        if parent_index < 0:
            continue
        parent = sections[parent_index]
        child_start = (
            float(section[0, axis1]), float(section[0, axis2]), float(section[0, 3])
        )
        child_end = (
            float(section[-1, axis1]), float(section[-1, axis2]), float(section[-1, 3])
        )
        start_parent = nearest_point(parent, child_start[0], child_start[1], axis1, axis2)
        end_parent = nearest_point(parent, child_end[0], child_end[1], axis1, axis2)
        start_distance = np.hypot(
            start_parent[0] - child_start[0], start_parent[1] - child_start[1]
        )
        end_distance = np.hypot(
            end_parent[0] - child_end[0], end_parent[1] - child_end[1]
        )
        child, parent_point = (
            (child_start, start_parent) if start_distance <= end_distance
            else (child_end, end_parent)
        )
        child_x, child_y, child_d = child
        parent_x, parent_y, parent_d = parent_point
        if np.hypot(parent_x - child_x, parent_y - child_y) < 1e-9:
            continue
        segments.append((child_x, parent_x, child_y, parent_y, child_d, parent_d))
        is_soma.append(False)

    segments = np.asarray(segments, dtype=np.float64)
    rotated = segments.copy()
    rotated[:, 0] = -segments[:, 2]
    rotated[:, 1] = -segments[:, 3]
    rotated[:, 2] = segments[:, 0]
    rotated[:, 3] = segments[:, 1]

    selected = np.zeros(TOTAL_CHANNELS, dtype=bool)
    selected[np.arange(EXCITATORY_CHANNELS, TOTAL_CHANNELS)[::2]] = True
    dispersed = np.flatnonzero(cluster_ids[:EXCITATORY_CHANNELS] < 0)
    selected[dispersed[::2]] = True
    groups = np.unique(cluster_ids[:EXCITATORY_CHANNELS][cluster_ids[:EXCITATORY_CHANNELS] >= 0])
    selected[:EXCITATORY_CHANNELS] |= np.isin(cluster_ids[:EXCITATORY_CHANNELS], groups[::2])
    synapse_xy = []
    for name, location in zip(synapse_sections[selected], synapse_locations[selected]):
        section = sections[section_map[name]]
        arcs = section[:, 4]
        target = float(location) * arcs[-1]
        x = float(np.interp(target, arcs, section[:, axis1]))
        y = float(np.interp(target, arcs, section[:, axis2]))
        synapse_xy.append((-y, x))

    return rotated, np.asarray(is_soma, dtype=bool), np.asarray(synapse_xy), synapse_type[selected]


TITLE = "Mixed"


def main():
    segments, is_soma, synapse_xy, synapse_type = build_plot_data()
    exc = synapse_xy[synapse_type == "exc"]
    inh = synapse_xy[synapse_type == "inh"]
    lines = np.stack((segments[:, (0, 2)], segments[:, (1, 3)]), axis=1)
    widths = np.clip(0.30 + 0.16 * (segments[:, 4] + segments[:, 5]) / 2.0,
                     0.35, np.where(is_soma, 3.2, 1.8))
    with plt.rc_context({"font.family": "DejaVu Sans", "font.size": 15,
                         "pdf.fonttype": 42, "ps.fonttype": 42}):
        fig, ax = plt.subplots(figsize=(2.85, 6.2))
        ax.add_collection(LineCollection(lines, colors="#000000", linewidths=widths,
                                         capstyle="round", joinstyle="round", zorder=1))
        xs, ys = segments[:, :2].ravel(), segments[:, 2:4].ravel()
        dx, dy = xs.max() - xs.min(), ys.max() - ys.min()
        px, py = dx * 0.025 if dx > 0 else 1.0, dy * 0.025 if dy > 0 else 1.0
        ax.set_xlim(xs.min() - px, xs.max() + px)
        ax.set_ylim(ys.min() - py, ys.max() + py)
        ax.set_aspect("equal", adjustable="box")
        for points, color, zorder in ((inh, "#000000", 3), (exc, "#e41a1c", 4)):
            if len(points):
                ax.scatter(points[:, 0], points[:, 1], s=18.0, color=color,
                           edgecolors="none", zorder=zorder)
        ax.set_title(TITLE, fontsize=28, fontweight="bold", pad=2, x=0.57)
        ax.axis("off")
        fig.subplots_adjust(left=0.005, right=0.995, bottom=0.005, top=0.95)
        fig.savefig(OUTPUT, format="pdf", bbox_inches="tight", pad_inches=0.02)
        plt.close(fig)


if __name__ == "__main__":
    main()
