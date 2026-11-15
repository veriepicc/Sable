# Warnings

Sable ships a static warning layer that runs over the parsed program before
code generation. Warnings never change the emitted code; they only produce
diagnostics. **Every warning is off by default**, so a plain build behaves
exactly as before until you opt in.

## Turning warnings on

```sh
sable -Wall file.sb                 # enable every warning
sable -Wunused-local file.sb        # enable one warning
sable -Wunused-local -Wshadowed-variable file.sb
sable -Wall -Wno-unused-parameter file.sb   # all of them, minus one
sable -Werror file.sb               # treat enabled warnings as errors
sable -Wlist                        # list every warning kind
```

Rules:

- `-Wall` enables everything, then any later `-Wno-<name>` removes one.
- `-W<name>` enables a single warning; `-Wno-<name>` disables one.
- `-Wnone` (or `-Wno-all`) disables every warning.
- `-Werror` escalates all *enabled* warnings to errors, so the build fails.
  Combine with the enable list to gate CI: `-Wunused-local -Werror`.
- An unknown `-Wname` is itself an error (`try -Wlist`).
- Warnings print to stdout after a successful compile and do not affect the
  exit code unless `-Werror` is in effect. They are also printed on `--run`.

## Warning kinds

| Flag | Meaning |
| :--- | :--- |
| `-Wunused-local` | a `let`/`var` binding is never read |
| `-Wunused-parameter` | a function parameter is never read |
| `-Wunused-import` | an imported module is never referenced |
| `-Wshadowed-variable` | a binding shadows an outer binding |
| `-Wunreachable-code` | a statement follows `return`/`break`/`continue` |
| `-Wimplicit-narrowing` | a signed value is assigned to a narrower unsigned type |
| `-Wself-assignment` | `x = x`, `x -= x`, `x /= x`, `x %= x` |
| `-Wredundant-compare` | a value is compared with itself |
| `-Wbool-int-compare` | a `bool` is compared against an integer literal |
| `-Wconst-condition` | an `if`/`while` condition is a literal |
| `-Wempty-block` | an `if`/`while`/`for`/`loop` has an empty body |
| `-Wempty-function` | a function body is empty |
| `-Wloop-never-runs` | a literal `range(a, b)` with `a >= b` can never iterate |
| `-Wduplicate-switch-case` | the same `case` value appears twice |
| `-Wunreachable-switch-case` | a `case` appears after the default `else` |
| `-Wunused-decl` | a top-level function/struct/view/class/enum/constant/global is never referenced |
| `-Wshift-count` | a shift count is negative or `>= 64` |
| `-Wcomparison-always-true` | a comparison folds to a constant (both sides are constants) |
| `-Wduplicate-condition` | a branch of an `if`/`else if` chain repeats an earlier condition |
| `-Wshadowed-parameter` | a local binding shadows an enclosing parameter |
| `-Wunused-loop-var` | a `for`/`parallel for` loop variable is never read |
| `-Wdiv-by-zero-const` | division/modulo by a constant expression that folds to zero |
| `-Wvoid-value-used` | the result of a `void` call is bound to a value |
| `-Wredundant-cast` | a literal is cast to the type it already has |
| `-Wassign-in-condition` | an assignment is used as an `if`/`while` condition |

Names starting with `_` are treated as intentionally unused, so `_buf` never
triggers `unused-local` and a `_`-prefixed or `self` parameter never triggers
`unused-parameter`.

## Example

```c
function int f(int used, int not_used) {   // -Wunused-parameter
    let spare = 1                          // -Wunused-local
    let outer = 2
    {
        let outer = 3                      // -Wshadowed-variable
        return used + outer
    }
}
```

```sh
$ sable -Wall f.sb
warning: f.sb:2:9: unused local 'spare' [unused-local]
warning: f.sb:5:13: 'outer' shadows an outer binding [shadowed-variable]
warning: f.sb:1:30: unused parameter 'not_used' [unused-parameter]
```

## Notes

- Diagnostics carry `file:line:column` when the position is known. Expression
  positions fall back to the enclosing statement, which is always located.
- Warnings are independent of the "possible leak" ownership diagnostics, which
  are always on.

## Hard errors

Some conditions are always bugs and are rejected outright, not warned about:

- dividing or taking a modulo by a literal `0`
- indexing an array or string binding with a literal out-of-range index
  (`let a = [1,2,3]  a[10]`, `"hi"[1000]`, or a negative literal index)
- using `str`/`char` operands with arithmetic, bitwise, or ordering operators
  (`str < 0`, `int + str`, `str + str`) — use the string helpers instead
- rebinding an immutable binding, or writing to a `for`/`parallel for` loop
  variable
- revisiting an already-freed binding (use-after-free), double free
- calling a builtin with the wrong number of arguments
- a struct / view / class field declared more than once
- an enum variant declared more than once
- a function or method parameter name used more than once
- a struct literal that omits a declared field, or sets one twice
- dereferencing a value whose static type is an integer / float / void
- indexing a value whose static type is a float / bool / void / struct
- casting to a type name that resolves to no known type
- integer modulo (`%`) on a float operand
- a negative literal shift count
- returning a value from a `void` function, or a bare `return` from a function
  that must produce a value, or returning the result of a `void` call

## Runtime guards

The generated program must not fault on bad input. These cases are handled at
the instruction level and yield a defined value instead of a `#DE`/page fault:

- `/ 0` and `% 0` yield `0`; `INT64_MIN / -1` wraps to `INT64_MIN`
- indexing through a null pointer (`p[i]`) reads `0`; a store is ignored
- reading a field through a null struct pointer reads `0`; a store is ignored
- a computed index past the end of a heap array reads `0`; a store is ignored

Out of bounds *literal* indices are rejected at compile time (see above), so the
runtime guards only cover computed indices. `mem.read`/`mem.write` remain raw:
they fault on a bad address and are recovered by the SEH crash handler, which is
the documented desugaring for direct memory access.
