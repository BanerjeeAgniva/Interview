#include <iostream>
#include <vector>
using namespace std;
// Function to find the index of the largest element <= k
int findFloor(vector<int> &arr, int k) {
  int left = 0;
  int right = arr.size() - 1;
  if (arr[0] > k)
    return -1;
  int lb;
  while (left <= right) {
    int mid = (left + right) >> 1;
    if (arr[mid] > k)
      right = mid - 1;
    else {
      lb = mid; // <-------
      left = mid + 1;
    }
  }
  return lb;
}
/*
Given a sorted array of distinct integers and a target value, return the index
if the target is found. If not, return the index where it would be if it were
inserted in order.
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
int findCeilIndex(const vector<int> &arr, int k) {
  int low = 0, high = arr.size() - 1;
  int ceilIndex = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] >= k) {
      ceilIndex = mid; // <-----
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
int search(vector<int> &arr, int target) {
  int left = 0;
  int right = arr.size() - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (arr[mid] == target)
      return mid;
    // for any given index either the left is sorted or the right is sorted
    else if (arr[left] <= arr[mid]) // Left of mid is sorted
    {
      // arr[left]----target-----arr[mid]
      if (arr[left] <= target && target <= arr[mid])
        right = mid - 1;
      else
        left = mid + 1;
    } else // right of mid is sorted
    {
      //                        arr[mid]-----target---------arr[right]
      if (arr[mid] <= target && target <= arr[right])
        left = mid + 1;
      else
        right = mid - 1;
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
The original sorted array is 1 2 3 4 5. We can see that the array was rotated 1
times to the right. How many times was the array shifted to the right?
*/
int findKRotation(vector<int> &arr) {
  int left = 0;
  int right = arr.size() - 1;
  int minn = INT_MAX;
  int ans = 0; // --------->
  while (left <= right) {
    int mid = (left + right) / 2;
    if (arr[left] <= arr[mid]) // Left of mid is sorted
    {
      if (arr[left] < minn) {
        minn = arr[left];
        ans = left;
      }
      left = mid + 1;
    } else // right of mid is sorted
    {
      if (arr[mid] < minn) {
        minn = arr[mid];
        ans = mid;
      }
      right = mid - 1;
    }
  }
  return ans;
}
/*
You are given a sorted array consisting of only integers where every element
appears exactly twice, except for one element which appears exactly once. Return
the single element that appears only once. Your solution must run in O(log n)
time and O(1) space.

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
int singleNonDuplicate(vector<int> &nums) {
  if (nums.size() == 1)
    return nums[0];
  int left = 0;
  int right = nums.size() - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (mid == 0) {
      if (nums[mid] != nums[mid + 1])
        return nums[mid];
      else
        left = mid + 1;
    } else if (mid == nums.size() - 1) {
      if (nums[mid] != nums[mid - 1])
        return nums[mid];
      else
        right = mid - 1;
    } else if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1])
      return nums[mid];
    else if (mid % 2 == 1) {
      if (nums[mid] == nums[mid - 1])
        left = mid + 1;
      else
        right = mid - 1;
    } else {
      if (nums[mid] == nums[mid + 1])
        left = mid + 1;
      else
        right = mid - 1;
    }
  }
  return 9;
}
/*
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index
number 2.
*/

int findPeakElement(vector<int> &nums) {
  int left = 0;
  if (nums.size() == 1)
    return 0;
  int right = nums.size() - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    //-----OBVIOUS-----------------------------------------
    if (mid == 0 && nums[mid] > nums[mid + 1])
      return mid;
    if (mid == nums.size() - 1 && nums[mid - 1] < nums[mid])
      return mid;
    if (mid > 0 && mid < nums.size() - 1 && nums[mid] > nums[mid - 1] &&
        nums[mid] > nums[mid + 1])
      return mid;
    //----OBVIOUS-------------------------------------------
    if (mid - 1 >= 0 && nums[mid] > nums[mid - 1])
      left = mid; // choosing the greater element
    else
      right = mid - 1;
  }
  return 29834;
}

// sqrt using bs find nth root of m  ---> left=1 -> right=m
// smallest divisor
//  -----
/*
Minimize the Maximum Capacity

A conveyor belt has packages that must be shipped from one port to another
within d days. The ith package on the conveyor belt has a weight of weights[i].
Each day, we load the ship with packages on the conveyor belt (in the order
given by weights). We may not load more weight than the maximum weight capacity
of the ship. Return the least weight capacity of the ship that will result in
all the packages on the conveyor belt being shipped within d days.

Input: weights = [1,2,3,4,5,6,7,8,9,10] ---> order not changeable , d = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5
days like this: 1st day: 1, 2, 3, 4, 5 2nd day: 6, 7 3rd day: 8 4th day: 9 5th
day: 10

Note that the cargo must be shipped in the order given, so using a ship of
capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7),
(8), (9), (10) is not allowed.
*/
/*
You would need minimum max_weight as max(weights) and maximum will go up to
sum(weights)
*/
// ---------------------------
/*
1539. Kth Missing Positive Number

Given an array arr of positive integers sorted in a strictly increasing order,
and an integer k. Return the kth positive integer that is missing from this
array. Example 1:

Input: arr = [2,3,4,7,11], k = 5
Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...].
The 5th missing positive integer is 9.
*/

/*
2     3     4     7      11   ----> arr[ind]
1     2     3     4       5   ---->one-based indexing = zero-based indexing + 1
1     1     1     3       6   ---->number of missing numbers before the index

Number of missing numbers before index i = arr[i] - (i+1)
find mid such that missingnos = arr[mid]-(mid+1) = k <------- SOLUTION
if(missingnos<k) left=mid+1 ; else right=mid-1;
*/
//------
/*
aggressive cows
The problem is to place 𝐶 in N stalls (located at given positions along a
straight line) such that the minimum distance between any two cows is maximized.
The goal is to find this largest possible minimum distance between the cows. C=3
1 2 4 8 9
place at 1 2 4 ---> min_dist = 1 same for 1 2 8 || 1 2 9
place at 1 4 8 ----> min_dist=3  same for 1 4 9
place at 1 8 9 ---> min_distance=1
so max(min_distance)=3
*/
/*
binary search on minimum_distance from 1 to max=highest-low
*/
//-------------
/*
Book allocation problem // minimized largest sum of the split. // Painters
Partition Problem

Given an array ‘arr’ of integer numbers, ‘arr[i]’ represents the number of pages
in the ‘i-th’ book. There are ‘m’ number of students, and the task is to
allocate all the books to the students. Allocate books in such a way that:
1. Each student gets at least one book.
2. Each book should be allocated to only one student.
3. Book allocation should be in a contiguous manner.
You have to allocate the book to ‘m’ students such that the maximum number of
pages assigned to a student is minimum. If the allocation of books is not
possible, return -1.

Example:
Input: ‘n’ = 4 ‘m’ = 2
‘arr’ = [12, 34, 67, 90]

Output: 113

Explanation: All possible ways to allocate the ‘4’ books to '2' students are:

12 | 34, 67, 90 - the sum of all the pages of books allocated to student 1 is
‘12’, and student two is ‘34+ 67+ 90 = 191’, so the maximum is ‘max(12, 191)=
191’. 12, 34 | 67, 90 - the sum of all the pages of books allocated to student 1
is ‘12+ 34 = 46’, and student two is ‘67+ 90 = 157’, so the maximum is ‘max(46,
157)= 157’. 12, 34, 67 | 90 - the sum of all the pages of books allocated to
student 1 is ‘12+ 34 +67 = 113’, and student two is ‘90’, so the maximum is
‘max(113, 90)= 113’.
*/
int check(int mid, vector<int> &arr, int m) // m is unused
{ // returns number of students who have been allocated "mid" number of pages at
  // max
  int pages = 0;
  int curr = 0;
  for (int i = 0; i < arr.size(); i++) {
    if (pages + arr[i] <= mid)
      pages += arr[i];
    else {
      curr++;
      pages = arr[i];
    }
  }
  if (pages > mid)
    curr++;
  return curr;
}
int findPages(vector<int> &arr, int n, int m) {
  if (m > n)
    return -1;
  int left = *max_element(arr.begin(), arr.end());
  int right = 0;
  for (int i = 0; i < arr.size(); i++)
    right += arr[i];
  int ans;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (check(mid, arr, m) < m)
      right = mid - 1;
    else {
      ans = left;
      left = mid + 1;
    }
  }
  return left;
}
//-----
