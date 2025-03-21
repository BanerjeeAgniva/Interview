# https://leetcode.com/problems/divide-array-into-equal-pairs/description/?envType=daily-question&envId=2025-03-17

class Solution(object):
    def divideArray(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        sett= set()
        for num in nums: 
            if num in sett : 
                sett.remove(num)
            else :
                sett.add(num)
        return len(sett)==0

"""
XOR doesnt work because --> 1^2^4^7 = 0
"""
