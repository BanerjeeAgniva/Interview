# https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/?envType=daily-question&envId=2025-03-19
class Solution(object):
    def minOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        ops = 0  
        for i in range(len(nums) - 2):
          if nums[i] == 0:  
            nums[i] ^= 1
            nums[i + 1] ^= 1
            nums[i + 2] ^= 1
            ops += 1  
        return ops if all(num == 1 for num in nums) else -1 
