#!/bin/bash
cd "$(dirname "$0")/.."

make re > /dev/null

pass=0
fail=0

check_sorted() {
	label="$1"
	shift
	output=$(./PmergeMe "$@" 2>&1)
	after=$(echo "$output" | grep "^After:" | sed 's/After://')
	sorted_check=$(echo "$after" | tr ' ' '\n' | sort -n | tr '\n' ' ')
	actual_trimmed=$(echo "$after" | xargs)
	sorted_trimmed=$(echo "$sorted_check" | xargs)
	if [ "$actual_trimmed" == "$sorted_trimmed" ]; then
		pass=$((pass + 1))
		echo "OK   $label"
	else
		fail=$((fail + 1))
		echo "FAIL $label"
		echo "  got:      $actual_trimmed"
		echo "  expected: $sorted_trimmed"
	fi
}

echo "--- Subject example ---"
./PmergeMe 3 5 9 7 4

echo ""
echo "--- Sortedness checks ---"
check_sorted "5 elements"    3 5 9 7 4
check_sorted "1 element"     42
check_sorted "2 elements"    9 1
check_sorted "reverse 10"    10 9 8 7 6 5 4 3 2 1
check_sorted "duplicates"    5 3 5 1 5 2
check_sorted "already sorted" 1 2 3 4 5 6 7 8 9

echo ""
echo "--- Error case ---"
./PmergeMe "-1" "2"
echo "exit code: $?"

echo ""
echo "--- No arguments ---"
./PmergeMe
echo "exit code: $?"

echo ""
echo "--- 3000 random elements (timing demo) ---"
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ") | tail -n 2

echo ""
echo "Passed: $pass, Failed: $fail"

if command -v python3 > /dev/null; then
	echo ""
	echo "--- Running extended randomized stress test (tests/stress_test.py) ---"
	python3 tests/stress_test.py
fi
