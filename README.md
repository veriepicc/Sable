# Sable CI Results

## Performance

Up to **21.6× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 18.7 ms | **4.33 ms** | **4.6× faster** (19.71ms) | **1.3× faster** (5.72ms) | **24.9× faster** (107.64ms) |
| state | 9.7 ms | **4.39 ms** | **5.1× faster** (22.32ms) | **1.3× faster** (5.82ms) | **14.7× faster** (64.69ms) |
| branch | 9.2 ms | **4.64 ms** | **7.1× faster** (32.90ms) | **4.1× faster** (19.16ms) | **13.6× faster** (63.07ms) |
| general | 9.6 ms | **24.00 ms** | 1.2× slower (19.59ms) | 1.6× slower (15.37ms) | **1.7× faster** (40.34ms) |
| hft | 10.7 ms | **185.03 ms** | 1.5× slower (127.59ms) | 1.5× slower (120.37ms) | **1.4× faster** (266.32ms) |
| math_vec | 9.7 ms | **47.37 ms** | **5.0× faster** (237.39ms) | **5.0× faster** (235.67ms) | **6.2× faster** (292.40ms) |
| state_vec | 9.5 ms | **47.05 ms** | **7.8× faster** (367.48ms) | **7.6× faster** (355.66ms) | **11.0× faster** (517.95ms) |
| branch_vec | 11.4 ms | **48.07 ms** | **5.0× faster** (240.68ms) | **4.9× faster** (236.21ms) | **6.5× faster** (311.59ms) |
| general_vec | 9.9 ms | **26.28 ms** | **7.0× faster** (185.10ms) | **6.8× faster** (179.70ms) | **9.1× faster** (238.86ms) |
| hft_vec | 9.8 ms | **27.00 ms** | **6.6× faster** (179.04ms) | **6.7× faster** (180.17ms) | **8.6× faster** (233.16ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43717497981) · Source: `2fb45a7057a6`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43717497981) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43717497981) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43717497981) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43717497981) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43717497981) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43717497981) · Source: `2fb45a7057a6`.
