#include<string>
#include<vector> 
using namespace std;

/*

3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest 
substring
 without repeating characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

*/
// screenshtot attached 
int lengthofLongestSubstring(string s) {
      vector < int > mpp(256, -1);

      int left = 0, right = 0;
      int n = s.size();
      int len = 0;
      while (right < n) {
        if (mpp[s[right]] != -1)
          left = max(mpp[s[right]] + 1, left);

        mpp[s[right]] = right;

        len = max(len, right - left + 1);
        right++;
      }
      return len;
    }

/*

You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character.
You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.
Example 1:

Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

*/
//======
/*
"BAAAB"    -----> important case to understand that you have to store maxfreq 

Input: s = "AABABBA", k = 1
Output: 4

concept is  : 
LENGTH_CURR_SUBSTRING  -  MAXFREQoccuredtill now  should be <=  k 

ROOKIE MISTAKE --->   Length_curr_substring  -  map[s[right]]  <=k    |||||| map[s[right]] is wrong  
 maxfreq=max(maxfreq,map[s[right]] is correct 
*/
 int characterReplacement(string s, int k) {
        int maxfreq=0,ans=0,j=0;
        vector<int>freq(26,0);
        for(int i=0;i<s.size();i++){
            freq[s[i]-'A']++;
            maxfreq=max(maxfreq,freq[s[i]-'A']); 
            if(i-j+1-maxfreq>k && j<i){
                freq[s[j]-'A']--;
                j++;
            }
           if(i-j+1-maxfreq<=k) ans=max(ans,i-j+1);
        }
        return ans;
    }