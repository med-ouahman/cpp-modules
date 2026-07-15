#!/bin/bash

make re 2>&1
echo ""

OUTPUT=$(./identify 2>&1)
echo "$OUTPUT"
echo ""

PASS=0
FAIL=0

check_line() {
    local label="$1"
    local expected="$2"
    local actual
    actual=$(echo "$OUTPUT" | grep "^$label" | awk '{print $NF}')
    if [ "$actual" = "$expected" ]; then
        echo "PASS  $label = $expected"
        PASS=$((PASS + 1))
    else
        echo "FAIL  $label expected '$expected', got '$actual'"
        FAIL=$((FAIL + 1))
    fi
}

check_line "A ptr:" "A"
check_line "A ref:" "A"
check_line "B ptr:" "B"
check_line "B ref:" "B"
check_line "C ptr:" "C"
check_line "C ref:" "C"

echo ""

PTR_LIST=$(echo "$OUTPUT" | grep "^ptr:" | awk '{print $2}')
REF_LIST=$(echo "$OUTPUT" | grep "^ref:" | awk '{print $2}')
PTR_ARR=($PTR_LIST)
REF_ARR=($REF_LIST)
MISMATCH=0
for i in "${!PTR_ARR[@]}"; do
    if [ "${PTR_ARR[$i]}" != "${REF_ARR[$i]}" ]; then
        echo "FAIL  round $((i+1)): ptr=${PTR_ARR[$i]} ref=${REF_ARR[$i]} (mismatch)"
        MISMATCH=$((MISMATCH + 1))
        FAIL=$((FAIL + 1))
    fi
done
if [ "$MISMATCH" -eq 0 ]; then
    echo "PASS  all random ptr/ref pairs agree across 10 rounds"
    PASS=$((PASS + 1))
fi

echo ""
echo "Results: $PASS passed, $FAIL failed"
