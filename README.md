# Sable CI Results

## Performance

Up to **19.1× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 12.9 ms | **4.49 ms** | **6.6× faster** (29.47ms) | **1.2× faster** (5.61ms) | **33.6× faster** (151.04ms) |
| state | 8.8 ms | **4.27 ms** | **4.9× faster** (20.98ms) | **1.3× faster** (5.61ms) | **30.2× faster** (129.15ms) |
| branch | 9.4 ms | **4.37 ms** | **6.8× faster** (29.68ms) | **4.9× faster** (21.42ms) | **23.7× faster** (103.36ms) |
| general | 9.5 ms | **22.84 ms** | 1.2× slower (18.37ms) | 1.2× slower (18.52ms) | **3.1× faster** (70.58ms) |
| hft | 10.8 ms | **200.61 ms** | 1.4× slower (138.39ms) | 1.5× slower (132.36ms) | **1.9× faster** (384.91ms) |
| math_vec | 9.6 ms | **44.15 ms** | **4.9× faster** (217.60ms) | **5.0× faster** (220.14ms) | **6.9× faster** (303.26ms) |
| state_vec | 9.2 ms | **44.65 ms** | **7.3× faster** (323.93ms) | **7.3× faster** (327.59ms) | **11.3× faster** (504.79ms) |
| branch_vec | 9.5 ms | **44.80 ms** | **4.8× faster** (216.71ms) | **4.7× faster** (209.68ms) | **7.3× faster** (325.43ms) |
| general_vec | 9.6 ms | **24.48 ms** | **6.7× faster** (163.11ms) | **6.5× faster** (159.15ms) | **10.6× faster** (260.68ms) |
| hft_vec | 9.5 ms | **24.14 ms** | **6.8× faster** (163.33ms) | **7.0× faster** (168.42ms) | **10.8× faster** (259.64ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43636543095) · Source: `e366dfabf8a4`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43636543095) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43636543095) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43636543095) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43636543095) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43636543095) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43636543095) · Source: `e366dfabf8a4`.
