#include "ListNode.h"

using namespace std;

ListNode *reverseList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode *pre_node = nullptr;
    ListNode *curr_node = head;
    while (curr_node != nullptr) {
        ListNode *next_node = head->next;
        curr_node->next = pre_node;
        pre_node = curr_node;
        curr_node = next_node;
    }
    return curr_node;
}