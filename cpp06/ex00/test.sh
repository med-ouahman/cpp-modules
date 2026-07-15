#!/bin/bash

make re 2>&1
echo ""

PASS=0
FAIL=0

check() {
    local input="$1"
    local expected="$2"
    local actual
    actual=$(./convert "$input" 2>&1)
    if [ "$actual" = "$expected" ]; then
        echo "PASS  ./convert $input"
        PASS=$((PASS + 1))
    else
        echo "FAIL  ./convert $input"
        echo "  expected:"
        echo "$expected" | sed 's/^/    /'
        echo "  got:"
        echo "$actual" | sed 's/^/    /'
        FAIL=$((FAIL + 1))
    fi
}

check "0" "char: Non displayable
int: 0
float: 0.0f
double: 0.0"

check "42" "char: '*'
int: 42
float: 42.0f
double: 42.0"

check "42.0f" "char: '*'
int: 42
float: 42.0f
double: 42.0"

check "42.0" "char: '*'
int: 42
float: 42.0f
double: 42.0"

check "'a'" "char: 'a'
int: 97
float: 97.0f
double: 97.0"

check "nan" "char: impossible
int: impossible
float: nanf
double: nan"

check "nanf" "char: impossible
int: impossible
float: nanf
double: nan"

check "+inf" "char: impossible
int: impossible
float: +inff
double: +inf"

check "-inf" "char: impossible
int: impossible
float: -inff
double: -inf"

check "+inff" "char: impossible
int: impossible
float: +inff
double: +inf"

check "-inff" "char: impossible
int: impossible
float: -inff
double: -inf"

check "-42" "char: impossible
int: -42
float: -42.0f
double: -42.0"

check "127" "char: Non displayable
int: 127
float: 127.0f
double: 127.0"

check "65" "char: 'A'
int: 65
float: 65.0f
double: 65.0"

check "2147483647" "char: impossible
int: 2147483647
float: 2147483648.0f
double: 2147483647.0"

echo ""
echo "Results: $PASS passed, $FAIL failed"
