import random

# @param n: size of the list to generate
# @return: list of sorted numbers
def generate_random_sorted_list(n):
    nums = random.sample(range(0, n * 10), n)
    return sorted(nums)


# @param max: the maximum number to generate
# @param min: the minimum number to generate
# @return: always return a number between min (inclusive) and max (exclusive)
def generate_random_num(min=0, max=100):
    return random.randrange(min, max)


# @param list: the list of numbers to search
# @param target: the number to find
# @return: tuple(index, comparisons):
#          the index of the number (-1) if not found
#          and the number of comparisons

def binary_search(list, target):
    lo = 0
    hi = len(list) - 1
    comparisons = 0

    while lo <= hi:
        mid = (lo + hi) // 2

        comparisons += 1

        if list[mid] == target:
            return mid, comparisons

        if target < list[mid]:
            hi = mid - 1
        else:
            lo = mid + 1

    return -1, comparisons

def main():
    nums = generate_random_sorted_list(7)

    print(nums)

    for i in range(len(nums) + 1):
        if i == 0:
            target = nums[0] - 1
        elif i == len(nums):
            target = nums[-1] + 1
        else:
            target = (nums[i - 1] + nums[i]) // 2

        index, comparisons = binary_search(nums, target)

        print(
            f"position={i}, "
            f"target={target}, "
            f"index={index}, "
            f"comparisons={comparisons}"
        )

if __name__ == "__main__":
    main()