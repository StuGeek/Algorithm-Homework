#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
}Node;

typedef struct stack{
    Node *top;
    int size;
} *Stack;

Stack creat_stack(){
    Stack stk = (Stack)malloc(sizeof(struct stack));
    stk->top = NULL;
    stk->size = 0;
    return stk;
}

void push(Stack stk, int val){
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = val;
    new_node->next = stk->top;
    stk->top = new_node;
    stk->size++;
}

void pop(Stack stk){
    if (stk->size == 0) return;
    Node *t = stk->top;
    stk->top = stk->top->next;
    stk->size--;
    free(t);
    t = NULL;
}

int empty(Stack stk){
    if (stk->size == 0) return 1;
    else return 0;
}

int top(Stack stk){
    if (stk->size == 0) return 0;
    return stk->top->value;
}

int size(Stack stk){
    return stk->size;
}

void printStack(Stack stk){
    Node *t = stk->top;
    while(t != NULL){
        printf("%d ", t->value);
        t = t->next;
    }
}

void freeStack(Stack stk){
    Node *t = stk->top;
    while(t != NULL){
        stk->top = stk->top->next;
        free(t);
        t = stk->top;
    }    
}

int main(){
    Stack stk = creat_stack();
    push(stk, 1);
    push(stk, 3);
    push(stk, 4);
    push(stk, 5);
    push(stk, 6);
    push(stk, 2);
    pop(stk);
    pop(stk);
    printf("%d ", size(stk));
    printf("%d ", top(stk));
    printStack(stk);
    freeStack(stk);
}



