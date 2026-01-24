#ifndef FLATTEN_NODE_H
#define FLATTEN_NODE_H

struct Node {
  int data;
  struct Node *next;
  struct Node *bottom;

  Node(int x) {
    data = x;
    next = NULL;
    bottom = NULL;
  }
};

#endif // FLATTEN_NODE_H

