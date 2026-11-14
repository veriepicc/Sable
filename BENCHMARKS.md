# Benchmark Showdown

- **Date:** 2026-11-14
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 7763 64-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX2 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.89 ms** | 31.93 ms | 6.40 ms | 131.94 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.98 ms** | 22.84 ms | 6.62 ms | 84.74 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.59 ms** | 31.71 ms | 20.94 ms | 51.76 ms | **Sable** |
| **General Logic (6M iter)** | 24.46 ms | **20.13 ms** | 20.66 ms | 48.90 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 191.97 ms | 141.48 ms | **132.40 ms** | 401.62 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **49.06 ms** | 138.88 ms | 136.58 ms | 213.94 ms | **Sable** |
| **State SIMD Vector (40M items)** | **48.72 ms** | 202.06 ms | 207.00 ms | 361.07 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **49.86 ms** | 153.13 ms | 142.36 ms | 251.64 ms | **Sable** |
| **General SIMD Vector (20M items)** | **27.56 ms** | 109.82 ms | 107.82 ms | 196.55 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **27.86 ms** | 112.93 ms | 110.24 ms | 198.74 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX2`) | GCC (`-O3 -march=native`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 18.4 ms (5.0 KiB) | 245.4 ms (105.0 KiB) | 3296.7 ms (14.5 KiB) | **16.8 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **10.0 ms (5.0 KiB)** | 131.6 ms (105.0 KiB) | 116.1 ms (14.5 KiB) | 12.1 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **9.8 ms (5.0 KiB)** | 112.0 ms (105.0 KiB) | 323.5 ms (14.5 KiB) | 12.4 ms (2.5 KiB) |
| **General Logic (6M iter)** | **10.2 ms (5.0 KiB)** | 146.9 ms (105.5 KiB) | 168.7 ms (14.5 KiB) | 12.0 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **11.0 ms (6.0 KiB)** | 153.5 ms (106.0 KiB) | 213.1 ms (15.0 KiB) | 12.5 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **10.5 ms (9.5 KiB)** | 195.6 ms (106.0 KiB) | 244.1 ms (15.0 KiB) | 12.1 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **9.8 ms (8.0 KiB)** | 125.7 ms (106.0 KiB) | 132.3 ms (14.5 KiB) | 11.9 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **10.4 ms (10.5 KiB)** | 138.2 ms (106.0 KiB) | 138.2 ms (15.0 KiB) | 12.6 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | 12.4 ms (8.0 KiB) | 121.9 ms (106.0 KiB) | 127.7 ms (14.5 KiB) | **12.2 ms (2.5 KiB)** |
| **HFT SIMD Vector (20M items)** | **10.4 ms (10.0 KiB)** | 123.0 ms (106.5 KiB) | 137.0 ms (15.0 KiB) | 13.1 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 18ms / **4.89ms** | 10ms / **4.98ms** | 10ms / **4.59ms** | 10ms / **24.46ms** | 11ms / **191.97ms** | 10ms / **49.06ms** | 10ms / **48.72ms** | 10ms / **49.86ms** | 12ms / **27.56ms** | 10ms / **27.86ms** |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 14ms / **3.14ms** | 7ms / **3.07ms** | 7ms / **3.07ms** | 8ms / **22.28ms** | 9ms / **187.45ms** | 7ms / **45.19ms** | 7ms / **41.26ms** | 8ms / **41.55ms** | 8ms / **25.71ms** | 8ms / **24.86ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 120ms / **14.95ms** | 31ms / **14.88ms** | 29ms / **14.73ms** | 39ms / **31.23ms** | 33ms / **211.12ms** | 41ms / **48.44ms** | 31ms / **45.61ms** | 29ms / **54.62ms** | 33ms / **31.13ms** | 31ms / **34.03ms** |
| **Linux x86_64** | `Intel(R) Xeon(R) 6975P-C` | 21ms / **13.28ms** | 23ms / **11.54ms** | 12ms / **7.15ms** | 12ms / **18.66ms** | 23ms / **138.55ms** | 20ms / **76.04ms** | 15ms / **75.53ms** | 22ms / **73.42ms** | 12ms / **42.48ms** | 15ms / **43.52ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43642425574) · Source: `d2b6f85d0c31`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

