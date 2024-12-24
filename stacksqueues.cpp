#include <queue>
#include <string>
#include<stack>
#include <iostream>
using namespace std;
/*
stack using array
*/
int top=-1;
int arr[1000];
int pop_stack(){
   if(top==-1) return -1;
   int x=arr[top];
   top-- ;
   return x;
}
void push_stack(int x){
    top++ ;
    arr[top]=x;
}
//=======================>>
/*
queue using array
*/
int front=0; int rear=0;
void push_queue(int x)
{
    arr[rear]=x;
    rear++ ;
}
int pop_queue()
{
    if(front==rear) return -1;
    int num=arr[front];
    front++ ;
    return num;
}
//=======================>>
/*
stack using queue

The element at the top of the stack should be present at the front of the queue // NOT REAR 
SO how do you achieve this ??
suppose stakc empty 
push 3        3                queue --> 3
push 4                          queue   ----> 3 4  BUT you ideally want 4 3 so that when you pop 4 gets popped LIFO
so push the current element x     a b c d e x 
Now keep rotating   b c d e x a       c d e x a b      d e x a b c        e x a b c d     x a b c d e  (rotate for n times where n is no of elements before you pushed x )
now when you pop you get x 
*/
queue<int> stackq;
int func(string command){
    int front=0; int rear=0;
    if(command=="push")
    {
        int x; cin>>x;
        int n=stackq.size();
        stackq.push(x);
        for(int i=0;i<n;i++){
            stackq.push(stackq.front());
            stackq.pop();
        }
        return 0;
    }
    else if(command=="pop")
    {
        int num=stackq.front();
        stackq.pop();
        return num;
    }
    else if(command=="top"){
        return stackq.front();
    }
    else if(command=="empty"){
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

to do this every time there is a new element you have to dump all the elements in the first stack into another and stack 
then enter the element x   so that its something like x 1 2 3  ] <---- bottom of stack

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
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
nums2 -->  
push 2      2]       as stack was empty  --->   m[2]=-1
4 encountered   is 4>=top_of_stack (2) yes? pop       4]             as stack was empty before 4 was pushed  --->   m[4]=-1
3 encountered  is 3>=top_of_stack(4)  no?   push    3  4]          m[3] = top_of_stack before 3 was pushed  =  4 
1 encountered                                                                    1   3   4]
maintain monotically increasing stack --->  1 2 4 
if you push 3 into this 
then1  2 get popped out
Final status ->
3 4
*/

int main(){

}
