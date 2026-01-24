 #include<iostream>
 #include<vector>
 #include<stack> 
 using namespace std;
 int largestRectangleArea(vector<int>& heights) {
       int n=heights.size();
       int ans=0;
       stack<pair<int,int>> st; //height,index
       st.push({-1,-1});
       int i=0;
       while(i<n)
       {
          while(heights[i]<=st.top().first)
          {
            int heighttop=st.top().first;
            st.pop();
            int rightbound=i;
            int leftbound=st.top().second;
            ans=max(ans,heighttop*(rightbound-leftbound-1));
          }
          st.push({heights[i] , i});
          i++ ;
       }
       //-------------------------------------------------------
       while(st.top().first!=-1)
       {
          int heighttop=st.top().first;
          st.pop();
          int rightbound=i; //n
          int leftbound=st.top().second;
          ans=max(ans,heighttop*(rightbound-leftbound-1));
       }
       return ans;
    }