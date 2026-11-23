# Benchmark Showdown

- **Date:** 2026-11-23
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 7763 64-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX2 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.33 ms** | 30.35 ms | 5.61 ms | 130.66 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.33 ms** | 21.01 ms | 5.75 ms | 83.84 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.37 ms** | 30.57 ms | 20.31 ms | 50.48 ms | **Sable** |
| **General Logic (6M iter)** | 23.17 ms | 22.29 ms | **19.24 ms** | 47.49 ms | **GCC** |
| **HFT Order Book (12M iter)** | 191.49 ms | 148.18 ms | **131.56 ms** | 400.72 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **46.73 ms** | 134.53 ms | 135.00 ms | 214.26 ms | **Sable** |
| **State SIMD Vector (40M items)** | **47.13 ms** | 199.06 ms | 207.11 ms | 349.99 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **47.68 ms** | 147.23 ms | 136.88 ms | 244.95 ms | **Sable** |
| **General SIMD Vector (20M items)** | **25.87 ms** | 108.32 ms | 104.87 ms | 193.85 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **26.14 ms** | 109.23 ms | 104.85 ms | 194.90 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX2`) | GCC (`-O3 -march=native`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | **13.9 ms (5.0 KiB)** | 247.7 ms (106.0 KiB) | 3746.8 ms (14.5 KiB) | 15.9 ms (2.5 KiB) |
| **State Accumulation (50M iter)** | **8.6 ms (5.0 KiB)** | 110.4 ms (106.0 KiB) | 110.6 ms (14.5 KiB) | 10.6 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **8.6 ms (5.0 KiB)** | 121.9 ms (106.0 KiB) | 345.8 ms (14.5 KiB) | 10.7 ms (2.5 KiB) |
| **General Logic (6M iter)** | **9.5 ms (5.0 KiB)** | 121.5 ms (106.0 KiB) | 169.5 ms (14.5 KiB) | 10.6 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **9.7 ms (6.0 KiB)** | 132.8 ms (106.5 KiB) | 474.2 ms (15.0 KiB) | 12.5 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **11.0 ms (9.5 KiB)** | 222.3 ms (106.5 KiB) | 261.5 ms (15.0 KiB) | 11.7 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **9.6 ms (8.0 KiB)** | 116.9 ms (106.0 KiB) | 129.0 ms (14.5 KiB) | 12.4 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **9.4 ms (10.5 KiB)** | 135.3 ms (106.5 KiB) | 126.5 ms (15.0 KiB) | 11.4 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **9.4 ms (8.0 KiB)** | 121.2 ms (106.5 KiB) | 126.2 ms (14.5 KiB) | 11.5 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **9.6 ms (10.0 KiB)** | 128.3 ms (106.5 KiB) | 124.5 ms (15.0 KiB) | 11.4 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 14ms / **4.33ms** | 9ms / **4.33ms** | 9ms / **4.37ms** | 10ms / **23.17ms** | 10ms / **191.49ms** | 11ms / **46.73ms** | 10ms / **47.13ms** | 9ms / **47.68ms** | 9ms / **25.87ms** | 10ms / **26.14ms** |
| **Windows AMD64** | `AMD EPYC 9V74 80-Core Processor` | 8ms / **2.45ms** | 6ms / **2.42ms** | 6ms / **2.45ms** | 6ms / **19.02ms** | 7ms / **145.70ms** | 6ms / **23.66ms** | 6ms / **20.32ms** | 6ms / **24.30ms** | 6ms / **13.47ms** | 7ms / **13.77ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 204ms / **15.10ms** | 29ms / **12.91ms** | 28ms / **13.70ms** | 38ms / **29.62ms** | 31ms / **212.06ms** | 39ms / **48.34ms** | 29ms / **45.65ms** | 28ms / **53.75ms** | 29ms / **30.06ms** | 29ms / **33.03ms** |
| **Linux x86_64** | `Intel(R) Xeon(R) 6975P-C` | 22ms / **9.26ms** | 24ms / **15.82ms** | 23ms / **12.19ms** | 14ms / **26.14ms** | 24ms / **141.52ms** | 24ms / **83.49ms** | 24ms / **84.07ms** | 13ms / **83.74ms** | 23ms / **42.90ms** | 13ms / **48.81ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/45182763174) · Source: `9258f21017d5`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

