#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

struct dnode {
  int val;
  struct dnode *next = NULL;
  struct dnode *prev = NULL;
};

#endif // DOUBLY_LINKED_LIST_NODE_H

