#!/bin/bash
cd "$(dirname "$0")/.."

make re > /dev/null

pass=0
fail=0

check() {
	expr="$1"
	expected="$2"
	actual=$(./RPN "$expr" 2>&1)
	if [ "$actual" == "$expected" ]; then
		pass=$((pass + 1))
		echo "OK   '$expr' => '$actual'"
	else
		fail=$((fail + 1))
		echo "FAIL '$expr' => got '$actual', expected '$expected'"
	fi
}

check "8 9 * 9 - 9 - 9 - 4 - 1 +" "42"
check "7 7 * 7 -" "42"
check "1 2 * 2 / 2 * 2 4 - +" "0"
check "(1 + 1)" "Error"
check "1 1 1 + +" "3"
check "3 4 +" "7"
check "5 1 2 + 4 * + 3 -" "14"
check "1 0 /" "Error"
check "1 +" "Error"
check "1 2" "Error"
check "" "Error"
check "9 9 9 9 9 9 9 9 *" "Error"

echo ""
echo "Passed: $pass, Failed: $fail"
