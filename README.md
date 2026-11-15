# Sable CI Results

## Performance

Up to **27.7× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 13.3 ms | **4.49 ms** | **7.0× faster** (31.55ms) | **1.3× faster** (5.89ms) | **29.4× faster** (131.90ms) |
| state | 10.7 ms | **4.53 ms** | **4.8× faster** (21.88ms) | **1.3× faster** (5.96ms) | **18.8× faster** (85.03ms) |
| branch | 10.4 ms | **4.62 ms** | **6.8× faster** (31.50ms) | **4.4× faster** (20.44ms) | **13.0× faster** (60.16ms) |
| general | 10.6 ms | **24.21 ms** | 1.2× slower (19.78ms) | 1.2× slower (20.30ms) | **2.0× faster** (48.57ms) |
| hft | 10.7 ms | **191.27 ms** | 1.4× slower (141.51ms) | 1.5× slower (131.70ms) | **2.1× faster** (401.00ms) |
| math_vec | 9.6 ms | **48.11 ms** | **2.8× faster** (134.85ms) | **2.8× faster** (136.85ms) | **4.4× faster** (213.21ms) |
| state_vec | 9.6 ms | **47.74 ms** | **4.1× faster** (197.67ms) | **4.2× faster** (201.22ms) | **7.3× faster** (348.50ms) |
| branch_vec | 9.8 ms | **48.26 ms** | **3.0× faster** (144.30ms) | **2.8× faster** (135.11ms) | **5.0× faster** (243.62ms) |
| general_vec | 9.6 ms | **27.00 ms** | **3.9× faster** (106.50ms) | **3.9× faster** (105.38ms) | **7.1× faster** (192.01ms) |
| hft_vec | 9.5 ms | **26.15 ms** | **4.2× faster** (108.53ms) | **4.0× faster** (105.36ms) | **7.5× faster** (195.45ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43715440225) · Source: `7ec71b14cc04`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43715440225) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43715440225) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43715440225) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43715440225) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43715440225) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43715440225) · Source: `7ec71b14cc04`.
