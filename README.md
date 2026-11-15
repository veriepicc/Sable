# Sable CI Results

## Performance

Up to **20.1× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 11.0 ms | **3.84 ms** | **7.0× faster** (26.68ms) | **1.1× faster** (4.39ms) | **29.9× faster** (114.78ms) |
| state | 7.9 ms | **3.86 ms** | **4.9× faster** (18.73ms) | **1.2× faster** (4.50ms) | **19.1× faster** (73.50ms) |
| branch | 7.9 ms | **3.35 ms** | **8.2× faster** (27.51ms) | **5.3× faster** (17.72ms) | **12.0× faster** (40.26ms) |
| general | 9.8 ms | **20.92 ms** | 1.3× slower (16.33ms) | 1.3× slower (16.52ms) | **1.8× faster** (37.95ms) |
| hft | 8.3 ms | **148.33 ms** | 1.2× slower (120.32ms) | 1.3× slower (117.50ms) | **1.7× faster** (258.54ms) |
| math_vec | 8.2 ms | **27.52 ms** | **4.5× faster** (123.02ms) | **4.4× faster** (121.74ms) | **6.7× faster** (184.55ms) |
| state_vec | 8.2 ms | **26.95 ms** | **6.7× faster** (181.82ms) | **7.1× faster** (190.41ms) | **12.0× faster** (323.87ms) |
| branch_vec | 8.4 ms | **26.94 ms** | **4.5× faster** (121.91ms) | **4.6× faster** (124.97ms) | **7.9× faster** (213.13ms) |
| general_vec | 8.0 ms | **15.86 ms** | **5.9× faster** (93.68ms) | **6.2× faster** (98.04ms) | **11.0× faster** (174.12ms) |
| hft_vec | 7.9 ms | **14.95 ms** | **6.4× faster** (96.35ms) | **6.5× faster** (96.96ms) | **11.8× faster** (176.39ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43718567943) · Source: `3e5ae0f247bf`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43718567943) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43718567943) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43718567943) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43718567943) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43718567943) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43718567943) · Source: `3e5ae0f247bf`.
