#include <bits/stdc++.h>
using namespace std;
struct node{
    node* left;
    int value;
    node* right;
};
struct node* newnode(int val)
{
    struct node* temp=new struct node;
    temp->left=NULL;
    temp->value=val;
    temp->right=NULL;
}
struct node* insert(struct node* root, int to_be_inserted)
{
    if(root==NULL) return newnode(to_be_inserted);
    if(root->value<to_be_inserted) root->right=insert(root->right,to_be_inserted);
    else root->left=insert(root->left,to_be_inserted);
    return root;
}
struct node* search(struct node* root,int x)
{
    if(root==NULL) return NULL;
    if(root->value > x ) return search(root->left,x);
    else if(root->value < x) return search(root->right,x);
    else return root; 
}
int minValue(struct node* root) 
{
    if(root->left==NULL) return root->value;
    else return minValue(root->left);
}
int findCeil(struct node* root, int input) {
    int ans=-1;
    while(root){
       if(root->value < input) root=root->right;
       else{
         if(root->value==input) return input;
         ans=root->value;
         root=root->left;
       }
    }
    return ans;
}
int floor(struct node* root, int x) {
        int ans=-1;
        while(root)
        {
            if(root->value>x) root=root->left;
            else{
                if(root->value==x) return x;
                ans=root->value;
                root=root->right;
            }
        }
        return ans;
    }
struct node* deleteNode(struct node* root, int key )
{
    if(root==NULL) return NULL;
    if(root->value>key) root->left=deleteNode(root->left,key);
    else if(root->value<key) root->right=deleteNode(root->right,key);
    else
    {
       if(root->left==NULL && root->right==NULL) return NULL;
       if(root->left==NULL) return root->right;
       if(root->right==NULL) return root->left;
       struct node* lst=root->left;
       struct node* rst=root->right;
       // Attach leftsubtree to the leftmost child of the rightsubtree
       struct node* lmcrst=rst;
       while(lmcrst->left) lmcrst=lmcrst->left;
       lmcrst->left=lst;
       return rst;
    }
    return root;
}
int kthSmallest(struct node* root, int k) {
    stack<struct node*> st;
    struct node* temp=root;
    while(k--)
    {
        while(temp)
        {
         st.push(temp);
         temp=temp->left;
        }
        temp=st.top();
        st.pop();
        if(k==0) return temp->value;
        temp=temp->right;
    }
    return -1;
}
int kthLargest(struct node* root,int k){
    stack<struct node*> st;
    while(k--)
    {
        while(root)
        {
            st.push(root);
            root=root->right;            
        }
        root=st.top();
        st.pop();
        if(k==0) return root->value;
        root=root->left;
    }
    return -1;
}
//-------------------------------------------------------------------------------
bool func(struct node* root, struct node* lb, struct node* rb)
    {
        if(root==NULL) return true;
        // THE ROOT VALUE SHOULD BE WITHIN THE LEFT AND THE RIGHT BOUNDARY
        if(lb && root->value <= lb->value) return false;
        if(rb && root->value >= rb->value) return false;
        return func(root->left,lb,root) && func(root->right,root,rb);
        
    }
bool isValidBST(struct node* root) {
     return func(root,NULL,NULL);
}
//-------------------------------------------------------------------------------
struct node* lowestCommonAncestor(struct node* root, struct node* p, struct node* q){
        //go to left subtree of root if p and q are both less than root
        //go to right subtree of root if p and q are both less than root
        //if p and q are in different subtrees your answer is root
        if(root==NULL) return NULL;
        if(p->value>root->value && q->value>root->value) return lowestCommonAncestor(root->right,p,q);
        else if (p->value<root->value && q->value<root->value)return lowestCommonAncestor(root->left,p,q);
        return root;
    }
struct node* inOrderSuccessor(struct node*root, struct node*x)
    {
        struct node* ans=NULL;
        while(root!=x)
        {
            if(root->value > x->value) {
                ans=root;
                root=root->left;
            }
            else root=root->right;
        }
        if(root->right){
            root=root->right;
            while(root->left){
                root=root->left;
            }
            return root;
        }
        return ans;
    }
//--------------------------------------------------------------------------
struct node* func(struct node* lower,vector<int>& pre,int& i, struct node* upper)
    {
        if( i==pre.size() || (upper && pre[i] > upper->value)  ) return NULL;
        struct node* node=newnode(pre[i++]);
        node->left=func(lower,pre,i,node);
        node->right=func(node,pre,i,upper);
        return node;
    } 
struct node* bstFromPreorder(vector<int>& preorder) {
        int i=0;
        return func(NULL,preorder,i,NULL);
}
//------------------------------------------------------------------------------
    stack<struct node*> st;
    struct node* x;
    BSTIterator(struct node* root) {
        x=root;
        while(x){
            st.push(x);
            x=x->left;
        }
    }
    int next() {
        int ans=st.top()->value;
        x=st.top();
        st.pop();
        x=x->right;
        while(x)
        {
           st.push(x);
           x=x->left;
        }
        return ans;
    }
    bool hasNext() {
        return !st.empty();
    }
//-------------------------------------------------
int main()
{
    struct node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    //cout<<"-----"<<minValue(root)<<endl;
    //cout<<"___"<<findCeil(root,61)<<endl;
    //cout<<"___"<<floor(root,61)<<endl;
    //cout<<"-----"<<kthSmallest(root,1)<<endl;
    //cout<<"-----"<<kthSmallest(root,2)<<endl;
    //cout<<"-----"<<kthSmallest(root,3)<<endl;
    //deleteNode(root,60);
    // cout<<"*** "<<kthLargest(root,1)<<endl;
    // cout<<"*** "<<kthLargest(root,2)<<endl;
    // cout<<"*** "<<kthLargest(root,3)<<endl;
    int key = 6;
 
    // Searching in a BST
    if (search(root, key) == NULL)
        cout << key << " not found" << endl;
    else
        cout << key << " found" << endl;
 
    key = 60;
 
    // Searching in a BST
    if (search(root, key) == NULL)
        cout << key << " not found" << endl;
    else
        cout << key << " found" << endl;

}