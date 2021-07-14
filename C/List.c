#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
} *List;

List creat_List(){
    List head = (List)malloc(sizeof(struct node));
    head->next = NULL;
    return head;
}

int getValue(List myList,int index)
{
    if (index < 0 || myList->next == NULL) return 0;
    List t = myList->next;
    for (int i = 0; i < index; ++i){
        t = t->next;
        if (t == NULL) return 0;
    }
    return t->value;
}

void addAtHead(List myList,int val)
{
    List new_Node = (List)malloc(sizeof(struct node));
    new_Node->value = val;
    new_Node->next = myList->next;
    myList->next = new_Node;
}

void addAtTail(List myList,int val)
{
    List new_Node = (List)malloc(sizeof(struct node));
    new_Node->value = val;
    new_Node->next = NULL;
    List t = myList;
    while(t -> next != NULL){
        t = t->next;
    }
    t->next = new_Node;
}

int addAtIndex(List myList,int index,int val)
{
    List new_Node = (List)malloc(sizeof(struct node));
    new_Node->value = val;
    List t = myList;
    for (int i = 0; i < index; ++i){
        t = t->next;
    }
    new_Node->next = t->next;
    t->next = new_Node;
    return 1;
}

int deleteAtHead(List myList)
{
    if (myList == NULL || myList->next == NULL) return 0;
    List t = myList->next;
    myList->next = myList->next->next;
    free(t);
    t = NULL;
    return 1;
}

int deleteAtIndex(List myList,int index)
{
    List pre = myList;
    List t = myList->next;
    while(index--){
        pre = pre->next;
        t = t->next;
        if (t == NULL) return 0;
    }
    pre->next = pre->next->next;
    free(t);
    t = NULL;
    return 1;
}

void reverseList(List myList)
{
    if (myList == NULL || myList->next == NULL || myList->next->next == NULL) return;
    List pre_node = myList->next;
    List cur_node = myList->next->next;
    pre_node->next = NULL;
    while(cur_node != NULL){
        List t = cur_node->next;
        cur_node->next = pre_node;
        pre_node = cur_node;
        cur_node = t;
    }
    myList->next = pre_node;
}

void printList(List myList)
{
    List t = myList->next;
    while(t != NULL){
        printf("%d ", t->value);
        t = t->next;
    }
}

void freeList(List myList)
{
    List t = myList;
    while(t != NULL){
        myList = myList->next;
        free(t);
        t = myList; 
    }
}

int main(){
    List list = creat_List();
    addAtHead(list, 1);
    addAtTail(list, 3);
    addAtHead(list, 4);
    addAtTail(list, 2);
    addAtIndex(list, 1, 5);
    addAtIndex(list, 0, 6);
    addAtIndex(list, 6, 7);
    reverseList(list);
    printList(list);
    freeList(list);
}