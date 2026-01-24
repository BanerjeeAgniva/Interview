#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
using namespace std;
double myPow(double x, int n) {
  if (n < 0)
    return myPow(1 / x, abs(n));
  double res = 1;
  while (n) {
    if (n % 2) {
      res = res * x;
      n--;
    } else {
      x = x * x;
      n = n >> 1;
    }
    cout << x << " " << n << " " << res << endl;
  }
  return res;
}
/*
A digit string is good if the digits (0-indexed) at even indices are even and
the digits at odd indices are prime (2, 3, 5, or 7).

For example, "2582" is good because the digits (2 and 8) at even positions are
even and the digits (5 and 2) at odd positions are prime. However, "3245" is not
good because 3 is at an even index but is not even.

*/
int countGoodNumbers(long long n) {
  long long mod = 1e9 + 7;
  return (long long)(myPow(4, n / 2) * myPow(5, n / 2 + n % 2)) % mod;
}
/*
 _ _ _ _  --> even places have 5(0 2 4 6 8) choices each and odd places have 4(2
 3 5 7) choices number of even indices in number of length n --> n/2 + n%2   odd
 indices --> n/2

*/
//---
/*
Stack: 11 2 32 3 41
Output: 41 32 11 3 2
Given a stack, the task is to sort it such that the top of the stack has the
greatest element.
*/
void insertInSortedOrder(stack<int> &stack, int element) {
  if (stack.empty() || stack.top() <= element) {
    stack.push(element); // element is my next number in the sorted manner
    return;
  }
  int topElement = stack.top();
  stack.pop();
  insertInSortedOrder(stack, element);
  stack.push(topElement);
}
void sortStack(stack<int> &stack) {
  if (stack.empty()) {
    return;
  }
  int topElement = stack.top();
  stack.pop();
  // cout<<"sortstack called"<<endl;
  sortStack(stack);
  // cout<<"insertstack called"<<endl;
  insertInSortedOrder(stack, topElement);
}
/*
Recursively reverse a stack
*/
void Insertatbottom(stack<int> &s, int a) {
  if (s.empty())
    s.push(a);
  else {
    int b = s.top();
    s.pop();
    Insertatbottom(s, a);
    s.push(b);
  }
}
void Reverse(stack<int> &St) {
  if (!St.empty()) {
    int a = St.top();
    St.pop();
    Reverse(St);
    Insertatbottom(St, a);
  }
}
/*
Generate all binary strings of length n such that there are no consecutive 1s

Input : K = 3
Output : 000 , 001 , 010 , 100 , 101
Input : K  = 4
Output :0000 0001 0010 0100 0101 1000 1001 1010
*/
void generate(vector<string> &ans, string s, int i) {
  if (i >= s.size()) {
    ans.push_back(s);
    return;
  }
  s[i] = '1';
  generate(ans, s, i + 2); // consecutive 1s
  s[i] = '0';
  generate(ans, s, i + 1);
}
void generateAllStrings(int n) {
  vector<string> ans;
  string s = "";
  for (int i = 0; i < n; i++)
    s.push_back('0');
  generate(ans, s, 0);
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << " ";
  }
}

/*
Generate parantheses
Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
*/

void func(vector<string> &ans, string s, int open, int close, int n) {
  if (open == n && close == n) {
    ans.push_back(s);
    return;
  }
  if (open < n) {
    s.push_back('(');
    func(ans, s, open + 1, close, n);
    s.pop_back();
  }
  if (close < open) {
    s.push_back(')');
    func(ans, s, open, close + 1, n);
    s.pop_back();
  }
}
vector<string> generateParenthesis(int n) {
  vector<string> ans;
  string s = "";
  func(ans, s, 0, 0, n);
  return ans;
}
/*
Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

*/
void util(int index, vector<vector<int>> &ans, vector<int> &nums,
          vector<int> curr) {
  if (index == nums.size()) {
    ans.push_back(curr);
    return;
  }
  // not take
  util(index + 1, ans, nums, curr);

  // take
  curr.push_back(nums[index]);
  util(index + 1, ans, nums, curr);
}
vector<vector<int>> subsets(vector<int> &nums) {
  vector<vector<int>> ans;
  vector<int> curr;
  util(0, ans, nums, curr);
  return ans;
}
/*
Any number can be used multiple times
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple
times. 7 is a candidate, and 7 = 7. These are the only two combinations.
*/
vector<vector<int>> ans;
vector<int> sub;
void generate(vector<int> &nums, int i, int target) {
  if (i == nums.size() || target < 0)
    return;
  if (target == 0) {
    ans.push_back(sub);
    return;
  }
  sub.push_back(nums[i]);
  generate(nums, i, target - nums[i]); // take
  sub.pop_back();                      // not take
  generate(nums, i + 1, target);       // move forward
}
vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
  generate(candidates, 0, target);
  return ans;
}
//------------------
/*
Time Complexity: O(2^t * k) where t is the target, k is the average length

Reason: Assume if you were not allowed to pick a single element multiple times,
every element will have a couple of options: pick or not pick which is 2^n
different recursion calls, also assuming that the average length of every
combination generated is k. (to put length k data structure into another data
structure) Why not (2^n) but (2^t) (where n is the size of an array)? Assume
that there is 1 and the target you want to reach is 10 so 10 times you can “pick
or not pick” an element.

Space Complexity: O(k*x), k is the average length and x is the no. of
combinations
*/
//-------------------
/*
collection of candidate numbers (candidates) and a target number (target), find
all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used ONCE in the combination.



Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output:
[
[1,2,2],
[5]
]
*/
void util(int index, vector<int> &candidates, vector<vector<int>> &ans,
          int target, vector<int> curr) {
  if (target < 0)
    return;
  if (index == candidates.size()) {
    if (target == 0)
      ans.push_back(curr);
    return;
  }
  /* DOESNT WORK
          while(index+1<candidates.size() &&
     candidates[index+1]==candidates[index]) index++; util(index+1, candidates,
     ans, target, curr);
  */
  // to avoid picking up the same combnations i.e. we don't pick same element
  // for certain kth position of a combination not take
  //  does not work because it modifies the index directly in the middle of the
  //  recursion. This skips over necessary steps and creates logical
  //  inconsistencies in the recursion.

  int j = index;
  while (j + 1 < candidates.size() && candidates[j + 1] == candidates[j])
    j++;
  util(j + 1, candidates, ans, target, curr);
  // take
  curr.push_back(candidates[index]);
  util(index + 1, candidates, ans, target - candidates[index], curr);
  curr.pop_back();
}
vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
  vector<vector<int>> ans;
  vector<int> curr;
  sort(candidates.begin(), candidates.end());
  util(0, candidates, ans, target, curr);
  return ans;
}
/*
Time Complexity:O(2^n*k)

Reason: Assume if all the elements in the array are unique then the no. of
subsequence you will get will be O(2^n). we also add the ds to our ans when we
reach the base case that will take “k”//average space for the ds.

Space Complexity:O(k*x)
*/
/*
Given a array arr of integers, return the sums of all subsets in the list.
Return the sums in any order. Input: arr[] = [5, 6, 7] Output: [0, 5, 6, 7, 11,
12, 13, 18] Explanation: The possible subset sums are 0 (no elements), 5, 6, 7,
and their combinations.
*/
void bt(vector<int> &arr, vector<int> &ans, int i, int sum) {
  if (i == arr.size()) {
    ans.push_back(sum);
    return;
  }
  bt(arr, ans, i + 1, sum);
  bt(arr, ans, i + 1, sum + arr[i]);
}
vector<int> subsetSums(vector<int> arr, int n) {
  vector<int> ans;
  bt(arr, ans, 0, 0);
  return ans;
}

/*
Given an integer array nums that may contain duplicates, return all possible
subsets
 (the power set).

The solution set must not contain duplicate subsets. Return the solution in any
order.



Example 1:

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
*/
/*
Find all valid combinations of k numbers that sum up to n such that the
following conditions are true: Only numbers 1 through 9 are used. Each number is
used at most once. Return a list of all possible valid combinations. The list
must not contain the same combination twice, and the combinations may be
returned in any order.

Example 2:

Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.
*/
vector<vector<int>> ans;
void f(vector<int> &cur, int cnum, int k, int n) {
  if (n < 0 || cur.size() > k)
    return;
  if (n == 0 && cur.size() == k) {
    ans.push_back(cur);
    return;
  }
  for (int i = cnum; i <= 9; ++i) {
    cur.push_back(i);
    f(cur, i + 1, k, n - i);
    cur.pop_back();
  }
}
vector<vector<int>> combinationSum3(int k, int n) {
  vector<int> cur;
  f(cur, 1, k, n);
  return ans;
}

vector<string> letterCombinationsOfAphoneNumber(string digits) {
  vector<string> ans;
  if (digits == "") {
    return ans;
  }
  vector<string> map = {"",    "",    "abc",  "def", "ghi",
                        "jkl", "mno", "pqrs", "tuv", "wxyz"};
  string one = "", two = "", three = "", four = "";
  int noofdigits = 0;
  if (digits.size() >= 1) {
    one = map[digits[0] - '0'];
    noofdigits++;
  }
  if (digits.size() >= 2) {
    two = map[digits[1] - '0'];
    noofdigits++;
  }
  if (digits.size() >= 3) {
    three = map[digits[2] - '0'];
    noofdigits++;
  }
  if (digits.size() == 4) {
    four = map[digits[3] - '0'];
    noofdigits++;
  }
  string temp = "";
  for (int i = 0; i < one.size(); i++) {
    temp += one[i];
    cout << temp << " ";
    if (temp.size() == noofdigits) {
      ans.push_back(temp);
      temp.pop_back();
    }
    cout << temp << " ";
    for (int j = 0; j < two.size(); j++) {
      temp += two[j];
      cout << temp << " ";
      if (temp.size() == noofdigits) {
        ans.push_back(temp);
        temp.pop_back();
      }
      cout << temp << " ";
      for (int k = 0; k < three.size(); k++) {
        temp += three[k];
        cout << temp << " ";
        if (temp.size() == noofdigits) {
          ans.push_back(temp);
          temp.pop_back();
        }
        cout << temp << " ";
        for (int l = 0; l < four.size(); l++) {
          temp += four[l];
          cout << temp << " ";
          if (temp.size() == noofdigits) {
            ans.push_back(temp);
            temp.pop_back();
          }
          cout << temp << " ";
        }
      }
    }
    temp = "";
    cout << endl;
  }
  return ans;
}

void backtrack(const string &digits, const vector<string> &map, string &current,
               int index, vector<string> &result) {
  if (index == digits.size()) {
    result.push_back(current);
    return;
  }
  string letters = map[digits[index] - '0'];
  for (char c : letters) {
    current.push_back(c);
    backtrack(digits, map, current, index + 1,
              result); // ----> backtrack inside a for loop !!
    current.pop_back();
  }
}

vector<string> letterCombinationsOfAphoneNumberr(string digits) {
  if (digits.empty())
    return {};

  vector<string> map = {"",    "",    "abc",  "def", "ghi",
                        "jkl", "mno", "pqrs", "tuv", "wxyz"};
  vector<string> result;
  string current;
  backtrack(digits, map, current, 0, result);
  return result;
}
/*
Palindrome Partitioning
Given a string s, partition s such that every
substring
 of the partition is a
palindrome
. Return all possible palindrome partitioning of s.



Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
Example 2:

Input: s = "a"
Output: [["a"]]


abab  -->  a,b,a,b     aba,b        a,bab

is a palindrome? yes --->   Okay now the subproblem becomes to check for all
answer in  bab Now --> ab  ab is not a palndrome then lite Now aba -->
palindrome ---> Okay subproblem becomes to check for all partitions in b

*/
bool checkPalindrome(string s) {
  int len = s.length();
  int i = 0;
  int j = len - 1;
  while (i <= j) {
    if (s[i] != s[j])
      return false;
    i++;
    j--;
  }
  return true;
}
void util(int index, string s, vector<vector<string>> &ans,
          vector<string> curr) {
  if (index == s.length()) {
    ans.push_back(curr);
    return;
  }
  // partition
  string temp = "";
  for (int i = index; i < s.length(); i++) {
    temp += s[i];
    if (checkPalindrome(temp)) {
      curr.push_back(temp);
      util(i + 1, s, ans, curr);
      curr.pop_back();
    }
  }
}
vector<vector<string>> partition(string s) {
  vector<vector<string>> ans;
  vector<string> curr;
  util(0, s, ans, curr);
  return ans;
}
/*
Input: board =
[
["A","B","C","E"],
["S","F","C","S"],
["A","D","E","E"]
],
word = "ABCCED"
Output: true

DFS + Backtracking

How will you backtrack?
 whenever you encounter a letter mark it  * to show that it has been encountered
  and once you are done checking in that direction change it back to original
*/
int x[4] = {-1, 0, 1, 0};
int y[4] = {0, 1, 0, -1};
bool help(vector<vector<char>> &board, string word, int i, int j, int check) {
  if (check == word.size())
    return true;
  if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size())
    return false;
  if (word[check] != board[i][j])
    return false;
  board[i][j] = '*'; // used
  int ans = false;
  for (int r = 0; r < 4; r++) {
    ans = ans | help(board, word, i + x[r], j + y[r], check + 1);
  }
  board[i][j] = word[check];
  return ans;
}
bool exist(vector<vector<char>> &board, string word) {
  int m = board.size();
  int n = board[0].size();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == word[0]) {
        if (help(board, word, i, j, 0))
          return true;
      }
    }
  }
  return false;
}

/*
If you have placed a queen in row r then i wont place another queen in the
same row For every row iterate through all the columns : If there is already a
queen in the colum then continue If there is already a queen in the positive
diagonal (bottom left to top right) denoted by same R+C value
      ------>  (3,0) (2,1) (1,2) (0,3)  then you cant put a queen there
    If there is already a queen in the negative diagonal (top left to bottom
right) denoted by same R-C value
      ------>  (0,0) (1,1) (2,2) (3,3)  then you cant put a queen there
   IF YOU CAN PUT A QUEEN ---> Mark that spot call backtrack for the next row
   so that the sub problem becomes the board (r-1 * c) remaining board
  After returning unmark the spot that you had marked Q so that other answers
can be recorded

Space optimize --> O(N) by  :::::::>>>>
        vector<int> cols(n, 0);
        vector<int> posdiag(2 * n - 1, 0);
        vector<int> negdiag(2 * n - 1, 0);

TIme Complexity ---> O(N!)
The time complexity of the backtracking solution for the N-Queens problem is
approximately \(O(N!)\) in the worst case. This is because the first queen has
\(N\) options for placement, the second queen has
\(N-1\) options after placing the first queen, the third queen has \(N-2\)
options after placing the first two queens, and so forth. This factorial
growth represents the upper bound of the time complexity. Although the actual
complexity is often less than \(N!\) due to the pruning of invalid positions
as the algorithm progresses, the factorial bound still provides a good
estimate of the worst-case scenario.
 */

vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> ans;
  string s(n, '.');
  vector<string> board(n);
  for (int i = 0; i < n; i++)
    board[i] = s;
  vector<int> leftRow(n, 0);
  vector<int> uppDiag(2 * n - 1, 0);
  vector<int> lowDiag(2 * n - 1, 0);
  util(0, n, ans, leftRow, uppDiag, lowDiag, board);
  return ans;
}
void util(int col, int n, vector<vector<string>> &ans, vector<int> &leftRow,
          vector<int> &uppDiag, vector<int> &lowDiag, vector<string> board) {
  if (col == n) {
    ans.push_back(board);
    return;
  }
  // check each row for the particular column
  for (int row = 0; row < n; row++) {
    if (leftRow[row] == 0 && uppDiag[row + col] == 0 &&
        lowDiag[n - 1 + row - col] == 0) {
      leftRow[row] = 1;
      uppDiag[row + col] = 1;
      lowDiag[n - 1 + row - col] = 1;
      board[row][col] = 'Q';
      util(col + 1, n, ans, leftRow, uppDiag, lowDiag, board);
      board[row][col] = '.';
      leftRow[row] = 0;
      uppDiag[row + col] = 0;
      lowDiag[n - 1 + row - col] = 0;
    }
  }
}
/*
rat maze --> 1 is unblocked
Input: mat[][] =
[
[1, 0, 0, 0],
[1, 1, 0, 1],
[1, 1, 0, 0],
[0, 1, 1, 1]]
Output: ["DDRDRR", "DRDDRR"]
Explanation: The rat can reach the destination at (3, 3) from (0, 0) by two
paths - DRDDRR and DDRDRR, when printed in sorted order we get DDRDRR DRDDRR.
*/
int xx[4] = {1, 0, -1, 0};
int yy[4] = {0, 1, 0, -1};
string dir = "DRUL";
void backtrack(int i, int j, vector<string> &ans, vector<vector<int>> &grid,
               string curr) {
  // if(i<0||j<0||i>=grid.size()||j>=grid.size()) return;
  if (grid[i][j] != 1)
    return;
  if (i == grid.size() - 1 && j == grid.size() - 1) {
    ans.push_back(curr);
    return;
  }
  for (int r = 0; r < 4; r++) {
    int newx = i + xx[r];
    int newy = j + yy[r];
    if (newx < 0 || newy < 0 || newx >= grid.size() || newy >= grid.size())
      continue;
    grid[i][j] = 2;
    backtrack(newx, newy, ans, grid, curr + dir[r]);
    grid[i][j] = 1;
  }
}
/*
Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen
apple". Note that you are allowed to reuse a dictionary word. Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false

*/

bool func(string s, unordered_set<string> &dict, int ind, int check) {
  if (ind >= s.size()) {
    return check == s.size();
  }
  string temp = "";
  bool ans = false;
  for (int i = ind; i < s.size(); i++) {
    temp = temp + s[i];
    if (dict.find(temp) != dict.end()) {
      ans = ans | func(s, dict, i + 1, check + temp.size());
      if (ans == true)
        return true;
    }
  }
  return false;
}
bool wordBreak(string s, vector<string> &wordDict) {
  unordered_set<string> dict;
  dict.insert(wordDict.begin(), wordDict.end());
  return func(s, dict, 0, 0);
}

vector<string> findPath(vector<vector<int>> &m, int n) {
  vector<string> ans;
  backtrack(0, 0, ans, m, "");
  return ans;
}
int main() {
  stack<int> st;
  st.push(41);
  st.push(8);
  st.push(7);
  st.push(6);
  st.push(5);
  sortStack(st);
  while (!st.empty()) {
    cout << st.top() << " ";
    st.pop();
  }
}
// 11 2 32 3 41