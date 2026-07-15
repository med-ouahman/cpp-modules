#!/bin/bash
cd "$(dirname "$0")/.."

make re > /dev/null

echo "--- Test 1: no argument ---"
./btc

echo "--- Test 2: file that does not exist ---"
./btc nope.txt

echo "--- Test 3: subject example input ---"
./btc tests/input.txt

echo "--- Test 4: empty file ---"
touch tests/empty.txt
./btc tests/empty.txt
rm -f tests/empty.txt

echo "--- Test 5: malformed lines ---"
printf "date | value\nnotadate | 3\n2011-01-03 | abc\n2011-01-03 | \n2011-02-30 | 1\n" > tests/malformed.txt
./btc tests/malformed.txt
rm -f tests/malformed.txt

echo "All ex00 tests completed."
