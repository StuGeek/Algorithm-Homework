#include <iostream>
using namespace std;

template <typename Node_entry>struct Node {
//  data members
   Node_entry entry;
   Node *next;
//  constructors
   Node(){next = NULL;};
   Node(Node_entry item, Node *add_on = NULL){entry = item; next = add_on;};
};

