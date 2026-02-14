import os
import sys
import json
import time
import numpy as np
from tqdm import tqdm
from neuron import h
from Purkinje_py3 import Purkinje_py3

# ================================
# NEURON 设置
# ================================
h.load_file("stdrun.hoc")
cv = h.CVode()
cv.active(0)

h.dt = 0.1


# ================================
# 创建 Purkinje 神经元
# ================================
cell = Purkinje_py3()

# 收集所有 section
sec_list = [sec for sec in h.allsec()]


# ============================================================
# 创建随机突触 + Poisson 刺激
# ============================================================
def create_random_synapses(N_syn, freq_hz):
    syns = []
    netstims = []
    netcons = []

    for i in range(N_syn):
        sec = np.random.choice(sec_list)
        loc = np.random.rand()

        syn = h.ExpSyn(sec(loc))
        syn.tau = 2.0
        syns.append(syn)

        ns = h.NetStim()
        ns.interval = 1000.0 / freq_hz
        ns.start = 0
        ns.number = 1e9
        ns.noise = 1
        netstims.append(ns)

        nc = h.NetCon(ns, syn)
        nc.weight[0] = 0.005
        netcons.append(nc)

    return syns, netstims, netcons


# ============================================================
# 单一参数组合下运行 n 次并计时
# ============================================================
def run_simulation(duration, N_syn, freq_hz, n_repeat=3):
    run_times = []

    inner_bar = tqdm(range(n_repeat), desc=f"  Repeats (N={N_syn}, freq={freq_hz}, dur={duration})", leave=False)

    for run_id in inner_bar:

        h.Random().Random123(run_id + 1, run_id * 7 + 11)

        syns, ns, nc = create_random_synapses(N_syn, freq_hz)

        t0 = time.time()
        h.finitialize(-65)
        h.continuerun(duration)
        t1 = time.time()

        elapsed = t1 - t0
        run_times.append(elapsed)

        # 每次运行完立即输出结果
        print(f"      → Run {run_id+1}/{n_repeat} finished: {elapsed:.3f} s")

    avg_time = float(np.mean(run_times))
    print(f"      → Average runtime for (N={N_syn}, freq={freq_hz}, dur={duration}) = {avg_time:.3f} s\n")

    return avg_time, run_times


# ============================================================
# 主流程：对所有参数循环（带 tqdm）
# ============================================================
def sweep_parameters(duration_list, synapse_list, freq_list, outfile="runtime_results.json"):
    results = {}

    total_tasks = len(duration_list) * len(synapse_list) * len(freq_list)
    pbar = tqdm(total=total_tasks, desc="Total Parameter Sweep")

    for duration in duration_list:
        for N_syn in synapse_list:
            for freq in freq_list:

                key = f"duration_{duration}_syn_{N_syn}_freq_{freq}"

                avg, each = run_simulation(duration, N_syn, freq)

                results[key] = {
                    "duration_ms": duration,
                    "synapses": N_syn,
                    "freq_hz": freq,
                    "avg_runtime_sec": avg,
                    "runs": each,
                }

                pbar.update(1)

    pbar.close()

    with open(outfile, "w") as f:
        json.dump(results, f, indent=4)

    print(f"\n参数扫描结束，结果已保存：{outfile}\n")
    return results


# ============================================================
# 设置并运行参数扫描
# ============================================================
duration_list = [5000] #[1000, 2000, 5000]
synapse_list = [10] #[10, 100, 1000]
freq_list = [10] #[10, 20, 50]

sweep_parameters(duration_list, synapse_list, freq_list, outfile="runtime_results_new.json")
