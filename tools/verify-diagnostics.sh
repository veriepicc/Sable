#!/usr/bin/env bash
# Proof artifact for the diagnostics-hardening goal.
#
#   bash tools/verify-diagnostics.sh
#
# Asserts two things:
#   1. every new hard error is rejected by the compiler (exit != 0)
#   2. every new warning kind fires under -Wall on the trigger file
# and prints a summary the reviewer can read.

set -u
cd "$(dirname "$0")/.."

SABLE="bin/Release/sable.exe"
pass=0
fail=0
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT

check_reject() {
    local name="$1" file="$2" needle="$3"
    wine "$SABLE" --fast "$file" >"$tmp/$name.out" 2>&1
    local rc=$?
    local text
    text="$(sed 's/\x1b\[[0-9;]*m//g' "$tmp/$name.out")"
    if [ "$rc" -eq 0 ]; then
        echo "  FAIL $name: compiled but should be rejected"
        fail=$((fail+1))
    elif [ -n "$needle" ] && ! grep -qF "$needle" <<<"$text"; then
        echo "  FAIL $name: rejected but message missing '$needle'"
        echo "       got: $(grep -v '^$' <<<"$text" | head -1)"
        fail=$((fail+1))
    else
        echo "  ok   $name -> $(grep -v '^$' <<<"$text" | head -1)"
        pass=$((pass+1))
    fi
}

check_warning() {
    local kind="$1"
    if grep -q "\[$kind\]" "$tmp/warn.out"; then
        echo "  ok   -W$kind fired"
        pass=$((pass+1))
    else
        echo "  FAIL -W$kind never fired"
        fail=$((fail+1))
    fi
}

echo "== hard errors (each must be rejected) =="
check_reject dup-struct-field    tests/invalid_dup_struct_field.sb    "more than once"
check_reject dup-enum-variant    tests/invalid_dup_enum_variant.sb    "more than once"
check_reject dup-parameter       tests/invalid_dup_parameter.sb       "more than once"
check_reject deref-non-pointer   tests/invalid_deref_non_pointer.sb   "cannot dereference"
check_reject index-float         tests/invalid_index_float.sb         "cannot index a value"
check_reject struct-missing      tests/invalid_struct_missing_field.sb "missing field"
check_reject cast-unknown        tests/invalid_cast_unknown_type.sb   "unknown cast target type"
check_reject mod-float           tests/invalid_mod_float.sb           "integer operand"
check_reject shift-negative      tests/invalid_shift_negative.sb      "shift count"
check_reject return-value-void   tests/invalid_return_value_from_void.sb "no return type"
check_reject return-bare-value   tests/invalid_return_bare_from_value.sb "return with no value"

echo
echo "== warnings (all must fire from one -Wall pass) =="
wine "$SABLE" --fast -Wall tests/test_warnings.sb >"$tmp/warn.out" 2>&1
for k in unused-decl shift-count comparison-always-true duplicate-condition \
         shadowed-parameter unused-loop-var div-by-zero-const void-value-used \
         redundant-cast assign-in-condition; do
    check_warning "$k"
done

echo
echo "== stdlib modules (both must compile with zero errors and zero warnings) =="
for m in hash bitset strbuf; do
    wine "$SABLE" --fast -Wall -Werror "tests/test_$m.sb" >"$tmp/$m.out" 2>&1
    rc=$?
    n=$({ grep -c "error" "$tmp/$m.out" || true; })
    w=$({ grep -c "warning" "$tmp/$m.out" || true; })
    if [ "$rc" -eq 0 ] && [ "$n" -eq 0 ] && [ "$w" -eq 0 ]; then
        echo "  ok   test_$m.sb: exit 0, 0 errors, 0 warnings (-Wall -Werror)"
        pass=$((pass+1))
    else
        echo "  FAIL test_$m.sb: exit=$rc errors=$n warnings=$w"
        fail=$((fail+1))
    fi
    timeout 30 wine "tests/test_$m.exe" >"$tmp/$m.run" 2>/dev/null
    echo "       run: $(head -1 "$tmp/$m.run")"
done

echo
echo "== total warning kinds registered =="
wine "$SABLE" -Wlist 2>&1 | sed 's/\x1b\[[0-9;]*m//g' | grep -c '^  -W' | sed 's/^/  /'

echo
echo "== summary =="
echo "  passed: $pass"
echo "  failed: $fail"
[ "$fail" -eq 0 ]
