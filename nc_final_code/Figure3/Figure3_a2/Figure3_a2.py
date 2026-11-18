import csv
import os
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import torch
from torch import nn

FIGURE = 'Figure3_a2'
AXIS = 'a'
LEVELS = [('duration_1x', '1x'), ('duration_2x', '2x'), ('duration_4x', '4x'), ('duration_8x', '8x'), ('duration_16x', '16x')]
METRIC = 'f1'
X_LABEL = 'Simulation duration (relative scale)'
Y_LABEL = 'Relative F1 (%)'
BASELINE = 'duration_1x'
CASES = ("all_ampa", "ampa_nmda_2to1", "ampa_nmda_1to1", "ampa_nmda_1to2")
LABELS = ("All AMPA", "AMPA:NMDA=2:1", "AMPA:NMDA=1:1", "AMPA:NMDA=1:2")
COLORS = ("#B24A4A", "#D1844F", "#A6AD55", "#4AB27E")
MARKERS = ("o", "^", "s", "D")
STYLES = ("-", "--", "-.", ":")


class Bilinear(nn.Module):
    def __init__(self, device):
        super().__init__()
        self.weight = nn.Parameter(torch.zeros((1, 500, 500), device=device))
        self.register_buffer("bias", torch.zeros(1, device=device))

    def forward(self, x):
        return torch.einsum("...i,ij,...j->...", x, self.weight[0], x).unsqueeze(-1) + self.bias


class Model(nn.Module):
    def __init__(self, steps, device):
        super().__init__()
        self.steps = steps
        self.tau_rise = nn.Parameter(torch.zeros(500, device=device))
        self.tau_decay = nn.Parameter(torch.zeros(500, device=device))
        self.omega = nn.Parameter(torch.zeros(500, device=device))
        self.v_th = nn.Parameter(torch.zeros((), device=device))
        self.reset_amp = nn.Parameter(torch.zeros((), device=device))
        self.tau_reset = nn.Parameter(torch.zeros((), device=device))
        self.bilinear = Bilinear(device)
        self.kernel_fft = None
        self.reset_alpha = None
        self.reset_amplitude = None
        self.reset_powers = None

    def forward(self, x):
        full_length = 2 * self.steps - 1
        fft_size = 1 << (full_length - 1).bit_length()
        if self.kernel_fft is None:
            lag = (torch.arange(self.steps, dtype=self.omega.dtype, device=self.omega.device) - .5).clamp_min(0.)
            kernels = self.omega[:, None] * (1 - torch.exp(-lag[None] / self.tau_rise[:, None])) * torch.exp(-lag[None] / self.tau_decay[:, None])
            self.kernel_fft = torch.fft.rfft(kernels, n=fft_size, dim=1)
            tau = torch.clamp(torch.abs(self.tau_reset), min=1e-4).to(dtype=self.omega.dtype)
            self.reset_alpha = torch.exp(-torch.ones((), device=self.omega.device, dtype=self.omega.dtype) / tau)
            self.reset_amplitude = torch.abs(self.reset_amp).to(dtype=self.omega.dtype)
            self.reset_powers = self.reset_alpha.pow(torch.arange(self.steps, device=self.omega.device, dtype=self.omega.dtype))
        x_fft = torch.fft.rfft(x, n=fft_size, dim=2)
        filtered = torch.fft.irfft(x_fft * self.kernel_fft.unsqueeze(0), n=fft_size, dim=2)[..., :self.steps].permute(0, 2, 1)
        drive = (self.bilinear(filtered) + torch.sum(filtered, dim=2).unsqueeze(-1)).squeeze(-1)
        alpha, amplitude, powers = self.reset_alpha, self.reset_amplitude, self.reset_powers
        voltage = torch.empty_like(drive)
        reset = torch.zeros((), device=drive.device, dtype=drive.dtype)
        t = 0
        while t < self.steps:
            segment = drive[0, t:] + reset * powers[:self.steps - t]
            found = torch.nonzero(segment >= self.v_th, as_tuple=False)
            if found.numel() == 0:
                voltage[0, t:] = segment
                break
            offset = int(found[0, 0].item())
            voltage[0, t:t + offset + 1] = segment[:offset + 1]
            at_spike = reset * powers[offset]
            reset = alpha * at_spike - amplitude
            t += offset + 1
        return voltage


def spike_counts(truth, predicted):
    used = np.zeros(len(predicted), dtype=bool)
    matched = 0
    for spike in truth:
        possible = np.flatnonzero((~used) & (np.abs(predicted - spike) <= 10.))
        if len(possible):
            closest = possible[np.argmin(np.abs(predicted[possible] - spike))]
            used[closest] = True
            matched += 1
    return matched, int((~used).sum()), len(truth) - matched


def evaluate_group(folder, state, device):
    inputs = np.load(folder / "test_ip.npy", mmap_mode="r", allow_pickle=False)
    voltage = np.load(folder / "test_op.npy", mmap_mode="r", allow_pickle=False)
    spikes = np.load(folder / "test_spike_time.npy", allow_pickle=True)
    assert len(inputs) == len(voltage) == len(spikes) == 100 and inputs.shape[1] == 500
    assert voltage.shape[1] == inputs.shape[2]
    model = Model(inputs.shape[2], device)
    model.load_state_dict(state, strict=True)
    model.eval()
    assert torch.count_nonzero(torch.diagonal(model.bilinear.weight[0])).item() == 0
    threshold = float(model.v_th.detach().cpu())
    totals = np.zeros(9, dtype=np.float64)
    with torch.inference_mode():
        for i in range(100):
            x = torch.as_tensor(np.array(inputs[i:i + 1]), dtype=torch.float32, device=device)
            prediction = model(x).cpu().numpy()[0]
            target = np.asarray(voltage[i], dtype=np.float64)
            truth = np.asarray(spikes[i], dtype=np.float64).ravel()
            assert np.isfinite(target).all() and np.isfinite(truth).all()
            mask = np.ones(len(target), dtype=bool)
            for spike in truth:
                mask[max(0, int(np.floor(spike - 10))):min(len(mask), int(np.ceil(spike + 10)) + 1)] = False
            residual = (target - prediction)[mask]
            above = prediction >= threshold
            predicted = np.flatnonzero(above[1:] & ~above[:-1]) + 1
            if above[0]:
                predicted = np.r_[0, predicted]
            tp, fp, fn = spike_counts(truth, predicted)
            totals += np.array([len(residual), residual.sum(), residual @ residual,
                                len(target), target.sum(), target @ target, tp, fp, fn], dtype=np.float64)
    nr, sr, ssr, nt, st, sst, tp, fp, fn = totals
    ve = 1 - (ssr / nr - (sr / nr) ** 2) / (sst / nt - (st / nt) ** 2)
    f1 = 2 * tp / (2 * tp + fp + fn) if 2 * tp + fp + fn else 0.
    return np.array([ve, f1])




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


def write_metrics_table(path, cases, levels, values, normalized):
    columns, runs, means, stds = [], [], [], []
    for case_index, case in enumerate(cases):
        for level_index, (level, _) in enumerate(levels):
            for metric_index, metric in enumerate(("VE", "F1")):
                raw = values[case_index, level_index, :, metric_index]
                relative = normalized[case_index, level_index, :, metric_index]
                columns.extend((f"{case}_{level}_{metric}_raw", f"{case}_{level}_{metric}_relative_percent"))
                runs.extend((raw, relative * 100.0))
                means.extend((raw.mean(), relative.mean() * 100.0))
                stds.extend((raw.std(ddof=0), relative.std(ddof=0) * 100.0))
    write_table(path, columns, runs, means, stds)


def main():
    torch.set_num_threads(2)
    torch.backends.cuda.matmul.allow_tf32 = False
    torch.backends.cudnn.allow_tf32 = False
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    root = Path(__file__).resolve().parents[3]
    data_root = root / "nc_final_data" / "Figure3" / f"Figure3_{AXIS}"
    result_root = root / "nc_final_source_data" / "Figure3" / f"Figure3_{AXIS}"
    baseline_index = [name for name, _ in LEVELS].index(BASELINE)
    values = np.empty((4, len(LEVELS), 5, 2), dtype=float)
    for case_index, case in enumerate(CASES):
        checkpoint = torch.load(data_root / case / "dbnn_checkpoint.pt", map_location="cpu", weights_only=True)
        assert list(checkpoint) == ["model_state"]
        for level_index, (level, _) in enumerate(LEVELS):
            for group_index in range(5):
                folder = data_root / case / level / f"group_{group_index + 1}"
                values[case_index, level_index, group_index] = evaluate_group(folder, checkpoint["model_state"], device)
    normalized = values / values[:, baseline_index:baseline_index + 1, :, :]
    metric_index = 0 if METRIC == "ve" else 1
    mean = normalized[:, :, :, metric_index].mean(axis=2) * 100.
    std = normalized[:, :, :, metric_index].std(axis=2, ddof=0) * 100.
    positions = np.arange(len(LEVELS), dtype=float)
    write_metrics_table(result_root / f"Figure3_{AXIS}.csv", CASES, LEVELS, values, normalized)
    plt.rcParams.update({"font.size": 13, "axes.labelsize": 14, "xtick.labelsize": 13,
                         "ytick.labelsize": 13, "legend.fontsize": 11, "axes.linewidth": 1.,
                         "pdf.fonttype": 42, "ps.fonttype": 42})
    fig, ax = plt.subplots(figsize=(333. / 72., 222. / 72.))
    for i in range(len(CASES)):
        ax.fill_between(positions, mean[i] - std[i], mean[i] + std[i], color=COLORS[i], alpha=.16, linewidth=0)
        for repeat in range(normalized.shape[2]):
            ax.plot(positions, normalized[i, :, repeat, metric_index] * 100., color=COLORS[i],
                    linewidth=.65, alpha=.48, marker="o", markersize=2.4,
                    markerfacecolor="white", markeredgewidth=.45, zorder=2)
        ax.plot(positions, mean[i], color=COLORS[i], marker=MARKERS[i], linestyle=STYLES[i],
                markersize=5, linewidth=2, label=LABELS[i], zorder=3)
    ticks = [label for _, label in LEVELS]
    ticks[baseline_index] += "*"
    ax.set_xticks(positions, ticks)
    ax.set_xlabel(X_LABEL)
    ax.set_ylabel(Y_LABEL)
    if AXIS == "a":
        ax.set_ylim(80., 102.)
        ax.set_yticks(np.arange(80., 101., 5.))
    else:
        combined = np.r_[np.ravel(mean - std), np.ravel(mean + std), 100.]
        lower = 5. * np.floor((float(combined.min()) - 3.) / 5.)
        upper = 5. * np.ceil((float(combined.max()) + 3.) / 5.)
        step = 5. if upper - lower <= 20. else 10.
        ax.set_ylim(lower, upper)
        ax.set_yticks(np.arange(step * np.ceil(lower / step), upper + .1 * step, step))
    ax.axhline(100., color="0.65", linestyle="--", linewidth=.9, zorder=0)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    ax.legend(frameon=False, fontsize=11, loc="best")
    fig.subplots_adjust(left=.19, right=.97, bottom=.28 if AXIS == "b" else .20, top=.96)
    fig.savefig(Path(__file__).with_suffix(".pdf"), format="pdf")
    plt.close(fig)


if __name__ == "__main__":
    main()
