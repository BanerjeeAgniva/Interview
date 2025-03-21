#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

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
// --------