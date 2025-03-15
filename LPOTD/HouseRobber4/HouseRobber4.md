# House Robber - Minimum Capability

## Problem Statement
There are several consecutive houses along a street, each containing some amount of money. A robber wants to steal from these houses but cannot rob adjacent houses. The **capability** of the robber is the maximum amount stolen from any single house among the chosen houses.

Given an integer array `nums` representing the money in each house and an integer `k` (minimum houses to rob), return the **minimum possible capability** the robber can have while ensuring at least `k` houses are robbed.

### Example 1:
```plaintext
Input: nums = [2,3,5,9], k = 2
Output: 5
Explanation: The possible ways to rob at least 2 houses are:
- Rob houses at indices (0,2) → Capability = max(2,5) = 5
- Rob houses at indices (0,3) → Capability = max(2,9) = 9
- Rob houses at indices (1,3) → Capability = max(3,9) = 9
The minimum among these capabilities is 5.
```

### Example 2:
```plaintext
Input: nums = [2,7,9,3,1], k = 2
Output: 2
Explanation: The optimal way is to rob houses at (0,4), so capability = max(2,1) = 2.
```

## Intuition & Approach
### Key Observations:
1. **Binary Search on Capability**: Instead of brute-force checking all subsets (`O(2^n)`), we binary search the capability value.
2. **Greedy Validation**: For a given capability `money`, we check if it's possible to rob **at least `k` houses** while ensuring no adjacent houses are robbed.
3. **Binary Search Process**:
   - Start with `l = min(nums)` (smallest money in a house) and `r = max(nums)` (largest money in a house).
   - Use binary search to find the **minimum capability** that allows robbing at least `k` houses.

### Algorithm:
1. Define `is_valid(capability)` to check if at least `k` houses can be robbed while ensuring all robbed houses have money ≤ `capability`.
2. Use **binary search** on the possible `capability` values (`min(nums)` to `max(nums)`).
3. Update the answer when a valid capability is found and try to minimize it further.

### Complexity Analysis:
- **Binary Search**: `O(log(max(nums) - min(nums)))`
- **Validation Function**: `O(n)`
- **Total Complexity**: `O(n log(max(nums) - min(nums)))`, which is efficient for large `n` (up to `10^5`).

