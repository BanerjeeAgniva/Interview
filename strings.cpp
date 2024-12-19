#include<string>
using namespace std;
/*
1021. Remove Outermost Parentheses
Input: s = "(()())(())"
Output: "()()()"
Explanation: 
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
*/
/*
Solution --> keep a counter of number of open brackets 
*/
string removeOuterParentheses(string s) {
        string ans="";
        int count=0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]=='(')
            {
               if(count!=0) ans=ans+"(" ; // put into answer if it is not the outermost open bracket 
               count++ ;
            }
            else
            {
               if(count!=1) ans=ans+")" ; // put into answer if it is not the outermost closing bracket 
               count-- ;
            }
        }
        return ans;
    }

//  -----> s.substr(startpos,length) --> gives "length"-lengthed substring starting from startpos 

/*
Largest common prefix 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"

-----

take the 0th string as your reference and check for all other strings whether the ith letter match 
if it does for all -> then add to answer 

-----
*/
/*

Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another
character while preserving the order of characters. No two characters may map
to the same character, but a character may map to itself.

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
                if (charMap[sc] != tc) return false;
            } else {
                for (auto& pair : charMap) {   // If you want to avoid this step, increase the space complexity by using another unordered_map to keep track whether t[i] has occured previosuly or not 
                    if (pair.second == tc) return false;
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
        if(s.size()!=goal.size()) return false;
        s=s+s;
        int i=0,j=0;
        while(i<s.size())
        {
            if(s[i]==goal[j])
            {
                i++ ;
                j++ ;
                if(j==goal.size()) return true;
            }
            else
            {
                if(j==0) i++ ;
                else 
                {
                    /*
                    abcdeabcde
                    abcdd
                    */
                    i=i-j+1;  // <---- IMP
                    j=0;
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
        vector<int> v(26,0);
        for(int i=0;i<s.length();i++) v[s[i]-'a']++ ;
        for(int i=0;i<t.length();i++) v[t[i]-'a']-- ;
        for(int i=0;i<26;i++) if(v[i]!=0) return false;
        return true;
    }
