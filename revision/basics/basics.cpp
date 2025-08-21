#include <vector>
#include <unordered_set>
#include <iostream> // for cout
using namespace std;
class Solution {

    /*
    https://leetcode.com/problems/contains-duplicate/description/
    217. Contains Duplicate
    Difficulty: Easy
    Given an integer array nums, return true if any value appears at least twice in the array,
    and return false if every element is distinct.
    */

public:
    bool containsDuplicate(vector<int>& nums)
    {
        unordered_set<int> s;
        for (int i = 0;i < nums.size();i++)
        {
            if (s.find(nums[i]) != s.end()) return true; // found duplicate
            s.insert(nums[i]);
        }
        return false;
        // Time Complexity: O(n)
        // Space Complexity: O(n) for the set
    }

/*
26. Remove Duplicates from Sorted Array
Difficulty: Easy
Topics: Arrays, Two Pointers
Problem:
https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
*/
};

int main()
{
    Solution sol;
    vector<int> nums = { 1, 2, 3, 1 };
    bool result = sol.containsDuplicate(nums);
    cout << (result ? "1" : "0") << endl; // Output: true
}













/*
function runcpp {
>>     param([string]$file)
>>     $name = [System.IO.Path]::GetFileNameWithoutExtension($file)
>>     g++ $file -o "x.exe"
>>     if ($LASTEXITCODE -eq 0) {
>>         & ".\x.exe"
>>     }
>> }
>>
*/