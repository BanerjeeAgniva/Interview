#include <iostream>
using namespace std;
//-------------------------------
struct node {
  int val;
  struct node *next = NULL;
};
//-------------------------------
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
// DOUBLE LINKEDLIST //
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
void add_dnode(struct dnode *root, int pos, int data)
// add dnode after "pos" index
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
struct dnode *deletednode(struct dnode *root, int x) {
  // delete dnode at "x" position
  if (x == 1) {
    // HANDLING FIRST NODE DELETION
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
  if (nextnode == NULL) {
    prevnode->next = NULL;
    return root;
  }
  prevnode->next = nextnode;
  if (nextnode != NULL)
    nextnode->prev = prevnode;
  // HANDLING LAST NODE DELETION
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
    curr->prev = nextt; // addn.
    prevv = curr;
    curr = nextt;
    nextt = nextt->next;
  }
  //<----- LAST NODE ----->
  curr->next = prevv;
  curr->prev = nextt; // addn.
  return curr;
}
struct node *reversenode(struct node *head) {
  if (head == NULL || head->next == NULL)
    return head;
  // prev curr next
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
//---------PRINT------------------------------------------
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
//---------PRINT------------------------------------------
//--------------------------------------------------------
// In even number of nodes, the slow will point to the 2nd middle 1->2->3->4
// slow will point to 3 at end
struct node *middleNode(struct node *head) {
  struct node *slow = head;
  struct node *fast = head;
  while (fast != NULL && fast->next != NULL) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}
// In even number of nodes, the slow will point to the first middle
struct node *firstmiddleNode(struct node *head) {
  struct node *slow = head;
  struct node *fast = head;
  while (fast != NULL && fast->next != NULL) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}
/*
Brute force :
take one pointer, go node by node, keep storing the nodes in the map, if you
find a node already present in the map, return that node. TC -> O(2N)   SC->O(N)

Optimal :
Take fast pointer and slow pointer, when the slow pointer has reached the
starting point of the cycle after covering a distance say L, the fast pointer
has covered that distance L and also an extra distance L on the cycle. Let the
distance between the slow pointer and the fast pointer be D in a clockwise
sense. Now the fast pointer is moving towards slow pointer at 2 units speed and
the slow pointer is moving away from the fast pointer at 1 unit speed, so the
distance between them is decreasing by 1 every moment. The distance decreases
like D , D-1 , D-2 , .................. D-D So when the slow pointer and the
fast pointer intersect they will do so at a distance of D from the starting
point in a clockwise sense.

So if we start the fast pointer from the point of intersection in a clockwise
sense and set it at one unit speed and we start the slow pointer from the head
of the linkedlist at one unit speed they will meet at the starting point of the
cycle because both the Distances are L.

TC-->O(N)  SC->O(1)
*/
struct node *hasCycle(struct node *head) { // Node at which cycle begins
  if (!head)
    return NULL;
  struct node *tort = head;
  struct node *hare = head->next;
  while (hare && hare->next) {
    if (hare == tort) // cycle exists
    {
      hare = head;
      while (hare != tort) {
        hare = hare->next;
        tort = tort->next;
      }
      return tort;
    }
    tort = tort->next;
    hare = hare->next->next;
  }
  return NULL;
}
/*
Input: head = [1,2,3,4,5]
Output: [1,3,5,2,4]
Given the head of a singly linked list, group all the nodes with odd INDICES
together followed by the nodes with even INCDICES, and return the reordered
list. The first node is considered odd, and the second node is even, and so on.
*/
struct node *oddEvenList(struct node *head) {
  if (head == NULL || head->next == NULL)
    return head;
  struct node *h1 = head;
  struct node *h2 = head->next;
  struct node *temp1 = h1;
  struct node *temp2 = h2;
  while (h2) {
    if (h1->next) {
      h1->next = h1->next->next; // 1->3->4->5  and also  2->3->4->5
      h1 = h1->next;             //  h1 at 3
    }
    h2->next = h2->next->next; // 1->3->4->5   and 2->4->5
    h2 = h2->next;             //                 h2 at 4
  }
  h1->next = temp2;
  return temp1;
}
/*
SORT LL  <------ IMP
*/
struct node *mergeTwoSortedLinkedLists(struct node *list1, struct node *list2) {
  struct node *dummyNode = newnode(-1);
  struct node *temp = dummyNode;
  while (list1 != nullptr && list2 != nullptr) {
    if (list1->val <= list2->val) {
      temp->next = list1;
      list1 = list1->next;
    } else {
      temp->next = list2;
      list2 = list2->next;
    }
    temp = temp->next;
  }

  if (list1 != nullptr)
    temp->next = list1;
  else
    temp->next = list2;

  return dummyNode->next;
}

struct node *sortLL(struct node *head) {
  if (head == NULL || head->next == NULL)
    return head;
  struct node *middle = firstmiddleNode(head);
  struct node *right = middle->next;
  middle->next = nullptr;
  struct node *left = head;
  left = sortLL(left);
  right = sortLL(right);
  return mergeTwoSortedLinkedLists(left, right);
}

// revise at end --> tough problem --> not intuitive at all
struct node *reverseKGroup(struct node *head, int k) {
  if (head == NULL || k == 1) {
    return head;
  }
  struct node *dummy = newnode(0);
  dummy->next = head;
  struct node *curr = dummy;
  struct node *nex = dummy;
  struct node *point = dummy;

  int count = 0;
  struct node *temp = head;
  while (temp != NULL) {
    temp = temp->next;
    count++;
  }
  while (count >= k) {
    curr = point->next;
    nex = curr->next;
    for (int i = 1; i < k; i++) {
      curr->next = nex->next;
      nex->next = point->next;
      point->next = nex;
      nex = curr->next;
    }
    point = curr;
    count -= k;
  }
  return dummy->next;
}
//------

struct node *rotateRight(struct node *head, int k) {
  if (!head)
    return head;
  struct node *ans = head;
  int count = 1;
  while (ans->next) {
    ans = ans->next;
    count++;
  }
  ans->next = head;
  ans = ans->next;
  count = count - (k % count) - 1;
  while (count--)
    ans = ans->next;
  head = ans->next;
  ans->next = NULL;
  return head;
}
// Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]
//------

/* Node structure  used in the program

struct Node{
    int data;
    struct Node * next;
    struct Node * bottom;

    Node(int x){
        data = x;
        next = NULL;
        bottom = NULL;
    }

};
*/
//----Flatten LL----//
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
Node *merge(Node *a, Node *b) {
  Node *res = new Node(-1);
  Node *temp = res;
  while (a && b) {
    if (a->data < b->data) {
      temp->bottom = a;
      a = a->bottom;
    } else {
      temp->bottom = b;
      b = b->bottom;
    }
    temp = temp->bottom;
  }
  if (a)
    temp->bottom = a;
  else
    temp->bottom = b;
  return res->bottom;
}
// Function which returns the  root of the flattened linked list.
Node *flatten(Node *root) {
  if (root == NULL || root->next == NULL)
    return root;
  root->next = flatten(root->next);
  root = merge(root, root->next);
  return root;
}
//------
/*
segregate LL of 0,1,2s into 0s first then 1s then 2s
Just make 3 counters count0, count1, count2
*/
/*
https://leetcode.com/problems/copy-list-with-random-pointer/description/  -->
Copy List with Random Pointer
*/
int main() {
  cout << "Size of node: " << sizeof(node) << " bytes" << endl;
  /*
int val: Typically 4 bytes.
struct node* next: 4 bytes on a 32-bit system, 8 bytes on a 64-bit system.
Padding:
On most platforms, pointers require alignment to their size (4 or 8 bytes).
If int is 4 bytes and a pointer is 8 bytes (64-bit)
the compiler will add 4 bytes of padding after int to align the pointer.
Total Size (Assuming 64-bit System):
int (4 bytes) + Padding (4 bytes) = 8 bytes.
Pointer (struct node*) (8 bytes) = 8 bytes.
Total = 8 (val + padding) + 8 (next) = 16 bytes.
  */
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