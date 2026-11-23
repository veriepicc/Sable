# Sable CI Results

## Performance

Up to **20.2× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 13.9 ms | **4.33 ms** | **7.0× faster** (30.35ms) | **1.3× faster** (5.61ms) | **30.2× faster** (130.66ms) |
| state | 8.6 ms | **4.33 ms** | **4.9× faster** (21.01ms) | **1.3× faster** (5.75ms) | **19.4× faster** (83.84ms) |
| branch | 8.6 ms | **4.37 ms** | **7.0× faster** (30.57ms) | **4.6× faster** (20.31ms) | **11.5× faster** (50.48ms) |
| general | 9.5 ms | **23.17 ms** | tied (22.29ms) | 1.2× slower (19.24ms) | **2.0× faster** (47.49ms) |
| hft | 9.7 ms | **191.49 ms** | 1.3× slower (148.18ms) | 1.5× slower (131.56ms) | **2.1× faster** (400.72ms) |
| math_vec | 11.0 ms | **46.73 ms** | **2.9× faster** (134.53ms) | **2.9× faster** (135.00ms) | **4.6× faster** (214.26ms) |
| state_vec | 9.6 ms | **47.13 ms** | **4.2× faster** (199.06ms) | **4.4× faster** (207.11ms) | **7.4× faster** (349.99ms) |
| branch_vec | 9.4 ms | **47.68 ms** | **3.1× faster** (147.23ms) | **2.9× faster** (136.88ms) | **5.1× faster** (244.95ms) |
| general_vec | 9.4 ms | **25.87 ms** | **4.2× faster** (108.32ms) | **4.1× faster** (104.87ms) | **7.5× faster** (193.85ms) |
| hft_vec | 9.6 ms | **26.14 ms** | **4.2× faster** (109.23ms) | **4.0× faster** (104.85ms) | **7.5× faster** (194.90ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/45182763174) · Source: `9258f21017d5`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/45182763174) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/45182763174) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/45182763174) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/45182763174) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/45182763174) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/45182763174) · Source: `9258f21017d5`.
