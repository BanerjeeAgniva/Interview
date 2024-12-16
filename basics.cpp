#include <iostream>
#include <vector>
using namespace std;
// Given a positive integer n, The task is to find the value of Σi from 1 to n F(i) where function F(i) 
// for the number i is defined as the sum of all divisors of i.
int sumdivisors(int n){
    int sum=0;
    for(int i=1;i<=n;i++) sum+= (n/i) * i  ;  // number of times i has apperared * i 
    return sum; 
    /*
    LOGIC 
    1  -> 1 
    2  -> 1  2
    3  -> 1        3
    4 ->  1  2            4
    5  -> 1                         5
    */
}
int gcd(int n,int m){
    if(m==0) return n;
    return gcd(m,n%m);
    /*
    gcd(20,15) -->
    gcd(15,5) --> 
    gcd(5,0) --->
    5
    */
}
// You are given an array arr[] containing positive integers. The elements in the array arr[] range from 1 to n 
// (where n is the size of the array), and some numbers may be repeated or absent. Your task is to count the frequency 
// of all numbers in the range 1 to n and return an array of size n such that result[i] represents the frequency of 
// the number i (1-based indexing).
// How will you do it in O(1) extra space? 
vector<int> frequencyCount(vector<int>& arr) {
   /*
   2  3  3  2  5 
   3 -1  3  2  5
   3 -1 -1  2  5
   0 -1 -2  2  5
   0 -2 -2  0  5
   0 -2 -2  0 -1 
   */
  int i=0;
  while(i<arr.size()){
     if(arr[i]>0){
       if(arr[arr[i] - 1]<0){  // -1 because 1 based indexing
        arr[arr[i] - 1]-- ; //increase the frequency
        arr[i]=0;  // erase and 
        i++ ; //move forward 
       }
       else{
        int temp=arr[i];
        arr[i]=arr[arr[i]-1];  // swap 
        arr[temp-1]=-1;    // this is the first time you have counted number of value arr[i]
       }
    }
    else i++;
  }
  for(int i=0;i<arr.size();i++){
    arr[i]=-1*arr[i];
  }
  return arr;
}
// The frequency of an element is the number of times it occurs in an array.
// You are given an integer array nums and an integer k. In one operation, 
//you can choose an index of nums and increment the element at that index by 1.
// Return the maximum possible frequency of an element after performing at most k operations.
// Example 1:
// Input: nums = [1,2,4], k = 5
// Output: 3
// Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
// 4 has a frequency of 3.
int maxFrequency(vector<int>& nums, int k) {
    // 1 1 2 ---> k=2 
    // 2 2 2 
    // 1 1 2  ---> currsum=4
    // required --> 6 ---> which is nums[rightpointer] * windowlength 
    // with currsum + k we can manage required sum  
    // ---------------------------------------------------------------------------------------
    // LOGIC --->  required = nums[right] * windowlen <= currsum + k   ----> This is ACCEPTED 
    // ---------------------------------------------------------------------------------------
    sort(nums.begin(),nums.end());
    int left=0,right=0;
    long long currsum=0;
    int ans=1;
    while(right<nums.size()){
        currsum+=(long long)nums[right];
        while(((right-left+1) * (long long)nums[right]) > (currsum+k)  && left<=right){
            currsum-=nums[left] ;
            left++ ;
        }
        ans=max(ans,right-left+1);
        right++ ;
    } 
    return ans;
}
int main()
{
    //cout<<sumdivisors(5)<<"\n";
    //cout<<gcd(20,15)<<"\n";
    // vector<int> arr={2,3,3,2,5}; // expected output --> {0,2,2,0,1}
    // arr=frequencyCount(arr);
    // for(int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }
    // cout<<"\n";
    // vector<int> arr={4,1,2,2,1};
    // cout<<maxFrequency(arr,2)<<endl;  // expected --> 4 2 2 2 2  ---> answer 4 
}
