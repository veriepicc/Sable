# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `INTEL(R) XEON(R) PLATINUM 8573C`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.69 ms** | 20.26 ms | 5.96 ms | 106.72 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.75 ms** | 23.03 ms | 6.23 ms | 62.66 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.58 ms** | 33.01 ms | 20.10 ms | 61.77 ms | **Sable** |
| **General Logic (6M iter)** | 24.08 ms | 19.88 ms | **15.97 ms** | 40.65 ms | **GCC** |
| **HFT Order Book (12M iter)** | 183.58 ms | 127.08 ms | **119.74 ms** | 262.71 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **47.96 ms** | 240.14 ms | 239.34 ms | 291.02 ms | **Sable** |
| **State SIMD Vector (40M items)** | **47.73 ms** | 368.27 ms | 358.52 ms | 451.28 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **47.63 ms** | 241.37 ms | 239.34 ms | 308.97 ms | **Sable** |
| **General SIMD Vector (20M items)** | **26.26 ms** | 188.15 ms | 183.29 ms | 237.11 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **26.28 ms** | 181.36 ms | 180.90 ms | 231.12 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 17.8 ms (5.0 KiB) | 308.6 ms (105.0 KiB) | 2794.5 ms (14.5 KiB) | **15.6 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **9.4 ms (5.0 KiB)** | 111.1 ms (105.0 KiB) | 113.0 ms (14.5 KiB) | 11.4 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **9.7 ms (5.0 KiB)** | 112.0 ms (105.0 KiB) | 302.4 ms (14.5 KiB) | 11.5 ms (2.5 KiB) |
| **General Logic (6M iter)** | **10.3 ms (5.0 KiB)** | 125.0 ms (105.5 KiB) | 159.3 ms (14.5 KiB) | 11.6 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **11.1 ms (6.0 KiB)** | 151.5 ms (106.0 KiB) | 214.9 ms (15.0 KiB) | 11.8 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **10.2 ms (9.5 KiB)** | 180.7 ms (106.5 KiB) | 223.6 ms (15.0 KiB) | 11.5 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **10.1 ms (8.0 KiB)** | 116.3 ms (106.0 KiB) | 127.5 ms (14.5 KiB) | 11.4 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **10.0 ms (10.5 KiB)** | 127.9 ms (106.5 KiB) | 139.2 ms (15.0 KiB) | 11.4 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **9.8 ms (8.0 KiB)** | 121.4 ms (106.0 KiB) | 122.1 ms (14.5 KiB) | 11.4 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **10.0 ms (10.0 KiB)** | 120.0 ms (107.0 KiB) | 127.0 ms (15.5 KiB) | 11.6 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `INTEL(R) XEON(R) PLATINUM 8573C` | 18ms / **4.69ms** | 9ms / **4.75ms** | 10ms / **4.58ms** | 10ms / **24.08ms** | 11ms / **183.58ms** | 10ms / **47.96ms** | 10ms / **47.73ms** | 10ms / **47.63ms** | 10ms / **26.26ms** | 10ms / **26.28ms** |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 10ms / **3.12ms** | 7ms / **3.09ms** | 7ms / **3.06ms** | 7ms / **21.68ms** | 8ms / **186.89ms** | 7ms / **41.62ms** | 7ms / **44.12ms** | 7ms / **44.26ms** | 7ms / **23.61ms** | 7ms / **23.64ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 123ms / **15.59ms** | 32ms / **15.46ms** | 30ms / **14.83ms** | 42ms / **31.50ms** | 36ms / **212.98ms** | 43ms / **49.52ms** | 30ms / **44.63ms** | 30ms / **54.69ms** | 37ms / **31.44ms** | 31ms / **34.22ms** |
| **Linux x86_64** | `Intel(R) Xeon(R) 6975P-C` | 22ms / **14.84ms** | 21ms / **7.06ms** | 14ms / **7.87ms** | 13ms / **19.18ms** | 23ms / **144.36ms** | 20ms / **74.03ms** | 22ms / **78.13ms** | 25ms / **75.13ms** | 12ms / **41.40ms** | 19ms / **40.94ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43744268736) · Source: `7c42a9e7db93`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

