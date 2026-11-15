# Benchmark Showdown

- **Date:** 2026-11-15
- **Host:** `Windows AMD64`
- **CPU:** `AMD EPYC 9V74 80-Core Processor`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **3.42 ms** | 26.50 ms | 4.45 ms | 114.66 ms | **Sable** |
| **State Accumulation (50M iter)** | **3.39 ms** | 18.17 ms | 4.56 ms | 73.37 ms | **Sable** |
| **Branch Parity (40M iter)** | **3.47 ms** | 26.67 ms | 17.22 ms | 39.73 ms | **Sable** |
| **General Logic (6M iter)** | 20.26 ms | **15.98 ms** | 16.50 ms | 38.19 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 148.29 ms | 119.86 ms | **117.32 ms** | 258.31 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **25.51 ms** | 121.27 ms | 121.06 ms | 183.06 ms | **Sable** |
| **State SIMD Vector (40M items)** | **25.72 ms** | 179.42 ms | 186.46 ms | 322.76 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **25.43 ms** | 122.03 ms | 123.56 ms | 209.66 ms | **Sable** |
| **General SIMD Vector (20M items)** | **14.57 ms** | 92.45 ms | 95.77 ms | 172.90 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **14.97 ms** | 95.80 ms | 96.51 ms | 172.88 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | 32.7 ms (5.0 KiB) | 227.1 ms (105.0 KiB) | 5309.6 ms (14.5 KiB) | **12.0 ms (2.5 KiB)** |
| **State Accumulation (50M iter)** | **7.7 ms (5.0 KiB)** | 94.5 ms (105.0 KiB) | 88.7 ms (14.5 KiB) | 8.6 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **7.7 ms (5.0 KiB)** | 89.6 ms (105.0 KiB) | 372.9 ms (14.5 KiB) | 9.2 ms (2.5 KiB) |
| **General Logic (6M iter)** | **8.0 ms (5.0 KiB)** | 148.5 ms (105.5 KiB) | 167.6 ms (14.5 KiB) | 8.6 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **8.4 ms (6.0 KiB)** | 131.2 ms (106.0 KiB) | 182.1 ms (15.0 KiB) | 9.0 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **7.8 ms (9.5 KiB)** | 180.3 ms (106.5 KiB) | 251.9 ms (15.0 KiB) | 9.1 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **8.1 ms (8.0 KiB)** | 99.7 ms (106.0 KiB) | 102.8 ms (14.5 KiB) | 9.5 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **8.3 ms (10.5 KiB)** | 105.9 ms (106.5 KiB) | 103.9 ms (15.0 KiB) | 9.1 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **7.9 ms (8.0 KiB)** | 97.0 ms (106.0 KiB) | 94.4 ms (14.5 KiB) | 9.3 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **8.0 ms (10.0 KiB)** | 101.1 ms (107.0 KiB) | 102.3 ms (15.5 KiB) | 9.1 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `AMD EPYC 9V74 80-Core Processor` | 33ms / **3.42ms** | 8ms / **3.39ms** | 8ms / **3.47ms** | 8ms / **20.26ms** | 8ms / **148.29ms** | 8ms / **25.51ms** | 8ms / **25.72ms** | 8ms / **25.43ms** | 8ms / **14.57ms** | 8ms / **14.97ms** |
| **Windows AMD64** | `AMD EPYC 7763 64-Core Processor` | 10ms / **3.06ms** | 7ms / **3.07ms** | 7ms / **3.11ms** | 7ms / **22.05ms** | 10ms / **198.38ms** | 7ms / **37.54ms** | 8ms / **42.55ms** | 7ms / **42.05ms** | 8ms / **20.95ms** | 8ms / **22.64ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 120ms / **15.05ms** | 30ms / **15.25ms** | 30ms / **14.87ms** | 40ms / **30.90ms** | 33ms / **211.46ms** | 43ms / **48.79ms** | 31ms / **45.49ms** | 31ms / **53.88ms** | 31ms / **30.61ms** | 30ms / **33.66ms** |
| **Linux x86_64** | `Intel(R) Xeon(R) 6975P-C` | 13ms / **7.68ms** | 21ms / **7.15ms** | 13ms / **7.48ms** | 19ms / **18.82ms** | 26ms / **139.55ms** | 21ms / **76.11ms** | 22ms / **78.65ms** | 23ms / **75.66ms** | 21ms / **45.89ms** | 23ms / **42.07ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43730804969) · Source: `7429ebe0af8c`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

