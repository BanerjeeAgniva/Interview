#include <bits/stdc++.h>
#include "../../include/bst_node.h"
using namespace std;

// ------------------ Function Prototypes ------------------

struct node* newnode(int val);
struct node* insert(struct node* root, int to_be_inserted);
struct node* search(struct node* root, int x);
int minValue(struct node* root);

// FLOOR AND CEIL
int findCeil(struct node* root, int input);
int floor(struct node* root, int x);
void findFloorCeil(TreeNode* root, int key, int& floor, int& ceil);
vector<int> floorCeilOfBST(TreeNode* root, int key);

// DELETE, KTH, VALID BST
struct node* deleteNode(struct node* root, int key);
int kthSmallest(struct node* root, int k);
int kthLargest(struct node* root, int k);
bool func(struct node* root, struct node* lb, struct node* rb);
bool isValidBST(struct node* root);

// LCA, SUCCESSOR
struct node* lowestCommonAncestor(struct node* root, struct node* p, struct node* q);
struct node* inOrderSuccessor(struct node* root, struct node* x);

// BST FROM PREORDER
struct node* func(struct node* lower, vector<int>& pre, int& i, struct node* upper);
struct node* bstFromPreorder(vector<int>& preorder);

// ITERATOR
void BSTIterator(struct node* root);
int next();
bool hasNext();

// ---------------------------------------------------------

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

// ================= FUNCTION DEFINITIONS AFTER MAIN =================

struct node* newnode(int val)
{
    struct node* temp = new struct node;
    temp->left = NULL;
    temp->value = val;
    temp->right = NULL;
    return temp;
}

struct node* insert(struct node* root, int to_be_inserted)
{
    if (root == NULL) return newnode(to_be_inserted);
    if (root->value < to_be_inserted) root->right = insert(root->right, to_be_inserted);
    else root->left = insert(root->left, to_be_inserted);
    return root;
}

struct node* search(struct node* root, int x)
{
    if (root == NULL) return NULL;
    if (root->value > x) return search(root->left, x);
    else if (root->value < x) return search(root->right, x);
    else return root;
}

int minValue(struct node* root)
{
    if (root->left == NULL) return root->value;
    else return minValue(root->left);
}

//--------------------------------------------------
//------- FLOOR AND CEIL IN BST ----------------------
int findCeil(struct node* root, int input) {
    int ans = -1;
    while (root) {
        if (root->value < input) root = root->right;
        else {
            if (root->value == input) return input;
            ans = root->value;
            root = root->left;
        }
    }
    return ans;
}

int floor(struct node* root, int x)
{
    int ans = -1;
    while (root)
    {
        if (root->value > x)
        {
            root = root->left;
        }
        else
        {
            if (root->value == x)
            {
                return x;
            }
            ans = root->value;
            root = root->right;
        }
    }
    return ans;
}

// Floor and ceil in one iteration (Most optimal)
void findFloorCeil(TreeNode* root, int key, int& floor, int& ceil) {
    floor = -1;
    ceil = -1;

    while (root) {
        if (root->data == key) {
            floor = root->data;
            ceil = root->data;
            return;
        }
        else if (key < root->data) {
            ceil = root->data;  // potential ceil
            root = root->left; // Why does this not screw up the calculation of floor?
            //
        }
        else {                // x > root->data
            floor = root->data;  // potential floor
            root = root->right;
        }
    }
}

vector<int> floorCeilOfBST(TreeNode* root, int key) {
    int floor = -1;
    int ceil = -1;
    findFloorCeil(root, key, floor, ceil);
    return { floor,ceil };
}

/*
    20
   /  \
 10    30
   \
    15

Find floor/ceil of x = 17

We traverse the BST iteratively:

Start at root = 20
- 17 < 20 → this node can be a ceil
  ceil = 20
  move left

At node = 10
- 17 > 10 → this node can be a floor
  floor = 10
  move right

At node = 15
- 17 > 15 → this node can be a floor
  floor = 15
  move right

At node = null → stop

Final Answer:
floor = 15
ceil  = 20
*/

//---------------------------------------------------
struct node* deleteNode(struct node* root, int key)
{
    if (root == NULL) return NULL;
    if (root->value > key) root->left = deleteNode(root->left, key);
    else if (root->value < key) root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL && root->right == NULL) return NULL;
        if (root->left == NULL) return root->right;
        if (root->right == NULL) return root->left;
        struct node* lst = root->left;
        struct node* rst = root->right;
        // Attach leftsubtree to the leftmost child of the rightsubtree
        struct node* lmcrst = rst;
        while (lmcrst->left) lmcrst = lmcrst->left;
        lmcrst->left = lst;
        return rst;
    }
    return root;
}

int kthSmallest(struct node* root, int k) {
    stack<struct node*> st;
    struct node* temp = root;
    while (k--)
    {
        while (temp)
        {
            st.push(temp);
            temp = temp->left;
        }
        temp = st.top();
        st.pop();
        if (k == 0) return temp->value;
        temp = temp->right;
    }
    return -1;
}

int kthLargest(struct node* root, int k) {
    stack<struct node*> st;
    while (k--)
    {
        while (root)
        {
            st.push(root);
            root = root->right;
        }
        root = st.top();
        st.pop();
        if (k == 0) return root->value;
        root = root->left;
    }
    return -1;
}

//-------------------------------------------------------------------------------
bool func(struct node* root, struct node* lb, struct node* rb)
{
    if (root == NULL) return true;
    // THE ROOT VALUE SHOULD BE WITHIN THE LEFT AND THE RIGHT BOUNDARY
    if (lb && root->value <= lb->value) return false;
    if (rb && root->value >= rb->value) return false;
    return func(root->left, lb, root) && func(root->right, root, rb);

}

bool isValidBST(struct node* root) {
    return func(root, NULL, NULL);
}

//-------------------------------------------------------------------------------
struct node* lowestCommonAncestor(struct node* root, struct node* p, struct node* q) {
    if (root == NULL) return NULL;
    if (p->value > root->value && q->value > root->value) return lowestCommonAncestor(root->right, p, q);
    else if (p->value < root->value && q->value < root->value)return lowestCommonAncestor(root->left, p, q);
    return root;
}

struct node* inOrderSuccessor(struct node* root, struct node* x)
{
    struct node* ans = NULL;
    while (root != x)
    {
        if (root->value > x->value) {
            ans = root;
            root = root->left;
        }
        else root = root->right;
    }
    if (root->right) {
        root = root->right;
        while (root->left) {
            root = root->left;
        }
        return root;
    }
    return ans;
}

//--------------------------------------------------------------------------
struct node* func(struct node* lower, vector<int>& pre, int& i, struct node* upper)
{
    if (i == pre.size() || (upper && pre[i] > upper->value)) return NULL;
    struct node* node = newnode(pre[i++]);
    node->left = func(lower, pre, i, node);
    node->right = func(node, pre, i, upper);
    return node;
}

struct node* bstFromPreorder(vector<int>& preorder) {
    int i = 0;
    return func(NULL, preorder, i, NULL);
}

//------------------------------------------------------------------------------
stack<struct node*> st;
struct node* x;

void BSTIterator(struct node* root) {
    x = root;
    while (x) {
        st.push(x);
        x = x->left;
    }
}

int next() {
    int ans = st.top()->value;
    x = st.top();
    st.pop();
    x = x->right;
    while (x)
    {
        st.push(x);
        x = x->left;
    }
    return ans;
}

bool hasNext() {
    return !st.empty();
}
