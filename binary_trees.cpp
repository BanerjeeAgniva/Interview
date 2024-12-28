
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
  Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void preorder(Node *root, vector<int> &arr) {
  if (root == nullptr) {
    return;
  }
  arr.push_back(root->data);
  preorder(root->left, arr);
  preorder(root->right, arr);
}

vector<int> preOrder(Node *root) {
  vector<int> arr;
  preorder(root, arr);
  return arr;
}

void inorder(Node *root, vector<int> &arr) {
  if (root == nullptr) {
    return;
  }
  inorder(root->left, arr);
  arr.push_back(root->data);
  inorder(root->right, arr);
}

vector<int> inOrder(Node *root) {
  vector<int> arr;
  inorder(root, arr);
  return arr;
}

void postorder(Node *root, vector<int> &arr) {
  if (root == NULL) {
    return;
  }
  postorder(root->left, arr);
  postorder(root->right, arr);
  arr.push_back(root->data);
}

vector<int> postOrder(Node *root) {
  vector<int> arr;
  postorder(root, arr);
  return arr;
}

vector<vector<int>> levelOrder(Node *root) {
  vector<vector<int>> ans;
  if (root == nullptr) {
    return ans;
  }
  queue<Node *> q;
  q.push(root);
  while (!q.empty()) {
    int size = q.size();
    vector<int> level;

    for (int i = 0; i < size; i++) {
      Node *node = q.front();
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

//-----
int maxDepth(Node *root) {
  if (root == NULL) {
    return 0;
  }
  int lh = maxDepth(root->left);
  int rh = maxDepth(root->right);
  return 1 + max(lh, rh);
}
//------
int dfsHeight(Node *root) {
  // Base case: if the current node is NULL, // return 0 (height of an empty
  // tree)
  if (root == NULL)
    return 0;
  // Recursively calculate the // height of the left subtree
  int leftHeight = dfsHeight(root->left);
  // If the left subtree is unbalanced, // propagate the unbalance status
  if (leftHeight == -1)
    return -1;
  // Recursively calculate the // height of the right subtree
  int rightHeight = dfsHeight(root->right);
  // If the right subtree is unbalanced, // propagate the unbalance status
  if (rightHeight == -1)
    return -1;
  // Check if the difference in height between // left and right subtrees is
  // greater than 1 If it's greater, the tree is unbalanced, // return -1 to
  // propagate the unbalance status
  if (abs(leftHeight - rightHeight) > 1)
    return -1;
  // Return the maximum height of left and // right subtrees, adding 1 for the
  // current node
  return max(leftHeight, rightHeight) + 1;
}
// Function to check if a binary tree is balanced
bool isBalanced(Node *root) {
  // Check if the tree's height difference
  // between subtrees is less than 2
  return dfsHeight(root) != -1;
}
//----------------------------------------------
int height(Node *node, int &diameter) {
  // Base case: If the node is null,
  // return 0 indicating the
  // height of an empty tree
  if (!node) {
    return 0;
  }

  // Recursively calculate the
  // height of left and right subtrees
  int lh = height(node->left, diameter);
  int rh = height(node->right, diameter);

  // Update the diameter with the maximum
  // of current diameter or sum of
  // left and right heights
  diameter = max(diameter, lh + rh);

  // Return the height of
  // the current node's subtree
  return 1 + max(lh, rh);
}
// Function to find the
// diameter of a binary tree
int diameterOfBinaryTree(Node *root) {
  // Initialize the variable to
  // store the diameter of the tree
  int diameter = 0;
  // Call the height function to traverse
  // the tree and calculate diameter
  height(root, diameter);
  // Return the calculated diameter
  return diameter;
}

int ans = INT_MIN;
// for max path sum
int mps(Node *root) {
  if (root == NULL)
    return 0;
  int leftsubtree = max(0, mps(root->left));   // dont take negative
  int rightsubtree = max(0, mps(root->right)); // dont take negative
  int umbrella =
      root->data + leftsubtree + rightsubtree; // 3 way path  LS---Root---RS
  ans = max(ans, umbrella);
  int currentroot = root->data + max(leftsubtree, rightsubtree);
  cout << umbrella << " " << currentroot << endl;
  return currentroot;
}
int maxPathSum(Node *root) {
  mps(root);
  return ans;
}

int main() {
  /*
  Node* root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(5);
  vector<int> result = preOrder(root);

  cout << "Preorder Traversal: ";
  for(int val : result) {
      cout << val << " ";
  }
  cout << endl;
  */
  Node *root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(5);
  root->left->right->right = new Node(6);
  root->left->right->right->right = new Node(7);
  cout << maxPathSum(root);
  return 0;
}
