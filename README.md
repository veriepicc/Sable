# Sable CI Results

## Performance

Up to **19.6× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 17.8 ms | **4.47 ms** | **7.0× faster** (31.48ms) | **1.3× faster** (5.59ms) | **29.4× faster** (131.22ms) |
| state | 9.4 ms | **4.42 ms** | **4.9× faster** (21.56ms) | **1.3× faster** (5.54ms) | **19.2× faster** (84.68ms) |
| branch | 9.3 ms | **4.25 ms** | **7.3× faster** (30.86ms) | **4.7× faster** (19.84ms) | **12.0× faster** (51.15ms) |
| general | 9.6 ms | **23.48 ms** | 1.2× slower (18.90ms) | 1.2× slower (19.43ms) | **2.0× faster** (47.96ms) |
| hft | 10.1 ms | **190.94 ms** | 1.3× slower (141.44ms) | 1.5× slower (131.35ms) | **2.1× faster** (400.73ms) |
| math_vec | 9.5 ms | **45.41 ms** | **2.9× faster** (131.14ms) | **2.9× faster** (132.33ms) | **4.7× faster** (211.42ms) |
| state_vec | 10.4 ms | **45.74 ms** | **4.2× faster** (192.00ms) | **4.4× faster** (199.35ms) | **7.6× faster** (346.21ms) |
| branch_vec | 9.4 ms | **45.67 ms** | **3.1× faster** (142.87ms) | **2.9× faster** (133.67ms) | **5.3× faster** (239.88ms) |
| general_vec | 10.8 ms | **24.56 ms** | **4.3× faster** (104.52ms) | **4.1× faster** (101.84ms) | **7.8× faster** (190.47ms) |
| hft_vec | 9.5 ms | **25.08 ms** | **4.2× faster** (105.22ms) | **4.1× faster** (102.30ms) | **7.6× faster** (191.59ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43717993123) · Source: `c542d5a8aab3`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43717993123) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43717993123) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43717993123) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43717993123) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43717993123) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43717993123) · Source: `c542d5a8aab3`.
