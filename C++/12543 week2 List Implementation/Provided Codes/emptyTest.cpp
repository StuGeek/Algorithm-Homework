#include "List.h"
#include <iostream>
#include <string.h>

using namespace std;

template <typename T>
List<T>::List(){
    head = nullptr;
    theSize = 0;
}

template <typename T>
List<T>::~List(){
    clear();
}

template <typename T>
List<T>::List(const List &l){
    head = l.head;
    theSize = l.theSize;
}

template <typename T>
const List<T> & List<T>::operator=(const List<T> &l){
    clear();
    head = l.head;
    theSize = l.theSize;
    return l;
}

template <typename T>
void List<T>::clear(){
    Ptr t = head;
    while(t != nullptr){
        Ptr temp = t;
        t = t->next;
        delete temp;
    }
    theSize = 0;
}

template <typename T>
List<T>::Ptr List<T>::find(T &x) const{
    Ptr t = head;
    while(t != nullptr){
        if (t->data == x) return t;
        t = t->next;
    }
    return nullptr;
}

template <typename T>
List<T>::Ptr List<T>::insert(List<T>::Ptr position, const T &x){
    if (position == 0) push_front(x);
    else{
        Ptr t = head;
        while(t->next != nullptr){
            t = t->next;
        }
        Ptr temp = new Node(x, nullptr);
        t->next = temp;
        theSize++;
    }
}

template <typename T>
void List<T>::push_front(const T &x){
    Ptr t = new Node(x, head);
    head = t;
    theSize++;
}

template <typename T>
void List<T>::push_back(const T &x){
    if (theSize == 0) push_front(x);
    else{
        Ptr t = head;
        while(t->next != nullptr){
            t = t->next;
        }
        Ptr temp = new Node(x, nullptr);
        t->next = temp;
        theSize++;
    }
}

template <typename T>
T & List<T>::front(){
    return head->data;
}

template <typename T>
T & List<T>::back(){
    Ptr t = head;
    while(t->next != nullptr){
        t = t->next;
    }
    return t->data;
}

template <typename T>
void List<T>::traverse(void (*visit)(T &)){
    Ptr t = head;
    for (int i = 0; i < theSize; ++i){
        (*visit)(t->data);
        t = t-> next;
    }
}

template <typename T>
List<T>::Ptr List<T>::advance(List<T>::Ptr p){
    return p->next;
}

template <typename T>
List<T>::Ptr List<T>::erase(List<T>::Ptr position){
    if (head == position) {
        Ptr t = head;
        head = head->next;
        delete t;
        theSize--;
        return t;
    }
    Ptr t = head;
    Ptr temp = head->next;
    for (int i = 0; i < theSize - 1; ++i){
        if (temp == position){
            t->next = temp->next;
            delete temp;
            theSize--;
            return temp;
        }
        t = temp;
        temp = temp->next;
    }
    return nullptr;
}