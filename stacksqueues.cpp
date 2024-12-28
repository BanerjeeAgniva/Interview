#include <iostream>
#include <queue>
#include <stack>
#include <string>
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

// 😉😉😉😉Please upvote if it helps 😉😉😉😉
class Solution {
public:
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
};

int main() {}
