#include <iostream>
#include <vector>
using namespace std;
// Function to find the index of the largest element <= k
int findFloor(vector<int> &arr, int k) { // lowerbound
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
int findCeilIndex(const vector<int> &arr, int k) { // upperbound
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
if you select any indice --> one of the sides will be sorted for sure
your question essentially becomes what is the indice of the first element of the
unrotated array so your question essentually becomes what is the indice of the
minimum element of the array
*/
//---
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
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
  int n1 = nums1.size();
  int n2 = nums2.size();
  if (n1 > n2)
    return findMedianSortedArrays(nums2, nums1);
  int cut1, cut2, l1, l2, r1, r2, lb, rb;
  int lhl = (n1 + n2 + 1) /
            2; // so that lefthalf has >= no of elements than right half
  int tot = (n1 + n2);
  lb = 0;
  rb = n1;
  while (lb <= rb) {
    cut1 = (lb + rb) / 2;
    cut2 = lhl - cut1;
    if (cut1 != 0)
      l1 = nums1[cut1 - 1];
    else
      l1 = INT_MIN;
    if (cut2 != 0)
      l2 = nums2[cut2 - 1];
    else
      l2 = INT_MIN;
    if (cut1 != n1)
      r1 = nums1[cut1];
    else
      r1 = INT_MAX;
    if (cut2 != n2)
      r2 = nums2[cut2];
    else
      r2 = INT_MAX;

    if (l1 <= r2 && l2 <= r1) {
      if (tot % 2 == 1)
        return max(l1, l2);
      else
        return (max(l1, l2) + min(r1, r2)) / 2.0;
    }
    if (l1 > r2)
      rb = cut1 - 1; // push cut1 towards left so that l1 decreases
    else if (l2 > r1)
      lb = cut1 + 1; //  push cut1 towards right so that r1 increases
  }
  return -2;
}
/*
Given two sorted arrays a[] and b[] and an element k, the task is to find the
element that would be at the kth position of the combined sorted array.
*/
int kthElement(int k, vector<int> &arr1, vector<int> &arr2) {
  int n1 = arr1.size(); // 3
  int n2 = arr2.size(); // 4
  if (n1 > n2)
    return kthElement(k, arr2, arr1);
  int left = max(0, k - n2); // k=2
  int right = min(n1, k);
  while (left <= right) {
    int cut1 = (left + right) / 2;
    int cut2 = k - cut1;
    int l1 = (cut1 == 0) ? INT_MIN : arr1[cut1 - 1];
    int l2 = (cut2 == 0) ? INT_MIN : arr2[cut2 - 1];
    int r1 = (cut1 == n1) ? INT_MAX : arr1[cut1];
    int r2 = (cut2 == n2) ? INT_MAX : arr2[cut2];
    if (l1 <= r2 && l2 <= r1)
      return max(l1, l2);
    else if (l1 > r2)
      right = cut1 - 1;
    else
      left = cut1 + 1;
  }
  return -1;
}
/*
Row with max 1s

n*m matrix
{{0, 0, 0, 1},     start from pos=3
                                     pos=2
 {0, 0, 1, 1},     start from pos=2
                                     pos=1
 {0, 1, 1, 1},     start from pos=1
                                     pos=0
 {1, 1, 1, 1}}     start from pos=0
                                     j=-1 return

LOGIC---> Once you have found where the starting one of the previous row is, you
dont again have to start from the rightmost position to find the starting one of
the next row, you can learn from the previous result
*/
int rowWithMax1s(vector<vector<int>> arr, int n, int m) {
  int count = 0;
  int ans = 0;
  int point = m - 1;

  for (int i = 0; i < n; i++) {
    int j = point;
    while (j >= 0) {
      if (arr[i][j] == 1) {
        j--;
        ans = i;
      } else {
        point = j;
        break;
      }
    }
    if (j < 0)
      return i;
  }
  return (point == m - 1) ? -1 : ans;
}
//----------
// Search in a 2D Matrix --> int row= mid/n ; int col= mid%n ;
//----
/* =====================================
Write an efficient algorithm that searches for a value target in an m x n
integer matrix matrix. This matrix has the following properties: Integers in
each row are sorted in ascending from left to right. Integers in each column are
sorted in ascending from top to bottom. Input: matrix =
[[1,4,7,11,15]
 [2,5,8,12,19],
 [3,6,9,16,22],
 [10,13,14,17,24],
 [18,21,23,26,30]],
 target = 5
Output: true
*/
/*
LOGIC --> Start from top-right element because the elements downwards will be
strictly increasing and the elements to the left will be strictly decreasing
(15) If our target element (5) is lesser than our current elemnt(15) then move
left (col--) Target element (5) < current element(11)  move left col-- Target
element(5) < current element(7) move left col-- Target element(5) > current
element(4) move down row++ Target elemenmt==current element return true
======================================================= */
// Median in a row-wise sorted Matrix   <---- STANDARD QUESTION
/*
Input: mat = [[1, 3, 5], [2, 6, 9], [3, 6, 9]]
Output: 5
Explanation: Sorting matrix elements gives us {1,2,3,3,5,6,6,9,9}. Hence, 5 is
median.
*/
int ub(vector<int> &arr, int num) {
  int left = 0;
  int right = arr.size();
  while (left < right) {
    int mid = (left + right) / 2;
    if (arr[mid] <=
        num) { // -----> we want strictly upperbound smallest number > num
      left = mid + 1; // we dont want smallest number >= num
    } else {
      right = mid;
    }
  }
  return left; // Left is now the number of elements <= num
}
int blackbox(vector<vector<int>> &matrix, int num) {
  int sum = 0;
  for (int i = 0; i < matrix.size(); i++) {
    sum += ub(matrix[i], num);
  }
  return sum;
}
// The number of numbers which are <= median should be greater than half of the
// total number of elements
int median(vector<vector<int>> &matrix, int R, int C) {
  int target = (R * C) / 2;
  int left = INT_MAX;
  int right = INT_MIN;
  for (int i = 0; i < R; i++) {
    left = min(left, matrix[i][0]);
    right = max(right, matrix[i][C - 1]);
  }
  while (left <= right) {
    int mid = (left + right) / 2;
    int curr = blackbox(matrix, mid);
    if (curr > target)
      right = mid - 1;
    else
      left = mid + 1;
  }
  return left;
}