#include<iostream> 
#include <stack>
using namespace std;
double myPow(double x, int n) {
        if(n<0) return myPow(1/x,abs(n));
        double res=1;
        while(n)
        {
           if(n%2)
           {
             res=res*x;
             n-- ;
           }
           else
           {
            x=x*x;
            n=n>>1; 
           }
           cout<<x<<" "<<n<<" "<<res<<endl;
        }
        return res;
    }
/*
A digit string is good if the digits (0-indexed) at even indices are even and 
the digits at odd indices are prime (2, 3, 5, or 7).

For example, "2582" is good because the digits (2 and 8) at even positions are even and the 
digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an 
even index but is not even.

*/
int countGoodNumbers(long long n) {
        long long mod=1e9+7;
        return (long long)(myPow(4,n/2) * myPow(5,n/2 + n%2))%mod;
    }
/*
 _ _ _ _  --> even places have 5(0 2 4 6 8) choices each and odd places have 4(2 3 5 7) choices 
 number of even indices in number of length n --> n/2 + n%2   odd indices --> n/2 

*/
//---
/*
Stack: 11 2 32 3 41
Output: 41 32 11 3 2
Given a stack, the task is to sort it such that the top of the stack has the greatest element.
*/
void insertInSortedOrder(stack<int>& stack, int element) {
    if (stack.empty() || stack.top() <= element) {
        stack.push(element); // element is my next number in the sorted manner 
        return;
    }
    int topElement = stack.top();
    stack.pop();
    insertInSortedOrder(stack, element);
    stack.push(topElement);
}
void sortStack(stack<int>& stack) {
    if (stack.empty()) {
        return;
    }
    int topElement = stack.top();
    stack.pop();
    //cout<<"sortstack called"<<endl;
    sortStack(stack);
    //cout<<"insertstack called"<<endl;
    insertInSortedOrder(stack, topElement);
}
/*
Recursively reverse a stack 
*/
void Insertatbottom(stack<int>& s,int a)
    {
       if(s.empty()) s.push(a);
       else
       {
           int b=s.top();
           s.pop();
           Insertatbottom(s,a);
           s.push(b);
       }
    }
    void Reverse(stack<int> &St){
        if(!St.empty())
        {
            int a=St.top();
            St.pop();
            Reverse(St);
            Insertatbottom(St,a);
        }
    }
/*
Generate all binary strings of length n such that there are no consecutive 1s 

Input : K = 3  
Output : 000 , 001 , 010 , 100 , 101 
Input : K  = 4 
Output :0000 0001 0010 0100 0101 1000 1001 1010
*/
void generate(vector<string>& ans,string s,int i)
{
  if(i>=s.size()) 
  {
    ans.push_back(s);
    return;
  }
  s[i]='1';
  generate(ans,s,i+2); // consecutive 1s 
  s[i]='0';
  generate(ans,s,i+1);  
}
void generateAllStrings(int n)
{
  vector<string> ans;
  string s="";
  for(int i=0;i<n;i++) s.push_back('0');
  generate(ans,s,0);
  for(int i=0;i<ans.size();i++)
  {
    cout<<ans[i]<<" ";
  }
}

/*
Generate parantheses 
Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
*/

void func(vector<string>& ans,string s,int open,int close,int n)
    {
        if(open==n && close==n)
        {
            ans.push_back(s);
            return;
        }
        if(open<n)
        {
            s.push_back('(');
            func(ans,s,open+1,close,n);
            s.pop_back();
        }
        if(close<open)
        {
            s.push_back(')');
            func(ans,s,open,close+1,n);
            s.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string s="";
        func(ans,s,0,0,n);
        return ans;
    }
/*
Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

*/
void util(int index, vector<vector<int>>&ans, vector<int>&nums, vector<int>curr){
        if(index==nums.size()){
            ans.push_back(curr);
            return;
        }
        // not take
        util(index+1, ans, nums, curr);

        //take
        curr.push_back(nums[index]);
        util(index+1, ans, nums, curr);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>>ans;
        vector<int>curr;
        util(0,ans,nums, curr);
        return ans;
    }

int main(){
    stack<int> st;
    st.push(41);
    st.push(8);
    st.push(7);
    st.push(6);
    st.push(5);
    sortStack(st);
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
}
//11 2 32 3 41