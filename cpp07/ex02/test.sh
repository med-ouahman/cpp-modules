#!/bin/bash

make re 2>&1
echo ""

OUTPUT=$(./array 2>&1)
echo "$OUTPUT"
echo ""

PASS=0
FAIL=0

check() {
    local label="$1"
    local expected="$2"
    if echo "$OUTPUT" | grep -qF "$expected"; then
        echo "PASS  $label"
        PASS=$((PASS + 1))
    else
        echo "FAIL  $label — expected: '$expected'"
        FAIL=$((FAIL + 1))
    fi
}

check "default size 0"               "size = 0"
check "size constructor size 5"      "size = 5"
check "value init zeros"             "ints[0] default = 0"
check "fill [0]=0"                   "[0] = 0"
check "fill [4]=40"                  "[4] = 40"
check "deep copy: original intact"   "original ints[0] = 0 (must stay 0)"
check "deep copy: copy modified"     "copy[0] = 999 (must be 999)"
check "assign: original intact"      "original ints[1] = 10 (must stay 10)"
check "assign: assigned modified"    "assigned[1] = 888 (must be 888)"
check "self-assign intact"           "ints[0] = 0 (must stay 0)"
check "string hello"                 "hello"
check "string world"                 "world"
check "string cpp"                   "cpp"
check "out of bounds non-empty"      "PASS: caught exception"
check "out of bounds empty"          "PASS: caught exception"
check "const out of bounds"          "PASS: const out-of-bounds"
check "value initialisation"         "PASS: all zero"

echo ""
echo "Results: $PASS passed, $FAIL failed"
