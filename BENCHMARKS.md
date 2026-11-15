# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 7763 64-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX2 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.49 ms** | 31.55 ms | 5.89 ms | 131.90 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.53 ms** | 21.88 ms | 5.96 ms | 85.03 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.62 ms** | 31.50 ms | 20.44 ms | 60.16 ms | **Sable** |
| **General Logic (6M iter)** | 24.21 ms | **19.78 ms** | 20.30 ms | 48.57 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 191.27 ms | 141.51 ms | **131.70 ms** | 401.00 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **48.11 ms** | 134.85 ms | 136.85 ms | 213.21 ms | **Sable** |
| **State SIMD Vector (40M items)** | **47.74 ms** | 197.67 ms | 201.22 ms | 348.50 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **48.26 ms** | 144.30 ms | 135.11 ms | 243.62 ms | **Sable** |
| **General SIMD Vector (20M items)** | **27.00 ms** | 106.50 ms | 105.38 ms | 192.01 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **26.15 ms** | 108.53 ms | 105.36 ms | 195.45 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX2`) | GCC (`-O3 -march=native`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | **13.3 ms (5.0 KiB)** | 240.8 ms (105.0 KiB) | 3516.4 ms (14.5 KiB) | 16.3 ms (2.5 KiB) |
| **State Accumulation (50M iter)** | **10.7 ms (5.0 KiB)** | 109.8 ms (105.0 KiB) | 114.0 ms (14.5 KiB) | 11.3 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **10.4 ms (5.0 KiB)** | 109.5 ms (105.0 KiB) | 359.0 ms (14.5 KiB) | 11.4 ms (2.5 KiB) |
| **General Logic (6M iter)** | **10.6 ms (5.0 KiB)** | 143.9 ms (105.5 KiB) | 190.2 ms (14.5 KiB) | 17.4 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **10.7 ms (6.0 KiB)** | 153.7 ms (106.0 KiB) | 215.3 ms (15.0 KiB) | 11.6 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **9.6 ms (9.5 KiB)** | 266.2 ms (106.0 KiB) | 240.7 ms (15.0 KiB) | 12.3 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **9.6 ms (8.0 KiB)** | 120.3 ms (106.0 KiB) | 140.0 ms (14.5 KiB) | 11.5 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **9.8 ms (10.5 KiB)** | 138.2 ms (106.0 KiB) | 134.8 ms (15.0 KiB) | 11.9 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **9.6 ms (8.0 KiB)** | 120.5 ms (106.0 KiB) | 125.1 ms (14.5 KiB) | 11.9 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **9.5 ms (10.0 KiB)** | 121.0 ms (106.5 KiB) | 128.3 ms (15.0 KiB) | 11.7 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 13ms / **4.49ms** | 11ms / **4.53ms** | 10ms / **4.62ms** | 11ms / **24.21ms** | 11ms / **191.27ms** | 10ms / **48.11ms** | 10ms / **47.74ms** | 10ms / **48.26ms** | 10ms / **27.00ms** | 9ms / **26.15ms** |
| **Windows AMD64** | `INTEL(R) XEON(R) PLATINUM 8573C` | 11ms / **3.49ms** | 8ms / **3.55ms** | 11ms / **3.45ms** | 8ms / **23.00ms** | 9ms / **179.14ms** | 8ms / **40.27ms** | 8ms / **44.38ms** | 8ms / **45.20ms** | 8ms / **25.23ms** | 8ms / **24.92ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 130ms / **16.84ms** | 34ms / **16.76ms** | 33ms / **16.72ms** | 44ms / **32.85ms** | 37ms / **212.66ms** | 45ms / **52.30ms** | 32ms / **47.53ms** | 33ms / **57.56ms** | 32ms / **32.61ms** | 35ms / **36.45ms** |
| **Linux x86_64** | `AMD EPYC 7763 64-Core Processor` | 30ms / **22.17ms** | 31ms / **22.13ms** | 31ms / **22.51ms** | 50ms / **41.48ms** | 37ms / **207.52ms** | 32ms / **109.96ms** | 33ms / **107.98ms** | 36ms / **107.00ms** | 30ms / **66.77ms** | 37ms / **66.91ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43715440225) · Source: `7ec71b14cc04`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

