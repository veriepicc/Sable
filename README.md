# Sable CI Results

## Performance

Up to **20.8× faster compilation** than MSVC · **5.0 KiB** smallest Sable executable.

| Workload | Sable compile | Sable runtime | vs MSVC | vs GCC | vs TCC |
| :--- | ---: | ---: | ---: | ---: | ---: |
| math | 16.0 ms | **3.54 ms** | **7.0× faster** (24.66ms) | **1.3× faster** (4.44ms) | **23.2× faster** (82.26ms) |
| state | 7.9 ms | **3.18 ms** | **5.4× faster** (17.16ms) | **1.4× faster** (4.40ms) | **16.6× faster** (52.85ms) |
| branch | 7.7 ms | **3.37 ms** | **4.7× faster** (15.84ms) | **4.5× faster** (15.02ms) | **9.2× faster** (30.98ms) |
| general | 9.3 ms | **14.64 ms** | 1.1× slower (13.61ms) | tied (14.80ms) | **1.9× faster** (27.58ms) |
| hft | 8.9 ms | **117.93 ms** | 1.2× slower (97.01ms) | 1.3× slower (92.16ms) | **1.5× faster** (177.22ms) |
| math_vec | 8.6 ms | **26.66 ms** | **4.1× faster** (108.67ms) | **4.1× faster** (110.35ms) | **6.3× faster** (168.59ms) |
| state_vec | 8.9 ms | **27.24 ms** | **5.6× faster** (153.17ms) | **5.9× faster** (162.03ms) | **10.0× faster** (273.61ms) |
| branch_vec | 8.8 ms | **27.35 ms** | **4.1× faster** (111.95ms) | **4.1× faster** (111.68ms) | **6.6× faster** (181.80ms) |
| general_vec | 9.4 ms | **15.70 ms** | **5.1× faster** (80.11ms) | **5.5× faster** (85.67ms) | **9.5× faster** (149.47ms) |
| hft_vec | 8.8 ms | **15.70 ms** | **5.4× faster** (85.30ms) | **5.4× faster** (85.14ms) | **9.2× faster** (144.98ms) |

Windows AMD64 · 5 measured runs · 2 warmups · minimum runtime.
[Full results & methodology](BENCHMARKS.md)

[Benchmark CI run](https://github.com/veriepicc/Sable/actions/runs/43737099177) · Source: `186bbcdf8f67`.


## Core CI Build Status

| Host & Toolchain | Target | Configuration | Build |
| :--- | :---: | :---: | :---: |
| Windows Server 2022 · MSVC | x64 | Release | [Passed](https://github.com/veriepicc/Sable/actions/runs/43737099177) |

## Platform CI Test Status

| Test Host | Execution | Passed | Failed | Skipped | Result |
| :--- | :--- | ---: | ---: | ---: | :---: |
| Windows Server 2022 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43737099177) |
| Windows Server 2025 | Native x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43737099177) |
| Windows 11 on Arm | x64 emulation | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43737099177) |
| Ubuntu 24.04 | Wine x64 | — | — | — | [No report](https://github.com/veriepicc/Sable/actions/runs/43737099177) |

Results: [CI run](https://github.com/veriepicc/Sable/actions/runs/43737099177) · Source: `186bbcdf8f67`.
