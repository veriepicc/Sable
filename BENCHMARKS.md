# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 7763 64-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX2 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.47 ms** | 31.48 ms | 5.59 ms | 131.22 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.42 ms** | 21.56 ms | 5.54 ms | 84.68 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.25 ms** | 30.86 ms | 19.84 ms | 51.15 ms | **Sable** |
| **General Logic (6M iter)** | 23.48 ms | **18.90 ms** | 19.43 ms | 47.96 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 190.94 ms | 141.44 ms | **131.35 ms** | 400.73 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **45.41 ms** | 131.14 ms | 132.33 ms | 211.42 ms | **Sable** |
| **State SIMD Vector (40M items)** | **45.74 ms** | 192.00 ms | 199.35 ms | 346.21 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **45.67 ms** | 142.87 ms | 133.67 ms | 239.88 ms | **Sable** |
| **General SIMD Vector (20M items)** | **24.56 ms** | 104.52 ms | 101.84 ms | 190.47 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **25.08 ms** | 105.22 ms | 102.30 ms | 191.59 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX2`) | GCC (`-O3 -march=native`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 17.8 ms (5.0 KiB) | 245.2 ms (105.0 KiB) | 3470.9 ms (14.5 KiB) | **16.5 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **9.4 ms (5.0 KiB)** | 107.7 ms (105.0 KiB) | 113.1 ms (14.5 KiB) | 11.2 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **9.3 ms (5.0 KiB)** | 114.7 ms (105.0 KiB) | 327.8 ms (14.5 KiB) | 10.8 ms (2.5 KiB) |
| **General Logic (6M iter)** | **9.6 ms (5.0 KiB)** | 130.4 ms (105.5 KiB) | 171.0 ms (14.5 KiB) | 11.5 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **10.1 ms (6.0 KiB)** | 149.1 ms (106.0 KiB) | 206.1 ms (15.0 KiB) | 11.0 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **9.5 ms (9.5 KiB)** | 187.1 ms (106.0 KiB) | 233.4 ms (15.0 KiB) | 11.5 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **10.4 ms (8.0 KiB)** | 120.2 ms (106.0 KiB) | 130.9 ms (14.5 KiB) | 11.8 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **9.4 ms (10.5 KiB)** | 126.4 ms (106.0 KiB) | 126.9 ms (15.0 KiB) | 11.2 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **10.8 ms (8.0 KiB)** | 119.6 ms (106.0 KiB) | 120.2 ms (14.5 KiB) | 11.3 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **9.5 ms (10.0 KiB)** | 114.7 ms (106.5 KiB) | 125.8 ms (15.0 KiB) | 11.1 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 18ms / **4.47ms** | 9ms / **4.42ms** | 9ms / **4.25ms** | 10ms / **23.48ms** | 10ms / **190.94ms** | 10ms / **45.41ms** | 10ms / **45.74ms** | 9ms / **45.67ms** | 11ms / **24.56ms** | 10ms / **25.08ms** |
| **Windows AMD64** | `AMD EPYC 9V74 80-Core Processor` | 11ms / **2.52ms** | 6ms / **2.38ms** | 6ms / **2.42ms** | 6ms / **19.46ms** | 7ms / **145.98ms** | 6ms / **24.48ms** | 6ms / **24.62ms** | 6ms / **24.58ms** | 6ms / **13.65ms** | 6ms / **13.63ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 148ms / **15.14ms** | 31ms / **14.71ms** | 30ms / **14.76ms** | 41ms / **31.32ms** | 35ms / **211.75ms** | 45ms / **50.21ms** | 31ms / **46.05ms** | 31ms / **54.56ms** | 31ms / **31.45ms** | 31ms / **34.18ms** |
| **Linux x86_64** | `AMD EPYC 9V45 96-Core Processor` | 24ms / **17.34ms** | 25ms / **17.05ms** | 24ms / **17.96ms** | 24ms / **28.57ms** | 77ms / **128.55ms** | 117ms / **73.08ms** | 24ms / **73.30ms** | 25ms / **73.24ms** | 27ms / **45.93ms** | 24ms / **45.27ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43717993123) · Source: `c542d5a8aab3`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

