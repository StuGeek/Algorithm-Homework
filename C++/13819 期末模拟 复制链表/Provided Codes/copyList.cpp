#include "NodeTemplate.h"

template<typename T>
Node<T>* copyList( const Node<T> *  head ) {
    if (head == nullptr) return nullptr;
    Node<T>* head = new Node<T>(head->entry);
    Node<T>* t = head;
    while (t->next != nullptr) {
        Node<T> *temp = new Node<T>(t->next->entry);
        t->next = temp;
        t = temp;
    }
    return head;
}