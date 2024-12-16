#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
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
// Given an integer array nums, rotate the array to the right by k steps, where
// k is non-negative.
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
// Given an array nums containing n distinct numbers in the range [0, n], return
// the only number in the range that is missing from the array.
//  answer ---> summation(1 to n) - sum(array)
//--------------
// Given a non-empty array of integers nums, every element appears twice except
// for one. Find that single one.
//  answer ---> a^a=0 0^b=b
//--------------
//  Longest Subarray with sum K
/*
Input: arr[] = [10, 5, 2, 7, 1, 9], k = 15
Output: 4
Explanation: The subarray [5, 2, 7, 1] has a sum of 15 and length 4.
//----
Input: arr[] = [1, -1, 5, -2, 3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] has a sum of 3 and a length 4.
*/
int lenOfLongestSubarr(vector<int> &A, int K) {
  unordered_map<int, int> m;
  int sum = 0;
  int maxlen = 0;
  m[0] = -1; //  -----> INDEX
  for (int i = 0; i < A.size(); i++) {
    sum += A[i];
    if (m.count(sum) == 0)
      m[sum] = i;
    // There is a (sum-K) amount which I can remove
    // I also have the first index where I have accumulated (sum-K)
    // at sum - (sum-K) = K  ==> curr index - m[sum-K]
    if (m.count(sum - K) != 0)
      maxlen = max(maxlen, i - m[sum - K]);
  }
  return maxlen;
}
// ----
// Number of Subarrays with Sum K
// Input: nums = [1,1,1], k = 2
// Output: 2
int subarraySum(vector<int> &nums, int k) {
  unordered_map<int, int> m;
  m[0] = 1; // Number of ways
  int currsum = 0;
  int ans = 0;
  for (int i = 0; i < nums.size(); i++) {
    currsum += nums[i];
    int requiredsum = currsum - k;
    if (m.find(requiredsum) !=
        m.end())             // There is a (sum-K) amount which I can remove
      ans += m[requiredsum]; // add the number of ways you can remove (sum-K)
    m[currsum]++;
  }
  return ans;
}
//-------- MAXIMUM PRODUCT SUBARRAY ----//
/*
[-1,-2,-9,-6] ---> 54
[-3,0,1,-2]  ---> 1
[-2,3,-4]  ---> 3
*/
int maxProduct(vector<int> &nums) {
  int currmaxsub = 1;
  int currminsub = 1;
  int ans = INT_MIN;
  for (int i = 0; i < nums.size(); i++) {
    int temp = currminsub;
    currminsub = min({nums[i], temp * nums[i], currmaxsub * nums[i]});
    currmaxsub = max({nums[i], temp * nums[i], currmaxsub * nums[i]});
    ans = max(ans, currmaxsub);
  }
  return ans;
}
//------
// Sort colours
// Input: nums = [2,0,2,1,1,0]
// Output: [0,0,1,1,2,2]
void sortColors(vector<int> &nums) {
  int point0 = 0;               // left to this pointer all are 0s
  int point2 = nums.size() - 1; // right to this pointer all are 1s
  int i = 0;
  while (i < point2) { //  ----------> IMP ---> when i reaches point2 it means
                       //  left side is 00000011111 and right side is 22222
    if (nums[i] == 2) {
      swap(nums[i], nums[point2]);
      point2--;
    } else if (nums[i] == 0) {
      swap(nums[i], nums[point0]);
      point0++;
      i++;
    } else
      i++;
  }
}

// Input: nums = [-1,0,1,2,-1,-4]  --> sort --> [-4,-1,-1,0,1,2]
// Output: [[-1,-1,2],[-1,0,1]]

vector<vector<int>> threeSum(vector<int> &nums) {
  sort(nums.begin(), nums.end());
  vector<vector<int>> ans;
  for (int i = 0; i < nums.size() - 2; i++) {
    if (i != 0 && nums[i] == nums[i - 1])
      continue; // avoid duplicates
    int left = i + 1;
    int right = nums.size() - 1;
    while (left < right) {
      if (nums[i] + nums[left] + nums[right] == 0) {
        ans.push_back({nums[i], nums[left], nums[right]});
        left++;
        right--;
        while (left < right &&
               nums[left] == nums[left - 1]) { // avoid duplicates
          left++;
        }
        while (right > left &&
               nums[right] == nums[right + 1]) { // avoid duplicates
          right--;
        }
      } else if (nums[i] + nums[left] + nums[right] < 0)
        left++;
      else
        right--;
    }
  }
  return ans;
}

// MAJORITY ELEMENT
//  Input:
//  nums = [4, 4, 4, 5, 6, 4, 5, 6, 6, 6]
//  Output:
//  [4, 6]
//  Explanation:
//  The size of the array n = 10. Elements that appear strictly more than ⌊10/3⌋
//  = 3 times are 4 (appears 4 times) and 6 (appears 4 times).

// CONCEPT ====>
/*

For an array of length n:

There can be AT MOST 1 majority element which is STRICTLY more than ⌊n/2⌋ times.
There can be at most 2 majority elements which are more than ⌊n/3⌋ times.
There can be at most 3 majority elements which are more than ⌊n/4⌋ times.
There cab be AT MOST x majority elements which are more than ⌊n/(x+1)⌋ times

There are 2 winners this case winner1 and winner2
count1 count2
*) if nums[i] is winner1 increase count1 BUT DONT DECREASE count2
*)
.......................winner2....................count2................................
*) if count1 is 0 and nums[i] is not winner1 nor winner2  ----> make winner1
nums[i]
*) if count2 is 0
...............................................................................
---> make winner2 nums[i]
*) if count1>0 and count2>0  but nums[i] is not winner1 nor winner2 ---->
decrease both the counts

*/

vector<int> majorityElement(vector<int> &nums) {
  int winner1 = nums[0];
  int winner2 = nums[nums.size() - 1];
  int count1 = 1;
  int count2 = 1;
  int n = nums.size();
  int minfreq = n / 3;
  vector<int> ans;
  for (int i = 1; i < n - 1; i++) {
    if (nums[i] == winner1)
      count1++;
    else if (nums[i] == winner2)
      count2++;
    else if (nums[i] != winner1 && nums[i] != winner2 &&
             count1 == 0) // winner1 is unallocated
    {
      winner1 = nums[i];
      count1 = 1;
    } else if (nums[i] != winner1 && nums[i] != winner2 &&
               count2 == 0) // winner2 is unallocated
    {
      winner2 = nums[i];
      count2 = 1;
    } else {
      count1--;
      count2--;
    }
  }
  count1 = 0;
  count2 = 0;
  for (int i = 0; i < n; i++) {
    if (nums[i] == winner1)
      count1++;
    if (nums[i] == winner2)
      count2++;
  }
  if (count1 > minfreq)
    ans.push_back(winner1);
  if (count2 > minfreq && winner1 != winner2)
    ans.push_back(winner2); // there can be atmost 2, might be there is only one
  return ans;
}

// MAXIMUM SUBARRAY --> Kadane's algorithm
// Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
// Output: 6
// Explanation: The subarray [4,-1,2,1] has the largest sum 6.
int maxSubArray(vector<int> &nums) {
  int ans = INT_MIN;
  int currsum = 0;
  for (int i = 0; i < nums.size(); i++) {
    currsum += nums[i];
    ans = max(ans, currsum);
    if (currsum < 0)
      currsum = 0;
  }
  return ans;
}

// Given an array arr[], with 0-based indexing, select any two indexes, i and j
// such that i < j. From the subarray arr[i...j], select the smallest and second
// smallest numbers and add them, you will get the score for that subarray.
// Return the maximum possible score across all the subarrays of array arr[].
// Input : arr[] = [4, 3, 1, 5, 6]
// Output : 11
// Explanation : Subarrays with smallest and second smallest are:- [4, 3]
// smallest = 3,second smallest = 4 [4, 3, 1] smallest = 1, second smallest = 3
// [4, 3, 1, 5] smallest = 1, second smallest = 3
// [4, 3, 1, 5, 6] smallest = 1, second smallest = 3
// [3, 1] smallest = 1, second smallest = 3
// [3, 1, 5] smallest = 1, second smallest = 3
// [3, 1, 5, 6] smallest = 1, second smallest = 3
// [1, 5] smallest = 1, second smallest = 5
// [1, 5, 6] smallest = 1, second smallest = 5
// [5, 6] smallest = 5, second smallest = 6
// Maximum sum among all above choices is, 5 + 6 = 11.
int pairWithMaxSum(int arr[], int N) {
  if (N < 2)
    return -1;
  int res = arr[0] + arr[1];
  for (int i = 1; i < N - 1; i++)
    res = max(res, arr[i] + arr[i + 1]);
  return res;
}
/*
LOGIC ==>
For a subarray with 2 elements, 1st and 2nd smallest elements are those 2
elements. Now, x and y are present in some subarray such that they are the
endpoints. Now, x, y must be the smallest 2 elements of that subarray.

If there are other elements Z1 , Z2, ……., ZK  between x and y, they are greater
than or equal to x and y, Case1 : If there is one element z between x and y,
then the smaller subarray with the elements max(x,y) and z , should be the
answer, because max(x,y) + z >= x + y Case2: If there are more than one elements
between x and y, then the subarray within x and y will have all consecutive
elements  (Zi + Zi+1) >= (x+y),  so (x,y) pair can’t be the answer. So, by
contradictions, x and y must be consecutive elements in the array.
*/
//------------
// Next permutation
void nextPermutation(vector<int> &nums) {
  int n = nums.size();
  int first_smaller =
      nums[nums.size() - 1]; // step1 --> find first decreasing ele from right
                             // to left (say index k)
  int small;
  int i;
  for (i = nums.size() - 1; i >= 0; i--) {
    if (nums[i] >= first_smaller)
      first_smaller = nums[i];
    else {
      first_smaller = nums[i];
      break;
    }
  }
  if (i == -1) {
    reverse(nums.begin(), nums.end());
    return;
  }
  int j;
  for (j = i + 1; j < nums.size(); j++)
    if (nums[j] > first_smaller || j == n - 1)
      break; // step2 --> find first element greater than arr[k] to the right of
             // arr[k]

  swap(nums[i], nums[j]); // step3  ----> swap these 2 elements
  reverse(nums.begin() + i + 1,
          nums.end()); // step4 ---> reverse the array k+1 to end
}
/*
1) traverse from right to left look for first decreasing eleemtn it is at index
k 2) now move right from k+1 to end of nums search for eleemtn JUST GREATER than
nums[k] 3)swap these 2 elements 4) reverse array from k+1 to end

1 4 3 2 5 7 8 9 6 ----->
1 4 3 2 5 7 9 6 8 (required)

1 4 3 2 5 7  8  9   6 ----->
1 4 3 2 5 7 [8] 9   6 ----->
1 4 3 2 5 7 [8] {9} 6 ------->
SWAP --->
1 4 3 2 5 7 9 8 6 ------>
1 4 3 2 5 7 9 [ 8 6 ] reverse --->
 1 4 3 2 5 7 9 6 8
*/
//--------->>>>LONGEST CONSECUTIVE SEQUENCE<<<-----> unordered set
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
// Therefore its length is 4.
int longestConsecutive(vector<int> &nums) {
  unordered_set<int> numSet(nums.begin(), nums.end()); // Convert vector to set
  int longest = 0;
  for (int num : numSet) {
    // Check if it's the start of a sequence
    if (numSet.find(num - 1) == numSet.end()) {
      int currentNum = num;
      int currentStreak = 1;
      // Check the length of the sequence starting with num
      while (numSet.find(currentNum + 1) != numSet.end()) {
        currentNum++;
        currentStreak++;
      }
      longest = max(longest, currentStreak);
    }
  }

  return longest;
}

/*
MATRIX ZEROES
Input Matrix       --->       Required Output Matrix
1  1  1                        1  0  1
1  0  1                        0  0  0
1  1  1                        1  0  1
*/

void setZeroes(vector<vector<int>> &matrix) {
  bool firstRow = false;
  bool firstCol = false;

  for (int i = 0; i < matrix.size(); i++) {
    if (matrix[i][0] == 0)
      firstCol = true;
  }

  for (int i = 0; i < matrix[0].size(); i++) {
    if (matrix[0][i] == 0)
      firstRow = true;
  }

  for (int i = 1; i < matrix.size(); i++) {
    for (int j = 1; j < matrix[0].size(); j++) {
      if (matrix[i][j] == 0) {
        matrix[0][j] = 0;
        matrix[i][0] = 0;
      }
    }
  }

  for (int i = 1; i < matrix.size(); i++) {
    if (matrix[i][0] == 0) {
      for (int j = 1; j < matrix[0].size(); j++)
        matrix[i][j] = 0;
    }
  }

  for (int j = 1; j < matrix[0].size(); j++) {
    if (matrix[0][j] == 0) {
      for (int i = 1; i < matrix.size(); i++)
        matrix[i][j] = 0;
    }
  }

  if (firstCol) {
    for (int i = 0; i < matrix.size(); i++)
      matrix[i][0] = 0;
  }
  if (firstRow) {
    for (int j = 0; j < matrix[0].size(); j++)
      matrix[0][j] = 0;
  }
}

/*
rotate matrix 90 degrees clockwise
Input Matrix       --->       Required Output Matrix
1  2  3                        7  4  1
4  5  6                        8  5  2
7  8  9                        9  6  3
*/
void rotate(vector<vector<int>> &matrix) {
  int n = matrix.size();
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
      swap(matrix[i][j], matrix[j][i]);

  for (int i = 0; i < n; i++)
    reverse(matrix[i].begin(), matrix[i].end());
}

// Number of Subarrays with given XOR
/*
A = [4, 2, 2, 6, 4]
B = 6
The subarrays having XOR of their elements as 6 are:
 [4, 2], [4, 2, 2, 6, 4], [2, 2, 6], [6]
 */
int givenXOR(vector<int> &A, int B) {
  int xorr = 0;
  int ans = 0;
  unordered_map<int, int> m;
  m[0] = 1; // picking no elements from left
  for (int i = 0; i < A.size(); i++) {
    xorr = xorr ^ A[i];
    int required = xorr ^ B;
    ans += m[required];
    m[xorr]++;
  }
  return ans;
}
/*
LOGIC ===>
suppose the xor from 0 to ith element is xorr
so a0 ^ a1 ^ a2 ^ a3 ......... ^ aj ^ aj+1 ...... ^ ai = xorr  ----> (I)
Suppose j to i is our target where xor is B
and aj ^ aj+1 ^ ...., ^ ai = B  ------------------------------------> (II)
so xorr ^ B becomes --> a0 ^ a1 ^ a2 ^ .... aj-1  = (xor till index i) ^
(required xorr) = xor part to be removed which is the xor of the required
subarray we need to REMOVE fro  0 to i part so that we only get j to ith index
as the subarray

(xor till index i ^ B) this is the required see how many times this has occured
to the left
*/
//-----------
/*
MERGE INTERVALS
Input Intervals:
1 ----> 3
    2 ------> 6
                 8 ----> 10
                             15 ----> 18

Merged Intervals:
1 --------------> 6
                     8 ----> 10
                                  15 ----> 18
*/
//-------
vector<vector<int>> merge(vector<vector<int>> &intervals) {
  sort(intervals.begin(), intervals.end());
  int prevstart = intervals[0][0];
  int prevend = intervals[0][1];
  vector<vector<int>> ans;
  for (int i = 1; i < intervals.size(); i++) {
    int currstart = intervals[i][0];
    int currend = intervals[i][1];
    if (currstart > prevend) {
      ans.push_back({prevstart, prevend});
      prevstart = intervals[i][0];
      prevend = intervals[i][1];
      continue;
    }
    prevend = max(prevend, currend);
  }
  ans.push_back({prevstart, prevend});
  return ans;
}
//---------------------
/*
Given an unsorted array arr of positive integers. One number a from the set [1,
2,....,n] is missing and one number b occurs twice in the array. Find numbers a
and b.
*/
/*
Consider
4 3 6 2 1 1         Missing number -> 5  (X)  Repeating -> 1 (Y)
1 2 3 4 5 6
-------------------  Minus
1 - 5   = Y - X = Sum(array) - Sum(first n natural numbers)
................................ eq 1
---------------------

4^2    3^2    6^2    2^2    1^2    1^2
1^2    2^2    3^2    4^2    5^2    6^2
-------------------------------------- Minus
1^2 - 5^2  =   Y^2 - X^2 = (Y+X)(Y-X) =
Sumofsquareof(array)-Sumofsquaresof(first_n_natural_numbers)
Y-X =
........................................................................................eq
2
---------------------------------------------------------------------------
*/
int main() {
  vector<int> v = {1, 0, 1, 0, 2, 0, 1, 2, 1, 0};
  sortColors(v);
  for (int i = 0; i < v.size(); i++)
    cout << v[i] << " ";
}