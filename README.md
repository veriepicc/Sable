# Sable CI Results

## Performance

Up to **23.2× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 32.7 ms | **3.42 ms** | **7.7× faster** (26.50ms) | **1.3× faster** (4.45ms) | **33.5× faster** (114.66ms) |
| state | 7.7 ms | **3.39 ms** | **5.4× faster** (18.17ms) | **1.3× faster** (4.56ms) | **21.6× faster** (73.37ms) |
| branch | 7.7 ms | **3.47 ms** | **7.7× faster** (26.67ms) | **5.0× faster** (17.22ms) | **11.5× faster** (39.73ms) |
| general | 8.0 ms | **20.26 ms** | 1.3× slower (15.98ms) | 1.2× slower (16.50ms) | **1.9× faster** (38.19ms) |
| hft | 8.4 ms | **148.29 ms** | 1.2× slower (119.86ms) | 1.3× slower (117.32ms) | **1.7× faster** (258.31ms) |
| math_vec | 7.8 ms | **25.51 ms** | **4.8× faster** (121.27ms) | **4.7× faster** (121.06ms) | **7.2× faster** (183.06ms) |
| state_vec | 8.1 ms | **25.72 ms** | **7.0× faster** (179.42ms) | **7.3× faster** (186.46ms) | **12.6× faster** (322.76ms) |
| branch_vec | 8.3 ms | **25.43 ms** | **4.8× faster** (122.03ms) | **4.9× faster** (123.56ms) | **8.2× faster** (209.66ms) |
| general_vec | 7.9 ms | **14.57 ms** | **6.3× faster** (92.45ms) | **6.6× faster** (95.77ms) | **11.9× faster** (172.90ms) |
| hft_vec | 8.0 ms | **14.97 ms** | **6.4× faster** (95.80ms) | **6.4× faster** (96.51ms) | **11.6× faster** (172.88ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43730804969) · Source: `7429ebe0af8c`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43730804969) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43730804969) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43730804969) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43730804969) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43730804969) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43730804969) · Source: `7429ebe0af8c`.
