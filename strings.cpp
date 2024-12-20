#include <queue>
#include <string>
using namespace std;
/*
1021. Remove Outermost Parentheses
Input: s = "(()())(())"
Output: "()()()"
Explanation:
The input string is "(()())(())", with primitive decomposition "(()())" +
"(())".
*/
/*
Solution --> keep a counter of number of open brackets
*/
string removeOuterParentheses(string s) {
  string ans = "";
  int count = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(') {
      if (count != 0)
        ans = ans +
              "("; // put into answer if it is not the outermost open bracket
      count++;
    } else {
      if (count != 1)
        ans = ans +
              ")"; // put into answer if it is not the outermost closing bracket
      count--;
    }
  }
  return ans;
}
/*
Similar solution for
// 1614. Maximum Nesting Depth of the Parentheses
Input: s = "(1+(2*3)+((8)/4))+1"
Output: 3
record max(count)
*/
//-------
//  -----> s.substr(startpos,length) --> gives "length"-lengthed substring
//  starting from startpos

/*
Largest common prefix

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"

-----

take the 0th string as your reference and check for all other strings whether
the ith letter match if it does for all -> then add to answer

-----
*/
/*

Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get
t. All occurrences of a character must be replaced with another character while
preserving the order of characters. No two characters may map to the same
character, but a character may map to itself.

Input: s = "egg", t = "add"
Output: true
Explanation:
The strings s and t can be made identical by:

Mapping 'e' to 'a'.
Mapping 'g' to 'd'.

*/
bool isIsomorphic(string s, string t) {
  unordered_map<char, char> charMap;

  for (int i = 0; i < s.length(); ++i) {
    char sc = s[i];
    char tc = t[i];

    if (charMap.count(sc)) {
      if (charMap[sc] != tc)
        return false;
    } else {
      for (auto &pair :
           charMap) { // If you want to avoid this step, increase the space
                      // complexity by using another unordered_map to keep track
                      // whether t[i] has occured previosuly or not
        if (pair.second == tc)
          return false;
      }
      charMap[sc] = tc;
    }
  }
  return true;
}

/*
Check if string "s" is a rotation of another string "goal"

Input: s = "abcde", goal = "cdeab"
Output: true

abcde
bcdea
cdeab
deabc
eabcd

abcdeabcde
*/

bool rotateString(string s, string goal) {
  if (s.size() != goal.size())
    return false;
  s = s + s;
  int i = 0, j = 0;
  while (i < s.size()) {
    if (s[i] == goal[j]) {
      i++;
      j++;
      if (j == goal.size())
        return true;
    } else {
      if (j == 0)
        i++;
      else {
        /*
        abcdeabcde
        abcdd
        */
        i = i - j + 1; // <---- IMP
        j = 0;
      }
    }
  }
  return false;
}
// SEE KMP algorithm for above https://www.youtube.com/watch?v=V5-7GzOfADQ&t=2s
/*
check if s and t are anagrams
*/
bool isAnagram(string s, string t) {
  if (s.size() != t.size())
    return false;
  vector<int> v(26, 0);
  for (int i = 0; i < s.length(); i++) {
    v[s[i] - 'a']++;
    v[t[i] - 'a']--;
  }
  for (int i = 0; i < 26; i++)
    if (v[i] != 0)
      return false;
  return true;
}
//----------
// 451. Sort Characters By Frequency
/*
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid
answer.
*/
/*
Input: s = "Aabb"
Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
*/

string frequencySort(string s) {
  unordered_map<char, int> m;
  for (int i = 0; i < s.size(); i++)
    m[s[i]]++;
  priority_queue<pair<int, char>> maxheap;
  for (auto x : m)
    maxheap.push({x.second, x.first});
  string ans = "";
  while (!maxheap.empty()) {
    char ele = maxheap.top().second;
    int freq = maxheap.top().first;
    maxheap.pop();
    for (int i = 0; i < freq; i++)
      ans = ans + ele;
  }
  return ans;
}
//-------
/*
Roman to Integer
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
Record all Roman Numbers in map m and just check whether m[s[i]]
*/
//--------
// Substrings with K Distinct
/*
Input: s = "aba", k = 2
Output: 3
Explanation: The substrings are: "ab", "ba" and "aba".
*/
int atMostK(string &s, int k) {
  if (k < 0)
    return 0;

  int i = 0, j = 0, cnt = 0;
  int res = 0;
  int m[26] = {0};

  while (j < s.length()) {
    m[s[j] - 'a']++;
    if (m[s[j] - 'a'] == 1)
      cnt++;

    while (cnt > k) {
      m[s[i] - 'a']--;
      if (m[s[i] - 'a'] == 0)
        cnt--;
      i++;
    }

    res += (j - i +
            1); // The number of substrings which end on index j with atmost k
    j++;        // distinct letters is (j-i+1) -------> j to j will be 1
    // j-1 to j will be 2 // j-2 to j will be 3 // j-i to j will be j-i+1
  }
  return res;
}

int countSubstr(string str, int k) {
  return atMostK(str, k) - atMostK(str, k - 1);
}
//--------
/*
Longest Palindrome Substring <------- IMP
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Most optimum -> O(n) --> Manacher's algorithm
*/
string longestPalindrome(string s) {
  // concept
  //  a palindrome has a character x such that
  //  <---SAME---x---SAME-->
  int n = s.size();
  int maxlen = 0;
  int ans;
  // palindrome of odd length   aba
  for (int i = 0; i < n; i++) {
    int left = i;
    int right = i;
    while (left >= 0 && right < n && s[left] == s[right]) {
      if (right - left + 1 > maxlen) {
        maxlen = right - left + 1;
        ans = left;
      }
      left--;
      right++;
    }
  }
  // palindrome of even length  abba
  //  <---SAME---xx---SAME-->
  for (int i = 0; i < n; i++) {
    int left = i;
    int right = i + 1;
    while (left >= 0 && right < n && s[left] == s[right]) {
      if (right - left + 1 > maxlen) {
        maxlen = right - left + 1;
        ans = left;
      }
      left--;
      right++;
    }
  }
  return s.substr(ans, maxlen);
}
//----
/*
Input: s = "a good   example"
Output: "example good a"
*/
string reverseWords(string s) {
  string ans = "";
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] == ' ')
      continue;
    string temp = "";
    while (i >= 0 && s[i] != ' ') {
      temp.push_back(s[i]);
      i--;
    }
    reverse(temp.begin(), temp.end());
    ans = ans + temp + " ";
  }
  ans.pop_back();
  return ans;
}
//--------
