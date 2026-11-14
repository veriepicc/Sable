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
| `-Wshadowed-variable` | a binding shadows an outer binding |
| `-Wunreachable-code` | a statement follows `return`/`break`/`continue` |
| `-Wimplicit-narrowing` | a signed value is assigned to a narrower unsigned type |
| `-Wself-assignment` | `x = x`, `x -= x`, `x /= x`, `x %= x` |
| `-Wredundant-compare` | a value is compared with itself |
| `-Wconst-condition` | an `if`/`while` condition is a literal |
| `-Wempty-block` | an `if`/`while`/`for`/`loop` has an empty body |
| `-Wduplicate-switch-case` | the same `case` value appears twice |
| `-Wunreachable-switch-case` | a `case` appears after the default `else` |

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
