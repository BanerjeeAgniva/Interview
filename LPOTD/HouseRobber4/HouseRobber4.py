# https://leetcode.com/problems/house-robber-iv/description/?envType=daily-question&envId=2025-03-15
class Solution(object):
    def minCapability(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        """
        Observation --> its not necessary to rob more than k hourses 
        Brute force --> 2^n 
        """
        """
        map={}
        def backtrack(i,k):
         if(i>=len(nums)): 
            if (k==0): return 0
            else : return float('inf') # never reached 
         if ((i,k) in map): return map[(i,k)]
         pos1=max(nums[i],backtrack(i+2,k-1)) #possibility1
         pos2=backtrack(i+1,k) #possibility2
         map[(i,k)]=min(pos1,pos2)
         return map[(i,k)]
        return backtrack(0,k)
        """
        def is_valid(capability): #calculates number of houses with money atMOST capability 
          count=0             #taking care of other conditions
          i=0
          while (i < len(nums)):
           if(nums[i] <= capability): 
            count+=1
            i+=2
           else:
            i+=1 
          return count>=k

        l,r=min(nums),max(nums)
        ans=0
        # we are searching for the minimum out of all the MAX monies
        while(l<=r):
            money = (l+r)>>1
            if(is_valid(money)):
                ans=money 
                r=money-1 #look for a lesser minimum
            else:
                l=money+1
        return ans                

         

