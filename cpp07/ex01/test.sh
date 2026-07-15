#!/bin/bash

make re 2>&1
echo ""

OUTPUT=$(./iter 2>&1)
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
        echo "FAIL  $label — expected to find: '$expected'"
        FAIL=$((FAIL + 1))
    fi
}

check "int print 1"       "1"
check "int print 5"       "5"
check "increment: 2->3"   "3"
check "increment: 5->6"   "6"
check "string hello"      "hello"
check "string world"      "world"
check "printUpper HELLO"  "HELLO"
check "printUpper WORLD"  "WORLD"
check "const int 10"      "10"
check "const int 30"      "30"
check "double 1.1"        "1.1"
check "double 3.3"        "3.3"
check "empty array done"  "(done)"

INT_SECTION=$(echo "$OUTPUT" | awk '/increment then print/,/string array/' | grep -E '^[0-9]+$')
if echo "$INT_SECTION" | grep -q "^2$" && echo "$INT_SECTION" | grep -q "^6$"; then
    echo "PASS  increment range 2..6 correct"
    PASS=$((PASS + 1))
else
    echo "FAIL  increment range unexpected: $INT_SECTION"
    FAIL=$((FAIL + 1))
fi

echo ""
echo "Results: $PASS passed, $FAIL failed"
