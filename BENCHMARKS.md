# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `INTEL(R) XEON(R) PLATINUM 8573C`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.33 ms** | 19.71 ms | 5.72 ms | 107.64 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.39 ms** | 22.32 ms | 5.82 ms | 64.69 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.64 ms** | 32.90 ms | 19.16 ms | 63.07 ms | **Sable** |
| **General Logic (6M iter)** | 24.00 ms | 19.59 ms | **15.37 ms** | 40.34 ms | **GCC** |
| **HFT Order Book (12M iter)** | 185.03 ms | 127.59 ms | **120.37 ms** | 266.32 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **47.37 ms** | 237.39 ms | 235.67 ms | 292.40 ms | **Sable** |
| **State SIMD Vector (40M items)** | **47.05 ms** | 367.48 ms | 355.66 ms | 517.95 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **48.07 ms** | 240.68 ms | 236.21 ms | 311.59 ms | **Sable** |
| **General SIMD Vector (20M items)** | **26.28 ms** | 185.10 ms | 179.70 ms | 238.86 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **27.00 ms** | 179.04 ms | 180.17 ms | 233.16 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 18.7 ms (5.0 KiB) | 261.6 ms (105.0 KiB) | 4188.5 ms (14.5 KiB) | **14.8 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **9.7 ms (5.0 KiB)** | 114.2 ms (105.0 KiB) | 113.5 ms (14.5 KiB) | 11.5 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **9.2 ms (5.0 KiB)** | 116.0 ms (105.0 KiB) | 375.4 ms (14.5 KiB) | 10.9 ms (2.5 KiB) |
| **General Logic (6M iter)** | **9.6 ms (5.0 KiB)** | 129.9 ms (105.5 KiB) | 172.0 ms (14.5 KiB) | 11.0 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **10.7 ms (6.0 KiB)** | 160.0 ms (106.0 KiB) | 250.2 ms (15.0 KiB) | 11.5 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **9.7 ms (9.5 KiB)** | 209.3 ms (106.5 KiB) | 263.3 ms (15.0 KiB) | 11.4 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **9.5 ms (8.0 KiB)** | 119.3 ms (106.0 KiB) | 130.7 ms (14.5 KiB) | 11.5 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **11.4 ms (10.5 KiB)** | 137.2 ms (106.5 KiB) | 125.9 ms (15.0 KiB) | 11.8 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **9.9 ms (8.0 KiB)** | 115.0 ms (106.0 KiB) | 121.0 ms (14.5 KiB) | 11.6 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **9.8 ms (10.0 KiB)** | 124.9 ms (107.0 KiB) | 128.2 ms (15.5 KiB) | 11.4 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `INTEL(R) XEON(R) PLATINUM 8573C` | 19ms / **4.33ms** | 10ms / **4.39ms** | 9ms / **4.64ms** | 10ms / **24.00ms** | 11ms / **185.03ms** | 10ms / **47.37ms** | 9ms / **47.05ms** | 11ms / **48.07ms** | 10ms / **26.28ms** | 10ms / **27.00ms** |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 18ms / **3.06ms** | 7ms / **3.17ms** | 7ms / **3.01ms** | 8ms / **22.14ms** | 8ms / **187.22ms** | 8ms / **42.24ms** | 7ms / **42.21ms** | 7ms / **37.00ms** | 7ms / **20.41ms** | 8ms / **20.33ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 145ms / **14.84ms** | 29ms / **14.66ms** | 30ms / **14.77ms** | 40ms / **30.49ms** | 33ms / **210.96ms** | 40ms / **48.46ms** | 30ms / **45.30ms** | 29ms / **54.16ms** | 29ms / **29.95ms** | 29ms / **33.99ms** |
| **Linux x86_64** | `AMD EPYC 7763 64-Core Processor` | 30ms / **25.45ms** | 76ms / **22.61ms** | 31ms / **26.09ms** | 32ms / **41.48ms** | 34ms / **208.03ms** | 31ms / **108.36ms** | 37ms / **110.56ms** | 31ms / **109.40ms** | 35ms / **67.11ms** | 31ms / **68.10ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43717497981) · Source: `2fb45a7057a6`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

