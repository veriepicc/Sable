# Sable CI Results

## Performance

Up to **19.1× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 20.7 ms | **4.42 ms** | **7.0× faster** (30.95ms) | **1.3× faster** (5.75ms) | **29.7× faster** (131.58ms) |
| state | 9.4 ms | **4.52 ms** | **4.9× faster** (21.99ms) | **1.3× faster** (5.70ms) | **18.8× faster** (84.90ms) |
| branch | 9.7 ms | **4.33 ms** | **7.2× faster** (31.17ms) | **4.6× faster** (20.11ms) | **11.8× faster** (51.32ms) |
| general | 9.4 ms | **23.58 ms** | 1.2× slower (19.34ms) | 1.2× slower (19.58ms) | **2.1× faster** (48.40ms) |
| hft | 10.6 ms | **192.35 ms** | 1.4× slower (141.52ms) | 1.5× slower (131.56ms) | **2.1× faster** (400.49ms) |
| math_vec | 10.1 ms | **46.10 ms** | **2.9× faster** (132.84ms) | **2.9× faster** (133.65ms) | **4.6× faster** (211.33ms) |
| state_vec | 9.6 ms | **45.66 ms** | **4.2× faster** (193.55ms) | **4.4× faster** (200.70ms) | **7.6× faster** (347.19ms) |
| branch_vec | 9.7 ms | **46.40 ms** | **3.1× faster** (143.86ms) | **2.9× faster** (133.61ms) | **5.2× faster** (242.49ms) |
| general_vec | 9.5 ms | **25.54 ms** | **4.1× faster** (104.56ms) | **4.0× faster** (101.50ms) | **7.5× faster** (190.85ms) |
| hft_vec | 9.9 ms | **25.74 ms** | **4.1× faster** (106.64ms) | **4.0× faster** (101.78ms) | **7.5× faster** (192.59ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43723357219) · Source: `c66922de33bb`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43723357219) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43723357219) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43723357219) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43723357219) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43723357219) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43723357219) · Source: `c66922de33bb`.
