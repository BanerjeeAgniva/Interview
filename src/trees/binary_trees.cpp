#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "../../include/tree_node.h"

using namespace std;

// Function declarations
void preorder(Node* root, vector<int>& arr);
vector<int> preOrder(Node* root);
void inorder(Node* root, vector<int>& arr);
vector<int> inOrder(Node* root);
void postorder(Node* root, vector<int>& arr);
vector<int> postOrder(Node* root);
vector<vector<int>> levelOrder(Node* root);
int maxDepth(Node* root);
int dfsHeight(Node* root);
bool isBalanced(Node* root);
int countNodes(TreeNode* root);

// Main function
int main()
{
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    vector<int> result = preOrder(root);

    cout << "Preorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}

// Function definitions
void preorder(Node* root, vector<int>& arr) {
    if (root == nullptr) {
        return;
    }
    arr.push_back(root->data);
    preorder(root->left, arr);
    preorder(root->right, arr);
}

vector<int> preOrder(Node* root) {
    vector<int> arr;
    preorder(root, arr);
    return arr;
}

void inorder(Node* root, vector<int>& arr) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left, arr);
    arr.push_back(root->data);
    inorder(root->right, arr);
}

vector<int> inOrder(Node* root) {
    vector<int> arr;
    inorder(root, arr);
    return arr;
}

vector<int> inorderIterative(Node* root) {
    vector<int> arr;
    stack<Node*> s;
    Node* curr = root;
    while (true) {
        if (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        } else {
            if (s.empty()) break;
            curr = s.top();
            s.pop();
            arr.push_back(curr->data);
            curr = curr->right;
        }
    }
    return arr;
}

void postorder(Node* root, vector<int>& arr) {
    if (root == NULL) {
        return;
    }
    postorder(root->left, arr);
    postorder(root->right, arr);
    arr.push_back(root->data);
}

vector<int> postOrder(Node* root) {
    vector<int> arr;
    postorder(root, arr);
    return arr;
}

vector<vector<int>> levelOrder(Node* root) {
    vector<vector<int>> ans;
    if (root == nullptr) {
        return ans;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; i++) {
            Node* node = q.front();
            q.pop();
            level.push_back(node->data);
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
        }
        ans.push_back(level);
    }
    return ans;
}

int maxDepth(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return 1 + max(lh, rh);
}

int dfsHeight(Node* root) {
    // Base case: if the current node is NULL, // return 0 (height of an empty tree)
    if (root == NULL) return 0;
    // Recursively calculate the // height of the left subtree
    int leftHeight = dfsHeight(root->left);
    // If the left subtree is unbalanced, // propagate the unbalance status
    if (leftHeight == -1) return -1;
    // Recursively calculate the // height of the right subtree
    int rightHeight = dfsHeight(root->right);
    // If the right subtree is unbalanced, // propagate the unbalance status
    if (rightHeight == -1) return -1;
    // Check if the difference in height between // left and right subtrees is greater than 1
    // If it's greater, the tree is unbalanced, // return -1 to propagate the unbalance status
    if (abs(leftHeight - rightHeight) > 1)  return -1;
    // Return the maximum height of left and // right subtrees, adding 1 for the current node
    return max(leftHeight, rightHeight) + 1;
}

bool isBalanced(Node* root) {
    // Check if the tree's height difference
    // between subtrees is less than 2
    return dfsHeight(root) != -1;
}
//---------- Count Nodes in a Binary Tree ----------//
// worst case O(n) TC , O(h) SC --> skewed tree
int countNodes(TreeNode* root) { 
    if(root==nullptr) return 0;
    if(root->left==nullptr && root->right==nullptr) return 1;
    return 1+countNodes(root->left)+countNodes(root->right);
}

// count nodes in a complete binary tree
// most optimal --> O(log n * log n) TC , space complexity O(log n) --> recursion stack 

int leftHeight(TreeNode* root) {
    int h = 0;
    while (root) {
        h++;
        root = root->left;
    }
    return h;
}

int rightHeight(TreeNode* root) {
    int h = 0;
    while (root) {
        h++;
        root = root->right;
    }
    return h;
}

int countNodescompleteBT(TreeNode* root) {
    if (!root) return 0;

    int lh = leftHeight(root);
    int rh = rightHeight(root);

    // Perfect binary tree
    if (lh == rh)
        return (1 << lh) - 1;

    // Otherwise recurse
    return 1 + countNodescompleteBT(root->left) + countNodescompleteBT(root->right);
}

/*
Example Tree (Complete but not Perfect):

            1
          /   \
         2     3
        / \   /
       4   5 6

We want to count number of nodes using the optimal algorithm.

--------------------------------------------------

Call: countNodes(1)

At node 1:
Left height:
1 -> 2 -> 4 -> NULL   => lh = 3

Right height:
1 -> 3 -> NULL       => rh = 2

Since lh != rh, tree is NOT perfect.
So:
count(1) = 1 + count(2) + count(3)

--------------------------------------------------

Call: countNodes(2)

Subtree:
    2
   / \
  4   5

Left height:
2 -> 4 -> NULL   => lh = 2

Right height:
2 -> 5 -> NULL   => rh = 2

Since lh == rh, subtree is PERFECT.
So:
count(2) = 2^2 - 1 = 3

(No further recursion on this subtree)

--------------------------------------------------

Call: countNodes(3)

Subtree:
  3
 /
6

Left height:
3 -> 6 -> NULL   => lh = 2

Right height:
3 -> NULL       => rh = 1

Since lh != rh, NOT perfect.
So:
count(3) = 1 + count(6) + count(NULL)

--------------------------------------------------

Call: countNodes(6)

Subtree:
6

Left height:
6 -> NULL   => lh = 1

Right height:
6 -> NULL   => rh = 1

Since lh == rh, PERFECT.
So:
count(6) = 2^1 - 1 = 1

--------------------------------------------------

Now combine results:

count(3) = 1 + 1 + 0 = 2
count(1) = 1 + 3 + 2 = 6

--------------------------------------------------

Final Answer:
Total number of nodes = 6

Key Insight:
We directly counted large perfect subtrees using:
2^height - 1

This avoids visiting every node and gives:
Time Complexity = O((log n)^2)
*/

//------------------------------------------------------------//

    int height(TreeNode* root)
    {
        if(root==NULL) return 0;
        return 1+max(height(root->left),height(root->right));
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if(root==NULL) return 0;
        return max(height(root->left)+height(root->right),
               max(diameterOfBinaryTree(root->left),
                   diameterOfBinaryTree(root->right)));
    }
    // O(n^2)
    //-------------------------
    /*
Idea :  more efficient strategy is to calculate these heights in a bottom-up fashion using a Postorder traversal. This technique enables the validation of balance conditions and the computation of the diameter simultaneously during the traversal.    
    */
    int heightOptimized(TreeNode* root, int& diameter)
    {                                   //passed as reference 
        if(root==NULL) return 0;
        int leftsubtreeheight=heightOptimized(root->left,diameter);
        int rightsubtreeheight=heightOptimized(root->right,diameter);
        //update diameter at each node while calculating height
        diameter=max(diameter,leftsubtreeheight+rightsubtreeheight);
        // return height
        return 1+max(leftsubtreeheight,rightsubtreeheight);
    }
    int diameterOfBinaryTreeOptimized(TreeNode* root) {
        int diameter=0;
        heightOptimized(root,diameter);
        return diameter;
    }
    /*
Time Complexity
O(n) The height function visits each node exactly once in a post-order traversal. Therefore, the time complexity is proportional to the number of nodes, n.
Space Complexity
O(h) In the worst case (a skewed tree), the recursion stack can go as deep as the height of the tree, h. In a balanced tree, h is log n. Thus, the space complexity is O(h).
    */
// ----------------------------------------------------------------

