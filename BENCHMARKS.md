# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 7763 64-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX2 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.42 ms** | 30.95 ms | 5.75 ms | 131.58 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.52 ms** | 21.99 ms | 5.70 ms | 84.90 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.33 ms** | 31.17 ms | 20.11 ms | 51.32 ms | **Sable** |
| **General Logic (6M iter)** | 23.58 ms | **19.34 ms** | 19.58 ms | 48.40 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 192.35 ms | 141.52 ms | **131.56 ms** | 400.49 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **46.10 ms** | 132.84 ms | 133.65 ms | 211.33 ms | **Sable** |
| **State SIMD Vector (40M items)** | **45.66 ms** | 193.55 ms | 200.70 ms | 347.19 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **46.40 ms** | 143.86 ms | 133.61 ms | 242.49 ms | **Sable** |
| **General SIMD Vector (20M items)** | **25.54 ms** | 104.56 ms | 101.50 ms | 190.85 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **25.74 ms** | 106.64 ms | 101.78 ms | 192.59 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX2`) | GCC (`-O3 -march=native`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 20.7 ms (5.0 KiB) | 247.9 ms (105.0 KiB) | 3898.2 ms (14.5 KiB) | **15.6 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **9.4 ms (5.0 KiB)** | 114.0 ms (105.0 KiB) | 112.7 ms (14.5 KiB) | 11.0 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **9.7 ms (5.0 KiB)** | 107.2 ms (105.0 KiB) | 381.0 ms (14.5 KiB) | 12.0 ms (2.5 KiB) |
| **General Logic (6M iter)** | **9.4 ms (5.0 KiB)** | 136.0 ms (105.5 KiB) | 168.8 ms (14.5 KiB) | 11.1 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **10.6 ms (6.0 KiB)** | 152.4 ms (106.0 KiB) | 218.6 ms (15.0 KiB) | 11.4 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **10.1 ms (9.5 KiB)** | 192.8 ms (106.0 KiB) | 252.0 ms (15.0 KiB) | 11.6 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **9.6 ms (8.0 KiB)** | 118.7 ms (106.0 KiB) | 132.0 ms (14.5 KiB) | 11.7 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **9.7 ms (10.5 KiB)** | 137.7 ms (106.0 KiB) | 128.4 ms (15.0 KiB) | 11.5 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **9.5 ms (8.0 KiB)** | 115.4 ms (106.0 KiB) | 122.8 ms (14.5 KiB) | 11.3 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **9.9 ms (10.0 KiB)** | 123.3 ms (106.5 KiB) | 130.0 ms (15.0 KiB) | 11.3 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 21ms / **4.42ms** | 9ms / **4.52ms** | 10ms / **4.33ms** | 9ms / **23.58ms** | 11ms / **192.35ms** | 10ms / **46.10ms** | 10ms / **45.66ms** | 10ms / **46.40ms** | 9ms / **25.54ms** | 10ms / **25.74ms** |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 10ms / **3.19ms** | 7ms / **3.28ms** | 8ms / **3.27ms** | 8ms / **22.62ms** | 8ms / **187.24ms** | 8ms / **39.89ms** | 7ms / **43.56ms** | 8ms / **42.03ms** | 7ms / **23.15ms** | 8ms / **23.79ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 142ms / **13.57ms** | 29ms / **14.03ms** | 28ms / **13.85ms** | 39ms / **29.80ms** | 36ms / **210.50ms** | 40ms / **47.81ms** | 29ms / **44.33ms** | 28ms / **53.23ms** | 28ms / **29.87ms** | 37ms / **32.41ms** |
| **Linux x86_64** | `AMD EPYC 9V45 96-Core Processor` | 37ms / **18.22ms** | 24ms / **18.15ms** | 25ms / **17.94ms** | 29ms / **28.05ms** | 84ms / **126.27ms** | 145ms / **71.97ms** | 25ms / **73.30ms** | 26ms / **73.74ms** | 25ms / **47.19ms** | 24ms / **47.72ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43723357219) · Source: `c66922de33bb`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

