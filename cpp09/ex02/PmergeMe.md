# Exercise 02 — PmergeMe (Ford-Johnson merge-insertion sort)

## What this program does

`PmergeMe` takes a sequence of positive integers as arguments, sorts a copy in
a `std::vector<int>` and a copy in a `std::deque<int>` — each using a
hand-written **Ford-Johnson merge-insertion sort** — and prints the unsorted
sequence, the sorted sequence, and the time taken for each container.

## Concepts covered

- **Two different containers (`std::vector` and `std::deque`)**, neither of
  which is `std::map` (ex00) or `std::stack` (ex01), as the module requires.
- **The Ford-Johnson algorithm itself** (Knuth, *The Art of Computer
  Programming, Vol. 3*, "Merge Insertion", p.184) — see the breakdown below.
- **Binary insertion via `std::lower_bound`** (from `<algorithm>`, allowed in
  this module) instead of a linear scan, which is what makes merge-insertion
  better than naive insertion sort.
- **Recursion** as the natural way to express "sort the larger half, then use
  that sorted result to place the rest."
- **Timing with `gettimeofday`** (microsecond resolution, POSIX, not on the
  forbidden-function list) since C++98 has no `<chrono>`.
- Note that `<algorithm>` and STL containers are explicitly **allowed** in
  Module 09 (the "no STL" rule only applies through Module 07) — so using
  `std::lower_bound` here is intentional and within the rules; it's a *search*,
  not a call to `std::sort`, so it doesn't replace the algorithm the exercise
  asks you to implement.

## The algorithm, step by step

1. **Pair up elements.** Split the sequence into pairs and compare each pair,
   labeling the bigger one "large" and the smaller one "small". If there's an
   odd element left over, set it aside for later.
2. **Recurse on the larges.** Recursively apply the same algorithm to the array
   of "large" values only. This is where the recursion bottoms out at size 0
   or 1.
3. **Build the main chain.** The recursive call returns the larges, fully
   sorted. Insert the small that was paired with the *smallest* large directly
   at the front of this chain — no comparison needed, because it's guaranteed
   smaller than every element in the chain.
4. **Insert the rest of the smalls, in Jacobsthal order.** Each remaining small
   value is bounded above by its own paired large (it's smaller than that large
   by construction), so each one is inserted via `lower_bound` within the
   sub-range of the chain *up to* its large's position — never against the
   whole chain. The order in which the smalls are inserted (3, 2, 5, 4, 11, 10,
   9, 8, 7, 6, 21, ...) follows the Jacobsthal sequence
   (`J(n) = J(n-1) + 2*J(n-2)`, i.e. 0, 1, 1, 3, 5, 11, 21, 43, ...). This
   specific order is what makes Ford-Johnson better than plain insertion: it
   maximizes how much of the chain each binary search can rule out, which is
   what minimizes the total number of comparisons. Inserting in any other
   order would still be *correct*, just not optimal.
5. **Insert the odd element last**, against the whole final chain, if there was
   one.

## The bug that came up while testing this (and why the fix matters)

The first version of this code inserted the small from pairing-index 0 at the
front of the chain unconditionally — i.e. it assumed the first pair processed
is always the one holding the overall-smallest large value. That's only true
by coincidence; once the recursive call **sorts** the larges, the value that
ends up at the front of the sorted chain can originally have come from *any*
pairing index, especially on already-sorted or reverse-sorted input. Running
`./PmergeMe 10 9 8 7 6 5 4 3 2 1` against this first version produced
`1 3 9 2 4 5 8 6 7 10` — visibly not sorted.

The fix: before recursing, the original (pre-sort) "large" values are kept
aside. After recursion, the code explicitly figures out *which original
pairing index* holds the smallest large value (and, more generally, ranks all
the original indices by their large value) using a simple selection-style scan
— rather than assuming index 0. That ranking is what correctly drives both the
front-insertion step and the Jacobsthal insertion order. This was caught by a
494-case randomized stress test (`tests/stress_test.py`) comparing this
program's output against a known-correct sort across sizes 1–3000, including
sorted, reverse-sorted, duplicate-heavy, and random inputs — all 494 pass after
the fix.

## Design notes

- The algorithm is implemented **twice** — once for `std::vector`
  (`mergeInsertVector`) and once for `std::deque` (`mergeInsertDeque`) — rather
  than once generically, per the subject's explicit advice to avoid a generic
  function shared across containers.
- `parseArguments` rejects anything that isn't a plain non-negative integer
  string (optionally prefixed with `+`), and anything outside `int` range, so
  `-1`, non-numeric tokens, and overflow values all produce `Error` and a
  non-zero exit code.
- Duplicate values are accepted without any special handling, per the
  subject's note that "the management of errors related to duplicates is left
  to your discretion."
- The chain-ranking step (figuring out which original index is the smallest,
  second-smallest, etc.) is done with a manually written O(k²) selection scan
  rather than `std::sort`, since the point of the exercise is to hand-implement
  the sorting logic — `std::sort` is never called anywhere in this file. `k`
  here is at most half the input size, so this stays cheap even at 3000
  elements.

## Build & run

```
make
./PmergeMe 3 5 9 7 4
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")
```

## Tests

- `tests/run_tests.sh` builds the project, reproduces the subject's worked
  example, checks sortedness on several small/edge-case inputs (1 element, 2
  elements, reverse-sorted, duplicates), checks the `-1` argument error case
  and the no-argument case, runs a 3000-element timing demo, and (if `python3`
  is available) runs the extended stress test below.
- `tests/stress_test.py` is a randomized correctness check: every size from 1
  to 30 with 15 random permutations each, sorted/reverse-sorted sequences at
  several sizes up to 129, all-duplicate sequences, and several random arrays
  at sizes 500/1000/1500/3000, each compared against Python's `sorted()`.
  Current status: **494/494 passing**.

Run either with:

```
bash tests/run_tests.sh
python3 tests/stress_test.py
```

Example timing output (3000 random elements, this machine):

```
Time to process a range of 3000 elements with std::vector : 82034.00000 us
Time to process a range of 3000 elements with std::deque : 136092.00000 us
```

`std::deque` is consistently slower here than `std::vector` for this workload,
which is expected: `std::deque` is stored as separate fixed-size chunks rather
than one contiguous block, so the binary insertions involved in merge-insertion
sort don't benefit from `std::vector`'s cache locality. The subject itself
notes that the exact timing numbers in its own example are "deliberately
strange," so the goal here is a clearly visible difference between the two
containers, not any particular absolute number.
