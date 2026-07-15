#!/bin/bash

make re 2>&1
echo ""

OUTPUT=$(./serializer 2>&1)
echo "$OUTPUT"
echo ""

if echo "$OUTPUT" | grep -q "Pointers match   : YES"; then
    echo "PASS  pointer round-trip"
else
    echo "FAIL  pointer round-trip — pointers did not match"
fi

if echo "$OUTPUT" | grep -q "id    : 42"; then
    echo "PASS  id field preserved"
else
    echo "FAIL  id field not preserved"
fi

if echo "$OUTPUT" | grep -q "name  : hello"; then
    echo "PASS  name field preserved"
else
    echo "FAIL  name field not preserved"
fi

if echo "$OUTPUT" | grep -q "value : 3.14"; then
    echo "PASS  value field preserved"
else
    echo "FAIL  value field not preserved"
fi

RAW=$(echo "$OUTPUT" | grep "Serialized (int)" | awk '{print $NF}')
ORIG=$(echo "$OUTPUT" | grep "Original pointer" | awk '{print $NF}')
echo ""
echo "Serialized integer: $RAW  (will differ per run due to ASLR)"
echo "Original address  : $ORIG"
