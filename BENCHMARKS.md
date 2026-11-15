# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 9V74 80-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.22 ms** | 27.44 ms | 4.53 ms | 114.92 ms | **Sable** |
| **State Accumulation (50M iter)** | **3.53 ms** | 19.22 ms | 4.56 ms | 73.73 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.06 ms** | 27.63 ms | 18.06 ms | 40.45 ms | **Sable** |
| **General Logic (6M iter)** | 21.06 ms | **17.07 ms** | 17.32 ms | 38.70 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 148.58 ms | 120.43 ms | **117.34 ms** | 258.62 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **27.34 ms** | 122.71 ms | 122.18 ms | 184.59 ms | **Sable** |
| **State SIMD Vector (40M items)** | **26.97 ms** | 181.17 ms | 189.63 ms | 322.14 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **26.93 ms** | 123.21 ms | 124.06 ms | 211.12 ms | **Sable** |
| **General SIMD Vector (20M items)** | **15.97 ms** | 93.95 ms | 97.26 ms | 174.30 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **16.00 ms** | 95.54 ms | 96.12 ms | 175.28 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 18.6 ms (5.0 KiB) | 283.2 ms (105.0 KiB) | 4318.0 ms (14.5 KiB) | **13.2 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **7.7 ms (5.0 KiB)** | 105.2 ms (105.0 KiB) | 91.9 ms (14.5 KiB) | 10.4 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **7.9 ms (5.0 KiB)** | 99.2 ms (105.0 KiB) | 361.0 ms (14.5 KiB) | 9.7 ms (2.5 KiB) |
| **General Logic (6M iter)** | **8.7 ms (5.0 KiB)** | 119.9 ms (105.5 KiB) | 189.2 ms (14.5 KiB) | 9.5 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **8.4 ms (6.0 KiB)** | 136.2 ms (106.0 KiB) | 197.8 ms (15.0 KiB) | 9.6 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **8.2 ms (9.5 KiB)** | 211.2 ms (106.5 KiB) | 263.0 ms (15.0 KiB) | 9.5 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **8.3 ms (8.0 KiB)** | 106.5 ms (106.0 KiB) | 110.1 ms (14.5 KiB) | 9.3 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **8.4 ms (10.5 KiB)** | 113.2 ms (106.5 KiB) | 108.9 ms (15.0 KiB) | 9.8 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **8.3 ms (8.0 KiB)** | 102.7 ms (106.0 KiB) | 100.0 ms (14.5 KiB) | 9.9 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **8.1 ms (10.0 KiB)** | 108.1 ms (107.0 KiB) | 108.7 ms (15.5 KiB) | 9.5 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 9V74 80-Core Processor` | 19ms / **4.22ms** | 8ms / **3.53ms** | 8ms / **4.06ms** | 9ms / **21.06ms** | 8ms / **148.58ms** | 8ms / **27.34ms** | 8ms / **26.97ms** | 8ms / **26.93ms** | 8ms / **15.97ms** | 8ms / **16.00ms** |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 10ms / **3.05ms** | 7ms / **3.02ms** | 7ms / **3.00ms** | 7ms / **21.61ms** | 8ms / **186.38ms** | 7ms / **38.62ms** | 7ms / **41.58ms** | 7ms / **36.73ms** | 7ms / **20.79ms** | 7ms / **20.22ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 144ms / **16.49ms** | 36ms / **16.22ms** | 30ms / **15.99ms** | 41ms / **31.98ms** | 36ms / **212.67ms** | 44ms / **57.33ms** | 31ms / **47.90ms** | 32ms / **55.95ms** | 32ms / **31.98ms** | 32ms / **34.65ms** |
| **Linux x86_64** | `Intel(R) Xeon(R) 6975P-C` | 11ms / **10.80ms** | 20ms / **14.39ms** | 22ms / **14.96ms** | 23ms / **19.56ms** | 12ms / **144.21ms** | 22ms / **79.66ms** | 13ms / **82.19ms** | 17ms / **76.68ms** | 23ms / **42.62ms** | 18ms / **43.33ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43708605307) · Source: `12dce63c60a1`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

