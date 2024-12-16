#include <iostream> 
#include <vector>
using namespace std;
// selection sort --> pick the minimum and swap 
// bubble sort ---> pair-by-pair comparison for the entire length for a total of n-iterations 
// insertion sort ---> for an array of length n, you first sort out till length 1, then till length 2, .... till length n
//-----
// Merge Sort ---> Recursively sort out the left---mid and mid+1----right 
// and when merging the two subparts make sure it is sorted 
void merge(vector<int>& arr, int left, int mid, int right){
    vector<int> temp;
    int i=left;
    int j=mid+1;
    while(i<=mid && j<=right){
        if(arr[i]<arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while(i<=mid) temp.push_back(arr[i++]);
    while(j<=right) temp.push_back(arr[j++]);
    for(int i=left;i<=right;i++){
        arr[i]=temp[i-left];
    }
} 
void mergesort(vector<int>& arr,int left,int right){
    if(left>=right) return;  // no partitioning possible when one element left 
    int mid = left + (right - left) / 2;
    mergesort(arr,left,mid);     //     mergesort(arr,left,mid-1);   ---> This leads to 
    mergesort(arr,mid+1,right); //      mergesort(arr,mid,right);           SEG FAULT 
    merge(arr,left,mid,right);
}
void mergesort(vector<int>& arr){
    mergesort(arr,0,arr.size()-1);
}
//----------
int partition(vector<int>& arr,int left,int right)  //place pivot element in correct position
{
    int pivot=arr[left];
    int i=left+1;
    int j=right;
    while(true){
        while(arr[i]<pivot) i++ ; // we need to send greater elements than pivot to the right side 
        while(arr[j]>pivot) j-- ; // we need to keep smaller elements than pivot to the left side 
        if(j<i) break;
        swap(arr[i],arr[j]);
    }
    swap(arr[j],arr[left]); // put the pivot element = arr[left] in its correct position j 
    return j;
}
// timestamp--> 15:03 https://www.youtube.com/watch?v=WIrA4YexLRQ
void qs(vector<int>& arr, int left, int right){
    if(left>=right) return;
    int pind=partition(arr,left,right);  //partition index
    qs(arr,left,pind-1);
    qs(arr,pind+1,right);
}
void quicksort(vector<int>& arr){
    qs(arr,0,arr.size()-1);
}
int main(){
    vector<int> arr={4,3,5,6,1,2};
    //mergesort(arr);
    quicksort(arr);
    for(int i=0;i<arr.size();i++) cout<<arr[i]<<" ";
    cout<<endl;
}
