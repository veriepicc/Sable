# Standard Library

Sable ships with a growing standard library embedded into the compiler.

Import modules explicitly:

```c
import mem
import text
import fmt
```

## Current modules in active use

| Module | What it is for |
|-------|-----------------|
| `mem` | typed memory reads/writes, `mem.move`, `mem.move_cells`, `mem.make_zero` |
| `ascii` | ASCII classification, case conversion, hex nibble/byte helpers |
| `text` | O(N) string scanning, slicing, trimming, joining, repeating, padding |
| `fmt` | single-pass formatting (`fmt_bool`, `fmt_int`, `fmt_pair`, `fmt_csv3`, `fmt_hex_byte`) |
| `fs` | file read/write helpers |
| `json` | zero-copy `view`-backed JSON DOM parser, `json_stringify`, and fast lookups |
| `http` | WinHTTP client: request builder, headers, bodies, query strings, url codec, `http_fetch`/`http_get`, `http_ok`, `http_parse_url` |
| `path` | path joining, stem, extension, basename/dirname helpers |
| `process` | process ID, handle, dynamic DLL loading, message box, exit |
| `rand` | SplitMix64 + Xorshift64* PRNG (`rand_seed`, `rand_next`, `rand_range`) |
| `time` | millisecond tick and sleep helpers |
| `vec` | growable `int` vector (`vec_new`, `vec_push`, `vec_append`, `vec_remove_at`) |
| `algo` | median-of-3 quicksort, binary search, reductions, array transforms |
| `option` | `view`-backed optional wrappers (`OptI64`, `OptStr`, `OptPtr`) |
| `result` | `view`-backed result/error wrappers (`ResI64`, `ResStr`, `ResPtr`) |
| `owner` | manual ownership structs (`OwnedPtr`, `OwnedStr`, `OwnedBlock`) |
| `cpp_vector` | `view`-backed interop helper for C++-style vector buffers |
| `hash` | hashing and checksums: FNV-1a, djb2, CRC-32, splitmix64 mix, adler32/sum/xor |
| `bitset` | growable bitset over heap words: get/set/toggle, popcount, find, set algebra |
| `strbuf` | growable string builder: `strbuf_append`, `strbuf_append_int`, `strbuf_to_string` |
| `codec` | hex and base64 encode/decode over bytes and strings, with `*_into` variants |
| `math` | integer math: gcd/lcm, mod, pow_mod, isqrt, ipow, factorial, binomial, checked_* |
| `prelude` | convenience bundle importing core modules |

## `mem`

Preferred low-level surface:

```c
import mem

function int main() {
    let buf = malloc(16)
    mem.write(buf, 0x1122334455667788)
    mem.write32(buf + 8, 123)

    if mem.read(buf) == 0 {
        return 1
    }
    if mem.read32(buf + 8) != 123 {
        return 2
    }

    free(buf)
    return 0
}
```

`mem` and `view` are meant to work together:

```c
import mem

enum HeaderOffset {
    Magic = 0,
    Flags = 4,
}

view Header {
    magic: int @ HeaderOffset.Magic
    flags: int @ HeaderOffset.Flags
}

function int main() {
    let block = mem.make_zero(8)
    let hdr = block as Header
    hdr.magic = 0x1234
    hdr.flags = 7
    free(block)
    return 0
}
```

Use `mem` for allocation/copy/fill/read/write helpers.
Use `view` when those bytes represent a stable layout you want to name directly.
Use named offsets when those layouts are shared with SDK or offset-manager style code.

## `text` and `fmt`

```c
import text
import fmt

function int main() {
    let trimmed = text_trim("  sable  ")
    let pair = fmt_pair("mode", trimmed)
    print(pair)
    print("\n")
    free(trimmed)
    free(pair)
    return 0
}
```

## `fs` and `json`

`json` provides both quick single-field lookups (`json_get_int`, `json_get_bool`, `json_get_string`) and a full `view`-backed DOM (`json_parse`, `json_object_get`, `json_array_get`, `json_stringify`, `json_free`) with UTF-16 surrogate pair decoding.

```c
import fs
import json

function int main() {
    let file_path = "tests/tmp_doc_example.json"
    let src = "{\"name\":\"sable\",\"fast\":true}"
    if !fs_write_ok(file_path, src) {
        return 1
    }

    let content = fs_read_text(file_path)
    if content == 0 {
        return 2
    }
    if !json_get_bool(content, "fast", false) {
        free(content)
        return 3
    }

    let doc = json_parse(content)
    let out = json_stringify(doc)
    json_free(doc)
    free(out)
    free(content)
    return 0
}
```

## `http`

`http` wraps WinHTTP with typed function pointers and `view` overlays (`HttpUrl`, `HttpResponse`, `HttpRequest`). It covers simple GETs up to full request building with headers, bodies and query strings.

Simplest form:

```c
import http

function int main() {
    let resp = http_fetch("http://127.0.0.1:8080/status")
    if http_ok(resp) {
        println(resp.body)
    }
    http_response_free(resp)
    return 0
}
```

Full request building:

```c
import http

function int main() {
    let req = http_request_new("POST", "https://api.example.com/v1/items")
    http_request_header(req, "Accept", "application/json")
    http_request_body_text(req, "{\"name\":\"x\"}", "application/json")
    http_request_timeout(req, 5000)
    http_request_follow_redirects(req, true)

    let resp = http_request_send(req)
    http_request_free(req)

    if resp != 0 {
        print_int(resp.status)          // 200
        println(resp.body)              // response body
        let ct = http_response_content_type(resp)
        println(ct)                     // e.g. application/json
        free(ct)
        http_response_free(resp)
    }
    return 0
}
```

Verb helpers: `http_get`, `http_post`, `http_put`, `http_patch`, `http_delete`, `http_head`, plus generic `http_request(method, url)`.

Request builder: `http_request_new(method, url)`, `http_request_header(name, value)` (call repeatedly; the buffer grows), `http_request_body(bytes, len, content_type)`, `http_request_body_text(text, content_type)`, `http_request_user_agent(ua)`, `http_request_timeout(ms)`, `http_request_follow_redirects(bool)`, `http_request_free(req)`.

Response: `http_response_header(resp, name)` (case-insensitive, trimmed; returns a heap string or `0`), `http_response_content_type(resp)`, `http_ok(resp)`, `http_response_free(resp)`. For binary payloads use `resp.body_bytes` (raw buffer, keeps embedded NULs) with `resp.body_len`, since `resp.body` is a null-terminated str view that stops at the first NUL.

Helpers: `http_url_encode(s)` / `http_url_decode(s)` (RFC3986, `+` decodes to space), `http_build_query(keys, values, count)` builds `k=v&k2=v2` with percent-encoded values, `http_parse_url(url)` returns an `HttpUrl` view. Extras: `http_url_with_query(url, k, v)` / `http_request_add_query(req, k, v)` append encoded query args, `http_base64_encode(bytes, len)` + `http_basic_auth(user, pass)` / `http_request_basic_auth(req, user, pass)` build an `Authorization: Basic` header, and `http_multipart_field(name, value, boundary, _)` / `http_multipart_content_type(boundary)` build `multipart/form-data` bodies.

## `vec` and `algo`

`algo` includes median-of-3 quicksort (`algo_sort_i64`), overflow-safe binary search (`algo_binary_search_i64`), and reductions over `vec_data(items)`.

```c
import vec
import algo

function int main() {
    var items = vec_new(4)
    items = vec_push(items, 13)
    items = vec_push(items, 7)
    items = vec_push(items, 11)

    algo_sort_i64(vec_data(items), vec_len(items))
    if algo_binary_search_i64(vec_data(items), vec_len(items), 11) < 0 {
        vec_free(items)
        return 1
    }

    vec_free(items)
    return 0
}
```

## `option`, `result`, and `owner`

`option` and `result` provide `view`-backed nullable-safe wrappers (`opt_i64_some`, `opt_i64_unwrap_or`, `res_i64_ok`, `res_i64_err`), and `owner` provides explicit manual ownership structs (`OwnedPtr`, `OwnedStr`, `OwnedBlock`).

## `time` and `rand`

```c
import time
import rand

function int main() {
    let t0 = time_tick_ms()
    time_sleep_ms(1)
    if time_elapsed_ms(t0) < 0 {
        return 1
    }

    rand_seed(12345)
    let value = rand_next()
    if value < 0 {
        return 2
    }
    return 0
}
```

## `hash`

Hashing and checksums. Every function is pure: nothing allocates or frees.

```c
import hash

function int main() {
    let h = hash_fnv1a("hello")        // FNV-1a 64
    let c = hash_crc32("hello")        // IEEE CRC-32
    let b = hash_bucket(h, 256)        // 0..255, never negative, never /0
    let m = hash_mix_i64(0x12345678)   // splitmix64 avalanche
    return 0
}
```

`hash_fnv1a`, `hash_djb2`, `hash_crc32`, `hash_fnv1a_i64` cover strings and
integers; `hash_fnv1a_bytes`, `hash_crc32_bytes` work on raw buffers with a
length; `checksum_sum_bytes`, `checksum_xor_bytes`, `checksum_adler32` are the
cheap integrity checks; `hash_combine` merges two hashes order-sensitively.

## `bitset`

A growable bitset backed by heap 64-bit words. Constructors allocate and the
caller releases with `bitset_free`; every other call borrows the handle.

```c
import bitset

function int main() {
    let s = bitset_new()               // 64 bits
    bitset_set(s, 5)
    bitset_set(s, 1000)                // grows automatically
    if bitset_count(s) != 2 { return 1 }
    if bitset_find_next(s, 0) != 5 { return 2 }
    bitset_free(s)
    return 0
}
```

`bitset_get`/`set`/`clear`/`toggle` are bounds-aware, `bitset_count` is a
popcount, `bitset_find_next` iterates set bits, and `bitset_or_into`,
`bitset_and_count`, `bitset_intersects` do set algebra. Every accessor tolerates
a null handle (reads yield 0 / false, writes are ignored).

## `strbuf`

Growable string builder. Appending N pieces costs O(total), not the O(N * total)
of repeated `string_append`. Constructors allocate; release with `strbuf_free`.

```c
import strbuf

function int main() {
    let b = strbuf_new()
    strbuf_append(b, "value=")
    strbuf_append_int(b, 42)
    let s = strbuf_to_string(b)      // fresh heap string
    strbuf_free(b)
    free(s)
    return 0
}
```

`strbuf_append`, `strbuf_append_int`, `strbuf_append_repeat`,
`strbuf_push_byte` add content; `strbuf_view` reads the contents mid-build as a
null-terminated `str` (no allocation); `strbuf_to_string` materializes a heap
copy; `strbuf_clear` empties it; `strbuf_reserve` grows ahead of a known volume.

## `codec`

Hex and Base64 codecs over raw bytes, with both encode and decode.

```c
import codec

function int main() {
    let hex = codec_hex_encode("Man" as ptr, 3)   // "4d616e"
    let b64 = codec_b64_encode("Man" as ptr, 3)   // "TWFu"
    let dec = codec_b64_decode("TWFu")            // "Man"
    free(hex); free(b64); free(dec)
    return 0
}
```

`codec_hex_encode`/`_upper`/`_decode`, `codec_b64_encode`/`_decode`,
`codec_b64_encode_str`, plus `*_into` and `*_to_bytes` variants that write into a
caller buffer and allocate nothing. Decode skips non-alphabet characters (so
`"4d:61-6e"` and wrapped base64 blobs decode cleanly). For binary data, decode
with `codec_*_decode_to_bytes` into a buffer sized by `codec_*_decoded_len`, since
a native-image `str` is NUL-terminated and cannot carry an embedded `0x00`
length. `codec_hex_roundtrip`/`codec_b64_roundtrip` self-check a buffer.

## `math`

Integer mathematics: number theory, roots, sequences, and overflow-checked
arithmetic. All pure.

```c
import math

function int main() {
    let g = math_gcd(48, 18)          // 6
    let r = math_isqrt(100000000)     // 10000
    let m = math_pow_mod(2, 10, 1000) // 24
    let s = math_checked_add(9223372036854775807, 1, -1)  // -1 (overflow)
    return 0
}
```

`math_gcd`, `math_lcm`, `math_mod` (Euclidean, always non-negative),
`math_pow_mod`, `math_ext_gcd`, `math_isqrt`, `math_nth_root`, `math_ipow`,
`math_factorial`, `math_binomial`, `math_fibonacci`, and the `math_checked_add` /
`_sub` / `_mul` helpers that return a fallback instead of wrapping.

## Notes

- Functions returning heap strings (`text_*`, `fmt_*`, `path_*`, `fs_read_text`, `json_string`, `json_stringify`, `http_get`) transfer ownership to the caller; call `free(...)` when done.
- `test_stdlib_regression.sb` and `test_stdlib_expanded.sb` exercise the standard library surface across modules.
- For raw builtins vs module helpers, prefer the module surface whenever both exist.
