# Sable CI Results

## Performance

Up to **21.7× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 10.3 ms | **3.20 ms** | **7.4× faster** (23.80ms) | **1.2× faster** (3.89ms) | **25.0× faster** (80.03ms) |
| state | 7.5 ms | **3.04 ms** | **5.5× faster** (16.77ms) | **1.3× faster** (3.97ms) | **17.0× faster** (51.74ms) |
| branch | 7.3 ms | **3.14 ms** | **5.0× faster** (15.73ms) | **4.6× faster** (14.32ms) | **9.8× faster** (30.72ms) |
| general | 7.8 ms | **13.71 ms** | 1.1× slower (12.80ms) | tied (14.37ms) | **1.9× faster** (26.42ms) |
| hft | 8.1 ms | **113.19 ms** | 1.2× slower (94.68ms) | 1.3× slower (88.28ms) | **1.5× faster** (170.92ms) |
| math_vec | 7.5 ms | **24.13 ms** | **4.2× faster** (102.51ms) | **4.1× faster** (99.64ms) | **6.4× faster** (154.21ms) |
| state_vec | 7.7 ms | **24.81 ms** | **5.8× faster** (143.93ms) | **6.4× faster** (158.37ms) | **9.9× faster** (245.55ms) |
| branch_vec | 8.0 ms | **24.86 ms** | **4.2× faster** (103.84ms) | **4.2× faster** (105.10ms) | **6.9× faster** (171.65ms) |
| general_vec | 8.0 ms | **14.85 ms** | **5.0× faster** (74.12ms) | **5.6× faster** (83.03ms) | **8.8× faster** (130.81ms) |
| hft_vec | 7.6 ms | **14.57 ms** | **5.5× faster** (80.50ms) | **5.4× faster** (78.70ms) | **9.3× faster** (136.17ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43737982009) · Source: `d04ca899f85d`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43737982009) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | 357 | 0 | 4 | [Passed](https://github.com/veriepicc/Sable/actions/runs/43737982009) |
| Windows Server 2025 | Native x64 | 357 | 0 | 4 | [Passed](https://github.com/veriepicc/Sable/actions/runs/43737982009) |
| Windows 11 on Arm | x64 emulation | 357 | 0 | 4 | [Passed](https://github.com/veriepicc/Sable/actions/runs/43737982009) |
| Ubuntu 24.04 | Wine x64 | 357 | 0 | 4 | [Passed](https://github.com/veriepicc/Sable/actions/runs/43737982009) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43737982009) · Source: `d04ca899f85d`.
