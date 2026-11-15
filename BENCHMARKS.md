# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `INTEL(R) XEON(R) PLATINUM 8573C`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.87 ms** | 20.39 ms | 5.96 ms | 110.14 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.52 ms** | 22.84 ms | 5.83 ms | 69.87 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.71 ms** | 33.10 ms | 19.72 ms | 64.52 ms | **Sable** |
| **General Logic (6M iter)** | 24.13 ms | 19.65 ms | **15.71 ms** | 41.47 ms | **GCC** |
| **HFT Order Book (12M iter)** | 188.47 ms | 129.21 ms | **122.34 ms** | 268.33 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **47.86 ms** | 238.85 ms | 236.93 ms | 297.64 ms | **Sable** |
| **State SIMD Vector (40M items)** | **47.82 ms** | 369.70 ms | 357.79 ms | 467.19 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **47.39 ms** | 240.45 ms | 236.56 ms | 311.01 ms | **Sable** |
| **General SIMD Vector (20M items)** | **26.35 ms** | 187.76 ms | 179.28 ms | 242.23 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **26.00 ms** | 177.43 ms | 179.39 ms | 235.78 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | **13.1 ms (5.0 KiB)** | 229.6 ms (105.0 KiB) | 3245.3 ms (14.5 KiB) | 16.1 ms (2.5 KiB) |
| **State Accumulation (50M iter)** | **9.3 ms (5.0 KiB)** | 109.8 ms (105.0 KiB) | 110.8 ms (14.5 KiB) | 10.9 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **10.1 ms (5.0 KiB)** | 114.5 ms (105.0 KiB) | 341.0 ms (14.5 KiB) | 11.2 ms (2.5 KiB) |
| **General Logic (6M iter)** | **9.7 ms (5.0 KiB)** | 125.4 ms (105.5 KiB) | 165.4 ms (14.5 KiB) | 11.1 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **10.5 ms (6.0 KiB)** | 157.0 ms (106.0 KiB) | 215.1 ms (15.0 KiB) | 11.5 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **9.7 ms (9.5 KiB)** | 191.2 ms (106.5 KiB) | 237.1 ms (15.0 KiB) | 11.3 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **10.1 ms (8.0 KiB)** | 121.1 ms (106.0 KiB) | 128.0 ms (14.5 KiB) | 12.6 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **10.0 ms (10.5 KiB)** | 128.6 ms (106.5 KiB) | 125.7 ms (15.0 KiB) | 11.5 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **9.8 ms (8.0 KiB)** | 115.3 ms (106.0 KiB) | 121.6 ms (14.5 KiB) | 11.4 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **9.8 ms (10.0 KiB)** | 121.1 ms (107.0 KiB) | 130.4 ms (15.5 KiB) | 11.7 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `INTEL(R) XEON(R) PLATINUM 8573C` | 13ms / **4.87ms** | 9ms / **4.52ms** | 10ms / **4.71ms** | 10ms / **24.13ms** | 10ms / **188.47ms** | 10ms / **47.86ms** | 10ms / **47.82ms** | 10ms / **47.39ms** | 10ms / **26.35ms** | 10ms / **26.00ms** |
| **Windows AMD64** | `AMD EPYC 9V45 96-Core Processor` | 7ms / **2.11ms** | 6ms / **2.07ms** | 5ms / **2.10ms** | 6ms / **12.36ms** | 6ms / **112.02ms** | 6ms / **18.05ms** | 6ms / **20.50ms** | 6ms / **21.15ms** | 6ms / **12.53ms** | 6ms / **11.66ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 127ms / **13.87ms** | 28ms / **13.76ms** | 29ms / **13.85ms** | 39ms / **29.25ms** | 31ms / **210.82ms** | 40ms / **48.19ms** | 29ms / **44.84ms** | 29ms / **53.86ms** | 28ms / **30.09ms** | 28ms / **33.59ms** |
| **Linux x86_64** | `AMD EPYC 7763 64-Core Processor` | 32ms / **23.80ms** | 35ms / **22.71ms** | 34ms / **22.68ms** | 37ms / **46.74ms** | 32ms / **207.81ms** | 32ms / **106.90ms** | 33ms / **108.17ms** | 31ms / **107.11ms** | 32ms / **66.95ms** | 33ms / **65.23ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43720743159) · Source: `aefb6159240a`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

