from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure1" / "Figure1_b"
OUTPUT = SCRIPT_DIR / "Figure1_b1.pdf"
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
    points = np.load(DATA_DIR / "section_points.npy", allow_pickle=False)
    names = np.load(DATA_DIR / "section_names.npy", allow_pickle=False).astype(str)
    offsets = np.load(DATA_DIR / "section_offsets.npy", allow_pickle=False)
    parents = np.load(DATA_DIR / "section_parents.npy", allow_pickle=False)
    synapse_sections = np.load(DATA_DIR / "synapse_section.npy", allow_pickle=False).astype(str)
    synapse_locations = np.load(DATA_DIR / "synapse_location.npy", allow_pickle=False).astype(float)
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

    synapse_xy = []
    for name, location in zip(synapse_sections, synapse_locations):
        section = sections[section_map[name]]
        arcs = section[:, 4]
        target = float(location) * arcs[-1]
        x = float(np.interp(target, arcs, section[:, axis1]))
        y = float(np.interp(target, arcs, section[:, axis2]))
        synapse_xy.append((-y, x))

    return rotated, np.asarray(is_soma, dtype=bool), np.asarray(synapse_xy), synapse_type


def radius_for_diameter(diam, is_soma):
    radius = max(0.35, 0.5 * float(diam))
    return min(radius, 6.0) if is_soma else radius


def draw_tube_segment(ax, x0, x1, y0, y1, r0, r1):
    lx = x1 - x0
    ly = y1 - y0
    length = float(np.hypot(lx, ly))
    if length > 1e-12:
        nx = ly / length
        ny = -lx / length
        ax.fill(
            [x0 + r0 * nx, x1 + r1 * nx, x1 - r1 * nx, x0 - r0 * nx],
            [y0 + r0 * ny, y1 + r1 * ny, y1 - r1 * ny, y0 - r0 * ny],
            color="#000000",
            lw=0,
        )
    ax.add_patch(plt.Circle((x0, y0), r0, color="#000000", lw=0))
    ax.add_patch(plt.Circle((x1, y1), r1, color="#000000", lw=0))


def autoscale(segments, ax):
    xs = segments[:, :2].ravel()
    ys = segments[:, 2:4].ravel()
    xmin, xmax = xs.min(), xs.max()
    ymin, ymax = ys.min(), ys.max()
    dx = xmax - xmin
    dy = ymax - ymin
    pad_x = dx * 0.035 if dx > 0 else 1.0
    pad_y = dy * 0.035 if dy > 0 else 1.0
    ax.set_xlim(xmin - pad_x, xmax + pad_x)
    ax.set_ylim(ymin - pad_y, ymax + pad_y)
    ax.set_aspect("equal", adjustable="box")


def main():
    segments, is_soma, synapse_xy, synapse_type = build_plot_data()

    fig, ax = plt.subplots(figsize=(7.0, 10.0))
    for soma in (True, False):
        for x0, x1, y0, y1, d0, d1 in segments[is_soma == soma]:
            draw_tube_segment(
                ax, x0, x1, y0, y1,
                radius_for_diameter(d0, soma),
                radius_for_diameter(d1, soma),
            )
    autoscale(segments, ax)

    for kind, color, zorder in (("inh", "#000000", 3), ("exc", "#e41a1c", 4)):
        selected = synapse_xy[synapse_type == kind]
        if len(selected):
            px, py = selected.T
            ax.scatter(px, py, s=18.0, c=color, edgecolors="none", zorder=zorder)

    ax.invert_xaxis()
    ax.axis("off")
    fig.subplots_adjust(left=0.01, right=0.99, bottom=0.01, top=0.99)
    fig.savefig(OUTPUT, format="pdf", bbox_inches="tight", pad_inches=0.02)
    plt.close(fig)


if __name__ == "__main__":
    main()
