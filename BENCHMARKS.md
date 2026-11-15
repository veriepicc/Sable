# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 9V45 96-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **3.20 ms** | 23.80 ms | 3.89 ms | 80.03 ms | **Sable** |
| **State Accumulation (50M iter)** | **3.04 ms** | 16.77 ms | 3.97 ms | 51.74 ms | **Sable** |
| **Branch Parity (40M iter)** | **3.14 ms** | 15.73 ms | 14.32 ms | 30.72 ms | **Sable** |
| **General Logic (6M iter)** | 13.71 ms | **12.80 ms** | 14.37 ms | 26.42 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 113.19 ms | 94.68 ms | **88.28 ms** | 170.92 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **24.13 ms** | 102.51 ms | 99.64 ms | 154.21 ms | **Sable** |
| **State SIMD Vector (40M items)** | **24.81 ms** | 143.93 ms | 158.37 ms | 245.55 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **24.86 ms** | 103.84 ms | 105.10 ms | 171.65 ms | **Sable** |
| **General SIMD Vector (20M items)** | **14.85 ms** | 74.12 ms | 83.03 ms | 130.81 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **14.57 ms** | 80.50 ms | 78.70 ms | 136.17 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | **10.3 ms (5.0 KiB)** | 206.9 ms (105.0 KiB) | 3085.8 ms (14.5 KiB) | 11.9 ms (2.5 KiB) |
| **State Accumulation (50M iter)** | **7.5 ms (5.0 KiB)** | 87.0 ms (105.0 KiB) | 78.8 ms (14.5 KiB) | 8.5 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **7.3 ms (5.0 KiB)** | 83.1 ms (105.0 KiB) | 293.8 ms (14.5 KiB) | 9.3 ms (2.5 KiB) |
| **General Logic (6M iter)** | **7.8 ms (5.0 KiB)** | 100.6 ms (105.5 KiB) | 123.2 ms (14.5 KiB) | 8.7 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **8.1 ms (6.0 KiB)** | 131.4 ms (106.0 KiB) | 157.7 ms (15.0 KiB) | 8.2 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **7.5 ms (9.5 KiB)** | 162.6 ms (106.5 KiB) | 208.7 ms (15.0 KiB) | 9.0 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **7.7 ms (8.0 KiB)** | 91.0 ms (106.0 KiB) | 94.8 ms (14.5 KiB) | 9.1 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **8.0 ms (10.5 KiB)** | 98.0 ms (106.5 KiB) | 94.8 ms (15.0 KiB) | 8.8 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **8.0 ms (8.0 KiB)** | 91.9 ms (106.0 KiB) | 93.5 ms (14.5 KiB) | 9.6 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **7.6 ms (10.0 KiB)** | 89.5 ms (107.0 KiB) | 112.2 ms (15.5 KiB) | 8.8 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 9V45 96-Core Processor` | 10ms / **3.20ms** | 7ms / **3.04ms** | 7ms / **3.14ms** | 8ms / **13.71ms** | 8ms / **113.19ms** | 8ms / **24.13ms** | 8ms / **24.81ms** | 8ms / **24.86ms** | 8ms / **14.85ms** | 8ms / **14.57ms** |
| **Windows AMD64** | `AMD EPYC 9V74 80-Core Processor` | 13ms / **2.48ms** | 6ms / **2.46ms** | 6ms / **2.46ms** | 7ms / **19.51ms** | 7ms / **145.61ms** | 7ms / **25.88ms** | 7ms / **25.37ms** | 7ms / **25.32ms** | 6ms / **13.97ms** | 7ms / **14.28ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 119ms / **14.58ms** | 30ms / **14.29ms** | 31ms / **15.33ms** | 41ms / **31.02ms** | 34ms / **212.90ms** | 42ms / **50.12ms** | 29ms / **44.87ms** | 29ms / **54.36ms** | 27ms / **30.06ms** | 30ms / **33.50ms** |
| **Linux x86_64** | `Intel(R) Xeon(R) 6975P-C` | 18ms / **14.40ms** | 21ms / **10.37ms** | 20ms / **9.27ms** | 28ms / **18.86ms** | 25ms / **137.87ms** | 23ms / **75.20ms** | 20ms / **75.21ms** | 23ms / **76.86ms** | 15ms / **41.34ms** | 22ms / **47.92ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43737982009) · Source: `d04ca899f85d`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

