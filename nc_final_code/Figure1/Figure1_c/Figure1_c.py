import os
from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
import torch


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parents[2]
DATA_DIR = ROOT / "nc_final_data" / "Figure1" / "Figure1_c"
SOURCE_DIR = ROOT / "nc_final_source_data" / "Figure1" / "Figure1_c"
OUTPUT = SCRIPT_DIR / "Figure1_c.pdf"
SAMPLE_INTERVAL_MS = 1.0


def predict_voltage(raster, state):
    if raster.shape[0] != 500:
        raise ValueError(f"Expected 500 synapse channels, got {raster.shape[0]}")
    signs = np.ones(500, dtype=np.float32)
    signs[250:] = -1.0
    inputs = torch.from_numpy((raster.astype(np.float32) * signs[:, None])[None])
    steps = inputs.shape[-1]

    with torch.inference_mode():
        time_index = torch.arange(steps, device=state["tau_rise"].device)
        tau_rise = state["tau_rise"].unsqueeze(1)
        tau_decay = state["tau_decay"].unsqueeze(1)
        omega = state["omega"].unsqueeze(1)
        kernels = omega * (1 - torch.exp(-time_index / tau_rise)) * torch.exp(
            -time_index / tau_decay
        )
        full_length = 2 * steps - 1
        fft_size = 1 << (full_length - 1).bit_length()
        input_fft = torch.fft.rfft(inputs, n=fft_size, dim=2)
        kernel_fft = torch.fft.rfft(kernels, n=fft_size, dim=1)
        filtered = torch.fft.irfft(
            input_fft * kernel_fft.unsqueeze(0), n=fft_size, dim=2
        )[..., :full_length][..., :steps].permute(0, 2, 1)

        weight = state["bilinear.weight"].clone()
        diagonal = torch.arange(weight.shape[1], device=weight.device)
        weight[:, diagonal, diagonal] = 0
        bilinear = torch.einsum(
            "...i,ij,...j->...", filtered, weight[0], filtered
        ).unsqueeze(-1) + state["bilinear.bias"]
        linear = torch.sum(filtered, dim=2).unsqueeze(-1)
        drive = (bilinear + linear).squeeze(-1)

        tau = torch.clamp(torch.abs(state["tau_reset"]), min=1e-4).to(drive.dtype)
        alpha = torch.exp(-torch.ones((), dtype=drive.dtype) / tau)
        amplitude = torch.abs(state["reset_amp"]).to(drive.dtype)
        threshold = state["v_th"].to(drive.dtype)
        voltage = torch.empty_like(drive)
        reset = torch.zeros((drive.shape[0],), dtype=drive.dtype)
        for t in range(steps):
            value = drive[:, t] + reset
            spike = (value >= threshold).to(value.dtype)
            voltage[:, t] = value
            reset = alpha * reset - amplitude * spike
    return voltage.numpy()[0]


def detect_spike_indices(voltage, threshold):
    above = voltage >= float(threshold)
    rising = np.flatnonzero(np.logical_and(above[1:], ~above[:-1])) + 1
    if above[0]:
        rising = np.concatenate(([0], rising))
    return rising.astype(np.int32)


def displayed_neuron_voltage(voltage, spike_times_ms, interval_ms):
    displayed = np.asarray(voltage, dtype=float).copy()
    indices = np.rint(np.asarray(spike_times_ms, dtype=float) / interval_ms).astype(int)
    for index in indices:
        start = max(0, index - 2)
        stop = min(len(displayed), index + 3)
        if start < stop:
            peak = start + int(np.argmax(displayed[start:stop]))
            displayed[peak] = 0.0
    return displayed


def main():
    raster = np.load(DATA_DIR / "train_ip.npy", allow_pickle=False)[0]
    true_voltage = np.load(DATA_DIR / "train_op.npy", allow_pickle=False)[0]
    true_spikes = np.asarray(np.load(DATA_DIR / "train_spike_time.npy", allow_pickle=True)[0], dtype=float)
    checkpoint = torch.load(DATA_DIR / "dbnn_checkpoint.pt", map_location="cpu", weights_only=True)
    state = checkpoint["model_state"]

    torch.set_num_threads(1)
    prediction = predict_voltage(raster, state)
    threshold = float(state["v_th"].item())
    predicted_indices = detect_spike_indices(prediction, threshold)
    predicted_times_ms = predicted_indices.astype(float) * SAMPLE_INTERVAL_MS
    neuron_voltage = displayed_neuron_voltage(true_voltage, true_spikes, SAMPLE_INTERVAL_MS)
    time_ms = np.arange(len(true_voltage), dtype=float) * SAMPLE_INTERVAL_MS

    SOURCE_DIR.mkdir(parents=True, exist_ok=True)
    target = SOURCE_DIR / "Figure1_c.csv"
    temporary = target.with_name(f".{target.name}.{os.getpid()}.tmp")
    try:
        values = np.column_stack((time_ms, neuron_voltage, prediction.astype(np.float64)))
        np.savetxt(temporary, values, delimiter=",", header="time_ms,NEURON,DBNN", comments="", fmt="%.17g")
        os.replace(temporary, target)
    finally:
        if temporary.exists():
            temporary.unlink()

    fig, ax = plt.subplots(figsize=(14.0, 8.0))
    ax.plot(time_ms, neuron_voltage, color="black", linewidth=3.0)
    ax.plot(time_ms, prediction, color="c", linewidth=3.0)
    for spike_time, spike_index in zip(predicted_times_ms, predicted_indices):
        ax.vlines(
            spike_time,
            ymin=float(prediction[spike_index]),
            ymax=0.0,
            colors="c",
            linestyles="--",
            linewidth=3.0,
        )
    ax.axhline(y=threshold, color="red", linestyle="--", linewidth=1.0)
    ax.set_xlim(time_ms[0], time_ms[-1])
    ax.axis("off")
    fig.savefig(OUTPUT, format="pdf", dpi=800, bbox_inches="tight")
    plt.close(fig)


if __name__ == "__main__":
    main()
