# Sable CI Results

## Performance

Up to **25.9× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 18.6 ms | **4.22 ms** | **6.5× faster** (27.44ms) | **1.1× faster** (4.53ms) | **27.2× faster** (114.92ms) |
| state | 7.7 ms | **3.53 ms** | **5.5× faster** (19.22ms) | **1.3× faster** (4.56ms) | **20.9× faster** (73.73ms) |
| branch | 7.9 ms | **4.06 ms** | **6.8× faster** (27.63ms) | **4.4× faster** (18.06ms) | **10.0× faster** (40.45ms) |
| general | 8.7 ms | **21.06 ms** | 1.2× slower (17.07ms) | 1.2× slower (17.32ms) | **1.8× faster** (38.70ms) |
| hft | 8.4 ms | **148.58 ms** | 1.2× slower (120.43ms) | 1.3× slower (117.34ms) | **1.7× faster** (258.62ms) |
| math_vec | 8.2 ms | **27.34 ms** | **4.5× faster** (122.71ms) | **4.5× faster** (122.18ms) | **6.8× faster** (184.59ms) |
| state_vec | 8.3 ms | **26.97 ms** | **6.7× faster** (181.17ms) | **7.0× faster** (189.63ms) | **11.9× faster** (322.14ms) |
| branch_vec | 8.4 ms | **26.93 ms** | **4.6× faster** (123.21ms) | **4.6× faster** (124.06ms) | **7.8× faster** (211.12ms) |
| general_vec | 8.3 ms | **15.97 ms** | **5.9× faster** (93.95ms) | **6.1× faster** (97.26ms) | **10.9× faster** (174.30ms) |
| hft_vec | 8.1 ms | **16.00 ms** | **6.0× faster** (95.54ms) | **6.0× faster** (96.12ms) | **11.0× faster** (175.28ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43708605307) · Source: `12dce63c60a1`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43708605307) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43708605307) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43708605307) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43708605307) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43708605307) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43708605307) · Source: `12dce63c60a1`.
