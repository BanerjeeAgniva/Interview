# https://leetcode.com/problems/longest-nice-subarray/?envType=daily-question&envId=2025-03-18

class Solution(object):
    def longestNiceSubarray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        left, right = 0, 0
        uniquebits=0
        ans=0
        while(right<len(nums)):
            while(uniquebits&nums[right] != 0):  #ensure only uniquebits inside window 
                uniquebits=uniquebits^nums[left] #remove bits of leftmost element of the window
                left=left+1
            uniquebits=uniquebits | nums[right] #add bits of rightmost element 
            ans=max(ans,right-left+1)
            right=right+1
        return ans
