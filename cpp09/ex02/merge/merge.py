
def merge(lnums, rnums, nums):
    ln, rn = len(lnums), len(rnums)

    n, l, r = 0, 0, 0
    while l < ln and r < rn:
        if lnums[l] < rnums[r]:
            nums[n] = lnums[l]
            n += 1
            l += 1
        else:
            nums[n] = rnums[r]
            r += 1
            n += 1

    while l < ln:
        nums[n] = lnums[l]
        n += 1
        l += 1

    while r < rn:
        nums[n] = rnums[r]
        r += 1
        n += 1

def merge_sort(nums):
    l = len(nums)
    if l <= 1:
        return

    mid = l // 2
    lnums = nums[:mid]
    rnums = nums[mid:]
    merge_sort(lnums)
    merge_sort(rnums)
    merge(lnums, rnums, nums)

def main():
    nums = list(input("> ").split(' '))
    merge_sort(nums)
    print(nums)

if __name__ == "__main__":
    main()