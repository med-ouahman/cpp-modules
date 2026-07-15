#!/bin/bash

make re 2>&1
echo ""

OUTPUT=$(./whatever 2>&1)
echo "$OUTPUT"
echo ""

PASS=0
FAIL=0

check() {
    local label="$1"
    local expected="$2"
    local actual
    actual=$(echo "$OUTPUT" | grep "$label" | head -1)
    if echo "$actual" | grep -qF "$expected"; then
        echo "PASS  $label → $expected"
        PASS=$((PASS + 1))
    else
        echo "FAIL  $label"
        echo "      expected to contain: $expected"
        echo "      got: $actual"
        FAIL=$((FAIL + 1))
    fi
}

check "a = " "a = 3, b = 2"
check "min(a, b)" "min(a, b) = 2"
check "max(a, b)" "max(a, b) = 3"
check "c = " "c = chaine2, d = chaine1"
check "min(c, d)" "min(c, d) = chaine1"
check "max(c, d)" "max(c, d) = chaine2"
check "min(5, 5)" "5"
check "max(5, 5)" "5"
check "swap doubles" "p=2.2 q=1.1"
check "min(p, q)" "1.1"
check "max(p, q)" "2.2"

echo ""
echo "Results: $PASS passed, $FAIL failed"
