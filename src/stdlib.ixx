// generated file - do not edit by hand

export module sable.stdlib;

import std;

export namespace sable {
export inline const std::unordered_map<std::string, std::string>& embedded_stdlib_sources() {
    static const std::unordered_map<std::string, std::string> sources = {
        {"algo", R"SBALGO(import mem

// Fast algorithms for 8-byte integer spans.

function i64 algo_min_i64(i64 a, i64 b) {
    if a < b {
        return a
    }
    return b
}

function i64 algo_max_i64(i64 a, i64 b) {
    if a > b {
        return a
    }
    return b
}

function i64 algo_clamp_i64(i64 item, i64 lo, i64 hi) {
    if item < lo {
        return lo
    }
    if item > hi {
        return hi
    }
    return item
}

function i64 algo_abs_i64(i64 item) {
    if item < 0 {
        return -item
    }
    return item
}

function i64 algo_sign_i64(i64 item) {
    if item < 0 {
        return -1
    }
    if item > 0 {
        return 1
    }
    return 0
}

function bool algo_is_even_i64(i64 item) {
    return (item & 1) == 0
}

function bool algo_is_odd_i64(i64 item) {
    return (item & 1) != 0
}

function void algo_swap_i64(ptr a, ptr b) {
    if a == b {
        return
    }
    let tmp = mem.read(a)
    mem.write(a, mem.read(b))
    mem.write(b, tmp)
}

function void algo_fill_i64(ptr values, int len, i64 item) {
    if values == 0 || len <= 0 {
        return
    }
    var arr = values as *i64
    for i in range(0, len) {
        arr[i] = item
    }
}

function void algo_copy_i64(ptr dst, ptr src, int len) {
    if dst == 0 || src == 0 || len <= 0 || dst == src {
        return
    }
    memcpy(dst, src, len * 8)
}

function void algo_reverse_i64(ptr values, int len) {
    if values == 0 || len <= 1 {
        return
    }
    var arr = values as *i64
    var left = 0
    var right = len - 1
    while left < right {
        let tmp = arr[left]
        arr[left] = arr[right]
        arr[right] = tmp
        left++
        right--
    }
}

function i64 algo_sum_i64(ptr values, int len) {
    if values == 0 || len <= 0 {
        return 0
    }
    let arr = values as *i64
    var total = 0
    for i in range(0, len) {
        total += arr[i]
    }
    return total
}

function i64 algo_product_i64(ptr values, int len) {
    if values == 0 || len <= 0 {
        return 0
    }
    let arr = values as *i64
    var total = 1
    for i in range(0, len) {
        total *= arr[i]
    }
    return total
}

function i64 algo_index_of_i64(ptr values, int len, i64 target) {
    if values == 0 || len <= 0 {
        return -1
    }
    let arr = values as *i64
    for i in range(0, len) {
        if arr[i] == target {
            return i
        }
    }
    return -1
}

function bool algo_contains_i64(ptr values, int len, i64 target) {
    return algo_index_of_i64(values, len, target) >= 0
}

function i64 algo_count_i64(ptr values, int len, i64 target) {
    if values == 0 || len <= 0 {
        return 0
    }
    let arr = values as *i64
    var count = 0
    for i in range(0, len) {
        if arr[i] == target {
            count++
        }
    }
    return count
}

function i64 algo_min_span_i64(ptr values, int len) {
    if values == 0 || len <= 0 {
        return 0
    }
    let arr = values as *i64
    var best = arr[0]
    for i in range(1, len) {
        let item = arr[i]
        if item < best {
            best = item
        }
    }
    return best
}

function i64 algo_max_span_i64(ptr values, int len) {
    if values == 0 || len <= 0 {
        return 0
    }
    let arr = values as *i64
    var best = arr[0]
    for i in range(1, len) {
        let item = arr[i]
        if item > best {
            best = item
        }
    }
    return best
}

function i64 algo_binary_search_i64(ptr values, int len, i64 target) {
    if values == 0 || len <= 0 {
        return -1
    }
    let arr = values as *i64
    var low = 0
    var high = len - 1
    while low <= high {
        let mid = low + ((high - low) >> 1)
        let item = arr[mid]
        if item == target {
            return mid
        }
        if item < target {
            low = mid + 1
        } else {
            high = mid - 1
        }
    }
    return -1
}

internal function void algo_insertion_sort_i64(ptr values, int lo, int hi) {
    var arr = values as *i64
    var i = lo + 1
    while i <= hi {
        let key = arr[i]
        var j = i - 1
        while j >= lo {
            let cur = arr[j]
            if cur <= key {
                break
            }
            arr[j + 1] = cur
            j--
        }
        arr[j + 1] = key
        i++
    }
}

internal function void algo_qsort_i64(ptr values, int lo, int hi) {
    var arr = values as *i64
    while lo < hi {
        if hi - lo <= 16 {
            algo_insertion_sort_i64(values, lo, hi)
            return
        }

        let mid = lo + ((hi - lo) >> 1)
        if arr[mid] < arr[lo] {
            let t0 = arr[lo]; arr[lo] = arr[mid]; arr[mid] = t0
        }
        if arr[hi] < arr[lo] {
            let t1 = arr[lo]; arr[lo] = arr[hi]; arr[hi] = t1
        }
        if arr[hi] < arr[mid] {
            let t2 = arr[mid]; arr[mid] = arr[hi]; arr[hi] = t2
        }

        let pivot = arr[mid]
        var i = lo
        var j = hi
        while i <= j {
            while arr[i] < pivot {
                i++
            }
            while arr[j] > pivot {
                j--
            }
            if i <= j {
                if i != j {
                    let tmp = arr[i]
                    arr[i] = arr[j]
                    arr[j] = tmp
                }
                i++
                j--
            }
        }

        if j - lo < hi - i {
            if lo < j {
                algo_qsort_i64(values, lo, j)
            }
            lo = i
        } else {
            if i < hi {
                algo_qsort_i64(values, i, hi)
            }
            hi = j
        }
    }
}

function void algo_sort_i64(ptr values, int len) {
    if values == 0 || len <= 1 {
        return
    }
    algo_qsort_i64(values, 0, len - 1)
}
)SBALGO"},
        {"ascii", R"SBASCII(// ASCII-oriented helpers for formatting, parsing, and protocol work.
// Ownership:
// - ascii_hex_digit/ascii_hex_byte return heap strings; caller must free.

function bool ascii_is_lower(int ch) {
    return ch >= 97 and ch <= 122
}

function bool ascii_is_upper(int ch) {
    return ch >= 65 and ch <= 90
}

function bool ascii_is_alpha(int ch) {
    return ascii_is_lower(ch) or ascii_is_upper(ch)
}

function bool ascii_is_digit(int ch) {
    return ch >= 48 and ch <= 57
}

function bool ascii_is_alnum(int ch) {
    return ascii_is_alpha(ch) or ascii_is_digit(ch)
}

function bool ascii_is_space(int ch) {
    return ch == 32 or ch == 9 or ch == 10 or ch == 13
}

function int ascii_to_lower(int ch) {
    if ascii_is_upper(ch) {
        return ch + 32
    }
    return ch
}

function int ascii_to_upper(int ch) {
    if ascii_is_lower(ch) {
        return ch - 32
    }
    return ch
}

function int ascii_hex_value(int ch) {
    if ch >= 48 and ch <= 57 {
        return ch - 48
    }
    if ch >= 65 and ch <= 70 {
        return ch - 55
    }
    if ch >= 97 and ch <= 102 {
        return ch - 87
    }
    return -1
}

function int ascii_hex_nibble_char(int nibble) {
    var n = nibble
    if n < 0 {
        n = 0
    } else if n > 15 {
        n = 15
    }
    if n < 10 {
        return 48 + n
    }
    return 55 + n
}

function str ascii_hex_digit(int nibble) {
    let buf = malloc(2)
    if buf == 0 {
        return string_substring("", 0, 0)
    }
    mem_write_i8(buf, ascii_hex_nibble_char(nibble))
    mem_write_i8(buf + 1, 0)
    let out = make_string(buf)
    free(buf)
    return out
}

function str ascii_hex_byte(int byte_value) {
    let buf = malloc(3)
    if buf == 0 {
        return string_substring("", 0, 0)
    }
    mem_write_i8(buf, ascii_hex_nibble_char((byte_value >> 4) & 15))
    mem_write_i8(buf + 1, ascii_hex_nibble_char(byte_value & 15))
    mem_write_i8(buf + 2, 0)
    let out = make_string(buf)
    free(buf)
    return out
}
)SBASCII"},
        {"bitset", R"SBBITSET(import mem

// Dynamic bitset: a growable array of bits backed by a heap block of 64-bit
// words.
//
// Ownership:
// - bitset_new / bitset_with_capacity / bitset_clone allocate; the caller owns
//   the returned handle and must release it with bitset_free.
// - every other function borrows the handle and allocates nothing.
//
// Layout: the handle is a view over a 24-byte header.
//   [0]  words   : ptr  -> heap block of 8-byte words, words[0] is bit 0..63
//   [8]  word_count : int  -> number of allocated words
//   [16] bit_count  : int  -> number of valid bits (<= word_count*64)
//
// All bits above bit_count read as 0 and are cleared on resize, so a bits bit is
// always a valid bit.

view BitSet {
    words: ptr @ 0
    word_count: int @ 8
    bit_count: int @ 16
}

// one word is 64 bits
let BITSET_WORD_BITS: int = 64

function int bitset_words_for(int bit_count) {
    if bit_count <= 0 {
        return 0
    }
    return (bit_count + BITSET_WORD_BITS - 1) / BITSET_WORD_BITS
}

function BitSet bitset_alloc_handle() {
    var handle = malloc(24) as BitSet
    if handle != 0 {
        handle.words = 0
        handle.word_count = 0
        handle.bit_count = 0
    }
    return handle
}

function BitSet bitset_new() {
    return bitset_with_capacity(64)
}

function BitSet bitset_with_capacity(int bit_count) {
    if bit_count <= 0 {
        return bitset_alloc_handle()
    }
    let needed = bitset_words_for(bit_count)
    var block = mem.make_zero(needed * 8)
    if block == 0 {
        return 0 as BitSet
    }
    let handle = bitset_alloc_handle()
    if handle == 0 {
        free(block)
        return 0 as BitSet
    }
    handle.words = block
    handle.word_count = needed
    // logical size is the requested count; the allocated words round up, but the
    // tail bits are already zero so they read false
    handle.bit_count = bit_count
    return handle
}

function BitSet bitset_clone(BitSet source) {
    if source == 0 {
        return 0 as BitSet
    }
    let words = source.word_count
    var block = 0 as ptr
    if words > 0 {
        block = mem.make_copy(source.words, words * 8)
        if block == 0 {
            return 0 as BitSet
        }
    }
    let handle = bitset_alloc_handle()
    if handle == 0 {
        free(block)
        return 0 as BitSet
    }
    handle.words = block
    handle.word_count = words
    handle.bit_count = source.bit_count
    return handle
}

function void bitset_free(BitSet bits) {
    if bits == 0 {
        return
    }
    if bits.words != 0 {
        free(bits.words)
        bits.words = 0
    }
    free(bits)
}

function int bitset_len(BitSet bits) {
    if bits == 0 {
        return 0
    }
    return bits.bit_count
}

function bool bitset_is_empty(BitSet bits) {
    if bits == 0 || bits.bit_count <= 0 {
        return true
    }
    let words = bits.words as *i64
    var i = 0
    while i < bits.word_count {
        if words[i] != 0 {
            return false
        }
        i++
    }
    return true
}

// grow so that `bit_count` bits are representable. existing bits are preserved;
// new bits are zero. returns false on allocation failure (the bits is untouched).
function bool bitset_reserve(BitSet bits, int bit_count) {
    if bits == 0 {
        return false
    }
    if bit_count <= bits.bit_count {
        return true
    }
    let old_words = bits.word_count
    let new_words = bitset_words_for(bit_count)
    if new_words <= old_words {
        bits.bit_count = bit_count
        return true
    }
    let block = mem.make_zero(new_words * 8)
    if block == 0 {
        return false
    }
    if old_words > 0 && bits.words != 0 {
        mem.copy_cells(block, bits.words, old_words)
        free(bits.words)
    }
    bits.words = block
    bits.word_count = new_words
    bits.bit_count = bit_count
    return true
}

// read a bit. any index outside [0, bit_count) reads false.
function bool bitset_get(BitSet bits, int index) {
    if bits == 0 || index < 0 || index >= bits.bit_count {
        return false
    }
    let word_index = index / BITSET_WORD_BITS
    let bit_index = index % BITSET_WORD_BITS
    let words = bits.words as *i64
    let word = words[word_index]
    return ((word >> bit_index) & 1) != 0
}

function i64 bitset_word_mask(int bit_index) {
    return 1 << bit_index
}

// bits a bit to 1, growing if needed. returns false on allocation failure.
function bool bitset_set(BitSet bits, int index) {
    if bits == 0 || index < 0 {
        return false
    }
    if index >= bits.bit_count {
        if !bitset_reserve(bits, index + 1) {
            return false
        }
    }
    let word_index = index / BITSET_WORD_BITS
    let bit_index = index % BITSET_WORD_BITS
    let words = bits.words as *i64
    words[word_index] = words[word_index] | bitset_word_mask(bit_index)
    return true
}

// bits a bit to 0. does not grow; a bit outside the range is already 0.
function void bitset_clear(BitSet bits, int index) {
    if bits == 0 || index < 0 || index >= bits.bit_count {
        return
    }
    let word_index = index / BITSET_WORD_BITS
    let bit_index = index % BITSET_WORD_BITS
    let words = bits.words as *i64
    words[word_index] = words[word_index] & (bitset_word_mask(bit_index) ^ (0 - 1))
}

function void bitset_toggle(BitSet bits, int index) {
    if bits == 0 || index < 0 || index >= bits.bit_count {
        return
    }
    let word_index = index / BITSET_WORD_BITS
    let bit_index = index % BITSET_WORD_BITS
    let words = bits.words as *i64
    words[word_index] = words[word_index] ^ bitset_word_mask(bit_index)
}

function void bitset_set_all(BitSet bits) {
    if bits == 0 || bits.word_count <= 0 {
        return
    }
    let words = bits.words as *i64
    var i = 0
    while i < bits.word_count {
        words[i] = 0 - 1
        i++
    }
    bitset_trim_tail(bits)
}

function void bitset_clear_all(BitSet bits) {
    if bits == 0 || bits.words == 0 {
        return
    }
    memset(bits.words, 0, bits.word_count * 8)
}

// the top word can hold bits beyond bit_count; mask them off after set_all.
function void bitset_trim_tail(BitSet bits) {
    if bits == 0 || bits.word_count <= 0 || bits.bit_count <= 0 {
        return
    }
    let used_in_last = bits.bit_count % BITSET_WORD_BITS
    if used_in_last == 0 {
        return
    }
    let words = bits.words as *i64
    let last = bits.word_count - 1
    let keep = (1 << used_in_last) - 1
    words[last] = words[last] & keep
}

// number of bits bits. cheap to compute, this is a straightforward popcount.
function int bitset_count(BitSet bits) {
    if bits == 0 || bits.words == 0 {
        return 0
    }
    let words = bits.words as *i64
    var total = 0
    var i = 0
    while i < bits.word_count {
        var word = words[i]
        while word != 0 {
            word = word & (word - 1)
            total++
        }
        i++
    }
    return total
}

// index of the first bits bit at or after `start`, or -1 if none.
function int bitset_find_next(BitSet bits, int start) {
    if bits == 0 || bits.bit_count <= 0 {
        return -1
    }
    var index = start
    if index < 0 {
        index = 0
    }
    while index < bits.bit_count {
        if bitset_get(bits, index) {
            return index
        }
        index++
    }
    return -1
}

// bitset_set(a, index) for every bits bit in b. grows a as needed.
function void bitset_or_into(BitSet target, BitSet source) {
    if target == 0 || source == 0 {
        return
    }
    var index = bitset_find_next(source, 0)
    while index >= 0 {
        bitset_set(target, index)
        index = bitset_find_next(source, index + 1)
    }
}

function int bitset_and_count(BitSet a, BitSet b) {
    if a == 0 || b == 0 {
        return 0
    }
    let words_a = a.words as *i64
    let words_b = b.words as *i64
    var shared = a.word_count
    if b.word_count < shared {
        shared = b.word_count
    }
    var total = 0
    var i = 0
    while i < shared {
        var word = words_a[i] & words_b[i]
        while word != 0 {
            word = word & (word - 1)
            total++
        }
        i++
    }
    return total
}

// true when a and b share at)SBBITSET"
            R"SBBITSET( least one bits bit.
function bool bitset_intersects(BitSet a, BitSet b) {
    if a == 0 || b == 0 {
        return false
    }
    let words_a = a.words as *i64
    let words_b = b.words as *i64
    var shared = a.word_count
    if b.word_count < shared {
        shared = b.word_count
    }
    var i = 0
    while i < shared {
        if (words_a[i] & words_b[i]) != 0 {
            return true
        }
        i++
    }
    return false
}
)SBBITSET"},
        {"cpp_vector", R"SBCPPVECTO(import mem
import vec

using CppVectorSizeFn = fn(ptr) -> i64
using CppVectorDataFn = fn(ptr) -> ptr
using CppVectorPushBackI64Fn = fn(ptr, i64) -> void

// MSVC std::vector-style layout view for 8-byte cells:
// [first ptr][last ptr][end ptr]

enum CppVectorOffset {
    First = 0,
    Last = 8,
    Finish = 16,
}

view CppVector {
    first: ptr @ CppVectorOffset.First
    last: ptr @ CppVectorOffset.Last
    finish: ptr @ CppVectorOffset.Finish
}

function CppVector cpp_vector_from_range(ptr first, ptr last, ptr finish) {
    let view_obj = malloc(24) as CppVector
    if view_obj == 0 {
        return 0 as CppVector
    }
    view_obj.first = first
    view_obj.last = last
    view_obj.finish = finish
    return view_obj
}

function CppVector cpp_vector_read(ptr object_addr) {
    if object_addr == 0 {
        return cpp_vector_from_range(0, 0, 0)
    }
    let raw = object_addr as CppVector
    return cpp_vector_from_range(raw.first, raw.last, raw.finish)
}

function CppVector cpp_vector_from_array(ptr data) {
    if data == 0 {
        return cpp_vector_from_range(0, 0, 0)
    }

    let used = array_len(data)
    var capacity = mem.read(data - 8)
    if capacity < used {
        capacity = used
    }
    let last = data + used * 8
    let finish = data + capacity * 8
    return cpp_vector_from_range(data, last, finish)
}

function ptr cpp_vector_data(CppVector view_obj) {
    if view_obj == 0 {
        return 0
    }
    return view_obj.first
}

function int cpp_vector_size(CppVector view_obj) {
    if view_obj == 0 {
        return 0
    }
    let first = view_obj.first
    let last = view_obj.last
    if first == 0 || last < first {
        return 0
    }
    return (last - first) / 8
}

function int cpp_vector_capacity(CppVector view_obj) {
    if view_obj == 0 {
        return 0
    }
    let first = view_obj.first
    let finish = view_obj.finish
    if first == 0 || finish < first {
        return 0
    }
    return (finish - first) / 8
}

function bool cpp_vector_is_empty(CppVector view_obj) {
    return cpp_vector_size(view_obj) == 0
}

function i64 cpp_vector_at_i64(CppVector view_obj, int idx) {
    let count = cpp_vector_size(view_obj)
    if idx < 0 || idx >= count {
        return 0
    }
    let arr = view_obj.first as *i64
    return arr[idx]
}

function i64 cpp_vector_front_i64(CppVector view_obj) {
    return cpp_vector_at_i64(view_obj, 0)
}

function i64 cpp_vector_back_i64(CppVector view_obj) {
    let count = cpp_vector_size(view_obj)
    if count <= 0 {
        return 0
    }
    return cpp_vector_at_i64(view_obj, count - 1)
}

function Vec cpp_vector_copy_view_i64(CppVector view_obj) {
    let count = cpp_vector_size(view_obj)
    var out = vec_new(count)
    if count > 0 && view_obj.first != 0 && out.data != 0 {
        mem.copy_cells(out.data, view_obj.first, count)
        out.size = count
        mem.write(out.data - 16, count)
    }
    return out
}

function Vec cpp_vector_copy_i64(ptr object_addr) {
    let view_obj = cpp_vector_read(object_addr)
    let out = cpp_vector_copy_view_i64(view_obj)
    cpp_vector_free(view_obj)
    return out
}

function void cpp_vector_free(CppVector view_obj) {
    if view_obj != 0 {
        free(view_obj)
    }
}

function i64 cpp_vector_call_size(ptr method_addr, ptr this_vec) {
    let method = method_addr as CppVectorSizeFn
    return method(this_vec)
}

function ptr cpp_vector_call_data(ptr method_addr, ptr this_vec) {
    let method = method_addr as CppVectorDataFn
    return method(this_vec)
}

function void cpp_vector_call_push_back_i64(ptr method_addr, ptr this_vec, i64 item) {
    let method = method_addr as CppVectorPushBackI64Fn
    method(this_vec, item)
}
)SBCPPVECTO"},
        {"demo", R"SBDEMO(import mem
import text
import vec
import cpp_vector
import option
import result
import owner
import algo

// Headless smoke test for the standalone stdlib.
// Returns 0 on success so it can be used in automated host-compiler checks.

function int main() {
    let raw = mem_alloc_zero(32)
    if raw == 0 {
        return 1
    } else {
        mem_fill(raw, 0x41, 8)
        mem_write(raw + 8, 1234)
        if mem_read(raw + 8) != 1234 {
            return 2
        }
    }

    let greeting = text_join3("hello", " ", "stdlib")
    let padded = text_pad_right(greeting, 14, ".")
    if text_eq(greeting, "hello stdlib") == 0 {
        return 3
    }
    if text_eq(padded, "hello stdlib..") == 0 {
        return 4
    }

    var numbers = vec_new(4)
    numbers = vec_push(numbers, 30)
    numbers = vec_push(numbers, 10)
    numbers = vec_push(numbers, 20)
    if vec_len(numbers) != 3 {
        return 5
    }
    algo_sort_i64(vec_data(numbers), vec_len(numbers))
    if vec_first(numbers) != 10 {
        return 6
    }
    if vec_last(numbers) != 30 {
        return 7
    }
    numbers = vec_set(numbers, 1, 25)
    if vec_get(numbers, 1) != 25 {
        return 8
    }
    if vec_pop_value(numbers) != 30 {
        return 9
    }
    numbers = vec_pop(numbers)
    if vec_len(numbers) != 2 {
        return 10
    }
    if array_len(vec_data(numbers)) != vec_len(numbers) {
        return 29
    }
    if vec_contains(numbers, 25) == 0 {
        return 11
    }
    if vec_index_of(numbers, 25) != 1 {
        return 12
    }

    let maybe_total = opt_i64_some(vec_len(numbers))
    if opt_i64_is_some(maybe_total) == 0 {
        return 13
    }
    if opt_i64_unwrap(maybe_total) != 2 {
        return 14
    }
    opt_i64_free(maybe_total)

    let parsed = res_i64_ok(vec_first(numbers))
    if res_i64_is_ok(parsed) == 0 {
        return 15
    }
    if res_i64_unwrap(parsed) != 10 {
        return 16
    }
    res_i64_free(parsed)

    let foreign_cells = array_new(3)
    array_set(foreign_cells, 0, 7)
    array_set(foreign_cells, 1, 9)
    array_set(foreign_cells, 2, 11)
    let foreign_view = cpp_vector_from_array(foreign_cells)
    if cpp_vector_size(foreign_view) != 3 {
        return 17
    }
    if cpp_vector_back_i64(foreign_view) != 11 {
        return 18
    }

    var copied = cpp_vector_copy_view_i64(foreign_view)
    if vec_len(copied) != 3 {
        return 19
    }
    if vec_first(copied) != 7 {
        return 20
    }
    copied = vec_append(copied, numbers)
    if vec_len(copied) != 5 {
        return 21
    }
    copied = vec_remove_at(copied, 1)
    if vec_len(copied) != 4 {
        return 22
    }
    if array_len(vec_data(copied)) != vec_len(copied) {
        return 30
    }
    copied = vec_swap_remove(copied, 0)
    if vec_len(copied) != 3 {
        return 23
    }
    if array_len(vec_data(copied)) != vec_len(copied) {
        return 31
    }
    copied = vec_shrink_to_fit(copied)
    if vec_cap(copied) < vec_len(copied) {
        return 24
    }

    let copied_array = vec_to_array_copy(numbers)
    var wrapped_copy = vec_from_array_copy(copied_array)
    if vec_len(wrapped_copy) != vec_len(numbers) {
        return 25
    }
    if vec_first(wrapped_copy) != vec_first(numbers) {
        return 26
    }
    wrapped_copy = vec_clear(wrapped_copy)
    if array_len(vec_data(wrapped_copy)) != 0 {
        return 32
    }

    var owned_copy = owned_str_clone(padded)
    if owned_str_is_owned(owned_copy) == 0 {
        return 27
    }
    if text_eq(owned_str_get(owned_copy), padded) == 0 {
        return 28
    }

    cpp_vector_free(foreign_view)
    copied = vec_free(copied)
    wrapped_copy = vec_free(wrapped_copy)
    numbers = vec_free(numbers)
    owned_copy = owned_str_dispose(owned_copy)
    array_free(copied_array)
    array_free(foreign_cells)
    free(greeting)
    free(padded)
    mem_free_ptr(raw)

    return 0
}
)SBDEMO"},
        {"fmt", R"SBFMT(import ascii
import mem
import text

// Formatting helpers using single-pass buffer assembly.
// Ownership:
// - every fmt_* function returning str returns a heap string; caller must free.

function str fmt_bool(bool flag) {
    if flag {
        return text_clone("true")
    }
    return text_clone("false")
}

function str fmt_int(int number) {
    return int_to_string(number)
}

function str fmt_int_pad_left(int number, int width) {
    let raw = int_to_string(number)
    let out = text_pad_left(raw, width, "0")
    free(raw)
    return out
}

function str fmt_pair(str key, str val) {
    return text_join3(key, ": ", val)
}

function str fmt_csv3(str a, str b, str c) {
    let la = string_length(a)
    let lb = string_length(b)
    let lc = string_length(c)
    let total = la + lb + lc + 2
    let buf = malloc(total + 1)
    if buf == 0 {
        return text_clone("")
    }
    var pos = 0
    if la > 0 { memcpy(buf, a as ptr, la); pos += la }
    mem.write8(buf + pos, 44)
    pos++
    if lb > 0 { memcpy(buf + pos, b as ptr, lb); pos += lb }
    mem.write8(buf + pos, 44)
    pos++
    if lc > 0 { memcpy(buf + pos, c as ptr, lc); pos += lc }
    mem.write8(buf + pos, 0)
    let out = make_string(buf)
    free(buf)
    return out
}

function str fmt_wrap(str val, str left, str right) {
    return text_surround(val, left, right)
}

function str fmt_hex_byte(int byte_value) {
    let buf = malloc(5)
    if buf == 0 {
        return text_clone("0x00")
    }
    mem.write8(buf, 48)
    mem.write8(buf + 1, 120)
    mem.write8(buf + 2, ascii_hex_nibble_char((byte_value >> 4) & 15))
    mem.write8(buf + 3, ascii_hex_nibble_char(byte_value & 15))
    mem.write8(buf + 4, 0)
    let out = make_string(buf)
    free(buf)
    return out
}
)SBFMT"},
        {"fs", R"SBFS(import text

// Filesystem-style helpers over the builtin file/string layer.
// Ownership:
// - fs_read_text/fs_read_or return heap strings; caller must free.

function str fs_read_text(str file_path) {
    return read_file(file_path)
}

function int fs_write_text(str file_path, str body) {
    return write_file(file_path, body)
}

function bool fs_write_ok(str file_path, str body) {
    return fs_write_text(file_path, body) != 0
}

function str fs_read_or(str file_path, str fallback) {
    let content = fs_read_text(file_path)
    if content == 0 {
        return text_clone(fallback)
    }
    return content
}

function bool fs_starts_with(str file_path, str prefix) {
    let content = fs_read_text(file_path)
    if content == 0 {
        return false
    }
    let ok = text_starts_with(content, prefix)
    free(content)
    return ok
}

function bool fs_contains(str file_path, str needle) {
    let content = fs_read_text(file_path)
    if content == 0 {
        return false
    }
    let ok = text_contains(content, needle)
    free(content)
    return ok
}
)SBFS"},
        {"hash", R"SBHASH(import mem

// Hashing and checksums.
//
// Every function here is pure over its inputs: nothing allocates, nothing frees,
// nothing mutates the caller's memory. A hash is just an i64; run it through
// hash_mix_i64 and hash_bucket before using it as an index, because the raw
// hashes of short inputs are correlated in their low bits.
//
// Ownership: none of these functions return heap memory.

// FNV-1a 64-bit constants.
let HASH_FNV_OFFSET: i64 = 0xCBF29CE484222325
let HASH_FNV_PRIME: i64 = 0x100000001B3

// mask for the low 32 bits, used by the 32-bit CRC and the u32 wrapper.
let HASH_MASK32: i64 = 0xFFFFFFFF

// splitmix64 finalizer constants.
let HASH_MIX_MUL1: i64 = 0xBF58476D1CE4E5B9
let HASH_MIX_MUL2: i64 = 0x94D049BB133111EB

// FNV-1a over a raw buffer. Empty input yields the offset basis, which is a
// defined non-zero value, not an error.
function i64 hash_fnv1a_bytes(ptr data, int len) {
    if data == 0 || len <= 0 {
        return HASH_FNV_OFFSET
    }
    let bytes = data as *u8
    var h = HASH_FNV_OFFSET
    var i = 0
    while i < len {
        h = h ^ (bytes[i] as i64)
        h = h * HASH_FNV_PRIME
        i++
    }
    return h
}

function i64 hash_fnv1a(str text_value) {
    if text_value == 0 {
        return HASH_FNV_OFFSET
    }
    return hash_fnv1a_bytes(text_value as ptr, string_length(text_value))
}

// FNV-1a over the 8 native bytes of an integer. Useful for hashing ids.
function i64 hash_fnv1a_i64(i64 value) {
    var h = HASH_FNV_OFFSET
    var remaining = value
    var i = 0
    while i < 8 {
        h = h ^ (remaining & 0xFF)
        h = h * HASH_FNV_PRIME
        remaining = remaining >> 8
        i++
    }
    return h
}

// djb2: cheaper than FNV, weaker distribution. Handy for small string tables.
function i64 hash_djb2(str text_value) {
    if text_value == 0 {
        return 5381
    }
    let len = string_length(text_value)
    let bytes = text_value as ptr
    var h = 5381
    var i = 0
    while i < len {
        h = ((h << 5) + h) + mem.read8(bytes + i)
        i++
    }
    return h
}

// CRC-32 (IEEE 802.3, polynomial 0xEDB88320) over a raw buffer.
function i64 hash_crc32_bytes(ptr data, int len) {
    if data == 0 || len <= 0 {
        return 0
    }
    let bytes = data as *u8
    var crc = HASH_MASK32
    var i = 0
    while i < len {
        crc = crc ^ (bytes[i] as i64)
        var bit = 0
        while bit < 8 {
            if (crc & 1) != 0 {
                crc = (crc >> 1) ^ 0xEDB88320
            } else {
                crc = crc >> 1
            }
            bit++
        }
        i++
    }
    return crc ^ HASH_MASK32
}

function i64 hash_crc32(str text_value) {
    if text_value == 0 {
        return 0
    }
    return hash_crc32_bytes(text_value as ptr, string_length(text_value))
}

// splitmix64 finalizer: avalanches every input bit across the output. This is
// the step that makes a sequential id usable as a hash table index.
function i64 hash_mix_i64(i64 value) {
    var x = value
    x = x ^ (x >> 33)
    x = x * HASH_MIX_MUL1
    x = x ^ (x >> 29)
    x = x * HASH_MIX_MUL2
    x = x ^ (x >> 32)
    return x
}

// Combine two hashes into one. Order matters, so (a, b) and (b, a) differ.
function i64 hash_combine(i64 first, i64 second) {
    return hash_mix_i64(first ^ (hash_mix_i64(second) + 0x9E3779B97F4A7C15))
}

// The low 32 bits, zero-extended. This is CRC-32's natural width.
function i64 hash_to_u32(i64 value) {
    return value & HASH_MASK32
}

// Map any hash onto [0, buckets). Returns 0 when buckets <= 0 so a bad bucket
// count cannot divide by zero.
function i64 hash_bucket(i64 value, int buckets) {
    if buckets <= 0 {
        return 0
    }
    let mixed = hash_mix_i64(value)
    // keep the value non-negative before the modulo so the result is never
    // negative for a negative hash
    let positive = mixed & 0x7FFFFFFFFFFFFFFF
    return positive % (buckets as i64)
}

// Sum of every byte, wrapping at 64 bits. A cheap integrity check, not a hash:
// it cannot detect reordering.
function i64 checksum_sum_bytes(ptr data, int len) {
    if data == 0 || len <= 0 {
        return 0
    }
    let bytes = data as *u8
    var total = 0
    var i = 0
    while i < len {
        total = total + (bytes[i] as i64)
        i++
    }
    return total
}

// XOR of every byte. Cheap, and sensitive to every byte, but blind to
// duplicate bytes cancelling out.
function i64 checksum_xor_bytes(ptr data, int len) {
    if data == 0 || len <= 0 {
        return 0
    }
    let bytes = data as *u8
    var acc = 0
    var i = 0
    while i < len {
        acc = acc ^ (bytes[i] as i64)
        i++
    }
    return acc
}

// Adler-32: two running sums mod 65521, combined into 32 bits. Stronger than a
// plain sum for the same cost.
function i64 checksum_adler32(ptr data, int len) {
    if data == 0 || len <= 0 {
        return 1
    }
    let bytes = data as *u8
    var a = 1
    var b = 0
    var i = 0
    while i < len {
        a = (a + (bytes[i] as i64)) % 65521
        b = (b + a) % 65521
        i++
    }
    return (b << 16) | a
}
)SBHASH"},
        {"http", R"SBHTTP(import mem

// HTTP client helpers built on WinHTTP using typed function pointers and zero-copy views.

enum HttpUrlOffset {
    Secure = 0,
    Port = 8,
    Host = 16,
    Path = 24,
}

enum HttpResponseOffset {
    Status = 0,
    Body = 8,
    RawHeaders = 16,   // CRLF-separated header block (owned) or 0
    BodyBytes = 24,    // raw body buffer (owned), binary-safe, NOT null-terminated
    BodyLen = 32,      // length of BodyBytes in bytes
}

enum HttpWidePartsOffset {
    UserAgentW = 0,
    MethodW = 8,
    HostW = 16,
    PathW = 24,
}

view HttpUrl {
    secure: int @ HttpUrlOffset.Secure
    port: int @ HttpUrlOffset.Port
    host: str @ HttpUrlOffset.Host
    path: str @ HttpUrlOffset.Path
}

view HttpResponse {
    status: int @ HttpResponseOffset.Status
    body: str @ HttpResponseOffset.Body
    raw_headers: str @ HttpResponseOffset.RawHeaders
    body_bytes: ptr @ HttpResponseOffset.BodyBytes
    body_len: int @ HttpResponseOffset.BodyLen
}

view HttpWideParts {
    user_agent_w: ptr @ HttpWidePartsOffset.UserAgentW
    method_w: ptr @ HttpWidePartsOffset.MethodW
    host_w: ptr @ HttpWidePartsOffset.HostW
    path_w: ptr @ HttpWidePartsOffset.PathW
}

using WinHttpOpenFn = fn(ptr, int, ptr, ptr, int) -> ptr
using WinHttpSetTimeoutsFn = fn(ptr, int, int, int, int) -> int
using WinHttpConnectFn = fn(ptr, ptr, int, int) -> ptr
using WinHttpOpenRequestFn = fn(ptr, ptr, ptr, ptr, ptr, ptr, int) -> ptr
using WinHttpSendRequestFn = fn(ptr, ptr, int, ptr, int, int, int) -> int
using WinHttpReceiveResponseFn = fn(ptr, ptr) -> int
using WinHttpQueryHeadersFn = fn(ptr, int, ptr, ptr, ptr, ptr) -> int
using WinHttpQueryDataAvailableFn = fn(ptr, ptr) -> int
using WinHttpReadDataFn = fn(ptr, ptr, int, ptr) -> int
using WinHttpCloseHandleFn = fn(ptr) -> int
using WinHttpAddRequestHeadersFn = fn(ptr, ptr, int, int) -> int
using WinHttpSetOptionFn = fn(ptr, int, ptr, int) -> int

function str http_empty_text() {
    return string_substring("", 0, 0)
}

function ptr http_make_zero(int size) {
    return mem.make_zero(size)
}

function bool http_is_digit(int ch) {
    return ch >= 48 and ch <= 57
}

function int http_len(str text_value) {
    return string_length(text_value)
}

function bool http_eq(str left, str right) {
    return string_equals(left, right) != 0
}

function bool http_is_empty(str text_value) {
    return string_length(text_value) == 0
}

function str http_clone(str text_value) {
    if text_value == 0 {
        return http_empty_text()
    }
    return string_substring(text_value, 0, string_length(text_value))
}

function str http_slice(str text_value, int start_idx, int slice_len) {
    return string_substring(text_value, start_idx, slice_len)
}

function str http_prefix(str text_value, int slice_len) {
    return string_substring(text_value, 0, slice_len)
}

function str http_join2(str left, str right) {
    return string_append(left, right)
}

function str http_join3(str a, str b, str c) {
    let ab = string_append(a, b)
    let abc = string_append(ab, c)
    free(ab)
    return abc
}

function str http_join4(str a, str b, str c, str d) {
    let ab = string_append(a, b)
    let abc = string_append(ab, c)
    let abcd = string_append(abc, d)
    free(ab)
    free(abc)
    return abcd
}

function int http_hex_digit(int ch) {
    if ch >= 48 and ch <= 57 {
        return ch - 48
    }
    if ch >= 65 and ch <= 70 {
        return ch - 55
    }
    if ch >= 97 and ch <= 102 {
        return ch - 87
    }
    return -1
}

function int http_hex_char(int nibble) {
    if nibble < 10 {
        return 48 + nibble
    }
    return 65 + nibble - 10
}

// percent-encode for URLs and query values: unreserved (alnum -_.~) pass through
function int http_url_encoded_len(str text_value) {
    if text_value == 0 {
        return 0
    }
    let len = string_length(text_value)
    let p = text_value as ptr
    var total = 0
    var i = 0
    while i < len {
        let ch = mem.read8(p + i)
        let unreserved = (ch >= 48 and ch <= 57) or (ch >= 65 and ch <= 90) or
                         (ch >= 97 and ch <= 122) or ch == 45 or ch == 46 or
                         ch == 95 or ch == 126
        if unreserved {
            total++
        } else {
            total += 3
        }
        i++
    }
    return total
}

// write the percent-encoded form of text_value at dst+off, return the new offset
function int http_url_encode_into(ptr dst, int off, str text_value) {
    if text_value == 0 {
        return off
    }
    let len = string_length(text_value)
    let p = text_value as ptr
    var w = off
    var i = 0
    while i < len {
        let ch = mem.read8(p + i)
        let unreserved = (ch >= 48 and ch <= 57) or (ch >= 65 and ch <= 90) or
                         (ch >= 97 and ch <= 122) or ch == 45 or ch == 46 or
                         ch == 95 or ch == 126
        if unreserved {
            mem.write8(dst + w, ch)
            w++
        } else {
            mem.write8(dst + w, 37)
            mem.write8(dst + w + 1, http_hex_char((ch >> 4) & 15))
            mem.write8(dst + w + 2, http_hex_char(ch & 15))
            w += 3
        }
        i++
    }
    return w
}

function str http_url_encode(str text_value) {
    if text_value == 0 {
        return http_empty_text()
    }
    let need = http_url_encoded_len(text_value)
    let out = malloc(need + 1)
    if out == 0 {
        return http_empty_text()
    }
    let stop = http_url_encode_into(out, 0, text_value)
    mem.write8(out + stop, 0)
    let result = make_string(out)
    free(out)
    return result
}

// decode %XX and treat '+' as space
function str http_url_decode(str text_value) {
    if text_value == 0 {
        return http_empty_text()
    }
    let len = string_length(text_value)
    if len == 0 {
        return http_empty_text()
    }
    let p = text_value as ptr
    let out = malloc(len + 1)
    if out == 0 {
        return http_empty_text()
    }
    var write_idx = 0
    var i = 0
    while i < len {
        let ch = mem.read8(p + i)
        if ch == 37 and i + 2 < len {
            let hi = http_hex_digit(mem.read8(p + i + 1))
            let lo = http_hex_digit(mem.read8(p + i + 2))
            if hi >= 0 and lo >= 0 {
                mem.write8(out + write_idx, hi * 16 + lo)
                write_idx++
                i += 3
                continue
            }
        }
        if ch == 43 {
            mem.write8(out + write_idx, 32)
            write_idx++
            i++
            continue
        }
        mem.write8(out + write_idx, ch)
        write_idx++
        i++
    }
    mem.write8(out + write_idx, 0)
    let result = make_string(out)
    free(out)
    return result
}

function int http_find(str text_value, str needle) {
    let text_len_val = string_length(text_value)
    let needle_len = string_length(needle)
    if needle_len == 0 {
        return 0
    }
    if needle_len > text_len_val {
        return -1
    }

    let hay = text_value as ptr
    let ndl = needle as ptr
    let first = mem.read8(ndl)
    let limit = text_len_val - needle_len
    var i = 0
    while i <= limit {
        if mem.read8(hay + i) == first {
            if needle_len == 1 or memcmp(hay + i + 1, ndl + 1, needle_len - 1) == 0 {
                return i
            }
        }
        i++
    }
    return -1
}

function int http_rfind_char(str text_value, int ch) {
    let p = text_value as ptr
    let target = ch & 255
    var i = string_length(text_value) - 1
    while i >= 0 {
        if mem.read8(p + i) == target {
            return i
        }
        i--
    }
    return -1
}

function HttpUrl http_url_new() {
    let parsed = malloc(32) as HttpUrl
    if parsed == 0 {
        return 0 as HttpUrl
    }
    parsed.secure = 1
    parsed.port = 443
    parsed.host = 0 as str
    parsed.path = 0 as str
    return parsed
}

function void http_url_free(HttpUrl parsed) {
    if parsed == 0 {
        return
    }
    if parsed.host != 0 {
        free(parsed.host)
    }
    if parsed.path != 0 {
        free(parsed.path)
    }
    free(parsed)
}

// Response constructors take ownership of the header/body buffers they are
// given (http_request_send pas)SBHTTP"
            R"SBHTTP(ses freshly allocated ones). body_text and
// raw_headers must be heap-owned (or 0); pass a literal and the later
// http_response_free would hand a PE image pointer to HeapFree.
function HttpResponse http_response_new(int status, str body_text) {
    let response = malloc(40) as HttpResponse
    if response == 0 {
        if body_text != 0 {
            free(body_text)
        }
        return 0 as HttpResponse
    }
    response.status = status
    response.body = body_text
    response.raw_headers = 0 as str
    response.body_bytes = 0
    response.body_len = 0
    return response
}

function HttpResponse http_response_new_full(int status, str body_text, str raw_headers) {
    let response = malloc(40) as HttpResponse
    if response == 0 {
        if body_text != 0 {
            free(body_text)
        }
        if raw_headers != 0 {
            free(raw_headers)
        }
        return 0 as HttpResponse
    }
    response.status = status
    response.body = body_text
    response.raw_headers = raw_headers
    response.body_bytes = 0
    response.body_len = 0
    return response
}

// like http_response_new_full but also carries a binary-safe body buffer.
// body_bytes keeps the exact bytes (including embedded NULs) and body_len its
// length; body_text is a null-terminated view for convenience.
function HttpResponse http_response_new_binary(int status, ptr body_bytes, int body_len, str raw_headers) {
    let response = malloc(40) as HttpResponse
    if response == 0 {
        if raw_headers != 0 {
            free(raw_headers)
        }
        return 0 as HttpResponse
    }
    response.status = status
    response.raw_headers = raw_headers
    response.body_bytes = body_bytes
    response.body_len = body_len
    if body_bytes != 0 {
        response.body = make_string(body_bytes)
    } else {
        response.body = http_empty_text()
    }
    return response
}

function HttpWideParts http_wide_parts_new() {
    let parts = malloc(32) as HttpWideParts
    if parts == 0 {
        return 0 as HttpWideParts
    }
    parts.user_agent_w = 0
    parts.method_w = 0
    parts.host_w = 0
    parts.path_w = 0
    return parts
}

function void http_wide_parts_free(HttpWideParts parts) {
    if parts == 0 {
        return
    }
    if parts.user_agent_w != 0 {
        free(parts.user_agent_w)
    }
    if parts.method_w != 0 {
        free(parts.method_w)
    }
    if parts.host_w != 0 {
        free(parts.host_w)
    }
    if parts.path_w != 0 {
        free(parts.path_w)
    }
    free(parts)
}

function HttpResponse http_fail_response() {
    return http_response_new(0, http_empty_text())
}

function void http_response_free(HttpResponse response) {
    if response == 0 {
        return
    }
    if response.body != 0 {
        free(response.body)
    }
    if response.raw_headers != 0 {
        free(response.raw_headers)
    }
    if response.body_bytes != 0 {
        free(response.body_bytes)
    }
    free(response)
}

function bool http_ok(HttpResponse response) {
    if response == 0 {
        return false
    }
    return response.status >= 200 and response.status < 300
}

function int http_parse_port(str text_value) {
    let len = http_len(text_value)
    if len <= 0 or len > 5 {
        return -1
    }

    let p = text_value as ptr
    var value = 0
    var i = 0
    while i < len {
        let ch = mem.read8(p + i)
        if !http_is_digit(ch) {
            return -1
        }
        value = value * 10 + (ch - 48)
        i++
    }
    if value <= 0 or value > 65535 {
        return -1
    }
    return value
}

function ptr http_utf16z(str text_value) {
    if text_value == 0 {
        return 0
    }
    let len = string_length(text_value)
    let out = mem.make_zero((len + 1) * 2)
    if out == 0 {
        return 0
    }

    let p = text_value as ptr
    var i = 0
    while i < len {
        mem.write16(out + i * 2, mem.read8(p + i))
        i++
    }
    return out
}

function ptr http_url_host_utf16(HttpUrl parsed) {
    if parsed == 0 or parsed.host == 0 {
        return 0
    }
    return http_utf16z(parsed.host)
}

function ptr http_url_path_utf16(HttpUrl parsed) {
    if parsed == 0 or parsed.path == 0 {
        return 0
    }
    return http_utf16z(parsed.path)
}

function ptr http_open_session(ptr open_fn, ptr set_timeouts_fn) {
    let user_agent_w = http_utf16z("Sable/WinHTTP")
    if user_agent_w == 0 {
        return 0
    }

    let winhttp_open = open_fn as WinHttpOpenFn
    let session = winhttp_open(user_agent_w, 1, 0, 0, 0)
    free(user_agent_w)
    if session != 0 and set_timeouts_fn != 0 {
        let winhttp_set_timeouts = set_timeouts_fn as WinHttpSetTimeoutsFn
        winhttp_set_timeouts(session, 5000, 5000, 5000, 5000)
    }
    return session
}

function str http_bytes_to_text(ptr bytes, int len) {
    let copy = mem.make_zero(len + 1)
    if copy == 0 {
        return http_empty_text()
    }
    if len > 0 and bytes != 0 {
        memcpy(copy, bytes, len)
    }
    let out = make_string(copy)
    free(copy)
    return out
}

function str http_take_path(str url, int start_idx, int stop_idx) {
    if start_idx >= stop_idx {
        return http_clone("/")
    }

    let p = url as ptr
    let first = mem.read8(p + start_idx)
    if first == 47 {
        return http_slice(url, start_idx, stop_idx - start_idx)
    }

    let suffix = http_slice(url, start_idx, stop_idx - start_idx)
    let out = http_join2("/", suffix)
    free(suffix)
    return out
}

function HttpUrl http_parse_url(str url) {
    if url == 0 {
        return 0 as HttpUrl
    }
    let parsed = http_url_new()
    if parsed == 0 {
        return 0 as HttpUrl
    }

    let url_len = http_len(url)
    let p = url as ptr
    var start = 0

    if url_len >= 8 and memcmp(p, "https://" as ptr, 8) == 0 {
        parsed.secure = 1
        parsed.port = 443
        start = 8
    } else if url_len >= 7 and memcmp(p, "http://" as ptr, 7) == 0 {
        parsed.secure = 0
        parsed.port = 80
        start = 7
    }

    if start >= url_len {
        http_url_free(parsed)
        return 0 as HttpUrl
    }

    var host_end = start
    while host_end < url_len {
        let ch = mem.read8(p + host_end)
        if ch == 47 or ch == 63 {
            break
        }
        host_end++
    }

    if host_end <= start {
        http_url_free(parsed)
        return 0 as HttpUrl
    }

    // Optional host:port parsing
    var host_stop = host_end
    var colon_idx = start
    while colon_idx < host_end {
        if mem.read8(p + colon_idx) == 58 {
            let port_str = string_substring(url, colon_idx + 1, host_end - colon_idx - 1)
            let parsed_port = http_parse_port(port_str)
            free(port_str)
            if parsed_port <= 0 {
                http_url_free(parsed)
                return 0 as HttpUrl
            }
            parsed.port = parsed_port
            host_stop = colon_idx
            break
        }
        colon_idx++
    }

    if host_stop <= start {
        http_url_free(parsed)
        return 0 as HttpUrl
    }

    parsed.host = string_substring(url, start, host_stop - start)
    if parsed.host == 0 or string_length(parsed.host) == 0 {
        http_url_free(parsed)
        return 0 as HttpUrl
    }

    parsed.path = http_take_path(url, host_end, url_len)
    if parsed.path == 0 {
        http_url_free(parsed)
        return 0 as HttpUrl
    }

    return parsed
}

function void http_close_if(ptr close_fn, ptr handle_value) {
    if handle_value != 0 and close_fn != 0 {
        let winhttp_close = close_fn as WinHttpCloseHandleFn
        winhttp_close(handle_value)
    }
}

function int http_query_status(ptr request_handle, ptr query_headers) {
    let status_ptr = mem.make_zero(8)
    let size_ptr = mem.make_zero(8)
    if status_ptr == 0 or size_ptr == 0 {
        if status_ptr != 0 { free(status_ptr) }
        if size_ptr != 0 { free(size_ptr) }
        return 0
    }

    mem.write32(size_ptr, 4)
    var status = 0
    let query_fn = query_headers as WinHttpQueryHeadersFn
    // WINHTTP_QUERY_STATUS_CODE (19) | WINHTTP_QUERY_FLAG_NUMBER (0x20000000)
    let ok = query_fn(request_handle, 19 + 536870912,)SBHTTP"
            R"SBHTTP( 0, status_ptr, size_ptr, 0)
    if ok != 0 {
        status = mem.read32(status_ptr)
    }

    free(status_ptr)
    free(size_ptr)
    return status
}

// Read the full response body into a freshly allocated buffer.
// Returns the buffer pointer (caller frees) and writes the byte count to
// len_out. Keeps embedded NULs, so it is safe for binary payloads.
function ptr http_read_body_bytes(ptr request_handle, ptr query_data_available, ptr read_data, ptr len_out) {
    let available_ptr = mem.make_zero(8)
    let read_count_ptr = mem.make_zero(8)
    var cap = 4096
    var total_len = 0
    var buf = malloc(cap + 1)
    if available_ptr == 0 or read_count_ptr == 0 or buf == 0 {
        if available_ptr != 0 { free(available_ptr) }
        if read_count_ptr != 0 { free(read_count_ptr) }
        if buf != 0 { free(buf) }
        mem.write(len_out, 0)
        return 0
    }

    let query_avail_fn = query_data_available as WinHttpQueryDataAvailableFn
    let read_data_fn = read_data as WinHttpReadDataFn
    var failed = false

    while true {
        mem.write32(available_ptr, 0)
        if query_avail_fn(request_handle, available_ptr) == 0 {
            failed = true
            break
        }

        let available = mem.read32(available_ptr)
        if available <= 0 {
            break
        }

        if total_len + available + 1 > cap {
            var new_cap = cap
            while new_cap < total_len + available + 1 {
                new_cap = new_cap * 2
            }
            let next_buf = malloc(new_cap + 1)
            if next_buf == 0 {
                failed = true
                break
            }
            if total_len > 0 {
                memcpy(next_buf, buf, total_len)
            }
            free(buf)
            buf = next_buf
            cap = new_cap
        }

        mem.write32(read_count_ptr, 0)
        if read_data_fn(request_handle, buf + total_len, available, read_count_ptr) == 0 {
            failed = true
            break
        }

        let chunk_len = mem.read32(read_count_ptr)
        if chunk_len <= 0 {
            break
        }
        total_len = total_len + chunk_len
    }

    free(available_ptr)
    free(read_count_ptr)
    if failed {
        free(buf)
        mem.write(len_out, 0)
        return 0
    }
    mem.write8(buf + total_len, 0)
    mem.write(len_out, total_len)
    return buf
}

function str http_read_body(ptr request_handle, ptr query_data_available, ptr read_data) {
    let len_ptr = mem.make_zero(8)
    if len_ptr == 0 {
        return http_empty_text()
    }
    let buf = http_read_body_bytes(request_handle, query_data_available, read_data, len_ptr)
    free(len_ptr)
    if buf == 0 {
        return http_empty_text()
    }
    let out = make_string(buf)
    free(buf)
    return out
}

function HttpResponse http_fetch(str url) {
    let parsed = http_parse_url(url)
    if parsed == 0 {
        return http_fail_response()
    }

    let module_handle = load_library("winhttp.dll")
    if module_handle == 0 {
        http_url_free(parsed)
        return http_fail_response()
    }

    let open_fn = get_proc(module_handle, "WinHttpOpen")
    let connect_fn = get_proc(module_handle, "WinHttpConnect")
    let open_request_fn = get_proc(module_handle, "WinHttpOpenRequest")
    let send_request_fn = get_proc(module_handle, "WinHttpSendRequest")
    let receive_response_fn = get_proc(module_handle, "WinHttpReceiveResponse")
    let query_data_available_fn = get_proc(module_handle, "WinHttpQueryDataAvailable")
    let query_headers_fn = get_proc(module_handle, "WinHttpQueryHeaders")
    let read_data_fn = get_proc(module_handle, "WinHttpReadData")
    let set_timeouts_fn = get_proc(module_handle, "WinHttpSetTimeouts")
    let close_handle_fn = get_proc(module_handle, "WinHttpCloseHandle")

    if open_fn == 0 or connect_fn == 0 or open_request_fn == 0 or send_request_fn == 0 or
       receive_response_fn == 0 or query_data_available_fn == 0 or query_headers_fn == 0 or read_data_fn == 0 or
       set_timeouts_fn == 0 or close_handle_fn == 0 {
        http_url_free(parsed)
        return http_fail_response()
    }

    let host_w = http_url_host_utf16(parsed)
    let method_w = http_utf16z("GET")
    let path_w = http_url_path_utf16(parsed)
    if host_w == 0 or method_w == 0 or path_w == 0 {
        if host_w != 0 { free(host_w) }
        if method_w != 0 { free(method_w) }
        if path_w != 0 { free(path_w) }
        http_url_free(parsed)
        return http_fail_response()
    }

    let session = http_open_session(open_fn, set_timeouts_fn)
    if session == 0 {
        free(host_w)
        free(method_w)
        free(path_w)
        http_url_free(parsed)
        return http_fail_response()
    }

    let winhttp_connect = connect_fn as WinHttpConnectFn
    let connection = winhttp_connect(session, host_w, parsed.port, 0)
    free(host_w)
    if connection == 0 {
        free(method_w)
        free(path_w)
        http_close_if(close_handle_fn, session)
        http_url_free(parsed)
        return http_fail_response()
    }

    var request_flags = 0
    if parsed.secure != 0 {
        request_flags = 8388608
    }

    let winhttp_open_req = open_request_fn as WinHttpOpenRequestFn
    let request = winhttp_open_req(connection, method_w, path_w, 0, 0, 0, request_flags)
    free(method_w)
    free(path_w)
    http_url_free(parsed)

    if request == 0 {
        http_close_if(close_handle_fn, connection)
        http_close_if(close_handle_fn, session)
        return http_fail_response()
    }

    let winhttp_send = send_request_fn as WinHttpSendRequestFn
    let winhttp_recv = receive_response_fn as WinHttpReceiveResponseFn
    if winhttp_send(request, 0, 0, 0, 0, 0, 0) == 0 or winhttp_recv(request, 0) == 0 {
        http_close_if(close_handle_fn, request)
        http_close_if(close_handle_fn, connection)
        http_close_if(close_handle_fn, session)
        return http_fail_response()
    }

    let status = http_query_status(request, query_headers_fn)
    let raw_headers = http_query_raw_headers(request, query_headers_fn)
    let len_ptr = mem.make_zero(8)
    var body = 0
    var body_len = 0
    if len_ptr != 0 {
        body = http_read_body_bytes(request, query_data_available_fn, read_data_fn, len_ptr)
        body_len = mem.read(len_ptr)
        free(len_ptr)
    }

    http_close_if(close_handle_fn, request)
    http_close_if(close_handle_fn, connection)
    http_close_if(close_handle_fn, session)
    if body == 0 {
        return http_response_new_full(status, http_empty_text(), raw_headers)
    }
    return http_response_new_binary(status, body, body_len, raw_headers)
}

function int http_debug_fetch_stage(str url) {
    let response = http_fetch(url)
    if response == 0 {
        return 0
    }
    let status = response.status
    http_response_free(response)
    return status
}

function str http_get(str url) {
    let response = http_fetch(url)
    if response == 0 {
        return http_empty_text()
    }

    let body_text = response.body
    response.body = 0 as str
    if response.raw_headers != 0 {
        free(response.raw_headers)
    }
    if response.body_bytes != 0 {
        free(response.body_bytes)
    }
    free(response)
    if body_text == 0 {
        return http_empty_text()
    }
    return body_text
}

// ============================================================================
// Rich request builder (WinHTTP)
//
// http_request_new() returns a heap HttpRequest block. Setters copy their
// arguments, so callers keep ownership of anything they pass in. Send with
// http_request_send(), which returns an HttpResponse carrying status, body and
// the raw CRLF header block (queryable via http_response_header).
// ============================================================================

enum HttpRequestOffset {
    Method = 0,           // str
    Url = 8,              // str
    HeaderBuf = 16,       // ptr raw "Name: Value\r\n..." text
    HeaderLen = 24,       // int
    HeaderCap = 32,       // int
    Body = 40,            // ptr raw bytes
    BodyLen = 48,         // int
    ContentType = 56,     // str
    UserAgent = 64,      )SBHTTP"
            R"SBHTTP( // str
    TimeoutMs = 72,       // int
    FollowRedirects = 80, // int (bool)
}

enum HttpRequestSize { RequestBytes = 88 }

view HttpRequest {
    method: str @ HttpRequestOffset.Method
    url: str @ HttpRequestOffset.Url
    header_buf: ptr @ HttpRequestOffset.HeaderBuf
    header_len: int @ HttpRequestOffset.HeaderLen
    header_cap: int @ HttpRequestOffset.HeaderCap
    body: ptr @ HttpRequestOffset.Body
    body_len: int @ HttpRequestOffset.BodyLen
    content_type: str @ HttpRequestOffset.ContentType
    user_agent: str @ HttpRequestOffset.UserAgent
    timeout_ms: int @ HttpRequestOffset.TimeoutMs
    follow_redirects: int @ HttpRequestOffset.FollowRedirects
}

function str http_dup(str text_value) {
    if text_value == 0 {
        return 0 as str
    }
    return string_substring(text_value, 0, string_length(text_value))
}

// Grow a heap buffer so it can hold `used + add_len + 1` bytes, copying
// existing bytes. Returns the (possibly reallocated) pointer.
function ptr http_buf_reserve(ptr buf, int used, int cap, int add_len) {
    var need = used + add_len
    if need + 1 <= cap {
        return buf
    }
    var new_cap = cap
    if new_cap < 16 {
        new_cap = 16
    }
    while new_cap < need + 1 {
        new_cap = new_cap * 2
    }
    let next = malloc(new_cap + 1)
    if next == 0 {
        return buf
    }
    if used > 0 {
        memcpy(next, buf, used)
    }
    free(buf)
    mem.write8(next + used, 0)
    return next
}

function int http_buf_new_cap(int used, int cap, int add_len) {
    var need = used + add_len
    if need + 1 <= cap {
        return cap
    }
    var new_cap = cap
    if new_cap < 16 {
        new_cap = 16
    }
    while new_cap < need + 1 {
        new_cap = new_cap * 2
    }
    return new_cap
}

function HttpRequest http_request_new(str method, str url) {
    let req = mem.make_zero(HttpRequestSize.RequestBytes) as HttpRequest
    if req == 0 {
        return 0 as HttpRequest
    }
    req.method = http_dup(method)
    req.url = http_dup(url)
    req.header_buf = malloc(64)
    req.header_len = 0
    req.header_cap = 64
    req.body = 0
    req.body_len = 0
    req.content_type = 0 as str
    req.user_agent = 0 as str
    req.timeout_ms = 30000
    req.follow_redirects = 1
    if req.header_buf != 0 {
        mem.write8(req.header_buf, 0)
    }
    return req
}

function void http_request_header(HttpRequest req, str name, str value) {
    if req == 0 or req.header_buf == 0 {
        return
    }
    let line = http_join4(name, ": ", value, "\r\n")
    let line_len = string_length(line)
    let new_cap = http_buf_new_cap(req.header_len, req.header_cap, line_len)
    let grown = http_buf_reserve(req.header_buf, req.header_len, req.header_cap, line_len)
    req.header_buf = grown
    req.header_cap = new_cap
    if grown == 0 {
        free(line)
        return
    }
    memcpy(grown + req.header_len, line as ptr, line_len)
    req.header_len = req.header_len + line_len
    mem.write8(grown + req.header_len, 0)
    free(line)
}

function void http_request_body(HttpRequest req, ptr bytes, int len, str content_type) {
    if req == 0 {
        return
    }
    if req.body != 0 {
        free(req.body)
        req.body = 0
    }
    if bytes != 0 and len > 0 {
        req.body = mem.make_copy(bytes, len)
        req.body_len = len
    } else {
        req.body_len = 0
    }
    if req.content_type != 0 {
        free(req.content_type)
    }
    req.content_type = http_dup(content_type)
}

function void http_request_body_text(HttpRequest req, str text_value, str content_type) {
    if req == 0 {
        return
    }
    if text_value == 0 {
        http_request_body(req, 0, 0, content_type)
        return
    }
    http_request_body(req, text_value as ptr, string_length(text_value), content_type)
}

function void http_request_user_agent(HttpRequest req, str agent) {
    if req == 0 {
        return
    }
    if req.user_agent != 0 {
        free(req.user_agent)
    }
    req.user_agent = http_dup(agent)
}

function void http_request_timeout(HttpRequest req, int ms) {
    if req == 0 {
        return
    }
    req.timeout_ms = ms
}

function void http_request_follow_redirects(HttpRequest req, bool follow) {
    if req == 0 {
        return
    }
    if follow {
        req.follow_redirects = 1
    } else {
        req.follow_redirects = 0
    }
}

function void http_request_free(HttpRequest req) {
    if req == 0 {
        return
    }
    if req.method != 0 {
        free(req.method)
    }
    if req.url != 0 {
        free(req.url)
    }
    if req.header_buf != 0 {
        free(req.header_buf)
    }
    if req.body != 0 {
        free(req.body)
    }
    if req.content_type != 0 {
        free(req.content_type)
    }
    if req.user_agent != 0 {
        free(req.user_agent)
    }
    free(req)
}

// ============================================================================
// Send / response
// ============================================================================

function str http_query_raw_headers(ptr request_handle, ptr query_headers) {
    let size_ptr = mem.make_zero(8)
    if size_ptr == 0 {
        return 0 as str
    }
    mem.write32(size_ptr, 0)
    let query_fn = query_headers as WinHttpQueryHeadersFn
    // WINHTTP_QUERY_RAW_HEADERS_CRLF = 22. The exported WinHttpQueryHeaders here
    // is the wide (UTF-16) variant, so the length it returns is a WCHAR count.
    var ok = query_fn(request_handle, 22, 0, 0, size_ptr, 0)
    let needed = mem.read32(size_ptr)
    if needed <= 0 {
        free(size_ptr)
        return 0 as str
    }
    let wide = malloc(needed * 2 + 2)
    if wide == 0 {
        free(size_ptr)
        return 0 as str
    }
    mem.write32(size_ptr, needed)
    ok = query_fn(request_handle, 22, 0, wide, size_ptr, 0)
    free(size_ptr)
    if ok == 0 {
        free(wide)
        return 0 as str
    }
    // downconvert UTF-16 -> ASCII (header text is ASCII/ISO-8859-1)
    let out = malloc(needed + 1)
    if out == 0 {
        free(wide)
        return 0 as str
    }
    var i = 0
    var w = 0
    while i < needed {
        let lo = mem.read8(wide + i * 2)
        let hi = mem.read8(wide + i * 2 + 1)
        if lo == 0 and hi == 0 {
            break
        }
        mem.write8(out + w, lo)
        w++
        i++
    }
    mem.write8(out + w, 0)
    let result = make_string(out)
    free(out)
    free(wide)
    return result
}

function HttpResponse http_request_send(HttpRequest req) {
    if req == 0 or req.url == 0 {
        return http_fail_response()
    }

    let parsed = http_parse_url(req.url)
    if parsed == 0 {
        return http_fail_response()
    }

    let module_handle = load_library("winhttp.dll")
    if module_handle == 0 {
        http_url_free(parsed)
        return http_fail_response()
    }

    let open_fn = get_proc(module_handle, "WinHttpOpen")
    let connect_fn = get_proc(module_handle, "WinHttpConnect")
    let open_request_fn = get_proc(module_handle, "WinHttpOpenRequest")
    let send_request_fn = get_proc(module_handle, "WinHttpSendRequest")
    let receive_response_fn = get_proc(module_handle, "WinHttpReceiveResponse")
    let query_data_available_fn = get_proc(module_handle, "WinHttpQueryDataAvailable")
    let query_headers_fn = get_proc(module_handle, "WinHttpQueryHeaders")
    let read_data_fn = get_proc(module_handle, "WinHttpReadData")
    let set_timeouts_fn = get_proc(module_handle, "WinHttpSetTimeouts")
    let close_handle_fn = get_proc(module_handle, "WinHttpCloseHandle")
    let set_option_fn = get_proc(module_handle, "WinHttpSetOption")

    if open_fn == 0 or connect_fn == 0 or open_request_fn == 0 or send_request_fn == 0 or
       receive_response_fn == 0 or query_data_available_fn == 0 or query_headers_fn == 0 or
       read_data_fn == 0 or set_timeouts_fn == 0 or close_handle_fn == 0 {
        http_url_free(parsed)
        return http_fail_response()
    }

    let host_w = http_url_host_utf16(parsed)
    let method_w = http_utf16z(req.method)
    let path_w = http_url_path_utf16(parsed)
    if host_w == 0 or method_w == 0 or path_w == 0 {
        if host_w != 0 { free(host_w) }
        if method_w != 0 {)SBHTTP"
            R"SBHTTP( free(method_w) }
        if path_w != 0 { free(path_w) }
        http_url_free(parsed)
        return http_fail_response()
    }

    let session = http_open_session(open_fn, set_timeouts_fn)
    if session == 0 {
        free(host_w)
        free(method_w)
        free(path_w)
        http_url_free(parsed)
        return http_fail_response()
    }

    if req.timeout_ms > 0 {
        let winhttp_set_timeouts = set_timeouts_fn as WinHttpSetTimeoutsFn
        winhttp_set_timeouts(session, req.timeout_ms, req.timeout_ms, req.timeout_ms, req.timeout_ms)
    }

    // WINHTTP_OPTION_REDIRECT_POLICY = 88; values: 0 = never,
    // 1 = disallow https->http, 2 = always follow. Default is 2.
    if set_option_fn != 0 {
        let policy = mem.make_zero(4)
        if policy != 0 {
            if req.follow_redirects != 0 {
                mem.write32(policy, 2)
            } else {
                mem.write32(policy, 0)
            }
            let winhttp_set_option = set_option_fn as WinHttpSetOptionFn
            winhttp_set_option(session, 88, policy, 4)
            free(policy)
        }
    }

    let winhttp_connect = connect_fn as WinHttpConnectFn
    let connection = winhttp_connect(session, host_w, parsed.port, 0)
    free(host_w)
    if connection == 0 {
        free(method_w)
        free(path_w)
        http_close_if(close_handle_fn, session)
        http_url_free(parsed)
        return http_fail_response()
    }

    var request_flags = 0
    if parsed.secure != 0 {
        request_flags = 8388608 // WINHTTP_FLAG_SECURE
    }

    let winhttp_open_req = open_request_fn as WinHttpOpenRequestFn
    let request = winhttp_open_req(connection, method_w, path_w, 0, 0, 0, request_flags)
    free(method_w)
    free(path_w)
    http_url_free(parsed)

    if request == 0 {
        http_close_if(close_handle_fn, connection)
        http_close_if(close_handle_fn, session)
        return http_fail_response()
    }

    // Build the full wide (UTF-16) header block: accumulated headers plus a
    // Content-Type line when a body type was set. WinHttpSendRequest takes this
    // as lpszHeaders with dwHeadersLength = -1 (0xFFFFFFFF, null-terminated).
    var headers_w = 0
    var headers_present = 0
    if req.header_len > 0 or (req.content_type != 0 and string_length(req.content_type) > 0) {
        var ct_line = ""
        if req.content_type != 0 and string_length(req.content_type) > 0 {
            ct_line = http_join4("Content-Type", ": ", req.content_type, "\r\n")
        }
        let block = string_append(req.header_buf as str, ct_line)
        if string_length(ct_line) > 0 {
            free(ct_line)
        }
        headers_w = http_utf16z(block)
        free(block)
        if headers_w != 0 {
            headers_present = 1
        }
    }

    let winhttp_send = send_request_fn as WinHttpSendRequestFn
    let winhttp_recv = receive_response_fn as WinHttpReceiveResponseFn

    var send_ok = 0
    if headers_present != 0 {
        if req.body != 0 and req.body_len > 0 {
            send_ok = winhttp_send(request, headers_w, 0 as int - 1, req.body, req.body_len, req.body_len, 0)
        } else {
            send_ok = winhttp_send(request, headers_w, 0 as int - 1, 0, 0, 0, 0)
        }
    } else {
        if req.body != 0 and req.body_len > 0 {
            send_ok = winhttp_send(request, 0, 0, req.body, req.body_len, req.body_len, 0)
        } else {
            send_ok = winhttp_send(request, 0, 0, 0, 0, 0, 0)
        }
    }
    if headers_w != 0 {
        free(headers_w)
    }

    if send_ok == 0 or winhttp_recv(request, 0) == 0 {
        http_close_if(close_handle_fn, request)
        http_close_if(close_handle_fn, connection)
        http_close_if(close_handle_fn, session)
        return http_fail_response()
    }

    let status = http_query_status(request, query_headers_fn)
    let raw_headers = http_query_raw_headers(request, query_headers_fn)
    let body_len_ptr = mem.make_zero(8)
    var body_bytes = 0
    var body_len = 0
    if body_len_ptr != 0 {
        body_bytes = http_read_body_bytes(request, query_data_available_fn, read_data_fn, body_len_ptr)
        body_len = mem.read(body_len_ptr)
        free(body_len_ptr)
    }

    http_close_if(close_handle_fn, request)
    http_close_if(close_handle_fn, connection)
    http_close_if(close_handle_fn, session)

    if body_bytes == 0 {
        return http_response_new_full(status, http_empty_text(), raw_headers)
    }
    return http_response_new_binary(status, body_bytes, body_len, raw_headers)
}

// ============================================================================
// Response header lookup (case-insensitive)
// ============================================================================

function int http_ascii_lower(int ch) {
    if ch >= 65 and ch <= 90 {
        return ch + 32
    }
    return ch
}

function bool http_header_name_eq(str block, int start, int name_len, str name) {
    if string_length(name) != name_len {
        return false
    }
    let bp = block as ptr
    let np = name as ptr
    var i = 0
    while i < name_len {
        if http_ascii_lower(mem.read8(bp + start + i)) != http_ascii_lower(mem.read8(np + i)) {
            return false
        }
        i++
    }
    return true
}

// find "name: value" inside a CRLF header block, return value with surrounding
// spaces trimmed. Result is a heap string (caller frees) or 0 when absent.
function str http_header_find(str block, str name) {
    if block == 0 or name == 0 {
        return 0 as str
    }
    let len = string_length(block)
    let name_len = string_length(name)
    if len == 0 or name_len == 0 {
        return 0 as str
    }
    let bp = block as ptr
    var line_start = 0
    while line_start < len {
        // find end of this line
        var line_end = line_start
        while line_end < len and mem.read8(bp + line_end) != 13 {
            line_end++
        }
        // does "name:" start this line?
        if line_end - line_start > name_len and
           http_header_name_eq(block, line_start, name_len, name) and
           mem.read8(bp + line_start + name_len) == 58 {
            var value_start = line_start + name_len + 1
            // skip leading spaces/tabs
            while value_start < line_end and (mem.read8(bp + value_start) == 32 or mem.read8(bp + value_start) == 9) {
                value_start++
            }
            var value_end = line_end
            while value_end > value_start and (mem.read8(bp + value_end - 1) == 32 or mem.read8(bp + value_end - 1) == 9) {
                value_end--
            }
            if value_end <= value_start {
                return http_empty_text()
            }
            return string_substring(block, value_start, value_end - value_start)
        }
        // advance past CRLF
        line_start = line_end
        if line_start < len and mem.read8(bp + line_start) == 13 {
            line_start++
        }
        if line_start < len and mem.read8(bp + line_start) == 10 {
            line_start++
        }
    }
    return 0 as str
}

function str http_response_header(HttpResponse response, str name) {
    if response == 0 or response.raw_headers == 0 {
        return 0 as str
    }
    return http_header_find(response.raw_headers, name)
}

function str http_response_content_type(HttpResponse response) {
    let ct = http_response_header(response, "Content-Type")
    if ct == 0 {
        return http_empty_text()
    }
    return ct
}

// ============================================================================
// Verb convenience helpers
// ============================================================================

function HttpResponse http_request(str method, str url) {
    let req = http_request_new(method, url)
    if req == 0 {
        return http_fail_response()
    }
    let response = http_request_send(req)
    http_request_free(req)
    return response
}

function HttpResponse http_post(str url, str content_type, str body_text) {
    let req = http_request_new("POST", url)
    if req == 0 {
        return http_fail_response()
    }
    http_request_body_text(req, body_text, content_type)
    let respons)SBHTTP"
            R"SBHTTP(e = http_request_send(req)
    http_request_free(req)
    return response
}

function HttpResponse http_put(str url, str content_type, str body_text) {
    let req = http_request_new("PUT", url)
    if req == 0 {
        return http_fail_response()
    }
    http_request_body_text(req, body_text, content_type)
    let response = http_request_send(req)
    http_request_free(req)
    return response
}

function HttpResponse http_patch(str url, str content_type, str body_text) {
    let req = http_request_new("PATCH", url)
    if req == 0 {
        return http_fail_response()
    }
    http_request_body_text(req, body_text, content_type)
    let response = http_request_send(req)
    http_request_free(req)
    return response
}

function HttpResponse http_delete(str url) {
    return http_request("DELETE", url)
}

function HttpResponse http_head(str url) {
    return http_request("HEAD", url)
}

// build a query string from parallel key/value arrays; values are percent-encoded
function str http_build_query(ptr keys, ptr values, int count) {
    if count <= 0 {
        return http_empty_text()
    }
    // first pass: total length
    var total = 0
    var i = 0
    while i < count {
        let key = mem.read(keys + i * 8) as str
        let value = mem.read(values + i * 8) as str
        total += http_url_encoded_len(key) + 1 + http_url_encoded_len(value)
        if i < count - 1 {
            total += 1
        }
        i++
    }
    let out = malloc(total + 1)
    if out == 0 {
        return http_empty_text()
    }
    var w = 0
    i = 0
    while i < count {
        let key = mem.read(keys + i * 8) as str
        let value = mem.read(values + i * 8) as str
        w = http_url_encode_into(out, w, key)
        mem.write8(out + w, 61) // =
        w++
        w = http_url_encode_into(out, w, value)
        if i < count - 1 {
            mem.write8(out + w, 38) // &
            w++
        }
        i++
    }
    mem.write8(out + w, 0)
    let result = make_string(out)
    free(out)
    return result
}


// ============================================================================
// Additional request helpers: query appending, base64/basic auth, multipart
// ============================================================================

// append "?k=v" (or "&k=v" when the url already has a query) to a url.
// key and value are percent-encoded. Returns a new heap string.
function str http_url_with_query(str url, str key, str value) {
    if url == 0 {
        return http_empty_text()
    }
    var sep = "?"
    if http_find(url, "?") >= 0 {
        sep = "&"
    }
    let ek = http_url_encode(key)
    let ev = http_url_encode(value)
    let result = http_join4(url, sep, ek, http_join2("=", ev))
    free(ek)
    free(ev)
    return result
}

function str http_request_add_query(HttpRequest req, str key, str value) {
    if req == 0 or req.url == 0 {
        return 0 as str
    }
    let next_url = http_url_with_query(req.url, key, value)
    if next_url == 0 {
        return 0 as str
    }
    free(req.url)
    req.url = next_url
    return next_url
}

enum HttpBase64Chars { Alphabet = 0 }

function int http_base64_char(int index) {
    // standard alphabet: A-Z a-z 0-9 + /
    if index < 26 {
        return 65 + index
    }
    if index < 52 {
        return 97 + (index - 26)
    }
    if index < 62 {
        return 48 + (index - 52)
    }
    if index == 62 {
        return 43
    }
    return 47
}

// base64-encode raw bytes; returns a heap string (caller frees)
function str http_base64_encode(ptr bytes, int len) {
    if bytes == 0 or len <= 0 {
        return http_empty_text()
    }
    let groups = (len + 2) / 3
    let out = malloc(groups * 4 + 1)
    if out == 0 {
        return http_empty_text()
    }
    var w = 0
    var i = 0
    while i < len {
        let b0 = mem.read8(bytes + i)
        var b1 = 0
        var b2 = 0
        let have1 = i + 1 < len
        let have2 = i + 2 < len
        if have1 {
            b1 = mem.read8(bytes + i + 1)
        }
        if have2 {
            b2 = mem.read8(bytes + i + 2)
        }
        mem.write8(out + w, http_base64_char((b0 >> 2) & 63))
        mem.write8(out + w + 1, http_base64_char(((b0 & 3) << 4) | ((b1 >> 4) & 15)))
        if have1 {
            mem.write8(out + w + 2, http_base64_char(((b1 & 15) << 2) | ((b2 >> 6) & 3)))
        } else {
            mem.write8(out + w + 2, 61) // '='
        }
        if have2 {
            mem.write8(out + w + 3, http_base64_char(b2 & 63))
        } else {
            mem.write8(out + w + 3, 61) // '='
        }
        w += 4
        i += 3
    }
    mem.write8(out + w, 0)
    let result = make_string(out)
    free(out)
    return result
}

function str http_basic_auth(str username, str password) {
    let joined = http_join3(username, ":", password)
    let token = http_base64_encode(joined as ptr, string_length(joined))
    let header = http_join2("Basic ", token)
    free(joined)
    free(token)
    return header
}

// set an Authorization: Basic ... header from credentials
function void http_request_basic_auth(HttpRequest req, str username, str password) {
    if req == 0 {
        return
    }
    let value = http_basic_auth(username, password)
    http_request_header(req, "Authorization", value)
    free(value)
}

// build a multipart/form-data body with a single text field. Pair it with
// http_multipart_content_type(boundary) for the Content-Type header.
// Caller frees the returned body.
function str http_multipart_field(str field_name, str value, str boundary) {
    let part = http_join4("--", boundary, "\r\nContent-Disposition: form-data; name=\"", field_name)
    let part2 = http_join3("\"\r\n\r\n", value, "\r\n")
    let closing = http_join3("--", boundary, "--\r\n")
    let body = http_join3(part, part2, closing)
    free(part)
    free(part2)
    free(closing)
    return body
}

function str http_multipart_content_type(str boundary) {
    return http_join2("multipart/form-data; boundary=", boundary)
}
)SBHTTP"},
        {"json", R"SBJSON(import ascii
import mem
import text

// Full high-speed JSON DOM parser + stringify helpers backed by zero-copy views.
// Ownership:
// - json_parse allocates a tree that must be released with json_free.
// - json_key/json_string/json_number_text/json_get_string/json_quote_string/json_escape_string_inner/json_stringify return heap strings; caller must free.

let JSON_KIND_NULL: int = 0
let JSON_KIND_BOOL: int = 1
let JSON_KIND_NUMBER: int = 2
let JSON_KIND_STRING: int = 3
let JSON_KIND_ARRAY: int = 4
let JSON_KIND_OBJECT: int = 5

enum JsonValueOffset {
    Kind = 0,
    BoolValue = 8,
    Count = 16,
    Key = 24,
    Text = 32,
    Child = 40,
    Next = 48,
    Tail = 56,
}

enum JsonCursorOffset {
    Source = 0,
    SrcPtr = 8,
    Index = 16,
    Length = 24,
    Ok = 32,
}

enum JsonBufOffset {
    Data = 0,
    Len = 8,
    Cap = 16,
}

view JsonValue {
    kind: int @ JsonValueOffset.Kind
    bool_value: int @ JsonValueOffset.BoolValue
    count: int @ JsonValueOffset.Count
    key: str @ JsonValueOffset.Key
    text: str @ JsonValueOffset.Text
    child: ptr @ JsonValueOffset.Child
    next: ptr @ JsonValueOffset.Next
    tail: ptr @ JsonValueOffset.Tail
}

view JsonCursor {
    source: str @ JsonCursorOffset.Source
    src_ptr: ptr @ JsonCursorOffset.SrcPtr
    index: int @ JsonCursorOffset.Index
    length: int @ JsonCursorOffset.Length
    ok: int @ JsonCursorOffset.Ok
}

view JsonStrBuf {
    data: ptr @ JsonBufOffset.Data
    len: int @ JsonBufOffset.Len
    cap: int @ JsonBufOffset.Cap
}

function str json_owned_empty() {
    return text_clone("")
}

function JsonValue json_new(int kind) {
    let node = malloc(64) as JsonValue
    if node == 0 {
        return 0 as JsonValue
    }
    node.kind = kind
    node.bool_value = 0
    node.count = 0
    node.key = 0 as str
    node.text = 0 as str
    node.child = 0
    node.next = 0
    node.tail = 0
    return node
}

function void json_set_key(JsonValue value_node, str key_name) {
    if value_node == 0 {
        if key_name != 0 {
            free(key_name)
        }
        return
    }
    if value_node.key != 0 {
        free(value_node.key)
    }
    value_node.key = key_name
}

function void json_set_text(JsonValue value_node, str text_value) {
    if value_node == 0 {
        if text_value != 0 {
            free(text_value)
        }
        return
    }
    if value_node.text != 0 {
        free(value_node.text)
    }
    value_node.text = text_value
}

function JsonCursor json_cursor_new(str source) {
    let cursor = malloc(40) as JsonCursor
    if cursor == 0 {
        return 0 as JsonCursor
    }
    cursor.source = source
    cursor.src_ptr = source as ptr
    cursor.index = 0
    if source == 0 {
        cursor.length = 0
        cursor.ok = 0
    } else {
        cursor.length = string_length(source)
        cursor.ok = 1
    }
    return cursor
}

function JsonCursor json_cursor_at(str source, int start_idx) {
    let cursor = json_cursor_new(source)
    if cursor == 0 {
        return 0 as JsonCursor
    }

    if start_idx < 0 {
        cursor.index = 0
    } else if start_idx > cursor.length {
        cursor.index = cursor.length
    } else {
        cursor.index = start_idx
    }

    return cursor
}

function bool json_cursor_is_ok(JsonCursor cursor) {
    return cursor != 0 and cursor.ok != 0
}

function void json_fail(JsonCursor cursor) {
    if cursor != 0 {
        cursor.ok = 0
    }
}

function int json_peek(JsonCursor cursor) {
    if cursor == 0 {
        return 0
    }
    if cursor.index >= cursor.length {
        return 0
    }
    return mem.read8(cursor.src_ptr + cursor.index)
}

function int json_peek_offset(JsonCursor cursor, int offset) {
    if cursor == 0 {
        return 0
    }
    let idx = cursor.index + offset
    if idx < 0 or idx >= cursor.length {
        return 0
    }
    return mem.read8(cursor.src_ptr + idx)
}

function int json_take(JsonCursor cursor) {
    if cursor == 0 or cursor.index >= cursor.length {
        return 0
    }
    let ch = mem.read8(cursor.src_ptr + cursor.index)
    cursor.index = cursor.index + 1
    return ch
}

function void json_skip_ws_cursor(JsonCursor cursor) {
    if cursor == 0 {
        return
    }
    var idx = cursor.index
    let total = cursor.length
    let p = cursor.src_ptr
    while idx < total {
        let ch = mem.read8(p + idx)
        if !ascii_is_space(ch) {
            break
        }
        idx++
    }
    cursor.index = idx
}

function bool json_consume(JsonCursor cursor, int ch) {
    if json_peek(cursor) != ch {
        json_fail(cursor)
        return false
    }
    cursor.index = cursor.index + 1
    return true
}

function bool json_match_word(JsonCursor cursor, str word) {
    let word_len = string_length(word)
    if cursor == 0 or cursor.index + word_len > cursor.length {
        return false
    }
    if memcmp(cursor.src_ptr + cursor.index, word as ptr, word_len) != 0 {
        return false
    }
    cursor.index = cursor.index + word_len
    return true
}

function int json_hex4(JsonCursor cursor) {
    if cursor == 0 or cursor.index + 4 > cursor.length {
        json_fail(cursor)
        return -1
    }
    let p = cursor.src_ptr + cursor.index
    let n0 = ascii_hex_value(mem.read8(p))
    let n1 = ascii_hex_value(mem.read8(p + 1))
    let n2 = ascii_hex_value(mem.read8(p + 2))
    let n3 = ascii_hex_value(mem.read8(p + 3))
    if n0 < 0 or n1 < 0 or n2 < 0 or n3 < 0 {
        json_fail(cursor)
        return -1
    }
    cursor.index = cursor.index + 4
    return (n0 << 12) | (n1 << 8) | (n2 << 4) | n3
}

function int json_write_utf8(ptr buf, int out_idx, int codepoint) {
    if codepoint < 0 {
        codepoint = 63
    }

    if codepoint <= 127 {
        mem.write8(buf + out_idx, codepoint)
        return out_idx + 1
    }

    if codepoint <= 2047 {
        mem.write8(buf + out_idx, 192 + (codepoint >> 6))
        mem.write8(buf + out_idx + 1, 128 + (codepoint & 63))
        return out_idx + 2
    }

    if codepoint <= 65535 {
        mem.write8(buf + out_idx, 224 + (codepoint >> 12))
        mem.write8(buf + out_idx + 1, 128 + ((codepoint >> 6) & 63))
        mem.write8(buf + out_idx + 2, 128 + (codepoint & 63))
        return out_idx + 3
    }

    mem.write8(buf + out_idx, 240 + (codepoint >> 18))
    mem.write8(buf + out_idx + 1, 128 + ((codepoint >> 12) & 63))
    mem.write8(buf + out_idx + 2, 128 + ((codepoint >> 6) & 63))
    mem.write8(buf + out_idx + 3, 128 + (codepoint & 63))
    return out_idx + 4
}

function str json_parse_string_raw(JsonCursor cursor) {
    if !json_consume(cursor, 34) {
        return 0 as str
    }

    let total = cursor.length
    let p = cursor.src_ptr
    let start_idx = cursor.index

    // Fast path: scan for closing quote without escapes or control characters.
    var scan = start_idx
    var has_escape = false
    while scan < total {
        let ch = mem.read8(p + scan)
        if ch == 34 {
            cursor.index = scan + 1
            return string_substring(cursor.source, start_idx, scan - start_idx)
        }
        if ch == 92 {
            has_escape = true
            break
        }
        if ch < 32 {
            json_fail(cursor)
            return 0 as str
        }
        scan++
    }

    if !has_escape {
        json_fail(cursor)
        return 0 as str
    }

    let max_bytes = total - start_idx + 1
    let out_buf = malloc(max_bytes)
    if out_buf == 0 {
        json_fail(cursor)
        return 0 as str
    }

    var out_idx = scan - start_idx
    if out_idx > 0 {
        memcpy(out_buf, p + start_idx, out_idx)
    }
    cursor.index = scan

    while cursor.index < total {
        let ch = mem.read8(p + cursor.index)
        cursor.index = cursor.index + 1
        if ch == 34 {
            mem.write8(out_buf + out_idx, 0)
            let out = make_string(out_buf)
            free(out_buf)
            return out
        }

        if ch == 92 {
            if cursor.index >= total {
                free(out_buf)
                json_fail(cursor)
                return 0 as str
            }
            let esc = mem.read8(p + cursor.index)
            cursor.index = cursor.index + 1
     )SBJSON"
            R"SBJSON(       if esc == 34 {
                mem.write8(out_buf + out_idx, 34)
                out_idx++
            } else if esc == 92 {
                mem.write8(out_buf + out_idx, 92)
                out_idx++
            } else if esc == 47 {
                mem.write8(out_buf + out_idx, 47)
                out_idx++
            } else if esc == 98 {
                mem.write8(out_buf + out_idx, 8)
                out_idx++
            } else if esc == 102 {
                mem.write8(out_buf + out_idx, 12)
                out_idx++
            } else if esc == 110 {
                mem.write8(out_buf + out_idx, 10)
                out_idx++
            } else if esc == 114 {
                mem.write8(out_buf + out_idx, 13)
                out_idx++
            } else if esc == 116 {
                mem.write8(out_buf + out_idx, 9)
                out_idx++
            } else if esc == 117 {
                var codepoint = json_hex4(cursor)
                if codepoint < 0 {
                    free(out_buf)
                    return 0 as str
                }

                if codepoint >= 55296 and codepoint <= 56319 and cursor.index + 1 < total and mem.read8(p + cursor.index) == 92 and mem.read8(p + cursor.index + 1) == 117 {
                    cursor.index = cursor.index + 2
                    let low = json_hex4(cursor)
                    if low >= 56320 and low <= 57343 {
                        codepoint = 65536 + ((codepoint - 55296) << 10) + (low - 56320)
                    } else {
                        free(out_buf)
                        json_fail(cursor)
                        return 0 as str
                    }
                } else if codepoint >= 56320 and codepoint <= 57343 {
                    free(out_buf)
                    json_fail(cursor)
                    return 0 as str
                }

                out_idx = json_write_utf8(out_buf, out_idx, codepoint)
            } else {
                free(out_buf)
                json_fail(cursor)
                return 0 as str
            }
        } else {
            if ch < 32 {
                free(out_buf)
                json_fail(cursor)
                return 0 as str
            }
            mem.write8(out_buf + out_idx, ch)
            out_idx++
        }
    }

    free(out_buf)
    json_fail(cursor)
    return 0 as str
}

function str json_parse_number_raw(JsonCursor cursor) {
    if cursor == 0 {
        return 0 as str
    }

    let p = cursor.src_ptr
    let total = cursor.length
    var idx = cursor.index
    let start_idx = idx

    if idx < total and mem.read8(p + idx) == 45 {
        idx++
    }

    if idx >= total {
        json_fail(cursor)
        return 0 as str
    }

    let first = mem.read8(p + idx)
    if first == 48 {
        idx++
    } else if ascii_is_digit(first) {
        while idx < total and ascii_is_digit(mem.read8(p + idx)) {
            idx++
        }
    } else {
        json_fail(cursor)
        return 0 as str
    }

    if idx < total and mem.read8(p + idx) == 46 {
        idx++
        if idx >= total or !ascii_is_digit(mem.read8(p + idx)) {
            json_fail(cursor)
            return 0 as str
        }
        while idx < total and ascii_is_digit(mem.read8(p + idx)) {
            idx++
        }
    }

    if idx < total {
        let exp_ch = mem.read8(p + idx)
        if exp_ch == 101 or exp_ch == 69 {
            idx++
            if idx < total {
                let sign_ch = mem.read8(p + idx)
                if sign_ch == 43 or sign_ch == 45 {
                    idx++
                }
            }
            if idx >= total or !ascii_is_digit(mem.read8(p + idx)) {
                json_fail(cursor)
                return 0 as str
            }
            while idx < total and ascii_is_digit(mem.read8(p + idx)) {
                idx++
            }
        }
    }

    cursor.index = idx
    return string_substring(cursor.source, start_idx, idx - start_idx)
}

function void json_append_child(JsonValue parent, JsonValue child) {
    if parent == 0 or child == 0 {
        return
    }

    if parent.child == 0 {
        parent.child = child as ptr
        parent.tail = child as ptr
        parent.count = 1
        return
    }

    let last = parent.tail as JsonValue
    last.next = child as ptr
    parent.tail = child as ptr
    parent.count = parent.count + 1
}

function JsonValue json_parse_value(JsonCursor cursor) {
    json_skip_ws_cursor(cursor)
    if !json_cursor_is_ok(cursor) {
        return 0 as JsonValue
    }

    let ch = json_peek(cursor)
    if ch == 34 {
        let value_node = json_new(JSON_KIND_STRING)
        if value_node == 0 {
            json_fail(cursor)
            return 0 as JsonValue
        }
        let decoded = json_parse_string_raw(cursor)
        if decoded == 0 {
            json_free(value_node)
            return 0 as JsonValue
        }
        json_set_text(value_node, decoded)
        return value_node
    }

    if ch == 123 {
        json_take(cursor)
        let obj = json_new(JSON_KIND_OBJECT)
        if obj == 0 {
            json_fail(cursor)
            return 0 as JsonValue
        }
        json_skip_ws_cursor(cursor)
        if json_peek(cursor) == 125 {
            json_take(cursor)
            return obj
        }

        var done = false
        while json_cursor_is_ok(cursor) and !done {
            json_skip_ws_cursor(cursor)
            if json_peek(cursor) != 34 {
                json_free(obj)
                json_fail(cursor)
                return 0 as JsonValue
            }

            let key_name = json_parse_string_raw(cursor)
            if key_name == 0 {
                json_free(obj)
                return 0 as JsonValue
            }

            json_skip_ws_cursor(cursor)
            if !json_consume(cursor, 58) {
                free(key_name)
                json_free(obj)
                return 0 as JsonValue
            }

            let child = json_parse_value(cursor)
            if child == 0 {
                free(key_name)
                json_free(obj)
                return 0 as JsonValue
            }

            json_set_key(child, key_name)
            json_append_child(obj, child)

            json_skip_ws_cursor(cursor)
            let tail = json_peek(cursor)
            if tail == 44 {
                json_take(cursor)
            } else if tail == 125 {
                json_take(cursor)
                done = true
            } else {
                json_free(obj)
                json_fail(cursor)
                return 0 as JsonValue
            }
        }

        if done {
            return obj
        }

        json_free(obj)
        return 0 as JsonValue
    }

    if ch == 91 {
        json_take(cursor)
        let arr = json_new(JSON_KIND_ARRAY)
        if arr == 0 {
            json_fail(cursor)
            return 0 as JsonValue
        }
        json_skip_ws_cursor(cursor)
        if json_peek(cursor) == 93 {
            json_take(cursor)
            return arr
        }

        var done = false
        while json_cursor_is_ok(cursor) and !done {
            let child = json_parse_value(cursor)
            if child == 0 {
                json_free(arr)
                return 0 as JsonValue
            }

            json_append_child(arr, child)
            json_skip_ws_cursor(cursor)
            let tail = json_peek(cursor)
            if tail == 44 {
                json_take(cursor)
            } else if tail == 93 {
                json_take(cursor)
                done = true
            } else {
                json_free(arr)
                json_fail(cursor)
                return 0 as JsonValue
            }
        }

        if done {
            return arr
        }

        json_free(arr)
        return 0 as JsonValue
    }

    if ch == 116 {
        if !json_match_word(cursor, "true") {
            json_fail(cursor)
            return 0 as JsonValue
        }
        let value_node = json_new(JSON_KIND_BOOL)
        if value_node != 0 {
            value_node.bool_value = 1
        }
        return value_node
    }

    if ch == 102 {
        if !json_match_word(cur)SBJSON"
            R"SBJSON(sor, "false") {
            json_fail(cursor)
            return 0 as JsonValue
        }
        let value_node = json_new(JSON_KIND_BOOL)
        if value_node != 0 {
            value_node.bool_value = 0
        }
        return value_node
    }

    if ch == 110 {
        if !json_match_word(cursor, "null") {
            json_fail(cursor)
            return 0 as JsonValue
        }
        return json_new(JSON_KIND_NULL)
    }

    if ch == 45 or ascii_is_digit(ch) {
        let raw = json_parse_number_raw(cursor)
        if raw == 0 {
            return 0 as JsonValue
        }
        let value_node = json_new(JSON_KIND_NUMBER)
        if value_node == 0 {
            free(raw)
            json_fail(cursor)
            return 0 as JsonValue
        }
        json_set_text(value_node, raw)
        return value_node
    }

    json_fail(cursor)
    return 0 as JsonValue
}

function JsonValue json_parse(str source) {
    let cursor = json_cursor_new(source)
    if cursor == 0 {
        return 0 as JsonValue
    }
    let root = json_parse_value(cursor)
    json_skip_ws_cursor(cursor)
    if root == 0 or !json_cursor_is_ok(cursor) or cursor.index != cursor.length {
        if root != 0 {
            json_free(root)
        }
        free(cursor)
        return 0 as JsonValue
    }
    free(cursor)
    return root
}

function void json_free(JsonValue value_node) {
    if value_node == 0 {
        return
    }

    var child = value_node.child as JsonValue
    while child != 0 {
        let next_child = child.next as JsonValue
        json_free(child)
        child = next_child
    }

    if value_node.key != 0 {
        free(value_node.key)
    }
    if value_node.text != 0 {
        free(value_node.text)
    }
    free(value_node)
}

function int json_kind(JsonValue value_node) {
    if value_node == 0 {
        return JSON_KIND_NULL
    }
    return value_node.kind
}

function bool json_is_null(JsonValue value_node) {
    return json_kind(value_node) == JSON_KIND_NULL
}

function bool json_is_bool(JsonValue value_node) {
    return json_kind(value_node) == JSON_KIND_BOOL
}

function bool json_is_number(JsonValue value_node) {
    return json_kind(value_node) == JSON_KIND_NUMBER
}

function bool json_is_string(JsonValue value_node) {
    return json_kind(value_node) == JSON_KIND_STRING
}

function bool json_is_array(JsonValue value_node) {
    return json_kind(value_node) == JSON_KIND_ARRAY
}

function bool json_is_object(JsonValue value_node) {
    return json_kind(value_node) == JSON_KIND_OBJECT
}

function bool json_bool_value(JsonValue value_node, bool fallback) {
    if !json_is_bool(value_node) {
        return fallback
    }
    return value_node.bool_value != 0
}

function str json_key(JsonValue value_node) {
    if value_node == 0 or value_node.key == 0 {
        return json_owned_empty()
    }
    return text_clone(value_node.key)
}

function str json_string(JsonValue value_node) {
    if !json_is_string(value_node) or value_node.text == 0 {
        return json_owned_empty()
    }
    return text_clone(value_node.text)
}

function str json_number_text(JsonValue value_node) {
    if !json_is_number(value_node) or value_node.text == 0 {
        return json_owned_empty()
    }
    return text_clone(value_node.text)
}

function int json_int(JsonValue value_node, int fallback) {
    if !json_is_number(value_node) or value_node.text == 0 {
        return fallback
    }
    let raw_text = value_node.text
    if text_contains_char(raw_text, 46) or text_contains_char(raw_text, 101) or text_contains_char(raw_text, 69) {
        return fallback
    }
    return parse_int(raw_text)
}

function int json_count(JsonValue value_node) {
    if value_node == 0 {
        return 0
    }
    return value_node.count
}

function int json_array_len(JsonValue value_node) {
    if !json_is_array(value_node) {
        return 0
    }
    return value_node.count
}

function JsonValue json_child(JsonValue value_node) {
    if value_node == 0 {
        return 0 as JsonValue
    }
    return value_node.child as JsonValue
}

function JsonValue json_next(JsonValue value_node) {
    if value_node == 0 {
        return 0 as JsonValue
    }
    return value_node.next as JsonValue
}

function JsonValue json_array_at(JsonValue value_node, int index) {
    if !json_is_array(value_node) or index < 0 or index >= value_node.count {
        return 0 as JsonValue
    }

    var item = value_node.child as JsonValue
    var i = 0
    while item != 0 {
        if i == index {
            return item
        }
        item = item.next as JsonValue
        i++
    }
    return 0 as JsonValue
}

function JsonValue json_object_get(JsonValue value_node, str key_name) {
    if !json_is_object(value_node) or key_name == 0 {
        return 0 as JsonValue
    }

    let key_len = string_length(key_name)
    let key_ptr = key_name as ptr
    var item = value_node.child as JsonValue
    while item != 0 {
        if item.key != 0 {
            if string_length(item.key) == key_len {
                if key_len == 0 or memcmp(item.key as ptr, key_ptr, key_len) == 0 {
                    return item
                }
            }
        }
        item = item.next as JsonValue
    }
    return 0 as JsonValue
}

function bool json_object_has(JsonValue value_node, str key_name) {
    return json_object_get(value_node, key_name) != 0
}

function int json_hex_char(int nibble) {
    return ascii_hex_nibble_char(nibble & 15)
}

function int json_write_escape_u00(ptr out_buf, int out_idx, int ch) {
    mem.write8(out_buf + out_idx + 0, 92)
    mem.write8(out_buf + out_idx + 1, 117)
    mem.write8(out_buf + out_idx + 2, 48)
    mem.write8(out_buf + out_idx + 3, 48)
    mem.write8(out_buf + out_idx + 4, json_hex_char(ch >> 4))
    mem.write8(out_buf + out_idx + 5, json_hex_char(ch))
    return out_idx + 6
}

function str json_escape_string_inner(str raw_text) {
    if raw_text == 0 {
        return json_owned_empty()
    }
    let source_len = string_length(raw_text)
    let out_buf = mem.make_zero(source_len * 6 + 1)
    if out_buf == 0 {
        return json_owned_empty()
    }

    let p = raw_text as ptr
    var out_idx = 0
    var i = 0
    while i < source_len {
        let ch = mem.read8(p + i)
        if ch == 34 {
            mem.write8(out_buf + out_idx + 0, 92)
            mem.write8(out_buf + out_idx + 1, 34)
            out_idx = out_idx + 2
        } else if ch == 92 {
            mem.write8(out_buf + out_idx + 0, 92)
            mem.write8(out_buf + out_idx + 1, 92)
            out_idx = out_idx + 2
        } else if ch == 8 {
            mem.write8(out_buf + out_idx + 0, 92)
            mem.write8(out_buf + out_idx + 1, 98)
            out_idx = out_idx + 2
        } else if ch == 12 {
            mem.write8(out_buf + out_idx + 0, 92)
            mem.write8(out_buf + out_idx + 1, 102)
            out_idx = out_idx + 2
        } else if ch == 10 {
            mem.write8(out_buf + out_idx + 0, 92)
            mem.write8(out_buf + out_idx + 1, 110)
            out_idx = out_idx + 2
        } else if ch == 13 {
            mem.write8(out_buf + out_idx + 0, 92)
            mem.write8(out_buf + out_idx + 1, 114)
            out_idx = out_idx + 2
        } else if ch == 9 {
            mem.write8(out_buf + out_idx + 0, 92)
            mem.write8(out_buf + out_idx + 1, 116)
            out_idx = out_idx + 2
        } else if ch < 32 {
            out_idx = json_write_escape_u00(out_buf, out_idx, ch)
        } else {
            mem.write8(out_buf + out_idx, ch)
            out_idx++
        }
        i++
    }

    mem.write8(out_buf + out_idx, 0)
    let out = make_string(out_buf)
    free(out_buf)
    return out
}

function str json_quote_string(str raw_text) {
    let inner = json_escape_string_inner(raw_text)
    let out = text_surround(inner, "\"", "\"")
    free(inner)
    return out
}

function str json_append_keep(str left, str right) {
    let out = string_append(left, right)
    free(left)
    return out
}

function str json_append_take(str left, str right) {
    let out = string_append(left, right)
    free(left)
    free(right)
    return out
}

internal function bool json_bu)SBJSON"
            R"SBJSON(f_reserve(JsonStrBuf buf, int extra) {
    let needed = buf.len + extra + 1
    if needed <= buf.cap {
        return true
    }
    var new_cap = buf.cap
    if new_cap < 64 {
        new_cap = 64
    }
    while new_cap < needed {
        new_cap = new_cap * 2
    }
    let next_data = malloc(new_cap)
    if next_data == 0 {
        return false
    }
    if buf.data != 0 && buf.len > 0 {
        memcpy(next_data, buf.data, buf.len)
    }
    if buf.data != 0 {
        free(buf.data)
    }
    buf.data = next_data
    buf.cap = new_cap
    return true
}

internal function void json_buf_push_byte(JsonStrBuf buf, int ch) {
    if !json_buf_reserve(buf, 1) {
        return
    }
    mem.write8(buf.data + buf.len, ch)
    buf.len = buf.len + 1
}

internal function void json_buf_push_str(JsonStrBuf buf, str text_val) {
    if text_val == 0 {
        return
    }
    let slen = string_length(text_val)
    if slen <= 0 {
        return
    }
    if !json_buf_reserve(buf, slen) {
        return
    }
    memcpy(buf.data + buf.len, text_val as ptr, slen)
    buf.len = buf.len + slen
}

internal function void json_buf_push_escaped(JsonStrBuf buf, str raw_text) {
    json_buf_push_byte(buf, 34)
    if raw_text != 0 {
        let slen = string_length(raw_text)
        if slen > 0 and json_buf_reserve(buf, slen * 6) {
            let p = raw_text as ptr
            var out_idx = buf.len
            let dst = buf.data
            var i = 0
            while i < slen {
                let ch = mem.read8(p + i)
                if ch == 34 {
                    mem.write8(dst + out_idx, 92)
                    mem.write8(dst + out_idx + 1, 34)
                    out_idx += 2
                } else if ch == 92 {
                    mem.write8(dst + out_idx, 92)
                    mem.write8(dst + out_idx + 1, 92)
                    out_idx += 2
                } else if ch == 8 {
                    mem.write8(dst + out_idx, 92)
                    mem.write8(dst + out_idx + 1, 98)
                    out_idx += 2
                } else if ch == 12 {
                    mem.write8(dst + out_idx, 92)
                    mem.write8(dst + out_idx + 1, 102)
                    out_idx += 2
                } else if ch == 10 {
                    mem.write8(dst + out_idx, 92)
                    mem.write8(dst + out_idx + 1, 110)
                    out_idx += 2
                } else if ch == 13 {
                    mem.write8(dst + out_idx, 92)
                    mem.write8(dst + out_idx + 1, 114)
                    out_idx += 2
                } else if ch == 9 {
                    mem.write8(dst + out_idx, 92)
                    mem.write8(dst + out_idx + 1, 116)
                    out_idx += 2
                } else if ch < 32 {
                    out_idx = json_write_escape_u00(dst, out_idx, ch)
                } else {
                    mem.write8(dst + out_idx, ch)
                    out_idx++
                }
                i++
            }
            buf.len = out_idx
        }
    }
    json_buf_push_byte(buf, 34)
}

internal function void json_stringify_into(JsonStrBuf buf, JsonValue value_node) {
    if value_node == 0 {
        json_buf_push_str(buf, "null")
        return
    }
    let k = value_node.kind
    if k == JSON_KIND_NULL {
        json_buf_push_str(buf, "null")
        return
    }
    if k == JSON_KIND_BOOL {
        if value_node.bool_value != 0 {
            json_buf_push_str(buf, "true")
        } else {
            json_buf_push_str(buf, "false")
        }
        return
    }
    if k == JSON_KIND_NUMBER {
        if value_node.text != 0 and string_length(value_node.text) > 0 {
            json_buf_push_str(buf, value_node.text)
        } else {
            json_buf_push_str(buf, "0")
        }
        return
    }
    if k == JSON_KIND_STRING {
        json_buf_push_escaped(buf, value_node.text)
        return
    }
    if k == JSON_KIND_ARRAY {
        json_buf_push_byte(buf, 91)
        var item = value_node.child as JsonValue
        var first = true
        while item != 0 {
            if !first {
                json_buf_push_byte(buf, 44)
            }
            first = false
            json_stringify_into(buf, item)
            item = item.next as JsonValue
        }
        json_buf_push_byte(buf, 93)
        return
    }
    if k == JSON_KIND_OBJECT {
        json_buf_push_byte(buf, 123)
        var item = value_node.child as JsonValue
        var first = true
        while item != 0 {
            if !first {
                json_buf_push_byte(buf, 44)
            }
            first = false
            json_buf_push_escaped(buf, item.key)
            json_buf_push_byte(buf, 58)
            json_stringify_into(buf, item)
            item = item.next as JsonValue
        }
        json_buf_push_byte(buf, 125)
        return
    }
    json_buf_push_str(buf, "null")
}

function str json_stringify(JsonValue value_node) {
    if value_node == 0 {
        return text_clone("null")
    }
    let buf = malloc(24) as JsonStrBuf
    if buf == 0 {
        return text_clone("null")
    }
    buf.data = malloc(128)
    buf.len = 0
    if buf.data != 0 {
        buf.cap = 128
    } else {
        buf.cap = 0
    }
    json_stringify_into(buf, value_node)
    if buf.data == 0 {
        free(buf)
        return text_clone("null")
    }
    mem.write8(buf.data + buf.len, 0)
    let out = make_string(buf.data)
    free(buf.data)
    free(buf)
    return out
}

// Compatibility helpers for quick raw-text JSON lookup.

function int json_skip_ws(str source, int start_idx) {
    if source == 0 {
        return start_idx
    }
    let total = string_length(source)
    let p = source as ptr
    var idx = start_idx
    if idx < 0 {
        idx = 0
    }
    while idx < total {
        if !ascii_is_space(mem.read8(p + idx)) {
            break
        }
        idx++
    }
    return idx
}

function int json_find_key(str source, str key_name) {
    if source == 0 or key_name == 0 {
        return -1
    }
    let source_len = string_length(source)
    let key_len = string_length(key_name)
    if key_len <= 0 or source_len < key_len + 2 {
        return -1
    }

    let p = source as ptr
    let kp = key_name as ptr
    var i = 0
    while i < source_len {
        let ch = mem.read8(p + i)
        if ch == 34 {
            let str_start = i
            var j = i + 1
            while j < source_len {
                let c = mem.read8(p + j)
                if c == 92 {
                    j = j + 2
                    continue
                }
                if c == 34 {
                    break
                }
                j++
            }
            if j >= source_len {
                return -1
            }
            let inner_len = j - str_start - 1
            if inner_len == key_len {
                if memcmp(p + str_start + 1, kp, key_len) == 0 {
                    var after = j + 1
                    while after < source_len and ascii_is_space(mem.read8(p + after)) {
                        after++
                    }
                    if after < source_len and mem.read8(p + after) == 58 {
                        return str_start
                    }
                }
            }
            i = j + 1
            continue
        }
        i++
    }

    return -1
}

function int json_find_value_start(str source, str key_name) {
    let key_idx = json_find_key(source, key_name)
    if key_idx < 0 {
        return -1
    }

    let len = string_length(source)
    let p = source as ptr
    var idx = key_idx + 1 + string_length(key_name) + 1
    while idx < len {
        if mem.read8(p + idx) == 58 {
            return json_skip_ws(source, idx + 1)
        }
        idx++
    }
    return -1
}

function str json_get_string(str source, str key_name) {
    let start = json_find_value_start(source, key_name)
    if start < 0 or mem.read8((source as ptr) + start) != 34 {
        return json_owned_empty()
    }

    let cursor = json_cursor_at(source, start)
    if cursor == 0 {
        return json_owned_empty()
    }
    let out = json_parse_string_raw(cursor)
    free(cursor)
    if out == 0 {
  )SBJSON"
            R"SBJSON(      return json_owned_empty()
    }
    return out
}

function int json_get_int(str source, str key_name, int fallback) {
    let start = json_find_value_start(source, key_name)
    if start < 0 {
        return fallback
    }

    let cursor = json_cursor_at(source, start)
    if cursor == 0 {
        return fallback
    }
    let raw = json_parse_number_raw(cursor)
    free(cursor)
    if raw == 0 {
        return fallback
    }

    if text_contains_char(raw, 46) or text_contains_char(raw, 101) or text_contains_char(raw, 69) {
        free(raw)
        return fallback
    }

    let out = parse_int(raw)
    free(raw)
    return out
}

function bool json_get_bool(str source, str key_name, bool fallback) {
    let start = json_find_value_start(source, key_name)
    if start < 0 {
        return fallback
    }

    let len = string_length(source)
    let p = (source as ptr) + start
    if start + 4 <= len and memcmp(p, "true" as ptr, 4) == 0 {
        return true
    }
    if start + 5 <= len and memcmp(p, "false" as ptr, 5) == 0 {
        return false
    }

    return fallback
}

function bool json_has_key(str source, str key_name) {
    return json_find_value_start(source, key_name) >= 0
}
)SBJSON"},
        {"mem", R"SBMEM(// Memory operations and typed read/write helpers over compiler builtins.

function ptr make(int size) {
    if size <= 0 {
        return malloc(1)
    }
    return malloc(size)
}

function ptr make_zero(int size) {
    var alloc_size = size
    if alloc_size <= 0 {
        alloc_size = 1
    }
    let block = malloc(alloc_size)
    if block != 0 {
        memset(block, 0, alloc_size)
    }
    return block
}

function ptr make_copy(ptr src, int size) {
    if size <= 0 {
        return make_zero(1)
    }
    let block = malloc(size)
    if block != 0 && src != 0 {
        memcpy(block, src, size)
    }
    return block
}

function void free_ptr(ptr p) {
    if p == 0 {
        return
    }
    free(p)
}

function i64 read(ptr location) {
    return mem_read(location)
}

function i64 read8(ptr location) {
    return mem_read_i8(location)
}

function i64 read16(ptr location) {
    return mem_read_i16(location)
}

function i64 read32(ptr location) {
    return mem_read_i32(location)
}

function i64 read64(ptr location) {
    return mem_read(location)
}

function void write(ptr location, i64 cell) {
    mem_write(location, cell)
}

function void write8(ptr location, int byte_value) {
    mem_write_i8(location, byte_value)
}

function void write16(ptr location, int short_value) {
    mem_write_i16(location, short_value)
}

function void write32(ptr location, int int_value) {
    mem_write_i32(location, int_value)
}

function void write64(ptr location, i64 cell) {
    mem_write(location, cell)
}

function void text(ptr dst, str text_value) {
    if dst == 0 || text_value == 0 {
        return
    }
    let len = string_length(text_value)
    if len > 0 {
        memcpy(dst, text_value as ptr, len)
    }
}

function void textz(ptr dst, str text_value) {
    if dst == 0 {
        return
    }
    if text_value == 0 {
        mem_write_i8(dst, 0)
        return
    }
    let len = string_length(text_value)
    if len > 0 {
        memcpy(dst, text_value as ptr, len)
    }
    mem_write_i8(dst + len, 0)
}

function void zero(ptr dst, int size) {
    if dst == 0 || size <= 0 {
        return
    }
    memset(dst, 0, size)
}

function void fill(ptr dst, int byte_value, int size) {
    if dst == 0 || size <= 0 {
        return
    }
    memset(dst, byte_value, size)
}

function void copy(ptr dst, ptr src, int size) {
    if dst == 0 || src == 0 || size <= 0 || dst == src {
        return
    }
    memcpy(dst, src, size)
}

function void move(ptr dst, ptr src, int size) {
    if dst == 0 || src == 0 || size <= 0 || dst == src {
        return
    }
    if dst < src || dst >= src + size {
        memcpy(dst, src, size)
        return
    }
    var remaining = size
    while remaining >= 8 {
        remaining -= 8
        mem_write(dst + remaining, mem_read(src + remaining))
    }
    while remaining > 0 {
        remaining -= 1
        mem_write_i8(dst + remaining, mem_read_i8(src + remaining))
    }
}

function void copy_cells(ptr dst, ptr src, int cells) {
    if dst == 0 || src == 0 || cells <= 0 || dst == src {
        return
    }
    memcpy(dst, src, cells * 8)
}

function void move_cells(ptr dst, ptr src, int cells) {
    if cells <= 0 {
        return
    }
    move(dst, src, cells * 8)
}

function int compare(ptr a, ptr b, int size) {
    if size <= 0 || a == b {
        return 0
    }
    return memcmp(a, b, size)
}

function ptr dup(ptr src, int size) {
    return make_copy(src, size)
}

function ptr offset(ptr base, int delta) {
    return base + delta
}

function ptr after(ptr base, int delta) {
    return base + delta
}

function ptr mem_alloc_bytes(int size) {
    return make(size)
}

function ptr mem_alloc_zero(int size) {
    return make_zero(size)
}

function ptr mem_alloc_copy(ptr src, int size) {
    return make_copy(src, size)
}

function void mem_free_ptr(ptr p) {
    free_ptr(p)
}

function void mem_zero(ptr dst, int size) {
    zero(dst, size)
}

function void mem_fill(ptr dst, int byte_value, int size) {
    fill(dst, byte_value, size)
}

function void mem_copy(ptr dst, ptr src, int size) {
    copy(dst, src, size)
}

function void mem_move(ptr dst, ptr src, int size) {
    move(dst, src, size)
}

function void mem_copy_cells(ptr dst, ptr src, int cells) {
    copy_cells(dst, src, cells)
}

function void mem_move_cells(ptr dst, ptr src, int cells) {
    move_cells(dst, src, cells)
}

function int mem_compare(ptr a, ptr b, int size) {
    return compare(a, b, size)
}

function ptr mem_dup(ptr src, int size) {
    return dup(src, size)
}

function ptr mem_offset(ptr base, int delta) {
    return offset(base, delta)
}

function ptr mem_end(ptr base, int delta) {
    return after(base, delta)
}
)SBMEM"},
        {"option", R"SBOPTION(// Specialized optional value wrappers backed by zero-copy views.
// Sable does not have generics yet, so we keep the most useful payload shapes.

enum OptOffset {
    HasValue = 0,
    Item = 8,
}

view OptI64 {
    has_value: i64 @ OptOffset.HasValue
    item: i64 @ OptOffset.Item
}

view OptPtr {
    has_value: i64 @ OptOffset.HasValue
    item: ptr @ OptOffset.Item
}

view OptStr {
    has_value: i64 @ OptOffset.HasValue
    item: str @ OptOffset.Item
}

view OptBool {
    has_value: i64 @ OptOffset.HasValue
    item: i64 @ OptOffset.Item
}

function OptI64 opt_i64_some(i64 item) {
    let opt = malloc(16) as OptI64
    if opt == 0 {
        return 0 as OptI64
    }
    opt.has_value = 1
    opt.item = item
    return opt
}

function OptI64 opt_i64_none() {
    let opt = malloc(16) as OptI64
    if opt == 0 {
        return 0 as OptI64
    }
    opt.has_value = 0
    opt.item = 0
    return opt
}

function bool opt_i64_is_some(OptI64 opt) {
    if opt == 0 {
        return false
    }
    return opt.has_value != 0
}

function bool opt_i64_is_none(OptI64 opt) {
    if opt == 0 {
        return true
    }
    return opt.has_value == 0
}

function i64 opt_i64_unwrap(OptI64 opt) {
    if opt != 0 and opt.has_value != 0 {
        return opt.item
    }
    return 0
}

function i64 opt_i64_unwrap_or(OptI64 opt, i64 fallback) {
    if opt != 0 and opt.has_value != 0 {
        return opt.item
    }
    return fallback
}

function void opt_i64_free(OptI64 opt) {
    if opt != 0 {
        free(opt)
    }
}

function OptPtr opt_ptr_some(ptr item_ptr) {
    let opt = malloc(16) as OptPtr
    if opt == 0 {
        return 0 as OptPtr
    }
    opt.has_value = 1
    opt.item = item_ptr
    return opt
}

function OptPtr opt_ptr_none() {
    let opt = malloc(16) as OptPtr
    if opt == 0 {
        return 0 as OptPtr
    }
    opt.has_value = 0
    opt.item = 0
    return opt
}

function bool opt_ptr_is_some(OptPtr opt) {
    if opt == 0 {
        return false
    }
    return opt.has_value != 0
}

function bool opt_ptr_is_none(OptPtr opt) {
    if opt == 0 {
        return true
    }
    return opt.has_value == 0
}

function ptr opt_ptr_unwrap(OptPtr opt) {
    if opt != 0 and opt.has_value != 0 {
        return opt.item
    }
    return 0
}

function ptr opt_ptr_unwrap_or(OptPtr opt, ptr fallback) {
    if opt != 0 and opt.has_value != 0 {
        return opt.item
    }
    return fallback
}

function void opt_ptr_free(OptPtr opt) {
    if opt != 0 {
        free(opt)
    }
}

function OptStr opt_str_some(str text_value) {
    let opt = malloc(16) as OptStr
    if opt == 0 {
        return 0 as OptStr
    }
    opt.has_value = 1
    opt.item = text_value
    return opt
}

function OptStr opt_str_none() {
    let opt = malloc(16) as OptStr
    if opt == 0 {
        return 0 as OptStr
    }
    opt.has_value = 0
    opt.item = ""
    return opt
}

function bool opt_str_is_some(OptStr opt) {
    if opt == 0 {
        return false
    }
    return opt.has_value != 0
}

function bool opt_str_is_none(OptStr opt) {
    if opt == 0 {
        return true
    }
    return opt.has_value == 0
}

function str opt_str_unwrap(OptStr opt) {
    if opt != 0 and opt.has_value != 0 {
        return opt.item
    }
    return ""
}

function str opt_str_unwrap_or(OptStr opt, str fallback) {
    if opt != 0 and opt.has_value != 0 {
        return opt.item
    }
    return fallback
}

function void opt_str_free(OptStr opt) {
    if opt != 0 {
        free(opt)
    }
}

function OptBool opt_bool_some(bool flag) {
    let opt = malloc(16) as OptBool
    if opt == 0 {
        return 0 as OptBool
    }
    opt.has_value = 1
    if flag {
        opt.item = 1
    } else {
        opt.item = 0
    }
    return opt
}

function OptBool opt_bool_none() {
    let opt = malloc(16) as OptBool
    if opt == 0 {
        return 0 as OptBool
    }
    opt.has_value = 0
    opt.item = 0
    return opt
}

function bool opt_bool_is_some(OptBool opt) {
    if opt == 0 {
        return false
    }
    return opt.has_value != 0
}

function bool opt_bool_is_none(OptBool opt) {
    if opt == 0 {
        return true
    }
    return opt.has_value == 0
}

function bool opt_bool_unwrap(OptBool opt) {
    if opt != 0 and opt.has_value != 0 {
        return opt.item != 0
    }
    return false
}

function bool opt_bool_unwrap_or(OptBool opt, bool fallback) {
    if opt != 0 and opt.has_value != 0 {
        return opt.item != 0
    }
    return fallback
}

function void opt_bool_free(OptBool opt) {
    if opt != 0 {
        free(opt)
    }
}
)SBOPTION"},
        {"owner", R"SBOWNER(import mem
import text

// Manual ownership helpers.
// These are not RAII. They provide a strong convention for "who frees what".

struct OwnedPtr {
    value: ptr,
    owned: i64,
}

struct OwnedStr {
    value: str,
    owned: i64,
}

struct OwnedBlock {
    value: ptr,
    size: int,
    owned: i64,
}

function OwnedPtr owned_ptr_borrow(ptr value_ptr) {
    let owner = OwnedPtr {
        value: value_ptr,
        owned: 0,
    }
    return owner
}

function OwnedPtr owned_ptr_adopt(ptr value_ptr) {
    let owner = OwnedPtr {
        value: value_ptr,
        owned: 1,
    }
    return owner
}

function OwnedPtr owned_ptr_alloc(int size) {
    let value_ptr = mem_alloc_zero(size)
    let owner = OwnedPtr {
        value: value_ptr,
        owned: 1,
    }
    return owner
}

function ptr owned_ptr_get(OwnedPtr owner) {
    return owner.value
}

function bool owned_ptr_is_owned(OwnedPtr owner) {
    return owner.owned != 0
}

function ptr owned_ptr_release(*OwnedPtr owner) {
    owner.owned = 0
    return owner.value
}

function void owned_ptr_free(*OwnedPtr owner) {
    if owner.owned != 0 {
        if owner.value == 0 {
            owner.value = 0
            owner.owned = 0
            return
        }
        free(owner.value)
    }
    owner.value = 0
    owner.owned = 0
}

function OwnedPtr owned_ptr_dispose(OwnedPtr owner) {
    if owner.owned != 0 && owner.value != 0 {
        free(owner.value)
    }
    owner.value = 0
    owner.owned = 0
    return owner
}

function void owned_ptr_reset(*OwnedPtr owner, ptr value_ptr, bool take_ownership) {
    owned_ptr_free(owner)
    owner.value = value_ptr
    owner.owned = take_ownership
}

function OwnedStr owned_str_borrow(str text_value) {
    let owner = OwnedStr {
        value: text_value,
        owned: 0,
    }
    return owner
}

function OwnedStr owned_str_adopt(str text_value) {
    let owner = OwnedStr {
        value: text_value,
        owned: 1,
    }
    return owner
}

function OwnedStr owned_str_clone(str text_value) {
    let cloned = text_clone(text_value)
    let owner = OwnedStr {
        value: cloned,
        owned: 1,
    }
    return owner
}

function str owned_str_get(OwnedStr owner) {
    return owner.value
}

function bool owned_str_is_owned(OwnedStr owner) {
    return owner.owned != 0
}

function str owned_str_release(*OwnedStr owner) {
    owner.owned = 0
    return owner.value
}

function void owned_str_free(*OwnedStr owner) {
    if owner.owned != 0 {
        if owner.value == 0 {
            owner.value = ""
            owner.owned = 0
            return
        }
        free(owner.value)
    }
    owner.value = ""
    owner.owned = 0
}

function OwnedStr owned_str_dispose(OwnedStr owner) {
    if owner.owned != 0 && owner.value != 0 {
        free(owner.value)
    }
    owner.value = ""
    owner.owned = 0
    return owner
}

function void owned_str_reset(*OwnedStr owner, str text_value, bool take_ownership) {
    owned_str_free(owner)
    owner.value = text_value
    owner.owned = take_ownership
}

function OwnedBlock owned_block_alloc(int size) {
    let value_ptr = mem_alloc_zero(size)
    let block = OwnedBlock {
        value: value_ptr,
        size: size,
        owned: 1,
    }
    return block
}

function OwnedBlock owned_block_borrow(ptr value_ptr, int size) {
    let block = OwnedBlock {
        value: value_ptr,
        size: size,
        owned: 0,
    }
    return block
}

function ptr owned_block_get(OwnedBlock block) {
    return block.value
}

function int owned_block_size(OwnedBlock block) {
    return block.size
}

function bool owned_block_is_owned(OwnedBlock block) {
    return block.owned != 0
}

function ptr owned_block_release(*OwnedBlock block) {
    block.owned = 0
    return block.value
}

function void owned_block_free(*OwnedBlock block) {
    if block.owned != 0 {
        if block.value == 0 {
            block.value = 0
            block.size = 0
            block.owned = 0
            return
        }
        free(block.value)
    }
    block.value = 0
    block.size = 0
    block.owned = 0
}

function OwnedBlock owned_block_dispose(OwnedBlock block) {
    if block.owned != 0 && block.value != 0 {
        free(block.value)
    }
    block.value = 0
    block.size = 0
    block.owned = 0
    return block
}

function void owned_block_reset(*OwnedBlock block, ptr value_ptr, int size, bool take_ownership) {
    owned_block_free(block)
    block.value = value_ptr
    block.size = size
    block.owned = take_ownership
}
)SBOWNER"},
        {"path", R"SBPATH(import mem
import text

// Lightweight path helpers for common tooling tasks.
// Ownership:
// - path_join2/path_basename/path_dirname/path_ext/path_stem return heap strings; caller must free.

function int path_last_sep(str source) {
    if source == 0 {
        return -1
    }
    let p = source as ptr
    var i = string_length(source) - 1
    while i >= 0 {
        let ch = mem.read8(p + i)
        if ch == 47 or ch == 92 {
            return i
        }
        i--
    }
    return -1
}

function str path_join2(str left, str right) {
    if text_is_empty(left) {
        return text_clone(right)
    }
    if text_is_empty(right) {
        return text_clone(left)
    }

    let left_len = string_length(left)
    let last = mem.read8((left as ptr) + left_len - 1)
    if last == 47 or last == 92 {
        return string_append(left, right)
    }
    return text_join3(left, "/", right)
}

function str path_basename(str source) {
    let idx = path_last_sep(source)
    if idx < 0 {
        return text_clone(source)
    }
    return string_substring(source, idx + 1, string_length(source) - idx - 1)
}

function str path_dirname(str source) {
    let idx = path_last_sep(source)
    if idx < 0 {
        return text_clone("")
    }
    if idx == 0 {
        return string_substring(source, 0, 1)
    }
    return string_substring(source, 0, idx)
}

function str path_ext(str source) {
    let base_start = path_last_sep(source) + 1
    let total = string_length(source)
    let p = source as ptr
    var dot = total - 1
    while dot >= base_start {
        if mem.read8(p + dot) == 46 {
            return string_substring(source, dot + 1, total - dot - 1)
        }
        dot--
    }
    return text_clone("")
}

function str path_stem(str source) {
    let base_start = path_last_sep(source) + 1
    let total = string_length(source)
    let p = source as ptr
    var dot = total - 1
    while dot >= base_start {
        if mem.read8(p + dot) == 46 {
            return string_substring(source, base_start, dot - base_start)
        }
        dot--
    }
    return string_substring(source, base_start, total - base_start)
}
)SBPATH"},
        {"prelude", R"SBPRELUDE(import ascii
import fmt
import fs
import json
import mem
import path
import process
import rand
import text
import time
import vec
import cpp_vector
import option
import result
import owner
import algo
)SBPRELUDE"},
        {"process", R"SBPROCESS(// Process and runtime host helpers.

using MessageBoxAFn = fn(ptr, str, str, int) -> int

function int process_id() {
    return get_current_process_id()
}

function ptr process_handle() {
    return get_current_process()
}

function int process_last_error() {
    return get_last_error()
}

function ptr process_load_library(str lib_path) {
    return load_library(lib_path)
}

function ptr process_get_symbol(ptr module_handle, str symbol_name) {
    return get_proc(module_handle, symbol_name)
}

function int process_msgbox(str title, str body, int flags) {
    let user32 = load_library("user32.dll")
    if user32 == 0 {
        return 0
    }

    let raw = get_proc(user32, "MessageBoxA")
    if raw == 0 {
        return 0
    }

    let message_box = raw as MessageBoxAFn
    return message_box(0, body, title, flags)
}

function void process_exit(int code) {
    exit(code)
}
)SBPROCESS"},
        {"rand", R"SBRAND(import time

// Fast deterministic PRNG (SplitMix64 seeding + Xorshift64* mixing).

var rand_state: int = 0

function int rand_seed(int seed) {
    var z = seed
    if z == 0 {
        z = 1
    }
    z = (z ^ (z >> 30)) * -4658895280553007687
    z = (z ^ (z >> 27)) * -7723592293110705685
    z = z ^ (z >> 31)
    if z == 0 {
        z = 1
    }
    rand_state = z
    return rand_state
}

function int rand_seed_auto() {
    return rand_seed(time_tick_ms() ^ 0x9E3779B97F4A7C15)
}

function int rand_next() {
    if rand_state == 0 {
        rand_seed_auto()
    }

    var x = rand_state
    x = x ^ (x >> 12)
    x = x ^ (x << 25)
    x = x ^ (x >> 27)
    if x == 0 {
        x = 1
    }
    rand_state = x
    let mixed = x * 0x2545F4914F6CDD1D
    return mixed & 0x7FFFFFFFFFFFFFFF
}

function int rand_range(int low, int high) {
    if high <= low {
        return low
    }
    let span = high - low
    return low + (rand_next() % span)
}

function bool rand_bool() {
    return (rand_next() & 1) != 0
}

function int rand_pick2(int a, int b) {
    if rand_bool() {
        return a
    }
    return b
}
)SBRAND"},
        {"result", R"SBRESULT(// Result wrappers with a small error record backed by zero-copy views.

enum ResOffset {
    Ok = 0,
    Item = 8,
    ErrorCode = 16,
    Error = 24,
}

enum ResVoidOffset {
    Ok = 0,
    ErrorCode = 8,
    Error = 16,
}

view ResI64 {
    ok: i64 @ ResOffset.Ok
    item: i64 @ ResOffset.Item
    error_code: i64 @ ResOffset.ErrorCode
    error: str @ ResOffset.Error
}

view ResPtr {
    ok: i64 @ ResOffset.Ok
    item: ptr @ ResOffset.Item
    error_code: i64 @ ResOffset.ErrorCode
    error: str @ ResOffset.Error
}

view ResStr {
    ok: i64 @ ResOffset.Ok
    item: str @ ResOffset.Item
    error_code: i64 @ ResOffset.ErrorCode
    error: str @ ResOffset.Error
}

view ResVoid {
    ok: i64 @ ResVoidOffset.Ok
    error_code: i64 @ ResVoidOffset.ErrorCode
    error: str @ ResVoidOffset.Error
}

function ResI64 res_i64_ok(i64 item) {
    let result = malloc(32) as ResI64
    if result == 0 {
        return 0 as ResI64
    }
    result.ok = 1
    result.item = item
    result.error_code = 0
    result.error = ""
    return result
}

function ResI64 res_i64_err(i64 code, str message) {
    let result = malloc(32) as ResI64
    if result == 0 {
        return 0 as ResI64
    }
    result.ok = 0
    result.item = 0
    result.error_code = code
    result.error = message
    return result
}

function bool res_i64_is_ok(ResI64 result) {
    if result == 0 {
        return false
    }
    return result.ok != 0
}

function bool res_i64_is_err(ResI64 result) {
    if result == 0 {
        return true
    }
    return result.ok == 0
}

function i64 res_i64_unwrap(ResI64 result) {
    if result != 0 and result.ok != 0 {
        return result.item
    }
    return 0
}

function i64 res_i64_unwrap_or(ResI64 result, i64 fallback) {
    if result != 0 and result.ok != 0 {
        return result.item
    }
    return fallback
}

function i64 res_i64_error_code(ResI64 result) {
    if result == 0 {
        return 0
    }
    return result.error_code
}

function str res_i64_error(ResI64 result) {
    if result == 0 {
        return ""
    }
    return result.error
}

function void res_i64_free(ResI64 result) {
    if result != 0 {
        free(result)
    }
}

function ResPtr res_ptr_ok(ptr item_ptr) {
    let result = malloc(32) as ResPtr
    if result == 0 {
        return 0 as ResPtr
    }
    result.ok = 1
    result.item = item_ptr
    result.error_code = 0
    result.error = ""
    return result
}

function ResPtr res_ptr_err(i64 code, str message) {
    let result = malloc(32) as ResPtr
    if result == 0 {
        return 0 as ResPtr
    }
    result.ok = 0
    result.item = 0
    result.error_code = code
    result.error = message
    return result
}

function bool res_ptr_is_ok(ResPtr result) {
    if result == 0 {
        return false
    }
    return result.ok != 0
}

function bool res_ptr_is_err(ResPtr result) {
    if result == 0 {
        return true
    }
    return result.ok == 0
}

function ptr res_ptr_unwrap(ResPtr result) {
    if result != 0 and result.ok != 0 {
        return result.item
    }
    return 0
}

function ptr res_ptr_unwrap_or(ResPtr result, ptr fallback) {
    if result != 0 and result.ok != 0 {
        return result.item
    }
    return fallback
}

function i64 res_ptr_error_code(ResPtr result) {
    if result == 0 {
        return 0
    }
    return result.error_code
}

function str res_ptr_error(ResPtr result) {
    if result == 0 {
        return ""
    }
    return result.error
}

function void res_ptr_free(ResPtr result) {
    if result != 0 {
        free(result)
    }
}

function ResStr res_str_ok(str text_value) {
    let result = malloc(32) as ResStr
    if result == 0 {
        return 0 as ResStr
    }
    result.ok = 1
    result.item = text_value
    result.error_code = 0
    result.error = ""
    return result
}

function ResStr res_str_err(i64 code, str message) {
    let result = malloc(32) as ResStr
    if result == 0 {
        return 0 as ResStr
    }
    result.ok = 0
    result.item = ""
    result.error_code = code
    result.error = message
    return result
}

function bool res_str_is_ok(ResStr result) {
    if result == 0 {
        return false
    }
    return result.ok != 0
}

function bool res_str_is_err(ResStr result) {
    if result == 0 {
        return true
    }
    return result.ok == 0
}

function str res_str_unwrap(ResStr result) {
    if result != 0 and result.ok != 0 {
        return result.item
    }
    return ""
}

function str res_str_unwrap_or(ResStr result, str fallback) {
    if result != 0 and result.ok != 0 {
        return result.item
    }
    return fallback
}

function i64 res_str_error_code(ResStr result) {
    if result == 0 {
        return 0
    }
    return result.error_code
}

function str res_str_error(ResStr result) {
    if result == 0 {
        return ""
    }
    return result.error
}

function void res_str_free(ResStr result) {
    if result != 0 {
        free(result)
    }
}

function ResVoid res_void_ok() {
    let result = malloc(24) as ResVoid
    if result == 0 {
        return 0 as ResVoid
    }
    result.ok = 1
    result.error_code = 0
    result.error = ""
    return result
}

function ResVoid res_void_err(i64 code, str message) {
    let result = malloc(24) as ResVoid
    if result == 0 {
        return 0 as ResVoid
    }
    result.ok = 0
    result.error_code = code
    result.error = message
    return result
}

function bool res_void_is_ok(ResVoid result) {
    if result == 0 {
        return false
    }
    return result.ok != 0
}

function bool res_void_is_err(ResVoid result) {
    if result == 0 {
        return true
    }
    return result.ok == 0
}

function i64 res_void_error_code(ResVoid result) {
    if result == 0 {
        return 0
    }
    return result.error_code
}

function str res_void_error(ResVoid result) {
    if result == 0 {
        return ""
    }
    return result.error
}

function void res_void_free(ResVoid result) {
    if result != 0 {
        free(result)
    }
}
)SBRESULT"},
        {"strbuf", R"SBSTRBUF(import mem

// Growable string builder.
//
// Appending N pieces to a strbuf costs O(total) instead of the O(N * total) that
// repeated string_append would cost, because the buffer grows geometrically and
// the final string is materialized only once.
//
// Ownership:
// - strbuf_new / strbuf_with_capacity allocate; the caller owns the handle and
//   must release it with strbuf_free.
// - strbuf_to_string returns a NEW heap string; freeing the builder does not free
//   it, and freeing the string does not touch the builder.
//
// Layout: the handle is a view over a 24-byte header.
//   [0]  data : ptr -> heap block of `cap` bytes
//   [8]  len  : int -> bytes written so far
//   [16] cap  : int -> allocated bytes

view StrBuf {
    data: ptr @ 0
    len: int @ 8
    cap: int @ 16
}

// initial capacity for a builder created without an explicit size
let STRBUF_MIN_CAPACITY: int = 32

function StrBuf strbuf_alloc_handle() {
    var handle = malloc(24) as StrBuf
    if handle != 0 {
        handle.data = 0
        handle.len = 0
        handle.cap = 0
    }
    return handle
}

function StrBuf strbuf_with_capacity(int capacity) {
    var want = capacity
    if want < STRBUF_MIN_CAPACITY {
        want = STRBUF_MIN_CAPACITY
    }
    let block = mem.make_zero(want)
    if block == 0 {
        return 0 as StrBuf
    }
    let handle = strbuf_alloc_handle()
    if handle == 0 {
        free(block)
        return 0 as StrBuf
    }
    handle.data = block
    handle.len = 0
    handle.cap = want
    return handle
}

function StrBuf strbuf_new() {
    return strbuf_with_capacity(STRBUF_MIN_CAPACITY)
}

function void strbuf_free(StrBuf buf) {
    if buf == 0 {
        return
    }
    if buf.data != 0 {
        free(buf.data)
        buf.data = 0
    }
    free(buf)
}

function int strbuf_len(StrBuf buf) {
    if buf == 0 {
        return 0
    }
    return buf.len
}

function int strbuf_capacity(StrBuf buf) {
    if buf == 0 {
        return 0
    }
    return buf.cap
}

function bool strbuf_is_empty(StrBuf buf) {
    return strbuf_len(buf) == 0
}

function void strbuf_clear(StrBuf buf) {
    if buf == 0 {
        return
    }
    buf.len = 0
    if buf.data != 0 && buf.cap > 0 {
        mem.write8(buf.data, 0)
    }
}

// grow the backing block so it can hold at least `needed` bytes. returns false on
// allocation failure (the builder keeps its previous contents).
function bool strbuf_reserve(StrBuf buf, int needed) {
    if buf == 0 {
        return false
    }
    if needed <= buf.cap {
        return true
    }
    var want = buf.cap
    if want < STRBUF_MIN_CAPACITY {
        want = STRBUF_MIN_CAPACITY
    }
    while want < needed {
        let previous = want
        want = want + (want >> 1)
        if want <= previous {
            want = previous + 1
        }
    }
    let block = mem.make_zero(want)
    if block == 0 {
        return false
    }
    if buf.data != 0 && buf.len > 0 {
        memcpy(block, buf.data, buf.len)
        free(buf.data)
    }
    buf.data = block
    buf.cap = want
    return true
}

// append one byte. returns false only on allocation failure.
function bool strbuf_push_byte(StrBuf buf, int byte_value) {
    if buf == 0 {
        return false
    }
    if !strbuf_reserve(buf, buf.len + 1) {
        return false
    }
    mem.write8(buf.data + buf.len, byte_value & 0xFF)
    buf.len = buf.len + 1
    return true
}

// append a string's bytes (no null terminator is written). a null string is a
// no-op, so it is safe to append an optional value.
function bool strbuf_append(StrBuf buf, str text_value) {
    if buf == 0 {
        return false
    }
    if text_value == 0 {
        return true
    }
    let n = string_length(text_value)
    if n <= 0 {
        return true
    }
    if !strbuf_reserve(buf, buf.len + n) {
        return false
    }
    memcpy(buf.data + buf.len, text_value as ptr, n)
    buf.len = buf.len + n
    return true
}

// append a bounded slice of a string: bytes [start, start+count).
function bool strbuf_append_slice(StrBuf buf, str text_value, int start, int count) {
    if buf == 0 {
        return false
    }
    if text_value == 0 || count <= 0 {
        return true
    }
    var offset = start
    var n = count
    let total = string_length(text_value)
    if offset < 0 {
        n = n + offset
        offset = 0
    }
    if offset >= total || n <= 0 {
        return true
    }
    if offset + n > total {
        n = total - offset
    }
    if !strbuf_reserve(buf, buf.len + n) {
        return false
    }
    memcpy(buf.data + buf.len, (text_value as ptr) + offset, n)
    buf.len = buf.len + n
    return true
}

// append a signed integer in base 10.
function bool strbuf_append_int(StrBuf buf, i64 value) {
    if buf == 0 {
        return false
    }
    return strbuf_append(buf, int_to_string(value))
}

// append `count` copies of a single byte.
function bool strbuf_append_repeat(StrBuf buf, int byte_value, int count) {
    if buf == 0 {
        return false
    }
    if count <= 0 {
        return true
    }
    if !strbuf_reserve(buf, buf.len + count) {
        return false
    }
    memset(buf.data + buf.len, byte_value & 0xFF, count)
    buf.len = buf.len + count
    return true
}

// current contents as a str view into the builder's own storage. valid until the
// next append that grows the block or the next strbuf_free. this may reserve one
// extra byte for the terminator, so do not hold a view across an append.
function str strbuf_view(StrBuf buf) {
    if buf == 0 || buf.data == 0 {
        return "" as str
    }
    return strbuf_terminate_view(buf)
}

// ensure a null terminator after the used bytes, then return the data pointer as a
// str. the terminator lives in the capacity (reserve guarantees room for one extra
// byte beyond what has been appended).
function str strbuf_terminate_view(StrBuf buf) {
    if buf == 0 || buf.data == 0 {
        return "" as str
    }
    if !strbuf_reserve(buf, buf.len + 1) {
        return "" as str
    }
    mem.write8(buf.data + buf.len, 0)
    return buf.data as str
}

// materialize the contents as a fresh heap string. empty builders yield an empty
// string, never a null.
function str strbuf_to_string(StrBuf buf) {
    if buf == 0 || buf.data == 0 || buf.len <= 0 {
        return make_string("")
    }
    return string_substring(strbuf_view(buf), 0, buf.len)
}

// materialize the contents as a fresh heap string and reset the builder to empty.
function str strbuf_take_string(StrBuf buf) {
    if buf == 0 || buf.data == 0 || buf.len <= 0 {
        return make_string("")
    }
    let result = string_substring(strbuf_view(buf), 0, buf.len)
    strbuf_clear(buf)
    return result
}
)SBSTRBUF"},
        {"text", R"SBTEXT(import mem
import ascii

// High-speed O(N) text helpers layered over direct memory scans and single-pass builders.
// Ownership:
// - text_clone/text_slice/text_prefix/text_suffix/text_trim*/text_join*/text_repeat/text_pad*/text_surround return heap strings; caller must free.

function int text_len(str text) {
    return string_length(text)
}

function bool text_is_empty(str text) {
    return string_length(text) == 0
}

function bool text_eq(str a, str b) {
    return string_equals(a, b) != 0
}

function str text_clone(str text) {
    if text == 0 {
        return string_substring("", 0, 0)
    }
    return string_substring(text, 0, string_length(text))
}

function str text_slice(str text, int start, int length) {
    return string_substring(text, start, length)
}

function str text_prefix(str text, int length) {
    return string_substring(text, 0, length)
}

function str text_suffix(str text, int length) {
    if length <= 0 {
        return string_substring("", 0, 0)
    }
    let total = string_length(text)
    if length >= total {
        return text_clone(text)
    }
    return string_substring(text, total - length, length)
}

function int text_char_at(str text, int index) {
    if text == 0 || index < 0 {
        return 0
    }
    let len = string_length(text)
    if index >= len {
        return 0
    }
    return mem.read8((text as ptr) + index)
}

function bool text_starts_with(str text, str prefix) {
    let prefix_len = string_length(prefix)
    if prefix_len == 0 {
        return true
    }
    let text_len_val = string_length(text)
    if prefix_len > text_len_val {
        return false
    }
    return memcmp(text as ptr, prefix as ptr, prefix_len) == 0
}

function bool text_ends_with(str text, str suffix) {
    let suffix_len = string_length(suffix)
    if suffix_len == 0 {
        return true
    }
    let text_len_val = string_length(text)
    if suffix_len > text_len_val {
        return false
    }
    let start = text_len_val - suffix_len
    return memcmp((text as ptr) + start, suffix as ptr, suffix_len) == 0
}

function int text_find_char(str text, int ch) {
    if text == 0 {
        return -1
    }
    let len = string_length(text)
    let p = text as ptr
    let target = ch & 255
    var i = 0
    while i < len {
        if mem.read8(p + i) == target {
            return i
        }
        i++
    }
    return -1
}

function int text_rfind_char(str text, int ch) {
    if text == 0 {
        return -1
    }
    let p = text as ptr
    let target = ch & 255
    var i = string_length(text) - 1
    while i >= 0 {
        if mem.read8(p + i) == target {
            return i
        }
        i--
    }
    return -1
}

function int text_count_char(str text, int ch) {
    if text == 0 {
        return 0
    }
    let len = string_length(text)
    let p = text as ptr
    let target = ch & 255
    var count = 0
    var i = 0
    while i < len {
        if mem.read8(p + i) == target {
            count++
        }
        i++
    }
    return count
}

function bool text_contains_char(str text, int ch) {
    return text_find_char(text, ch) >= 0
}

function int text_find(str text, str needle) {
    let text_len_val = string_length(text)
    let needle_len = string_length(needle)
    if needle_len == 0 {
        return 0
    }
    if needle_len > text_len_val {
        return -1
    }

    let hay = text as ptr
    let ndl = needle as ptr
    let first = mem.read8(ndl)
    if needle_len == 1 {
        var i = 0
        while i < text_len_val {
            if mem.read8(hay + i) == first {
                return i
            }
            i++
        }
        return -1
    }

    let limit = text_len_val - needle_len
    let rest_len = needle_len - 1
    var i = 0
    while i <= limit {
        if mem.read8(hay + i) == first {
            if memcmp(hay + i + 1, ndl + 1, rest_len) == 0 {
                return i
            }
        }
        i++
    }
    return -1
}

function bool text_contains(str text, str needle) {
    return text_find(text, needle) >= 0
}

function bool text_is_blank(str text) {
    if text == 0 {
        return true
    }
    let len = string_length(text)
    let p = text as ptr
    var i = 0
    while i < len {
        if !ascii_is_space(mem.read8(p + i)) {
            return false
        }
        i++
    }
    return true
}

function str text_trim_left(str text) {
    let len = string_length(text)
    let p = text as ptr
    var start = 0
    while start < len {
        if !ascii_is_space(mem.read8(p + start)) {
            break
        }
        start++
    }
    return string_substring(text, start, len - start)
}

function str text_trim_right(str text) {
    let p = text as ptr
    var stop = string_length(text)
    while stop > 0 {
        if !ascii_is_space(mem.read8(p + stop - 1)) {
            break
        }
        stop--
    }
    return string_substring(text, 0, stop)
}

function str text_trim(str text) {
    let len = string_length(text)
    let p = text as ptr
    var start = 0
    while start < len {
        if !ascii_is_space(mem.read8(p + start)) {
            break
        }
        start++
    }
    var stop = len
    while stop > start {
        if !ascii_is_space(mem.read8(p + stop - 1)) {
            break
        }
        stop--
    }
    return string_substring(text, start, stop - start)
}

function str text_join2(str left, str right) {
    return string_append(left, right)
}

function str text_join3(str a, str b, str c) {
    let la = string_length(a)
    let lb = string_length(b)
    let lc = string_length(c)
    let total = la + lb + lc
    let buf = malloc(total + 1)
    if buf == 0 {
        return string_substring("", 0, 0)
    }
    if la > 0 { memcpy(buf, a as ptr, la) }
    if lb > 0 { memcpy(buf + la, b as ptr, lb) }
    if lc > 0 { memcpy(buf + la + lb, c as ptr, lc) }
    mem.write8(buf + total, 0)
    let out = make_string(buf)
    free(buf)
    return out
}

function str text_join4(str a, str b, str c, str d) {
    let la = string_length(a)
    let lb = string_length(b)
    let lc = string_length(c)
    let ld = string_length(d)
    let total = la + lb + lc + ld
    let buf = malloc(total + 1)
    if buf == 0 {
        return string_substring("", 0, 0)
    }
    var pos = 0
    if la > 0 { memcpy(buf, a as ptr, la); pos += la }
    if lb > 0 { memcpy(buf + pos, b as ptr, lb); pos += lb }
    if lc > 0 { memcpy(buf + pos, c as ptr, lc); pos += lc }
    if ld > 0 { memcpy(buf + pos, d as ptr, ld); pos += ld }
    mem.write8(buf + pos, 0)
    let out = make_string(buf)
    free(buf)
    return out
}

function str text_repeat(str text, int count) {
    if count <= 0 {
        return string_substring("", 0, 0)
    }
    let len = string_length(text)
    if len == 0 {
        return string_substring("", 0, 0)
    }
    if count == 1 {
        return text_clone(text)
    }

    let total = len * count
    let buf = malloc(total + 1)
    if buf == 0 {
        return string_substring("", 0, 0)
    }

    memcpy(buf, text as ptr, len)
    var filled = len
    while filled * 2 <= total {
        memcpy(buf + filled, buf, filled)
        filled *= 2
    }
    if filled < total {
        memcpy(buf + filled, buf, total - filled)
    }
    mem.write8(buf + total, 0)
    let out = make_string(buf)
    free(buf)
    return out
}

function str text_pad_left(str text, int width, str fill) {
    let len = string_length(text)
    if len >= width {
        return text_clone(text)
    }
    let fill_len = string_length(fill)
    if fill_len == 0 {
        return text_clone(text)
    }
    let reps = width - len
    let pad_bytes = fill_len * reps
    let total = pad_bytes + len
    let buf = malloc(total + 1)
    if buf == 0 {
        return text_clone(text)
    }
    memcpy(buf, fill as ptr, fill_len)
    var filled = fill_len
    while filled * 2 <= pad_bytes {
        memcpy(buf + filled, buf, filled)
        filled *= 2
    }
    if filled < pad_bytes {
        memcpy(buf + filled, buf, pad_bytes - filled)
    }
    if len > 0 {
        memcpy(buf + pad_bytes, text as ptr, len)
    }
    mem.write8(buf + total, 0)
    let out = make_string(buf)
    free(buf)
    return out)SBTEXT"
            R"SBTEXT(
}

function str text_pad_right(str text, int width, str fill) {
    let len = string_length(text)
    if len >= width {
        return text_clone(text)
    }
    let fill_len = string_length(fill)
    if fill_len == 0 {
        return text_clone(text)
    }
    let reps = width - len
    let pad_bytes = fill_len * reps
    let total = len + pad_bytes
    let buf = malloc(total + 1)
    if buf == 0 {
        return text_clone(text)
    }
    if len > 0 {
        memcpy(buf, text as ptr, len)
    }
    let pad_dst = buf + len
    memcpy(pad_dst, fill as ptr, fill_len)
    var filled = fill_len
    while filled * 2 <= pad_bytes {
        memcpy(pad_dst + filled, pad_dst, filled)
        filled *= 2
    }
    if filled < pad_bytes {
        memcpy(pad_dst + filled, pad_dst, pad_bytes - filled)
    }
    mem.write8(buf + total, 0)
    let out = make_string(buf)
    free(buf)
    return out
}

function str text_surround(str text, str left, str right) {
    return text_join3(left, text, right)
}
)SBTEXT"},
        {"time", R"SBTIME(// Time and delay helpers layered over the native builtins.

function int time_tick_ms() {
    return get_tick_count()
}

function void time_sleep_ms(int ms) {
    if ms <= 0 {
        return
    }
    sleep(ms)
}

function int time_elapsed_ms(int start_tick) {
    let now = time_tick_ms()
    if now < start_tick {
        return 0
    }
    return now - start_tick
}

function bool time_after_ms(int start_tick, int duration_ms) {
    return time_elapsed_ms(start_tick) >= duration_ms
}
)SBTIME"},
        {"vec", R"SBVEC(import mem

// Growable vector layered over the builtin array storage.
// Builtin array layout:
//   data - 16 => logical length
//   data -  8 => capacity
//   data      => contiguous 8-byte cells

struct Vec {
    data: ptr,
    size: int,
    cap: int,
}

function void vec_sync_len(Vec vec) {
    if vec.data != 0 {
        mem.write(vec.data - 16, vec.size)
    }
}

function Vec vec_new(int capacity) {
    if capacity < 4 {
        capacity = 4
    }

    let store = array_new(capacity)
    if store != 0 {
        mem.write(store - 16, 0)
    }
    return Vec {
        data: store,
        size: 0,
        cap: capacity,
    }
}

function Vec vec_from_array(ptr data) {
    if data == 0 {
        return vec_new(4)
    }

    let used = array_len(data)
    var capacity = mem.read(data - 8)
    if capacity < used {
        capacity = used
    }
    if capacity < 4 {
        capacity = 4
    }
    mem.write(data - 16, used)
    return Vec {
        data: data,
        size: used,
        cap: capacity,
    }
}

function Vec vec_from_array_copy(ptr data) {
    if data == 0 {
        return vec_new(4)
    }

    let used = array_len(data)
    var out = vec_new(used)
    if used > 0 && out.data != 0 {
        mem.copy_cells(out.data, data, used)
        mem.write(out.data - 16, used)
        out.size = used
    }
    return out
}

function ptr vec_data(Vec vec) {
    return vec.data
}

function int vec_len(Vec vec) {
    return vec.size
}

function int vec_cap(Vec vec) {
    return vec.cap
}

function bool vec_is_empty(Vec vec) {
    return vec.size == 0
}

function i64 vec_get(Vec vec, int idx) {
    if idx < 0 || idx >= vec.size || vec.data == 0 {
        return 0
    }
    let arr = vec.data as *i64
    return arr[idx]
}

function i64 vec_first(Vec vec) {
    if vec.size <= 0 || vec.data == 0 {
        return 0
    }
    let arr = vec.data as *i64
    return arr[0]
}

function i64 vec_last(Vec vec) {
    let used = vec.size
    if used <= 0 || vec.data == 0 {
        return 0
    }
    let arr = vec.data as *i64
    return arr[used - 1]
}

function i64 vec_peek_last(Vec vec) {
    return vec_last(vec)
}

function Vec vec_reserve(Vec vec, int min_capacity) {
    var current = vec.cap
    if min_capacity <= current {
        return vec
    }

    if current < 4 {
        current = 4
    }

    var previous = 0
    while current < min_capacity {
        previous = current
        current = current + (current >> 1)
        if current <= previous {
            current = previous + 1
        }
    }

    let next_data = array_new(current)
    if next_data == 0 {
        return vec
    }
    let used = vec.size
    let old_data = vec.data
    if old_data != 0 && used > 0 {
        mem.copy_cells(next_data, old_data, used)
    }
    mem.write(next_data - 16, used)

    if old_data != 0 {
        array_free(old_data)
    }

    vec.data = next_data
    vec.cap = current
    return vec
}

function Vec vec_push(Vec vec, i64 item) {
    let used = vec.size
    if used >= vec.cap {
        vec = vec_reserve(vec, used + 1)
        if vec.cap <= used {
            return vec
        }
    }

    var arr = vec.data as *i64
    arr[used] = item
    vec.size = used + 1
    mem.write(vec.data - 16, used + 1)
    return vec
}

function i64 vec_pop_value(Vec vec) {
    let used = vec.size
    if used <= 0 || vec.data == 0 {
        return 0
    }
    let arr = vec.data as *i64
    return arr[used - 1]
}

function Vec vec_drop_last(Vec vec) {
    let used = vec.size
    if used <= 0 {
        return vec
    }
    vec.size = used - 1
    vec_sync_len(vec)
    return vec
}

function Vec vec_pop(Vec vec) {
    return vec_drop_last(vec)
}

function Vec vec_set(Vec vec, int idx, i64 item) {
    if idx < 0 || idx >= vec.size || vec.data == 0 {
        return vec
    }
    var arr = vec.data as *i64
    arr[idx] = item
    return vec
}

function Vec vec_clear(Vec vec) {
    vec.size = 0
    vec_sync_len(vec)
    return vec
}

function i64 vec_index_of(Vec vec, i64 target) {
    let used = vec.size
    if used <= 0 || vec.data == 0 {
        return -1
    }
    let arr = vec.data as *i64
    for i in range(0, used) {
        if arr[i] == target {
            return i
        }
    }
    return -1
}

function bool vec_contains(Vec vec, i64 target) {
    return vec_index_of(vec, target) >= 0
}

function Vec vec_append(Vec vec, Vec other) {
    let other_used = other.size
    if other_used <= 0 || other.data == 0 {
        return vec
    }

    let used = vec.size
    vec = vec_reserve(vec, used + other_used)
    if vec.cap < used + other_used {
        return vec
    }
    mem.copy_cells(vec.data + used * 8, other.data, other_used)
    vec.size = used + other_used
    vec_sync_len(vec)
    return vec
}

function Vec vec_remove_at(Vec vec, int idx) {
    let used = vec.size
    if idx < 0 || idx >= used || vec.data == 0 {
        return vec
    }

    let stop = used - 1
    if idx < stop {
        mem.move_cells(vec.data + idx * 8, vec.data + (idx + 1) * 8, stop - idx)
    }
    vec.size = stop
    vec_sync_len(vec)
    return vec
}

function Vec vec_swap_remove(Vec vec, int idx) {
    let used = vec.size
    if idx < 0 || idx >= used || vec.data == 0 {
        return vec
    }

    let last_idx = used - 1
    if idx < last_idx {
        var arr = vec.data as *i64
        arr[idx] = arr[last_idx]
    }
    vec.size = last_idx
    vec_sync_len(vec)
    return vec
}

function Vec vec_shrink_to_fit(Vec vec) {
    let used = vec.size
    var target = used
    if target < 4 {
        target = 4
    }
    if target >= vec.cap {
        return vec
    }

    let old_data = vec.data
    let next_data = array_new(target)
    if next_data == 0 {
        return vec
    }
    if old_data != 0 && used > 0 {
        mem.copy_cells(next_data, old_data, used)
    }
    mem.write(next_data - 16, used)
    if old_data != 0 {
        array_free(old_data)
    }

    vec.data = next_data
    vec.cap = target
    return vec
}

function Vec vec_copy(Vec vec) {
    let used = vec.size
    var copy = vec_new(vec.cap)
    if used > 0 && vec.data != 0 && copy.data != 0 {
        mem.copy_cells(copy.data, vec.data, used)
        mem.write(copy.data - 16, used)
        copy.size = used
    }
    return copy
}

function ptr vec_to_array_copy(Vec vec) {
    let used = vec.size
    let out = array_new(used)
    if used > 0 && vec.data != 0 && out != 0 {
        mem.copy_cells(out, vec.data, used)
    }
    if out != 0 {
        mem.write(out - 16, used)
    }
    return out
}

function Vec vec_free(Vec vec) {
    if vec.data != 0 {
        array_free(vec.data)
    }
    vec.data = 0
    vec.size = 0
    vec.cap = 0
    return vec
}
)SBVEC"},
    };
    return sources;
}
}
