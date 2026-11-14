# Benchmark Showdown

- **Date:** 2026-11-14
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 9V45 96-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **3.28 ms** | 23.21 ms | 3.70 ms | 79.45 ms | **Sable** |
| **State Accumulation (50M iter)** | **2.86 ms** | 16.13 ms | 4.30 ms | 49.76 ms | **Sable** |
| **Branch Parity (40M iter)** | **2.80 ms** | 13.46 ms | 13.58 ms | 30.04 ms | **Sable** |
| **General Logic (6M iter)** | 13.72 ms | **10.95 ms** | 12.54 ms | 25.18 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 107.95 ms | 91.82 ms | **86.97 ms** | 163.03 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **24.01 ms** | 100.22 ms | 101.17 ms | 145.00 ms | **Sable** |
| **State SIMD Vector (40M items)** | **24.76 ms** | 138.36 ms | 153.77 ms | 235.53 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **23.79 ms** | 101.84 ms | 100.55 ms | 164.51 ms | **Sable** |
| **General SIMD Vector (20M items)** | **14.49 ms** | 73.59 ms | 78.31 ms | 126.80 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **12.55 ms** | 78.84 ms | 78.01 ms | 128.94 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 13.9 ms (5.0 KiB) | 224.1 ms (105.0 KiB) | 4291.3 ms (14.5 KiB) | **10.9 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **7.1 ms (5.0 KiB)** | 109.6 ms (105.0 KiB) | 82.8 ms (14.5 KiB) | 8.6 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **6.8 ms (5.0 KiB)** | 79.1 ms (105.0 KiB) | 388.5 ms (14.5 KiB) | 7.8 ms (2.5 KiB) |
| **General Logic (6M iter)** | 7.8 ms (5.0 KiB) | 97.1 ms (105.5 KiB) | 152.3 ms (14.5 KiB) | **7.1 ms (2.5 KiB)** |
| **HFT Order Book (12M iter)** | **8.0 ms (6.0 KiB)** | 146.0 ms (106.0 KiB) | 163.6 ms (15.0 KiB) | 8.3 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **7.3 ms (9.5 KiB)** | 162.7 ms (106.5 KiB) | 208.3 ms (15.0 KiB) | 8.3 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **7.6 ms (8.0 KiB)** | 86.7 ms (106.0 KiB) | 88.6 ms (14.5 KiB) | 8.7 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **7.5 ms (10.5 KiB)** | 108.5 ms (106.5 KiB) | 82.1 ms (15.0 KiB) | 8.5 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **7.6 ms (8.0 KiB)** | 86.8 ms (106.0 KiB) | 87.6 ms (14.5 KiB) | 9.2 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | 9.2 ms (10.0 KiB) | 97.2 ms (107.0 KiB) | 81.8 ms (15.5 KiB) | **8.9 ms (2.5 KiB)** |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 9V45 96-Core Processor` | 14ms / **3.28ms** | 7ms / **2.86ms** | 7ms / **2.80ms** | 8ms / **13.72ms** | 8ms / **107.95ms** | 7ms / **24.01ms** | 8ms / **24.76ms** | 7ms / **23.79ms** | 8ms / **14.49ms** | 9ms / **12.55ms** |
| **Windows AMD64** | `INTEL(R) XEON(R) PLATINUM 8573C` | 10ms / **3.31ms** | 7ms / **3.33ms** | 7ms / **3.24ms** | 8ms / **22.00ms** | 8ms / **179.83ms** | 8ms / **38.47ms** | 8ms / **39.77ms** | 8ms / **43.73ms** | 8ms / **23.36ms** | 8ms / **23.40ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 145ms / **15.68ms** | 31ms / **14.90ms** | 31ms / **14.58ms** | 40ms / **31.32ms** | 33ms / **211.61ms** | 41ms / **50.61ms** | 31ms / **45.64ms** | 35ms / **55.35ms** | 31ms / **30.66ms** | 31ms / **34.77ms** |
| **Linux x86_64** | `Intel(R) Xeon(R) 6975P-C` | 19ms / **7.67ms** | 13ms / **9.92ms** | 14ms / **13.25ms** | 23ms / **18.71ms** | 15ms / **140.62ms** | 25ms / **78.92ms** | 22ms / **83.25ms** | 13ms / **75.71ms** | 23ms / **41.58ms** | 23ms / **42.68ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43655116196) · Source: `fd983437f5d2`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

