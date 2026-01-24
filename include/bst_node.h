#ifndef BST_NODE_H
#define BST_NODE_H

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

struct node {
    node* left;
    int value;
    node* right;
};

#endif // BST_NODE_H

