#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef BENCH
#define BENCH 1
#endif

// ============================================================================
// THREAD + SIMD LAYER (vectorized benchmarks 6 - 10 only)
// the sable counterparts use parallel for + auto-vectorization, so the C
// side gets real os threads and exact int64 avx2 kernels to match. chunks
// are disjoint so every toolchain lands on the same checksum.
// ============================================================================

#if BENCH >= 6 && BENCH <= 10

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#if defined(__AVX2__) && !defined(__TINYC__)
#include <immintrin.h>
#define BENCH_SIMD 1
#else
#define BENCH_SIMD 0
#endif

typedef void (*bench_worker)(void* ctx, int64_t lo, int64_t hi);
typedef struct { bench_worker fn; void* ctx; int64_t lo, hi; } bench_job;

#ifdef _WIN32
static DWORD WINAPI bench_thunk(LPVOID p) {
    bench_job* j = (bench_job*)p;
    j->fn(j->ctx, j->lo, j->hi);
    return 0;
}
#else
static void* bench_thunk(void* p) {
    bench_job* j = (bench_job*)p;
    j->fn(j->ctx, j->lo, j->hi);
    return NULL;
}
#endif

static int bench_threads(void) {
#ifdef _WIN32
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    long n = (long)si.dwNumberOfProcessors;
#else
    long n = sysconf(_SC_NPROCESSORS_ONLN);
#endif
    if (n < 1) n = 1;
    if (n > 64) n = 64;
    return (int)n;
}

static void bench_parallel(int64_t n, bench_worker fn, void* ctx) {
    int t = bench_threads();
    if ((int64_t)t > n) t = (int)n;
    if (t < 1) t = 1;
    bench_job jobs[64];
#ifdef _WIN32
    HANDLE hs[64];
#else
    pthread_t hs[64];
#endif
    int64_t chunk = (n + t - 1) / t;
    int spawned = 0;
    for (int k = 0; k < t; k++) {
        int64_t lo = (int64_t)k * chunk;
        int64_t hi = lo + chunk;
        if (hi > n) hi = n;
        if (lo >= hi) break;
        jobs[k].fn = fn; jobs[k].ctx = ctx; jobs[k].lo = lo; jobs[k].hi = hi;
#ifdef _WIN32
        hs[spawned] = CreateThread(NULL, 0, bench_thunk, &jobs[k], 0, NULL);
        if (hs[spawned]) spawned++;
        else fn(ctx, lo, hi);
#else
        if (pthread_create(&hs[spawned], NULL, bench_thunk, &jobs[k]) == 0) spawned++;
        else fn(ctx, lo, hi);
#endif
    }
#ifdef _WIN32
    if (spawned) WaitForMultipleObjects((DWORD)spawned, hs, TRUE, INFINITE);
    for (int k = 0; k < spawned; k++) CloseHandle(hs[k]);
#else
    for (int k = 0; k < spawned; k++) pthread_join(hs[k], NULL);
#endif
}

typedef struct { int64_t *a, *b, *out; } bench_bufs;

#endif

// ============================================================================
// SCALAR BENCHMARKS (1 - 5)
// ============================================================================

#if BENCH == 1
int main(void) {
    int64_t result = 0;
    int64_t i = 0;
    while (i < 80000000) {
        int64_t x = i * 8;
        int64_t y = x + 1;
        int64_t z = 0;
        result = result + y + z;
        i = i + 1;
    }
    return (int)(result & 255);
}
#elif BENCH == 2
int main(void) {
    int64_t result = 0;
    int64_t i = 0;
    int64_t a = 1;
    int64_t b = 3;
    while (i < 50000000) {
        result = result + a;
        result = result + b;
        a = a + 3;
        b = b + 5;
        i = i + 1;
    }
    return (int)(result & 255);
}
#elif BENCH == 3
int main(void) {
    int64_t result = 0;
    int64_t i = 0;
    int64_t even = 1;
    int64_t odd = 3;
    while (i < 40000000) {
        if ((i & 1) == 0) {
            result = result + even;
            even = even + 3;
        } else {
            result = result + odd;
            odd = odd + 5;
        }
        i = i + 1;
    }
    return (int)(result & 255);
}
#elif BENCH == 4
static int64_t fold(int64_t x, int64_t bias) {
    int64_t y = x * 17 + bias;
    if (y < bias) y = y + 31; else y = y - 17;
    if (y < 1000) y = y + 7; else y = y - 5;
    return y;
}

static int64_t blend(int64_t left, int64_t right) {
    int64_t v = left + right * 3;
    if (left < right) v = v + left; else v = v - right;
    return v;
}

int main(void) {
    int64_t total = 0;
    int64_t state = 7;
    int64_t noise = 11;
    int64_t i = 0;
    while (i < 6000000) {
        int64_t a = fold(state, noise);
        int64_t b = blend(a, noise);
        if (b < state) {
            total = total + a;
            noise = noise + 5;
        } else {
            total = total + b;
            noise = noise - 3;
        }
        if (i < noise) {
            total = total + state;
            state = state + 2;
        } else {
            total = total - noise;
            state = state + 1;
        }
        i = i + 1;
    }
    return (int)total;
}
#elif BENCH == 5
static int64_t mix(int64_t i, int64_t salt) {
    int64_t x = i * 1103515245LL + salt * 2654435761LL;
    x = x ^ (x >> 13);
    x = x * 2246822519LL;
    return x & 1023;
}

int main(void) {
    int64_t bid_px = 100000, bid_sz = 24, ask_px = 100002, ask_sz = 26;
    int64_t last_px = 100001, last_qty = 4, seq = 1;
    int64_t inventory = 0, cash = 0, pnl = 0, buy_px = 0, sell_px = 0;
    int64_t buy_qty = 0, sell_qty = 0, fills = 0, rejects = 0, risk = 0, checksum = 0;
    for (int64_t i = 0; i < 12000000; i++) {
        int64_t bid_size_bump = (mix(i, 43) & 31) + 1;
        int64_t ask_size_bump = (mix(i, 59) & 31) + 1;
        bid_px += (mix(i, 17) & 7) - 3;
        ask_px += (mix(i, 29) & 7) - 3;
        if (ask_px <= bid_px) ask_px = bid_px + 1;
        if ((i & 1) == 0) { bid_sz += bid_size_bump; ask_sz -= ask_size_bump >> 1; }
        else { ask_sz += ask_size_bump; bid_sz -= bid_size_bump >> 1; }
        if (bid_sz < 1) bid_sz = 1 + (bid_size_bump & 15);
        if (ask_sz < 1) ask_sz = 1 + (ask_size_bump & 15);
        int64_t spread = ask_px - bid_px, mid = (ask_px + bid_px) >> 1;
        int64_t imbalance = bid_sz - ask_sz, skew = inventory >> 2;
        buy_px = mid - 1 - skew;
        sell_px = mid + 1 - skew;
        if (spread > 3) { buy_px--; sell_px++; }
        buy_qty = 8 + ((bid_sz + imbalance) & 15);
        sell_qty = 8 + ((ask_sz - imbalance) & 15);
        if (inventory > 96) { buy_qty = 1; sell_qty += 8; risk += 3; }
        else if (inventory < -96) { sell_qty = 1; buy_qty += 8; risk += 3; }
        else risk += (inventory * spread + imbalance) & 1;
        int64_t trigger = mix(i, inventory + 71);
        if (trigger < 96) { inventory += buy_qty; cash -= buy_px * buy_qty; fills++; }
        else if (trigger > 928) { inventory -= sell_qty; cash += sell_px * sell_qty; fills++; }
        else rejects++;
        last_px = mid;
        last_qty = ((bid_sz ^ ask_sz) & 63) + 1;
        seq++;
        pnl = cash + inventory * last_px - risk * 17;
        if (inventory > 128) { inventory -= 7; cash += bid_px * 7; checksum += inventory; }
        else if (inventory < -128) { inventory += 7; cash -= ask_px * 7; checksum -= inventory; }
        else checksum += pnl + seq + last_qty + rejects;
    }
    return (int)((checksum ^ pnl ^ last_px) & 255);
}

// ============================================================================
// VECTORIZED BENCHMARKS (6 - 10): os threads + exact avx2 int64 kernels
// ============================================================================

#elif BENCH == 6
// Math Vectorized (40M elements)
static void init6(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    for (int64_t i = lo; i < hi; i++) x->a[i] = i;
}
static void work6(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    int64_t i = lo;
#if BENCH_SIMD
    const __m256i one = _mm256_set1_epi64x(1);
    for (; i + 4 <= hi; i += 4) {
        __m256i av = _mm256_loadu_si256((const __m256i*)(x->a + i));
        _mm256_storeu_si256((__m256i*)(x->out + i),
                            _mm256_add_epi64(_mm256_slli_epi64(av, 3), one));
    }
#endif
    for (; i < hi; i++) x->out[i] = x->a[i] * 8 + 1;
}
int main(void) {
    int64_t n = 40000000;
    bench_bufs x;
    x.a = (int64_t*)malloc(n * sizeof(int64_t));
    x.b = NULL;
    x.out = (int64_t*)malloc(n * sizeof(int64_t));
    if (!x.a || !x.out) return 1;
    bench_parallel(n, init6, &x);
    bench_parallel(n, work6, &x);
    int64_t check = x.out[n / 2];
    free(x.a); free(x.out);
    return (int)check;
}

#elif BENCH == 7
// State Vectorized (40M elements)
static void init7(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    for (int64_t i = lo; i < hi; i++) { x->a[i] = 1; x->b[i] = 3; }
}
static void work7(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    int64_t i = lo;
#if BENCH_SIMD
    const __m256i three = _mm256_set1_epi64x(3);
    const __m256i five = _mm256_set1_epi64x(5);
    for (; i + 4 <= hi; i += 4) {
        __m256i av = _mm256_loadu_si256((const __m256i*)(x->a + i));
        __m256i bv = _mm256_loadu_si256((const __m256i*)(x->b + i));
        _mm256_storeu_si256((__m256i*)(x->out + i),
                            _mm256_add_epi64(_mm256_add_epi64(av, three),
                                             _mm256_add_epi64(bv, five)));
    }
#endif
    for (; i < hi; i++) x->out[i] = (x->a[i] + 3) + (x->b[i] + 5);
}
int main(void) {
    int64_t n = 40000000;
    bench_bufs x;
    x.a = (int64_t*)malloc(n * sizeof(int64_t));
    x.b = (int64_t*)malloc(n * sizeof(int64_t));
    x.out = (int64_t*)malloc(n * sizeof(int64_t));
    if (!x.a || !x.b || !x.out) return 1;
    bench_parallel(n, init7, &x);
    bench_parallel(n, work7, &x);
    int64_t check = x.out[n / 2];
    free(x.a); free(x.b); free(x.out);
    return (int)check;
}

#elif BENCH == 8
// Branch Vectorized (40M elements)
static void init8(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    for (int64_t i = lo; i < hi; i++) x->a[i] = i;
}
static void work8(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    int64_t i = lo;
#if BENCH_SIMD
    const __m256i one = _mm256_set1_epi64x(1);
    for (; i + 4 <= hi; i += 4) {
        __m256i av = _mm256_loadu_si256((const __m256i*)(x->a + i));
        __m256i par = _mm256_and_si256(av, one);
        __m256i p3 = _mm256_add_epi64(par, _mm256_slli_epi64(par, 1));
        __m256i a5 = _mm256_add_epi64(_mm256_slli_epi64(av, 2), av);
        _mm256_storeu_si256((__m256i*)(x->out + i), _mm256_add_epi64(p3, a5));
    }
#endif
    for (; i < hi; i++) x->out[i] = (x->a[i] & 1) * 3 + x->a[i] * 5;
}
int main(void) {
    int64_t n = 40000000;
    bench_bufs x;
    x.a = (int64_t*)malloc(n * sizeof(int64_t));
    x.b = NULL;
    x.out = (int64_t*)malloc(n * sizeof(int64_t));
    if (!x.a || !x.out) return 1;
    bench_parallel(n, init8, &x);
    bench_parallel(n, work8, &x);
    int64_t check = x.out[n / 2];
    free(x.a); free(x.out);
    return (int)(check & 255);
}

#elif BENCH == 9
// General Vectorized (20M elements)
static void init9(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    for (int64_t i = lo; i < hi; i++) { x->a[i] = 7; x->b[i] = 11; }
}
static void work9(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    int64_t i = lo;
#if BENCH_SIMD
    const __m256i c31 = _mm256_set1_epi64x(31);
    for (; i + 4 <= hi; i += 4) {
        __m256i av = _mm256_loadu_si256((const __m256i*)(x->a + i));
        __m256i bv = _mm256_loadu_si256((const __m256i*)(x->b + i));
        __m256i a17 = _mm256_add_epi64(_mm256_slli_epi64(av, 4), av);
        __m256i b3 = _mm256_add_epi64(_mm256_slli_epi64(bv, 1), bv);
        _mm256_storeu_si256((__m256i*)(x->out + i),
                            _mm256_add_epi64(_mm256_add_epi64(a17, c31),
                                             _mm256_add_epi64(av, b3)));
    }
#endif
    for (; i < hi; i++) x->out[i] = (x->a[i] * 17 + 31) + (x->a[i] + x->b[i] * 3);
}
int main(void) {
    int64_t n = 20000000;
    bench_bufs x;
    x.a = (int64_t*)malloc(n * sizeof(int64_t));
    x.b = (int64_t*)malloc(n * sizeof(int64_t));
    x.out = (int64_t*)malloc(n * sizeof(int64_t));
    if (!x.a || !x.b || !x.out) return 1;
    bench_parallel(n, init9, &x);
    bench_parallel(n, work9, &x);
    int64_t check = x.out[n / 2];
    free(x.a); free(x.b); free(x.out);
    return (int)check;
}

#elif BENCH == 10
// HFT Vectorized (20M elements)
static void init10(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    for (int64_t i = lo; i < hi; i++) { x->a[i] = 100000 + (i & 7); x->b[i] = 100005 + (i & 7); }
}
static void work10(void* c, int64_t lo, int64_t hi) {
    bench_bufs* x = (bench_bufs*)c;
    int64_t i = lo;
#if BENCH_SIMD
    const __m256i c17 = _mm256_set1_epi64x(17);
    for (; i + 4 <= hi; i += 4) {
        __m256i av = _mm256_loadu_si256((const __m256i*)(x->a + i));
        __m256i bv = _mm256_loadu_si256((const __m256i*)(x->b + i));
        __m256i spread8 = _mm256_slli_epi64(_mm256_sub_epi64(bv, av), 3);
        __m256i bid2 = _mm256_slli_epi64(av, 1);
        _mm256_storeu_si256((__m256i*)(x->out + i),
                            _mm256_sub_epi64(_mm256_add_epi64(spread8, bid2), c17));
    }
#endif
    for (; i < hi; i++) x->out[i] = ((x->b[i] - x->a[i]) * 8) + (x->a[i] * 2) - 17;
}
int main(void) {
    int64_t n = 20000000;
    bench_bufs x;
    x.a = (int64_t*)malloc(n * sizeof(int64_t));
    x.b = (int64_t*)malloc(n * sizeof(int64_t));
    x.out = (int64_t*)malloc(n * sizeof(int64_t));
    if (!x.a || !x.b || !x.out) return 1;
    bench_parallel(n, init10, &x);
    bench_parallel(n, work10, &x);
    int64_t check = x.out[n / 2];
    free(x.a); free(x.b); free(x.out);
    return (int)check;
}

#elif BENCH == 11
// Stdlib Memory Churn (300k appends + 200k slice alloc/free)
static char* m_buf;
// keep the allocated slice observable so the optimizer cannot erase the churn
static char* volatile m_live_slice;
static int64_t m_len, m_cap;
static void m_need(int64_t extra) {
    if (m_len + extra <= m_cap) return;
    while (m_cap < m_len + extra) m_cap *= 2;
    m_buf = (char*)realloc(m_buf, (size_t)m_cap);
}
static void m_put(const char* s, int64_t n) {
    m_need(n);
    memcpy(m_buf + m_len, s, (size_t)n);
    m_len += n;
}
static void m_dec(int64_t v) {
    char tmp[24];
    int k = 0;
    if (v == 0) tmp[k++] = '0';
    while (v > 0) { tmp[k++] = (char)('0' + (v % 10)); v /= 10; }
    m_need(k);
    for (int j = 0; j < k; j++) m_buf[m_len + j] = tmp[k - 1 - j];
    m_len += k;
}
int main(void) {
    m_cap = 64; m_len = 0;
    m_buf = (char*)malloc((size_t)m_cap);
    if (!m_buf) return 1;
    for (int64_t i = 0; i < 300000; i++) { m_put("ord|", 4); m_dec(i); m_put("|ok\n", 4); }
    int64_t sum = 0;
    for (int64_t k = 0; k < 200000; k++) {
        int64_t start = (k * 7) % (m_len - 16);
        char* s = (char*)malloc(16);
        memcpy(s, m_buf + start, 16);
        m_live_slice = s;
        sum += (unsigned char)m_live_slice[0];
        m_live_slice = NULL;
        free(s);
    }
    int64_t check = (m_len + sum) & 255;
    free(m_buf);
    return (int)check;
}
#endif
