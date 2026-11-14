# Sable CI Results

## Performance

Up to **18.7× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 18.4 ms | **4.89 ms** | **6.5× faster** (31.93ms) | **1.3× faster** (6.40ms) | **27.0× faster** (131.94ms) |
| state | 10.0 ms | **4.98 ms** | **4.6× faster** (22.84ms) | **1.3× faster** (6.62ms) | **17.0× faster** (84.74ms) |
| branch | 9.8 ms | **4.59 ms** | **6.9× faster** (31.71ms) | **4.6× faster** (20.94ms) | **11.3× faster** (51.76ms) |
| general | 10.2 ms | **24.46 ms** | 1.2× slower (20.13ms) | 1.2× slower (20.66ms) | **2.0× faster** (48.90ms) |
| hft | 11.0 ms | **191.97 ms** | 1.4× slower (141.48ms) | 1.4× slower (132.40ms) | **2.1× faster** (401.62ms) |
| math_vec | 10.5 ms | **49.06 ms** | **2.8× faster** (138.88ms) | **2.8× faster** (136.58ms) | **4.4× faster** (213.94ms) |
| state_vec | 9.8 ms | **48.72 ms** | **4.1× faster** (202.06ms) | **4.2× faster** (207.00ms) | **7.4× faster** (361.07ms) |
| branch_vec | 10.4 ms | **49.86 ms** | **3.1× faster** (153.13ms) | **2.9× faster** (142.36ms) | **5.0× faster** (251.64ms) |
| general_vec | 12.4 ms | **27.56 ms** | **4.0× faster** (109.82ms) | **3.9× faster** (107.82ms) | **7.1× faster** (196.55ms) |
| hft_vec | 10.4 ms | **27.86 ms** | **4.1× faster** (112.93ms) | **4.0× faster** (110.24ms) | **7.1× faster** (198.74ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43642425574) · Source: `d2b6f85d0c31`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43642425574) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43642425574) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43642425574) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43642425574) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43642425574) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43642425574) · Source: `d2b6f85d0c31`.
