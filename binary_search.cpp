#include<iostream>
#include<vector>
using namespace std;
// Function to find the index of the largest element <= k
int findFloor(vector<int>& arr, int k) {
        int left=0;
        int right=arr.size()-1;
        if(arr[0]>k) return -1;
        int lb;
        while(left<=right){
            int mid=(left+right)>>1;
            if(arr[mid]>k) right=mid-1;
            else {
                lb=mid; // <-------
                left=mid+1;
            }
        }
        return lb;
    }
/*
Given a sorted array of distinct integers and a target value, return the index if the target is found. 
If not, return the index where it would be if it were inserted in order.
---> implement lower bound 
Input: nums = [1,3,5,6], target = 2
Output: 1
-------
Find first and last occurence of x in a sorted array 
-
If an element x is present >=1 times in an array,
floor(x) will give the first occurence of x in the array 
ceil(x) will give the last occurence of x in the array 
--
Number of occurences of x = ceil(x) - floor(x)  [Assuming x is there ]
*/
// Function to find the index of the smallest element >= k
int findCeilIndex(const vector<int>& arr, int k) {
    int low = 0, high = arr.size() - 1;
    int ceilIndex = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (arr[mid] >= k) {
            ceilIndex = mid;  // <-----
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ceilIndex; 
}
/*
Search in a rotated array with DISTINCT values 
Input: nums = [4,5,6,7,0,1,2], target = 0  
Output: 4
*/
/*
CONCEPT ==>
For any given index x, either 0 to x  OR  x+1 to end is sorted  FOR SURE 
*/
int search(vector<int>& arr, int target) {
        int left=0;
        int right=arr.size()-1;
        while(left<=right)
        {
            int mid=(left+right)/2;
            if(arr[mid]==target) return mid;
            // for any given index either the left is sorted or the right is sorted
            else if(arr[left] <= arr[mid]) // Left of mid is sorted 
            {
                //arr[left]----target-----arr[mid]
                if(arr[left]<=target && target<=arr[mid]) right=mid-1;
                else left=mid+1;
            }
            else // right of mid is sorted 
            {
                //                        arr[mid]-----target---------arr[right]
                if(arr[mid]<=target && target<=arr[right]) left=mid+1;
                else right=mid-1;
            }
        }
        return -1;
    }
/*
[1,0,1,1,1]
How will you do it for sorted array WITH DUPLICATES ?     <------ IMP 
here arr[left]=arr[mid]=arr[right]
*/
/*
solution --->

            else if(arr[mid]==arr[left] && arr[mid]==arr[right])  <----- check 
            {
               left++ ;
               right-- ;
            }
*/
/*
Input: arr = [5, 1, 2, 3, 4]
Output: 1
Explanation: The given array is 5 1 2 3 4. 
The original sorted array is 1 2 3 4 5. We can see that the array was rotated 1 times to the right.
How many times was the array shifted to the right? 
*/
int findKRotation(vector<int> &arr) {
       int left=0;
        int right=arr.size()-1;
        int minn=INT_MAX;
        int ans=0;  // ---------> 
        while(left<=right)
        {
            int mid=(left+right)/2;
            if(arr[left] <= arr[mid]) // Left of mid is sorted 
            {
                if(arr[left]<minn) {
                    minn=arr[left];
                    ans=left;
                }
                left=mid+1;
            }
            else                        // right of mid is sorted 
            {
                if(arr[mid]<minn) {
                    minn=arr[mid];
                    ans=mid;
                }
                right=mid-1;
            }
        }
        return ans;
    }
/*
You are given a sorted array consisting of only integers where every element appears exactly twice,
 except for one element which appears exactly once.
Return the single element that appears only once.
Your solution must run in O(log n) time and O(1) space.

1 1 4 4 5 5 6 6 8 9 9 
0 1 2 3 4 5 6 7 8 9 10  // ----> indexes
1 1 4 4 5 5 6 6 8 9 9
<-----L------->   <-R->
In Part L, an odd index will have its repeat on the left side 
In Part R, an odd index will have its repeat on the right side 
And Viceversa 
In Part L, an even index will have its repeat on the right side 
and ....
---------------------------
*/
int singleNonDuplicate(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        int left=0;
        int right=nums.size()-1;
        while(left<=right){
            int mid=(left+right)/2 ;
            if(mid==0){
                if(nums[mid]!=nums[mid+1]) return nums[mid];
                else left=mid+1;
            }
            else if(mid==nums.size()-1){
                if(nums[mid]!=nums[mid-1]) return nums[mid];
                else right=mid-1;
            }
            else if(nums[mid]!=nums[mid-1] && nums[mid]!=nums[mid+1]) return nums[mid];
            else if(mid%2 == 1)
            {
                if(nums[mid]==nums[mid-1])  left=mid+1; 
                else right=mid-1;
            }
            else
            {
                if(nums[mid]==nums[mid+1]) left=mid+1;
                else right=mid-1;
            }
        }
        return 9;
    }
/*
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
*/

int findPeakElement(vector<int>& nums) {
        int left=0;
        if(nums.size()==1) return 0;
        int right=nums.size()-1;
        while(left<=right)  
        {
            int mid=(left+right)/2;
            //-----OBVIOUS-----------------------------------------
            if(mid==0 && nums[mid]>nums[mid+1]) return mid;
            if(mid==nums.size()-1 && nums[mid-1]<nums[mid]) return mid;
            if(mid>0 && mid<nums.size()-1 && nums[mid]>nums[mid-1] && nums[mid]>nums[mid+1]) return mid;
           //----OBVIOUS-------------------------------------------
           if(mid-1>=0 && nums[mid]>nums[mid-1]) left=mid; // choosing the greater element 
           else right=mid-1;
        }   
        return 29834;       
    }


