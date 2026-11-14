# Sable CI Results

## Performance

Up to **22.4× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 13.9 ms | **3.28 ms** | **7.1× faster** (23.21ms) | **1.1× faster** (3.70ms) | **24.2× faster** (79.45ms) |
| state | 7.1 ms | **2.86 ms** | **5.6× faster** (16.13ms) | **1.5× faster** (4.30ms) | **17.4× faster** (49.76ms) |
| branch | 6.8 ms | **2.80 ms** | **4.8× faster** (13.46ms) | **4.9× faster** (13.58ms) | **10.7× faster** (30.04ms) |
| general | 7.8 ms | **13.72 ms** | 1.3× slower (10.95ms) | 1.1× slower (12.54ms) | **1.8× faster** (25.18ms) |
| hft | 8.0 ms | **107.95 ms** | 1.2× slower (91.82ms) | 1.2× slower (86.97ms) | **1.5× faster** (163.03ms) |
| math_vec | 7.3 ms | **24.01 ms** | **4.2× faster** (100.22ms) | **4.2× faster** (101.17ms) | **6.0× faster** (145.00ms) |
| state_vec | 7.6 ms | **24.76 ms** | **5.6× faster** (138.36ms) | **6.2× faster** (153.77ms) | **9.5× faster** (235.53ms) |
| branch_vec | 7.5 ms | **23.79 ms** | **4.3× faster** (101.84ms) | **4.2× faster** (100.55ms) | **6.9× faster** (164.51ms) |
| general_vec | 7.6 ms | **14.49 ms** | **5.1× faster** (73.59ms) | **5.4× faster** (78.31ms) | **8.8× faster** (126.80ms) |
| hft_vec | 9.2 ms | **12.55 ms** | **6.3× faster** (78.84ms) | **6.2× faster** (78.01ms) | **10.3× faster** (128.94ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43655116196) · Source: `fd983437f5d2`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43655116196) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43655116196) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43655116196) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43655116196) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43655116196) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43655116196) · Source: `fd983437f5d2`.
