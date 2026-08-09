comp = 0
def binary_insert(chain, value, bound):
    """
    Insert `value` into chain before `bound`.

    We know value < bound, so bound is the exclusive
    upper boundary of the binary search.
    """
    hi = chain.index(bound)
    lo = 0
    global comp
    while lo < hi:
        mid = (lo + hi) // 2
        comp += 1
        if value < chain[mid]:
            hi = mid
        else:
            lo = mid + 1

    chain.insert(lo, value)


def merge_insertion_sort(nums):
    if len(nums) <= 1:
        return nums[:]

    # ------------------------------------------------------------
    # 1. Pair the elements
    # ------------------------------------------------------------

    pairs = []

    i = 0
    while i + 1 < len(nums):
        x = nums[i]
        y = nums[i + 1]

        if x < y:
            small, large = x, y
        else:
            small, large = y, x

        pairs.append((small, large))
        i += 2

    # Odd element has no pair.
    odd = nums[-1] if len(nums) % 2 else None

    # ------------------------------------------------------------
    # 2. Recursively sort the larger elements
    # ------------------------------------------------------------

    larger = [large for small, large in pairs]

    main = merge_insertion_sort(larger)

    # ------------------------------------------------------------
    # 3. Reconstruct the pending elements.
    #
    # Each small element is associated with its corresponding
    # large element.
    # ------------------------------------------------------------

    pending = []

    for small, large in pairs:
        pending.append((small, large))

    # ------------------------------------------------------------
    # 4. Insert pending elements.
    #
    # NO JACOBSTHAL ORDERING YET.
    #
    # We simply insert them in their current order.
    # ------------------------------------------------------------

    for small, large in pending:
        binary_insert(main, small, large)

    # ------------------------------------------------------------
    # 5. Insert the odd element.
    # ------------------------------------------------------------

    if odd is not None:
        # It has no partner, so it can be inserted anywhere.
        lo = 0
        hi = len(main)

        while lo < hi:
            mid = (lo + hi) // 2

            if odd < main[mid]:
                hi = mid
            else:
                lo = mid + 1

        main.insert(lo, odd)

    return main


def main():
    global comp
    while True:
        s = input("")
        nums = s.split()
        for i in range(len(nums)):
            nums[i] = int(nums[i])
        nums = merge_insertion_sort(nums)
        print(nums)
        print(f"Comparison count: {comp}")
        comp = 0
main()