# Sable CI Results

## Performance

Up to **17.7× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 17.8 ms | **4.69 ms** | **4.3× faster** (20.26ms) | **1.3× faster** (5.96ms) | **22.8× faster** (106.72ms) |
| state | 9.4 ms | **4.75 ms** | **4.8× faster** (23.03ms) | **1.3× faster** (6.23ms) | **13.2× faster** (62.66ms) |
| branch | 9.7 ms | **4.58 ms** | **7.2× faster** (33.01ms) | **4.4× faster** (20.10ms) | **13.5× faster** (61.77ms) |
| general | 10.3 ms | **24.08 ms** | 1.2× slower (19.88ms) | 1.5× slower (15.97ms) | **1.7× faster** (40.65ms) |
| hft | 11.1 ms | **183.58 ms** | 1.4× slower (127.08ms) | 1.5× slower (119.74ms) | **1.4× faster** (262.71ms) |
| math_vec | 10.2 ms | **47.96 ms** | **5.0× faster** (240.14ms) | **5.0× faster** (239.34ms) | **6.1× faster** (291.02ms) |
| state_vec | 10.1 ms | **47.73 ms** | **7.7× faster** (368.27ms) | **7.5× faster** (358.52ms) | **9.5× faster** (451.28ms) |
| branch_vec | 10.0 ms | **47.63 ms** | **5.1× faster** (241.37ms) | **5.0× faster** (239.34ms) | **6.5× faster** (308.97ms) |
| general_vec | 9.8 ms | **26.26 ms** | **7.2× faster** (188.15ms) | **7.0× faster** (183.29ms) | **9.0× faster** (237.11ms) |
| hft_vec | 10.0 ms | **26.28 ms** | **6.9× faster** (181.36ms) | **6.9× faster** (180.90ms) | **8.8× faster** (231.12ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43744268736) · Source: `7c42a9e7db93`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43744268736) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43744268736) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43744268736) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43744268736) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43744268736) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43744268736) · Source: `7c42a9e7db93`.
