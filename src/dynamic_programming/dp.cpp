	#include<iostream> 
    #include<vector>
    using namespace std;
    int mod=1000000007;
    /*
Input: arr[] = [5, 2, 3, 10, 6, 8], target = 10
Output: 3
Explanation: The subsets {5, 2, 3}, {2, 8}, and {10} sum up to the target 10.

    */
	int func(int index,int sum,vector<int>& nums,vector<vector<int>>& dp)
	{
	    if(index<0) return sum==0;
	    if(dp[index][sum]!=-1) return dp[index][sum];
	    int ans=func(index-1,sum,nums,dp)%mod; // not take 
	    int remainingsum=sum-nums[index];
	    if(remainingsum>=0) ans=(ans+func(index-1,remainingsum,nums,dp)%mod)%mod; //take 
	    return dp[index][sum]=ans;
	}
	int perfectSum(int arr[], int n, int sum)
	{
        vector<vector<int>> dp(n, vector<int> (sum+1 , -1));
        vector<int> nums;
        for(int i=0;i<n;i++) nums.push_back(arr[i]);
        dp[n-1][sum]=func(n-1,sum,nums,dp);
        return  dp[n-1][sum];
	}
