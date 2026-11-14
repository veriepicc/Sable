# Benchmark Showdown

- **Date:** 2026-11-14
- **Host:** `Windows AMD64`
- **CPU:** `Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz`
- **Toolchains:** Sable (native x64), MSVC (`/O2 /arch:AVX512 /Ob2 /Oi /Ot /GS-`), GCC (`-O3 -march=native -mprefer-vector-width=512 -fwrapv`), TCC

## Execution Runtime (lower is better)

| Workload | Sable | MSVC | GCC | TCC | Winner |
| :--- | ---: | ---: | ---: | ---: | :---: |
| **Math Loop (80M iter)** | **4.49 ms** | 29.47 ms | 5.61 ms | 151.04 ms | **Sable** |
| **State Accumulation (50M iter)** | **4.27 ms** | 20.98 ms | 5.61 ms | 129.15 ms | **Sable** |
| **Branch Parity (40M iter)** | **4.37 ms** | 29.68 ms | 21.42 ms | 103.36 ms | **Sable** |
| **General Logic (6M iter)** | 22.84 ms | **18.37 ms** | 18.52 ms | 70.58 ms | **MSVC** |
| **HFT Order Book (12M iter)** | 200.61 ms | 138.39 ms | **132.36 ms** | 384.91 ms | **GCC** |
| **Math SIMD Vector (40M items)** | **44.15 ms** | 217.60 ms | 220.14 ms | 303.26 ms | **Sable** |
| **State SIMD Vector (40M items)** | **44.65 ms** | 323.93 ms | 327.59 ms | 504.79 ms | **Sable** |
| **Branch SIMD Vector (40M items)** | **44.80 ms** | 216.71 ms | 209.68 ms | 325.43 ms | **Sable** |
| **General SIMD Vector (20M items)** | **24.48 ms** | 163.11 ms | 159.15 ms | 260.68 ms | **Sable** |
| **HFT SIMD Vector (20M items)** | **24.14 ms** | 163.33 ms | 168.42 ms | 259.64 ms | **Sable** |

## Compilation Speed & Binary Size

| Workload | Sable | MSVC (`/O2 /arch:AVX512`) | GCC (`-O3 -march=native -mprefer-vector-width=512`) | TCC |
| :--- | ---: | ---: | ---: | ---: |
| **Math Loop (80M iter)** | **12.9 ms (5.0 KiB)** | 221.8 ms (105.0 KiB) | 3093.7 ms (14.5 KiB) | 15.0 ms (2.5 KiB) |
| **State Accumulation (50M iter)** | **8.8 ms (5.0 KiB)** | 105.1 ms (105.0 KiB) | 109.6 ms (14.5 KiB) | 11.3 ms (2.5 KiB) |
| **Branch Parity (40M iter)** | **9.4 ms (5.0 KiB)** | 101.0 ms (105.0 KiB) | 349.6 ms (14.5 KiB) | 10.8 ms (2.5 KiB) |
| **General Logic (6M iter)** | **9.5 ms (5.0 KiB)** | 121.0 ms (105.5 KiB) | 165.7 ms (14.5 KiB) | 11.6 ms (2.5 KiB) |
| **HFT Order Book (12M iter)** | **10.8 ms (6.0 KiB)** | 142.6 ms (106.0 KiB) | 207.0 ms (15.0 KiB) | 11.6 ms (4.0 KiB) |
| **Math SIMD Vector (40M items)** | **9.6 ms (9.5 KiB)** | 184.2 ms (106.5 KiB) | 230.7 ms (15.0 KiB) | 11.0 ms (2.5 KiB) |
| **State SIMD Vector (40M items)** | **9.2 ms (8.0 KiB)** | 111.0 ms (106.0 KiB) | 125.6 ms (14.5 KiB) | 11.0 ms (2.5 KiB) |
| **Branch SIMD Vector (40M items)** | **9.5 ms (10.5 KiB)** | 120.7 ms (106.5 KiB) | 126.3 ms (15.0 KiB) | 11.1 ms (2.5 KiB) |
| **General SIMD Vector (20M items)** | **9.6 ms (8.0 KiB)** | 108.7 ms (106.0 KiB) | 119.1 ms (14.5 KiB) | 11.9 ms (2.5 KiB) |
| **HFT SIMD Vector (20M items)** | **9.5 ms (10.0 KiB)** | 116.6 ms (107.0 KiB) | 124.8 ms (15.5 KiB) | 11.3 ms (2.5 KiB) |

## Reproduction

```powershell
python benchmarks/run.py --iterations 5 --warmup 2
```

## Multi-Architecture Silicon Matrix (Sable: Compile / Runtime)

### Scalar Benchmarks
| Architecture & Host | Processor Model | Math (80M) | State (50M) | Branch (40M) | General (6M) | HFT (12M) | Math Vec (40M) | State Vec (40M) | Branch Vec (40M) | General Vec (20M) | HFT Vec (20M) |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows AMD64** | `Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz` | 13ms / **4.49ms** | 9ms / **4.27ms** | 9ms / **4.37ms** | 9ms / **22.84ms** | 11ms / **200.61ms** | 10ms / **44.15ms** | 9ms / **44.65ms** | 9ms / **44.80ms** | 10ms / **24.48ms** | 10ms / **24.14ms** |
| **Windows AMD64** | `INTEL(R) XEON(R) PLATINUM 8573C` | 15ms / **3.41ms** | 8ms / **3.45ms** | 7ms / **3.30ms** | 7ms / **21.69ms** | 9ms / **179.95ms** | 8ms / **45.47ms** | 8ms / **39.85ms** | 8ms / **44.52ms** | 8ms / **24.00ms** | 8ms / **24.35ms** |
| **Windows ARM64 (Prism x64)** | `Cobalt 100` | 111ms / **14.73ms** | 29ms / **14.25ms** | 28ms / **14.06ms** | 38ms / **29.92ms** | 32ms / **210.75ms** | 41ms / **48.59ms** | 29ms / **44.77ms** | 29ms / **54.08ms** | 29ms / **29.79ms** | 29ms / **33.03ms** |
| **Linux x86_64** | `AMD EPYC 9V45 96-Core Processor` | 21ms / **15.21ms** | 104ms / **15.52ms** | 21ms / **14.83ms** | 21ms / **24.48ms** | 24ms / **117.06ms** | 21ms / **65.68ms** | 23ms / **65.44ms** | 25ms / **65.54ms** | 24ms / **42.09ms** | 22ms / **40.90ms** |

Automated multi-host benchmarks recorded on [CI Run](https://github.com/veriepicc/Sable/actions/runs/43636543095) · Source: `e366dfabf8a4`.

## Reproduction

```powershell
./bin/Release/sable.exe build benchmarks/benchmark_hft.project
python benchmarks/run.py --iterations 5 --warmup 2
```

