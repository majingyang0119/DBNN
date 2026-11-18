from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.collections import LineCollection


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
LETTER = SCRIPT_DIR.name[-2]
DATA_DIR = ROOT / "nc_final_data" / "Figure2" / f"Figure2_{LETTER}1"


def canonical_name(name):
    name = str(name)
    return name.split(">.", 1)[-1] if ">." in name else name


def nearest_point(point, polyline):
    best_point = np.asarray(polyline[0], dtype=float)
    best_distance = float("inf")
    for start, stop in zip(polyline[:-1], polyline[1:]):
        start = np.asarray(start, dtype=float)
        stop = np.asarray(stop, dtype=float)
        delta = stop - start
        length_squared = float(np.dot(delta, delta))
        if length_squared <= 1e-12:
            candidate = start
        else:
            fraction = float(np.clip(np.dot(np.asarray(point) - start, delta) / length_squared, 0.0, 1.0))
            candidate = start + fraction * delta
        distance = float(np.linalg.norm(np.asarray(point) - candidate))
        if distance < best_distance:
            best_distance = distance
            best_point = candidate
    return best_point, best_distance


def geometry():
    points = np.load(DATA_DIR / "section_points.npy", allow_pickle=False)
    offsets = np.load(DATA_DIR / "section_offsets.npy", allow_pickle=False)
    names = np.load(DATA_DIR / "section_names.npy", allow_pickle=False).astype(str)
    parents = np.load(DATA_DIR / "section_parents.npy", allow_pickle=False)
    soma_index = int(np.load(DATA_DIR / "soma_index.npy", allow_pickle=False))
    synapse_sections = np.load(DATA_DIR / "synapse_section.npy", allow_pickle=False).astype(str)
    locations = np.load(DATA_DIR / "synapse_location.npy", allow_pickle=False).astype(float)
    sections = [points[offsets[i]:offsets[i + 1]] for i in range(len(names))]
    if len(names) != len(parents) or len(synapse_sections) != 500 or len(locations) != 500:
        raise ValueError("Inconsistent morphology or synapse data")
    ranges = np.ptp(np.concatenate([section[:, :3] for section in sections], axis=0), axis=0)
    axis_x, axis_y = [int(i) for i in np.argsort(ranges)[::-1][:2]]
    soma_point = tuple(sections[soma_index][:, [axis_x, axis_y]].mean(axis=0))
    segments = []
    widths = []
    for index, section in enumerate(sections):
        if index == soma_index:
            continue
        xy = section[:, [axis_x, axis_y]]
        segments.extend(zip(xy[:-1], xy[1:]))
        diameters = 0.5 * (section[:-1, 3] + section[1:, 3])
        widths.extend(np.clip(0.42 * diameters, 0.42, 3.75))
    for index, parent in enumerate(parents):
        if parent < 0:
            continue
        child_points = sections[index]
        parent_points = sections[int(parent)]
        child_xy = child_points[:, [axis_x, axis_y]]
        parent_xy = parent_points[:, [axis_x, axis_y]]
        candidates = []
        for child_index in (0, -1):
            if parent == soma_index:
                parent_point = parent_xy.mean(axis=0)
                distance = float(np.linalg.norm(child_xy[child_index] - parent_point))
            else:
                parent_point, distance = nearest_point(child_xy[child_index], parent_xy)
            candidates.append((distance, child_xy[child_index], parent_point, child_index))
        distance, child_point, parent_point, child_index = min(candidates, key=lambda item: item[0])
        if distance <= 1e-6:
            continue
        segments.append((child_point, parent_point))
        child_diameter = float(child_points[child_index, 3])
        widths.append(float(np.clip(0.42 * child_diameter, 0.42, 3.75)))
    name_map = {}
    for index, name in enumerate(names):
        name_map[name] = index
        name_map[canonical_name(name)] = index
    synapse_points = []
    for name, location in zip(synapse_sections, locations):
        index = name_map.get(name)
        if index is None:
            index = name_map.get(canonical_name(name))
        if index is None:
            raise KeyError(name)
        section = sections[index]
        target_arc = float(location) * section[-1, 4]
        x = float(np.interp(target_arc, section[:, 4], section[:, axis_x]))
        y = float(np.interp(target_arc, section[:, 4], section[:, axis_y]))
        synapse_points.append((x, y))
    coordinates = np.asarray(segments, dtype=float).reshape(-1, 2)
    width, height = np.ptp(coordinates, axis=0)
    if width > height:
        segments = [((-y0, x0), (-y1, x1)) for (x0, y0), (x1, y1) in segments]
        synapse_points = [(-y, x) for x, y in synapse_points]
        soma_point = (-soma_point[1], soma_point[0])
    return np.asarray(segments), np.asarray(widths), np.asarray(synapse_points), np.asarray(soma_point)


def main():
    segments, widths, synapse_points, soma_point = geometry()
    with plt.rc_context({"font.size": 12}):
        fig, ax = plt.subplots(figsize=(7.0, 7.0))
        ax.add_collection(LineCollection(segments, colors="black", linewidths=widths,
                                         capstyle="round", joinstyle="round", zorder=1))
        ax.scatter([soma_point[0]], [soma_point[1]], s=130.0 if LETTER == "d" else 32.5,
                   color="black", edgecolors="none", zorder=2)
        for selected, color, zorder in ((synapse_points[250:], "black", 2),
                                         (synapse_points[:250], "#E31A1C", 3)):
            if len(selected):
                x, y = selected.T
                ax.scatter(x, y, s=18.0, color=color, edgecolors="none", zorder=zorder)
        coordinates = segments.reshape(-1, 2)
        mins = coordinates.min(axis=0)
        maxs = coordinates.max(axis=0)
        padding = np.maximum((maxs - mins) * 0.025, 1.0)
        ax.set_xlim(mins[0] - padding[0], maxs[0] + padding[0])
        ax.set_ylim(mins[1] - padding[1], maxs[1] + padding[1])
        ax.set_aspect("equal", adjustable="box")
        ax.axis("off")
        fig.subplots_adjust(left=0.01, right=0.99, bottom=0.01, top=0.99)
        fig.savefig(SCRIPT_DIR / f"Figure2_{LETTER}1.pdf", format="pdf", bbox_inches="tight", pad_inches=0.02)
        plt.close(fig)


if __name__ == "__main__":
    main()
