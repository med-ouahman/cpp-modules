from math import ceil, log2


# ------------------------------------------------------------
# Binary insertion
# ------------------------------------------------------------

def binary_insert(nums, target, upper_index=None):
    """Return (new_list, insertion_index, comparisons)."""
    if upper_index is None:
        upper_index = len(nums)

    lo = 0
    hi = upper_index
    comparisons = 0

    while lo < hi:
        mid = (lo + hi) // 2
        comparisons += 1

        if target < nums[mid]:
            hi = mid
        else:
            lo = mid + 1

    result = nums[:]
    result.insert(lo, target)
    return result, lo, comparisons


def binary_insertion_worst_case(searchable_elements):
    """Worst-case comparisons for inserting into m elements."""
    if searchable_elements == 0:
        return 0
    return ceil(log2(searchable_elements + 1))


# ------------------------------------------------------------
# Jacobsthal
# ------------------------------------------------------------

def jacobsthal(n):
    """
    J0 = 0
    J1 = 1
    Jn = J(n-1) + 2*J(n-2)
    """
    if n < 0:
        raise ValueError("n must be non-negative")

    a, b = 0, 1

    if n == 0:
        return a

    for _ in range(2, n + 1):
        a, b = b, b + 2 * a

    return b


def jacobsthal_sequence_until(limit):
    values = []
    n = 0

    while True:
        value = jacobsthal(n)
        if value > limit:
            break
        values.append(value)
        n += 1

    return values


# ------------------------------------------------------------
# The two insertion orders
# ------------------------------------------------------------

def normal_order(n):
    """
    1-based pending indices.

    p1 is normally handled separately by Ford-Johnson, so the
    remaining natural order starts at p2.
    """
    return list(range(2, n + 1))


def jacobsthal_groups(n):
    """
    Explain the Jacobsthal grouping using 1-based pending indices.

    p1 is handled separately.

    Example:
        n = 11

        [3, 2]
        [5, 4]
        [11, 10, 9, 8, 7, 6]
    """
    if n <= 1:
        return []

    groups = []
    previous = 1
    k = 3

    while previous < n:
        current = min(jacobsthal(k), n)

        group = list(range(current, previous, -1))

        if group:
            groups.append(group)

        previous = current
        k += 1

    return groups


def jacobsthal_order(n):
    order = []

    for group in jacobsthal_groups(n):
        order.extend(group)

    return order


# ------------------------------------------------------------
# Explain the groups
# ------------------------------------------------------------

def explain_jacobsthal_groups(n):
    print(f"Pending indices: p1 ... p{n}")
    print("p1 is handled separately.")
    print()

    js = jacobsthal_sequence_until(n)
    print("Jacobsthal sequence:")
    print(js)
    print()

    useful = [x for x in js if x >= 3]
    if n > 1 and (not useful or useful[-1] != n):
        useful.append(n)

    print("Group boundaries:")
    print(useful)
    print()

    print("Groups:")

    for group in jacobsthal_groups(n):
        print("  ", group)

    print()
    print("Final Jacobsthal order:")
    print(jacobsthal_order(n))


# ------------------------------------------------------------
# Compare normal and Jacobsthal schedules
# ------------------------------------------------------------

def show_schedule(n):
    normal = normal_order(n)
    jacob = jacobsthal_order(n)

    print("Normal order:")
    print(normal)

    print()
    print("Jacobsthal order:")
    print(jacob)


def demonstrate_search_plateaus():
    print("Searchable elements -> worst-case comparisons")
    print("----------------------------------------------")

    for n in range(0, 33):
        print(
            f"{n:2} -> {binary_insertion_worst_case(n)}"
        )


# ------------------------------------------------------------
# Manual scheduling experiment
# ------------------------------------------------------------

def show_group_costs(searchable_sizes, order):
    """
    searchable_sizes[i] gives the number of elements in the
    bounded search for pending index i.

    This isolates the binary-search cost from the actual values.
    """
    total = 0

    print("index | searchable | positions | comparisons")
    print("----------------------------------------------")

    for i in order:
        size = searchable_sizes[i]
        positions = size + 1
        cost = binary_insertion_worst_case(size)
        total += cost

        print(
            f"p{i:>3} | "
            f"{size:>10} | "
            f"{positions:>9} | "
            f"{cost:>11}"
        )

    print("----------------------------------------------")
    print("total:", total)


# ------------------------------------------------------------
# Example
# ------------------------------------------------------------

if __name__ == "__main__":
    print("=" * 60)
    print("BINARY SEARCH PLATEAUS")
    print("=" * 60)
    demonstrate_search_plateaus()

    print()
    print("=" * 60)
    print("NORMAL VS JACOBSTHAL ORDER")
    print("=" * 60)
    show_schedule(11)

    print()
    print("=" * 60)
    print("HOW THE GROUPS ARE GENERATED")
    print("=" * 60)
    explain_jacobsthal_groups(21)

    print()
    print("=" * 60)
    print("ONE GROUP")
    print("=" * 60)
    print("Example Jacobsthal group:")
    print("[11, 10, 9, 8, 7, 6]")
