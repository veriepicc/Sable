# Sable CI Results

## Performance

Up to **19.7× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 13.1 ms | **4.87 ms** | **4.2× faster** (20.39ms) | **1.2× faster** (5.96ms) | **22.6× faster** (110.14ms) |
| state | 9.3 ms | **4.52 ms** | **5.0× faster** (22.84ms) | **1.3× faster** (5.83ms) | **15.4× faster** (69.87ms) |
| branch | 10.1 ms | **4.71 ms** | **7.0× faster** (33.10ms) | **4.2× faster** (19.72ms) | **13.7× faster** (64.52ms) |
| general | 9.7 ms | **24.13 ms** | 1.2× slower (19.65ms) | 1.5× slower (15.71ms) | **1.7× faster** (41.47ms) |
| hft | 10.5 ms | **188.47 ms** | 1.5× slower (129.21ms) | 1.5× slower (122.34ms) | **1.4× faster** (268.33ms) |
| math_vec | 9.7 ms | **47.86 ms** | **5.0× faster** (238.85ms) | **5.0× faster** (236.93ms) | **6.2× faster** (297.64ms) |
| state_vec | 10.1 ms | **47.82 ms** | **7.7× faster** (369.70ms) | **7.5× faster** (357.79ms) | **9.8× faster** (467.19ms) |
| branch_vec | 10.0 ms | **47.39 ms** | **5.1× faster** (240.45ms) | **5.0× faster** (236.56ms) | **6.6× faster** (311.01ms) |
| general_vec | 9.8 ms | **26.35 ms** | **7.1× faster** (187.76ms) | **6.8× faster** (179.28ms) | **9.2× faster** (242.23ms) |
| hft_vec | 9.8 ms | **26.00 ms** | **6.8× faster** (177.43ms) | **6.9× faster** (179.39ms) | **9.1× faster** (235.78ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43720743159) · Source: `aefb6159240a`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43720743159) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43720743159) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43720743159) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43720743159) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43720743159) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43720743159) · Source: `aefb6159240a`.
