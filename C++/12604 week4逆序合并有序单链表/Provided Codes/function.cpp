#include "function.h"

using namespace std;

Node *reverseList(Node *head) {
    if (head == nullptr || head->next == nullptr) return head;
    Node *pre_node = nullptr;
    Node *curr_node = head;
    while (curr_node != nullptr) {
        Node *next_node = head->next;
        curr_node->next = pre_node;
        pre_node = curr_node;
        curr_node = next_node;
    }
    return curr_node;
}

Node* ReverseMergeList(Node* list1, Node* list2){
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;
    Node *p = list1;
    Node *q = list2;
    Node *temp;
    if (list1->val > list2->val) temp = list2;
    else temp = list1;
    if ()
    while(p != nullptr && q != nullptr){
        if (p->val > q->val){
            Node *t = q->next;
            q->next = p;
            q = t;
        }
        else{
            Node *t = p->next;
            p->next = q;
            p = t;
        }
    }
    return reverseList(temp);
}