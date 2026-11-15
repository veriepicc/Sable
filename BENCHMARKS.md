# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 9V74 80-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **3.84 ms** | 26.68 ms | 4.39 ms | 114.78 ms | **Sable** |
| **State Accumulation (50M iter)** | **3.86 ms** | 18.73 ms | 4.50 ms | 73.50 ms | **Sable** |
| **Branch Parity (40M iter)** | **3.35 ms** | 27.51 ms | 17.72 ms | 40.26 ms | **Sable** |
| **General Logic (6M iter)** | 20.92 ms | **16.33 ms** | 16.52 ms | 37.95 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 148.33 ms | 120.32 ms | **117.50 ms** | 258.54 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **27.52 ms** | 123.02 ms | 121.74 ms | 184.55 ms | **Sable** |
| **State SIMD Vector (40M items)** | **26.95 ms** | 181.82 ms | 190.41 ms | 323.87 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **26.94 ms** | 121.91 ms | 124.97 ms | 213.13 ms | **Sable** |
| **General SIMD Vector (20M items)** | **15.86 ms** | 93.68 ms | 98.04 ms | 174.12 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **14.95 ms** | 96.35 ms | 96.96 ms | 176.39 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | **11.0 ms (5.0 KiB)** | 215.0 ms (105.0 KiB) | 3391.7 ms (14.5 KiB) | 12.5 ms (2.5 KiB) |
| **State Accumulation (50M iter)** | **7.9 ms (5.0 KiB)** | 91.2 ms (105.0 KiB) | 91.6 ms (14.5 KiB) | 9.0 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **7.9 ms (5.0 KiB)** | 94.3 ms (105.0 KiB) | 291.6 ms (14.5 KiB) | 9.4 ms (2.5 KiB) |
| **General Logic (6M iter)** | 9.8 ms (5.0 KiB) | 103.8 ms (105.5 KiB) | 138.6 ms (14.5 KiB) | **8.7 ms (2.5 KiB)** |
| **HFT Order Book (12M iter)** | **8.3 ms (6.0 KiB)** | 126.1 ms (106.0 KiB) | 234.1 ms (15.0 KiB) | 9.3 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **8.2 ms (9.5 KiB)** | 164.4 ms (106.5 KiB) | 210.2 ms (15.0 KiB) | 9.7 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **8.2 ms (8.0 KiB)** | 101.2 ms (106.0 KiB) | 109.7 ms (14.5 KiB) | 10.0 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **8.4 ms (10.5 KiB)** | 107.6 ms (106.5 KiB) | 104.6 ms (15.0 KiB) | 10.1 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **8.0 ms (8.0 KiB)** | 97.0 ms (106.0 KiB) | 105.0 ms (14.5 KiB) | 9.4 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **7.9 ms (10.0 KiB)** | 103.8 ms (107.0 KiB) | 101.8 ms (15.5 KiB) | 9.6 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 9V74 80-Core Processor` | 11ms / **3.84ms** | 8ms / **3.86ms** | 8ms / **3.35ms** | 10ms / **20.92ms** | 8ms / **148.33ms** | 8ms / **27.52ms** | 8ms / **26.95ms** | 8ms / **26.94ms** | 8ms / **15.86ms** | 8ms / **14.95ms** |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 17ms / **3.33ms** | 9ms / **3.33ms** | 7ms / **3.25ms** | 9ms / **22.55ms** | 9ms / **196.08ms** | 8ms / **46.59ms** | 8ms / **45.49ms** | 8ms / **40.11ms** | 8ms / **25.06ms** | 8ms / **24.70ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 102ms / **13.74ms** | 30ms / **13.88ms** | 30ms / **14.77ms** | 39ms / **29.74ms** | 32ms / **211.21ms** | 42ms / **55.08ms** | 28ms / **46.09ms** | 30ms / **54.78ms** | 30ms / **30.36ms** | 29ms / **34.26ms** |
| **Linux x86_64** | `AMD EPYC 9V74 80-Core Processor` | 28ms / **19.77ms** | 26ms / **19.04ms** | 38ms / **19.55ms** | 65ms / **34.85ms** | 64ms / **162.35ms** | 25ms / **77.97ms** | 26ms / **78.96ms** | 27ms / **75.26ms** | 26ms / **48.24ms** | 28ms / **49.33ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43718567943) · Source: `3e5ae0f247bf`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

