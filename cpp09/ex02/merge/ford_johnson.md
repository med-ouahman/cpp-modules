# Binary Search and Jacobsthal Ordering — Our Experiment

## Goal

We started with binary search and built toward the Ford–Johnson merge-insertion idea.

The key question was:

> Why does a particular insertion order reduce the worst-case number of comparisons?

The important chain is:

```text
binary-search cost
      ↓
known upper bounds for pending elements
      ↓
insertion order affects later search ranges
      ↓
grouping pending indices
      ↓
Jacobsthal group boundaries
      ↓
reverse traversal of each group
```

## 1. Binary search

For a sorted prefix containing `m` searchable elements, there are `m + 1` possible insertion positions.

The worst-case number of comparisons is:

\[
C(m) = ceil(log_2(m + 1))
\]

This creates plateaus:

| Elements | Possible positions | Worst case |
|---:|---:|---:|
| 0 | 1 | 0 |
| 1 | 2 | 1 |
| 2–3 | 3–4 | 2 |
| 4–7 | 5–8 | 3 |
| 8–15 | 9–16 | 4 |
| 16–31 | 17–32 | 5 |

So crossing a power-of-two boundary can increase the worst-case comparison count.

## 2. Pending elements and bounds

Ford–Johnson creates pairs conceptually like:

```text
p1 < c1
p2 < c2
p3 < c3
...
```

The `c` elements form the main chain. The `p` elements are pending.

The important fact is:

```text
pi < ci
```

Therefore, when inserting `pi`, we only need to binary-search up to `ci`, rather than the entire main chain.

## 3. Why insertion order matters

After inserting a pending element, it becomes part of the main chain.

That can increase the search range of later pending elements.

Therefore:

```text
p4 -> p5
```

and

```text
p5 -> p4
```

can produce different search-range histories.

However, one of our important observations was that **reversing one isolated group does not necessarily reduce its total cost**. The optimization is a global worst-case comparison optimization; the interaction between groups matters.

## 4. Jacobsthal numbers

The Jacobsthal sequence is:

\[
J_0=0,\quad J_1=1
\]

\[
J_n=J_{n-1}+2J_{n-2}
\]

giving:

```text
0, 1, 1, 3, 5, 11, 21, 43, 85, ...
```

The useful values for the insertion schedule are:

```text
3, 5, 11, 21, 43, ...
```

The sequence itself is **not** the insertion order.

## 5. Jacobsthal numbers become group boundaries

Using 1-based pending indices, `p1` is handled separately.

The useful boundaries create groups such as:

```text
3 -> 5
5 -> 11
11 -> 21
```

Each interval is traversed backwards:

```text
3 -> 5     => 5, 4
5 -> 11    => 11, 10, 9, 8, 7, 6
11 -> 21   => 21, 20, ..., 12
```

Thus, for 11 pending elements, the remaining insertion schedule is:

```text
p3, p2,
p5, p4,
p11, p10, p9, p8, p7, p6
```

`p1` is separate.

## 6. Why reverse the groups?

The Jacobsthal sequence itself is not reversed.

The **indices inside each interval** are traversed backwards.

This works together with:

\[
p_i < c_i
\]

and the changing search prefix caused by earlier insertions.

The larger-bound insertion is performed before the smaller-bound insertions in each group, helping keep the comparison depths balanced.

Again, reversal alone is not the complete optimization; the group boundaries and their interaction with binary-search plateaus are the important part.

## 7. Mathematical connection

Binary search is governed by powers of two:

```text
1, 2, 4, 8, 16, 32, ...
```

while the Ford–Johnson insertion ranges grow as pending elements are inserted.

The scheduling problem is therefore to arrange insertions so that worst-case binary searches remain inside favorable comparison-depth ranges as much as possible.

The recurrence

\[
J_n=J_{n-1}+2J_{n-2}
\]

produces the group boundaries used by Ford–Johnson.

Jacobsthal numbers also grow approximately as:

\[
J_n pprox rac{2^n}{3}
\]

which explains their close relationship with the powers of two governing binary-search depth.

## 8. What we learned

The important mental model is:

```text
pair elements
    ↓
main chain + pending elements
    ↓
known bounds: pi < ci
    ↓
choose an insertion schedule
    ↓
bounded binary insertion
    ↓
count comparisons
```

Jacobsthal supplies the structure for the insertion schedule:

```text
Jacobsthal numbers
    ↓
group boundaries
    ↓
reverse each group
    ↓
pending insertion order
```

The next useful experiment is to brute-force every insertion permutation for a small number of pending elements and compare its worst-case cost with the Jacobsthal schedule. That lets us discover the optimal structure experimentally rather than treating Jacobsthal as magic.
