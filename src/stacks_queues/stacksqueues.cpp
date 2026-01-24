#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <algorithm> // for reversing string 
#include <unordered_map>
using namespace std;
/*
stack using array
*/
int top = -1;
int arr[1000];
int pop_stack() {
  if (top == -1)
    return -1;
  int x = arr[top];
  top--;
  return x;
}
void push_stack(int x) {
  top++;
  arr[top] = x;
}
//=======================>>
/*
queue using array
*/
int front = 0;
int rear = 0;
void push_queue(int x) {
  arr[rear] = x;
  rear++;
}
int pop_queue() {
  if (front == rear)
    return -1;
  int num = arr[front];
  front++;
  return num;
}
//=======================>>
/*
stack using queue

The element at the top of the stack should be present at the front of the queue
// NOT REAR SO how do you achieve this ?? suppose stakc empty push 3        3
queue --> 3 push 4                          queue   ----> 3 4  BUT you ideally
want 4 3 so that when you pop 4 gets popped LIFO so push the current element x
a b c d e x Now keep rotating   b c d e x a       c d e x a b      d e x a b c
e x a b c d     x a b c d e  (rotate for n times where n is no of elements
before you pushed x ) now when you pop you get x
*/
queue<int> stackq;
int func(string command) {
  int front = 0;
  int rear = 0;
  if (command == "push") {
    int x;
    cin >> x;
    int n = stackq.size();
    stackq.push(x);
    for (int i = 0; i < n; i++) {
      stackq.push(stackq.front());
      stackq.pop();
    }
    return 0;
  } else if (command == "pop") {
    int num = stackq.front();
    stackq.pop();
    return num;
  } else if (command == "top") {
    return stackq.front();
  } else if (command == "empty") {
    return stackq.empty();
  }
}
//===================================>>
stack<int> queues;
/*
queue using stack
if you hav a queue  Front  3 2 1   Rear
maintian the stack like
3 ] <---- bottom of stack
3 2  ] <---- bottom of stack
3 2 1  ] <---- bottom of stack

to do this every time there is a new element you have to dump all the elements
in the first stack into another and stack then enter the element x   so that its
something like x 1 2 3  ] <---- bottom of stack

and then dump all these elements into the original stack

3 2 1 x  ] <---- bottom of stack
*/
// ========> <===========================

/*
Stack using LinkedList

3 2 1 ]<-----BOTTOM OF STOCK
3->2->1 -> NULL
Insert 4
4 3 2 1 ]
4->3->2->1->NULL
*/
/*  <======================================>
Queue using LinkedList

keep two points rear and front
front 3 2 1 rear
f pointer at 3, another pointer at 1
*/
/*
Balanced Paranthesis -->ez
*/
/*
Min Stack ===>
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.

void push(int val) {
        if(st.size()==0)
            st.push({val,val});
        else{
            st.push({val, min(st.top().second,val)});
        }
    }
*/

// prefix, Infix, PostFix Conversion Problems

// Monotonic Stack ---> CONCEPT
/*
Next Greater Element
The next greater element of some element x in an array is the first greater
element that is to the right of x in the same array. You are given two distinct
0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2. For
each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and
determine the next greater element of nums2[j] in nums2. If there is no next
greater element, then the answer for this query is -1.


Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
nums2 -->
push 2      2]       as stack was empty  --->   m[2]=-1
4 encountered   is 4>=top_of_stack (2) yes? pop       4]             as stack
was empty before 4 was pushed  --->   m[4]=-1 3 encountered  is
3>=top_of_stack(4)  no?   push    3  4]          m[3] = top_of_stack before 3
was pushed  =  4 1 encountered 1   3   4] maintain monotically increasing stack
--->  1 2 4 if you push 3 into this then1  2 get popped out Final status -> 3 4

<====== ||  Next Greater Element 2 || ========>

Given a circular integer array nums (i.e., the next element of nums[nums.length
- 1] is nums[0]) return the next greater number for every element in nums.

The next greater number of a number x is the first greater number to its
traversing-order next in the array which means you could search circularly to
find its next greater number. If it doesn't exist, return -1 for this number.

Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2;
The number 2 can't find next greater number.
The second 1's next greater number needs to search circularly, which is also 2.

// =====

*/
/*
Example:
Input:
nums1 = [4, 5, 2, 25] (array where we find the next greater elements)
nums2 = [4, 25, 2] (subset of nums1 whose "next greater elements" are needed)

Expected Output:
For nums2: [5, -1, 25]

for 25 stack is empty so m(25)=-1 push 25]
for 2, there is an element in stack which is greater than 2 so m(2)=25  push  2
25] for 5, top of stack is not greater -> pop 25] -> is top of stack (25)
greater now? yes m(5)=25 push 5 25] for 4, top of stack is greater -> m(4)=5 ,
push ---> 4 5 25]
*/
vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {
  int nge[nums1.size()];
  stack<int> st;
  map<int, int> mp;
  for (int i = nums2.size() - 1; i >= 0; i--) {
    while (!st.empty() && st.top() <= nums2[i])
      st.pop(); // <= because strictly greater
    if (st.empty())
      mp[nums2[i]] = -1;
    else
      mp[nums2[i]] = st.top();
    st.push(nums2[i]);
  }
  vector<int> ans(nums1.size());
  for (int i = 0; i < nums1.size(); i++) {
    ans[i] = mp[nums1[i]];
  }
  return ans;
}
/*
for A[] = {5,7,1,2,6,0}:
So, the resultant array is {7,-1,2,6,-1,-1}.
Remember that we have considered the array to be non-circular.
For a circular array, the resultant array should be {7,-1,2,6,7,5}.
*/
vector<int> nextGreaterElements(vector<int> &nums) {
  int n = nums.size();
  vector<int> nge(n, -1);
  stack<int> st;
  for (int i = 2 * n - 1; i >= 0; i--) { // circular
    while (!st.empty() && st.top() <= nums[i % n]) {
      st.pop();
    }
    if (i < n) {
      if (!st.empty())
        nge[i] = st.top();
    }
    st.push(nums[i % n]);
  }
  return nge;
}
/*
5 7 1 2 6 0 5 7 1 2 6 0
0]
6]
2 6]
1 2 6]
7]
5 7]
answer to 0 becomes ---> 5   0 5 7]
answer to 6 becomes ----> 7  6 7]
*/

/*
monotically decreasing stack
*/
vector<int> prevSmaller(vector<int> &A) {
  vector<int> ans(A.size());
  stack<int> st;
  for (int i = 0; i < A.size(); i++) {
    while (!st.empty() && A[i] <= st.top()) {
      st.pop();
    }
    if (st.empty()) {
      ans[i] = -1;
    } else {
      ans[i] = st.top();
    }
    st.push(A[i]);
  }
  return ans;
}
/*

Trapping rainwater

Brute force --->

The trapped water level at every index  (trapped hote gele oke du dikei dhakka
khete hobe)  is to be the minimum(leftmaxheight_building ,
rightmaxheight_building) - current building

Optimized

Hash leftmax
Hash Rightmax


*/

int trap(vector<int> &height) {
  int leftmax = 0;
  int rightmax = 0;
  int left = 0;
  int right = height.size() - 1;
  int ans = 0;
  while (left <= right) {
    if (leftmax < rightmax) {
      ans += max(0, leftmax - height[left]);
      leftmax = max(leftmax, height[left]);
      left++;
    } else {
      ans += max(0, rightmax - height[right]);
      rightmax = max(rightmax, height[right]);
      right--;
    }
  }
  return ans;
}

/*
Sum of Subarray Minimums
Input: arr = [3,1,2,4]
Output: 17
Explanation:
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4],
[3,1,2,4]. Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1. Sum is 17. 3*1times +
1*6times + 2*2times + 4*1times = 17

3 1 2 4

what is the previous smaller number index of 1 ---> -1  so number of elements on
the left which are smaller than 1 (1 inclusive) 1-(-1) =2 what is the next
smaller number index of 1 ---> 4  so number of elements 4-1 = 3

so total subarrays = 2*3 = 6

1 4 6 7 3 7 8 1 is a better example
*/

vector<int> findnse(vector<int> &arr) {
  int n = arr.size();
  vector<int> nse(n);
  stack<int> st1;
  for (int i = n - 1; i >= 0; i--) {
    while (!st1.empty() && arr[st1.top()] >= arr[i])
      st1.pop();
    nse[i] = st1.empty() ? n : st1.top();
    st1.push(i);
  }
  return nse;
}
vector<int> findpsee(vector<int> &arr) {
  int n = arr.size();
  vector<int> pse(n);
  stack<int> st2;
  for (int i = 0; i < n; i++) {
    while (!st2.empty() && arr[st2.top()] > arr[i])
      st2.pop();
    pse[i] = st2.empty() ? -1 : st2.top();
    st2.push(i);
  }
  return pse;
}
int sumSubarrayMins(vector<int> &arr) // IMPORTANT
{
  vector<int> nse = findnse(arr);
  vector<int> psee = findpsee(arr);
  int total = 0;
  int mod = (int)(1e9 + 7);
  for (int i = 0; i < arr.size(); i++) {
    int left = i - psee[i];
    int right = nse[i] - i;
    total = (total + (right * left * 1LL * arr[i]) % mod) % mod;
  }
  return total;
}

/*
Given an array of integers arr, find the sum of min(b), where b ranges over
every (contiguous) subarray of arr. Since the answer may be large, return the
answer modulo 109 + 7.



Example 1:

Input: arr = [3,1,2,4]
Output: 17
Explanation:
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4],
[3,1,2,4]. Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1. Sum is 17.

Answer = Sum(nums[i] * (previous less element index length ) * (next small index
length ))
*/

/*
Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
*/

vector<int> asteroidCollision(vector<int> &asteroids) {
  stack<int> st;
  int n = asteroids.size();
  for (int i = 0; i < n; i++) {
    if (st.empty() || st.top() * asteroids[i] > 0 ||
        (st.top() < 0 && asteroids[i] > 0)) // <-- imp
    {
      st.push(asteroids[i]);
      continue;
    }
    while (!st.empty() && st.top() > 0 && asteroids[i] < 0) {
      if (abs(asteroids[i]) < st.top())
        break;
      else {
        st.pop();
        if (st.empty() || st.top() * asteroids[i] > 0 ||
            st.top() < 0 && asteroids[i] > 0) {
          st.push(asteroids[i]);
          break;
        }
      }
    }
  }
  vector<int> ans;
  while (!st.empty()) {
    ans.push_back(st.top());
    st.pop();
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

/*
Given string num representing a non-negative integer num, and an integer k,
return the smallest possible integer after removing k digits from num. Example
1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219
which is the smallest.
*/
string removeKdigits(string num, int k) {
  // number of operation greater than length we return an empty string
  if (num.length() <= k)
    return "0";

  // k is 0 , no need of removing /  preforming any operation
  if (k == 0)
    return num;

  string res = ""; // result string
  stack<char> s;   // char stack

  s.push(num[0]); // pushing first character into stack

  for (int i = 1; i < num.length(); ++i) {
    while (k > 0 && !s.empty() && num[i] < s.top()) {
      // if k greater than 0 and our stack is not empty and the upcoming
      // digit, is less than the current top than we will pop the stack top
      --k;
      s.pop();
    }

    s.push(num[i]);

    // popping preceding zeroes
    if (s.size() == 1 && num[i] == '0')
      s.pop();
  }

  while (k && !s.empty()) {
    // for cases like "456" where every num[i] > num.top()
    --k;
    s.pop();
  }

  while (!s.empty()) {
    res.push_back(s.top()); // pushing stack top to string
    s.pop();                // pop the top element
  }

  reverse(res.begin(), res.end()); // reverse the string

  if (res.length() == 0)
    return "0";

  return res;
}

/*
The next greater element of some element x in an array is the first greater
element that is to the right of x in the same array.
You are given two distinct 0-indexed integer arrays nums1 and nums2,
where nums1 is a subset of nums2.
For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j]
and determine the next greater element of nums2[j] in nums2. If there is no next
greater element, then the answer for this query is -1. Return an array ans of
length nums1.length such that ans[i] is the next greater element as described
above.
*/

vector<int> nextGreaterElement(vector<int> &nums2, vector<int> &nums1) {
  unordered_map<int, int> m;
  stack<int> st;
  for (int i = nums1.size() - 1; i >= 0; i--) {
    while (!st.empty() && nums1[i] >= st.top()) {
      st.pop();
    }
    if (st.empty()) {
      m[nums1[i]] = -1;
      st.push(nums1[i]);
      continue;
    }
    m[nums1[i]] = st.top();
    st.push(nums1[i]);
  }
  vector<int> ans;
  for (int i = 0; i < nums2.size(); i++)
    ans.push_back(m[nums2[i]]);
  return ans;
}

int main() {}
