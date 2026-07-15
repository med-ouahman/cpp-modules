import random
import subprocess

random.seed(42)

failures = 0
total = 0

def run_case(arr):
    global failures, total
    total += 1
    args = [str(x) for x in arr]
    result = subprocess.run(["./PmergeMe"] + args, capture_output=True, text=True)
    lines = result.stdout.strip().split("\n")
    before_line = lines[0]
    after_line = lines[1]
    after_values = [int(x) for x in after_line.replace("After:", "").split()]
    expected = sorted(arr)
    if after_values != expected:
        failures += 1
        print(f"MISMATCH for input of size {len(arr)}")
        print(f"  input:    {arr}")
        print(f"  got:      {after_values}")
        print(f"  expected: {expected}")
    return after_values == expected

# exhaustive-ish small sizes with random permutations
for size in range(1, 30):
    for _ in range(15):
        arr = [random.randint(1, 200) for _ in range(size)]
        run_case(arr)

# sorted / reverse sorted edge cases for various sizes
for size in [1,2,3,4,5,6,7,8,9,10,15,16,17,31,32,33,63,64,65,100,127,128,129]:
    run_case(list(range(1, size + 1)))
    run_case(list(range(size, 0, -1)))

# all duplicates
for size in [1,2,3,4,5,10,20]:
    run_case([7] * size)

# large random tests
for size in [500, 1000, 1500, 3000, 3000, 3000]:
    arr = [random.randint(1, 1000000) for _ in range(size)]
    run_case(arr)

print(f"\n{total - failures}/{total} cases passed.")
