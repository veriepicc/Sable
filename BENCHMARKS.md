# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 9V45 96-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **3.54 ms** | 24.66 ms | 4.44 ms | 82.26 ms | **Sable** |
| **State Accumulation (50M iter)** | **3.18 ms** | 17.16 ms | 4.40 ms | 52.85 ms | **Sable** |
| **Branch Parity (40M iter)** | **3.37 ms** | 15.84 ms | 15.02 ms | 30.98 ms | **Sable** |
| **General Logic (6M iter)** | 14.64 ms | **13.61 ms** | 14.80 ms | 27.58 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 117.93 ms | 97.01 ms | **92.16 ms** | 177.22 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **26.66 ms** | 108.67 ms | 110.35 ms | 168.59 ms | **Sable** |
| **State SIMD Vector (40M items)** | **27.24 ms** | 153.17 ms | 162.03 ms | 273.61 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **27.35 ms** | 111.95 ms | 111.68 ms | 181.80 ms | **Sable** |
| **General SIMD Vector (20M items)** | **15.70 ms** | 80.11 ms | 85.67 ms | 149.47 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **15.70 ms** | 85.30 ms | 85.14 ms | 144.98 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 16.0 ms (5.0 KiB) | 229.3 ms (105.0 KiB) | 3636.8 ms (14.5 KiB) | **13.1 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **7.9 ms (5.0 KiB)** | 98.3 ms (105.0 KiB) | 86.7 ms (14.5 KiB) | 8.9 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **7.7 ms (5.0 KiB)** | 90.3 ms (105.0 KiB) | 326.3 ms (14.5 KiB) | 9.4 ms (2.5 KiB) |
| **General Logic (6M iter)** | **9.3 ms (5.0 KiB)** | 109.9 ms (105.5 KiB) | 142.3 ms (14.5 KiB) | 9.7 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **8.9 ms (6.0 KiB)** | 131.3 ms (106.0 KiB) | 192.7 ms (15.0 KiB) | 9.8 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **8.6 ms (9.5 KiB)** | 178.2 ms (106.5 KiB) | 219.5 ms (15.0 KiB) | 9.7 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **8.9 ms (8.0 KiB)** | 114.1 ms (106.0 KiB) | 101.6 ms (14.5 KiB) | 9.8 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **8.8 ms (10.5 KiB)** | 115.1 ms (106.5 KiB) | 102.5 ms (15.0 KiB) | 11.2 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **9.4 ms (8.0 KiB)** | 99.6 ms (106.0 KiB) | 100.0 ms (14.5 KiB) | 10.3 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **8.8 ms (10.0 KiB)** | 101.6 ms (107.0 KiB) | 104.8 ms (15.5 KiB) | 9.8 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 9V45 96-Core Processor` | 16ms / **3.54ms** | 8ms / **3.18ms** | 8ms / **3.37ms** | 9ms / **14.64ms** | 9ms / **117.93ms** | 9ms / **26.66ms** | 9ms / **27.24ms** | 9ms / **27.35ms** | 9ms / **15.70ms** | 9ms / **15.70ms** |
| **Windows AMD64** | `AMD EPYC 9V45 96-Core Processor` | 8ms / **2.18ms** | 6ms / **2.07ms** | 6ms / **2.09ms** | 6ms / **12.12ms** | 7ms / **112.32ms** | 6ms / **18.35ms** | 6ms / **21.56ms** | 6ms / **21.23ms** | 6ms / **11.80ms** | 6ms / **10.44ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 121ms / **14.68ms** | 29ms / **14.33ms** | 30ms / **14.23ms** | 40ms / **30.73ms** | 32ms / **212.12ms** | 42ms / **48.58ms** | 28ms / **44.88ms** | 28ms / **52.80ms** | 29ms / **29.87ms** | 29ms / **33.23ms** |
| **Linux x86_64** | `AMD EPYC 7763 64-Core Processor` | 39ms / **23.65ms** | 39ms / **27.69ms** | 36ms / **24.16ms** | 39ms / **43.05ms** | 33ms / **209.08ms** | 38ms / **111.37ms** | 38ms / **110.86ms** | 33ms / **112.38ms** | 38ms / **68.76ms** | 33ms / **69.11ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43737099177) · Source: `186bbcdf8f67`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

