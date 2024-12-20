#include <iostream>
using namespace std;
struct node {
  int val;
  struct node *next = NULL;
};
struct node *newnode(int x) {
  struct node *makenode = new struct node;
  makenode->val = x;
  return makenode;
}
struct node *ConstructLL(vector<int> &arr) {
  struct node *root = newnode(arr[0]);
  struct node *temp = root;
  for (int i = 1; i < arr.size(); i++) {
    temp->next = newnode(arr[i]);
    temp = temp->next;
  }
  return root;
}
//----------------------------------------------------

struct dnode {
  int val;
  struct dnode *next = NULL;
  struct dnode *prev = NULL;
};
struct dnode *newdnode(int x) {
  struct dnode *makednode = new struct dnode;
  makednode->val = x;
  return makednode;
}
struct dnode *ConstructDLL(vector<int> &arr) {
  struct dnode *root = newdnode(arr[0]);
  struct dnode *prevdnode = root;
  for (int i = 1; i < arr.size(); i++) {
    struct dnode *currdnode = newdnode(arr[i]);
    prevdnode->next = currdnode;
    currdnode->prev = prevdnode;
    prevdnode = currdnode;
  }
  return root;
}
void add_dnode(struct dnode *root, int pos,
               int data) // add dnode after "pos" index
{
  struct dnode *temp = root;
  while (pos--) {
    temp = temp->next;
  }
  struct dnode *nexxtnode = temp->next;
  struct dnode *newlynode = newdnode(data);
  temp->next = newlynode;
  nexxtnode->prev = newlynode;
  newlynode->next = nexxtnode;
  newlynode->prev = temp;
}
struct dnode *deletednode(struct dnode *root,
                          int x) { // delete dnode at "x" position
  if (x == 1) {                    // HANDLING FIRST NODE DELETION
    root = root->next;
    root->prev = NULL;
    return root;
  }
  x--;
  struct dnode *temp = root;
  //  x=2
  //  1<->2<->3<->4<->5
  //  1<->    3<->4<->5
  while (x--) {
    temp = temp->next;
  }
  struct dnode *prevnode = temp->prev;
  struct dnode *nextnode = temp->next;
  if (nextnode == NULL) // HANDLING LAST NODE DELETION
  {
    prevnode->next = NULL;
    return root;
  }
  prevnode->next = nextnode;
  nextnode->prev = prevnode;
  return root;
}
//---------------------------------------------------
struct dnode *reversednode(struct dnode *root) {
  if (root == NULL || root->next == NULL)
    return root;
  struct dnode *curr = root;
  struct dnode *prevv = NULL;
  struct dnode *nextt = root->next;
  while (nextt) {
    curr->next = prevv;
    curr->prev = nextt;
    prevv = curr;
    curr = nextt;
    nextt = nextt->next;
  }
  //<----- LAST NODE ----->
  curr->next = prevv;
  curr->prev = nextt;
  prevv = curr;
  return prevv;
}
struct node *reversenode(struct node *head) {
  if (head == NULL || head->next == NULL)
    return head;
  struct node *prev = NULL;
  struct node *curr = head;
  struct node *next = head->next;
  while (next) {
    curr->next = prev;
    prev = curr;
    curr = next;
    next = next->next;
  }
  curr->next = prev;
  return curr;
}
struct node *recursivelyreversenode(struct node *root) {
  if (root == NULL || root->next == NULL)
    return root;
  struct node *newhead = recursivelyreversenode(root->next);
  struct node *nextt = root->next;
  nextt->next = root;
  cout << nextt->val << "->next=" << root->val << "\n";
  root->next = NULL;
  return newhead;
}
//--------------------------------------------------
struct node *insertatend(struct node *root, int x) {
  struct node *head = root;
  struct node *xx = newnode(x);
  struct node *temp = root;
  while (temp->next) {
    temp = temp->next;
  }
  temp->next = xx;
  return head;
}
void deleteNode(struct node *x) {
  x->val = x->next->val;
  x->next = x->next->next;
}
int len(struct node *root) {
  struct node *temp = root;
  int ans = 0;
  while (temp) {
    ans++;
    temp = temp->next;
  }
  return ans;
}
bool search(struct node *head, int key) {
  struct node *temp = head;
  while (temp) {
    if (temp->val == key)
      return true;
    temp = temp->next;
  }
  return false;
}
//--------------------------------------------------------
void printLL(struct node *root) {
  struct node *temp = root;
  while (temp) {
    cout << temp->val << " ";
    temp = temp->next;
  }
  cout << "\n";
}
void printDLL(struct dnode *root) {
  struct dnode *temp = root;
  while (temp) {
    cout << temp->val << " ";
    if (temp->prev)
      cout << temp->prev->val << " ";
    else
      cout << "NO PREVIOUS ";
    if (temp->next)
      cout << temp->next->val << " ";
    else
      cout << "NO NEXT ";
    temp = temp->next;
    cout << "\n";
  }
  cout << "\n \n";
}
//---------------------------------------------------------
struct node *middleNode(struct node *head) {
  struct node *slow = head;
  struct node *fast = head;
  while (fast != NULL && fast->next != NULL) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}
bool hasCycle(struct node *head) {
  if (!head)
    return false;
  struct node *tort = head;
  struct node *hare = head->next;
  while (hare && hare->next) {
    if (hare == tort)
      return true;
    tort = tort->next;
    hare = hare->next->next;
  }
  return false;
}
struct node *oddEvenList(struct node *head) {
  if (head == NULL || head->next == NULL)
    return head;
  struct node *h1 = head;
  struct node *h2 = head->next;
  struct node *temp1 = h1;
  struct node *temp2 = h2;
  while (h2) {
    if (h1->next) {
      h1->next = h1->next->next;
      h1 = h1->next;
    }
    h2->next = h2->next->next;
    h2 = h2->next;
  }
  h1->next = temp2;
  return temp1;
}
int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  struct node *root = ConstructLL(v);
  struct dnode *droot = ConstructDLL(v);
  // printDLL(droot);
  // add_dnode(droot,3,100);
  // droot=deletednode(droot,5);
  // struct dnode* rdroot=reversednode(droot);
  // printLL(root);
  // cout<< middleNode(root)->val<<"\n";
  // printDLL(rdroot);
  // insertatend(root,109);
  printLL(root);
  root = oddEvenList(root);
  printLL(root);
  // cout<<len(root)<<"\n";
  // cout<<search(root,4)<<"\n";
}