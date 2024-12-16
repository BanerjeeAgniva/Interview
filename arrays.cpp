#include <iostream>
#include<vector>
using namespace std;
// Given an array nums, return true if the array was originally sorted in
// non-decreasing order, then rotated some number of positions (including zero).
// Otherwise, return false. There may be duplicates in the original array. Note:
// An array A rotated by x positions results in an array B of the same length
// such that A[i] == B[(i+x) % A.length], where % is the modulo operation.
bool check(vector<int> &a) {
  int n = a.size();
  int check = 0;
  for (int i = 0; i < n; i++)
    if (a[i] > a[(i + 1) % n])
      check++;
  return check <= 1;
  // 1 1 1
  // 1 2 3 4 5
  // 5 1 2 3 4
  // 4 5 1 2 3
  // 3 4 5 1 2
  // 2 3 4 5 1
  // 2 2 3 4 5 7 8 9 1 1 2 2
  // 10 1 4 6 7 8 9  --> passes
  // 9  1 4 6 7 8 10  ---> does not pass
}
//Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.
void rotate(vector<int> &nums, int k) {
  int n = nums.size();
  k = k % n;
  // 1 2 3   4 5 6 7
  // 7 6 5   4 3 2 1
  // 5 6 7   1 2 3 4
  reverse(nums.begin(), nums.end());
  reverse(nums.begin(), nums.begin() + k);
  reverse(nums.begin() + k, nums.end());
}
//Given an array nums containing n distinct numbers in the range [0, n], return the only number in the 
//range that is missing from the array.
// answer ---> summation(1 to n) - sum(array)
//--------------
//Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
// answer ---> a^a=0 0^b=b 
//--------------
// Longest Subarray with sum K 
/*
Input: arr[] = [10, 5, 2, 7, 1, 9], k = 15
Output: 4
Explanation: The subarray [5, 2, 7, 1] has a sum of 15 and length 4.
//----
Input: arr[] = [1, -1, 5, -2, 3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] has a sum of 3 and a length 4.
*/
    int lenOfLongestSubarr(vector<int>& A, int K) {
        unordered_map<int,int> m;
		int sum=0;
		int maxlen=0;
		m[0]=-1;
		for(int i=0;i<A.size();i++){
            sum+=A[i];
			if(m.count(sum)==0) m[sum]=i;
			// There is a (sum-K) amount which I can remove
			// I also have the first index where I have accumulated (sum-K)
			// at sum - (sum-K) = K  ==> curr index - m[sum-K]
            if(m.count(sum-K)!=0) maxlen=max(maxlen,i-m[sum-K]);
	    }
		return maxlen;
    }
//------
// Sort colours 
// Input: nums = [2,0,2,1,1,0]
// Output: [0,0,1,1,2,2]
void sortColors(vector<int>& nums) {
        int point0=0; // left to this pointer all are 0s
        int point2=nums.size()-1; //right to this pointer all are 1s 
        int i=0;
        while(i<point2){   //  ----------> IMP ---> when i reaches point2 it means left side is 00000011111 and right side is 22222
            if(nums[i]==2){
                swap(nums[i],nums[point2]);
                point2-- ;
            }
            else if(nums[i]==0){
                swap(nums[i],nums[point0]);
                point0++ ;
                i++ ;
            }
            else i++ ;
        }
    }

// Input: nums = [-1,0,1,2,-1,-4]  --> sort --> [-4,-1,-1,0,1,2]
// Output: [[-1,-1,2],[-1,0,1]]

vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(int i=0;i<nums.size()-2;i++)
        {
            if(i!=0 && nums[i]==nums[i-1]) continue; // avoid duplicates 
            int left=i+1;
            int right=nums.size()-1;
            while(left<right)
            {
                if(nums[i]+nums[left]+nums[right]==0){
                    ans.push_back({nums[i],nums[left],nums[right]});
                    left++ ; right-- ;
                    while(left<right && nums[left]==nums[left-1]){  // avoid duplicates 
                        left++ ;
                    }
                    while(right>left && nums[right]==nums[right+1]){  //avoid duplicates 
                        right--;
                    }
                }
                else if(nums[i]+nums[left]+nums[right] < 0) left++ ;
                else right-- ;
            }
        }
        return ans;
    }

//MAJORITY ELEMENT 
// Input:
// nums = [4, 4, 4, 5, 6, 4, 5, 6, 6, 6]
// Output:
// [4, 6]
// Explanation:
// The size of the array n = 10. Elements that appear strictly more than ⌊10/3⌋ = 3 times are 4 (appears 4 times) and 6 (appears 4 times).


//CONCEPT ====>
/*

For an array of length n:

There can be AT MOST 1 majority element which is STRICTLY more than ⌊n/2⌋ times.
There can be at most 2 majority elements which are more than ⌊n/3⌋ times.
There can be at most 3 majority elements which are more than ⌊n/4⌋ times.
There cab be AT MOST x majority elements which are more than ⌊n/(x+1)⌋ times

There are 2 winners this case winner1 and winner2 
count1 count2
*) if nums[i] is winner1 increase count1 BUT DONT DECREASE count2 
*) .......................winner2....................count2................................
*) if count1 is 0 and nums[i] is not winner1 nor winner2  ----> make winner1 nums[i]
*) if count2 is 0 ............................................................................... ---> make winner2 nums[i]
*) if count1>0 and count2>0  but nums[i] is not winner1 nor winner2 ----> decrease both the counts

*/

vector<int> majorityElement(vector<int>& nums) {
        int winner1=nums[0];
        int winner2=nums[nums.size()-1];
        int count1=1; int count2=1;
        int n=nums.size();
        int minfreq=n/3;
        vector<int> ans;
        for(int i=1;i<n-1;i++)
        {
            if(nums[i]==winner1) count1++ ;
            else if(nums[i]==winner2) count2++ ;
            else if(nums[i]!=winner1 &&  nums[i]!=winner2 && count1==0 )  //winner1 is unallocated 
            {
                winner1=nums[i]; count1=1;
            }
            else if(nums[i]!=winner1 &&  nums[i]!=winner2 && count2==0)  //winner2 is unallocated 
            {
                winner2=nums[i]; count2=1;
            }
            else
            {
                count1-- ; count2-- ;
            }
        }
        count1=0;count2=0;
        for(int i=0;i<n;i++) 
        {
            if(nums[i]==winner1) count1++ ;
            if(nums[i]==winner2) count2++ ;
        }
        if(count1>minfreq) ans.push_back(winner1);
        if(count2>minfreq && winner1!=winner2 ) ans.push_back(winner2);  //there can be atmost 2, might be there is only one 
        return ans;            
    }

// MAXIMUM SUBARRAY --> Kadane's algprithm 
// Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
// Output: 6
// Explanation: The subarray [4,-1,2,1] has the largest sum 6.
 int maxSubArray(vector<int>& nums) {
        int ans=INT_MIN;
        int currsum=0;
        for(int i=0;i<nums.size();i++)
        {
            currsum+=nums[i];
            ans=max(ans,currsum);
            if(currsum<0) currsum=0;
        }
        return ans;
    }

int main(){
    vector<int> v={1,0,1,0,2,0,1,2,1,0};
    sortColors(v);
    for(int i=0;i<v.size();i++) cout<<v[i]<<" ";
}