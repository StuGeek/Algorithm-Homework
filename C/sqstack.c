#include <stdio.h>
#include <stdlib.h>

typedef int TYPE;

typedef struct sqstack{
    TYPE *data;
    int top;
    int capacity;
} *SqStack;

SqStack creat_sqstack(){
    SqStack stk = (SqStack)malloc(sizeof(struct sqstack));
    stk->data = (TYPE *)malloc(100 * sizeof(TYPE));
    stk->top = 0;
    stk->capacity = 100;
    return stk;
}

void double_size(SqStack stk){
    TYPE *t;
    t = (TYPE *)malloc(stk->capacity * 2 * sizeof(TYPE));
    for (int i = 0; i < stk->top; ++i){
        t[i] = stk->data[i];
    }
    free(stk->data);
    stk->data = t;
    stk->capacity *= 2;
}

void push(SqStack stk, TYPE val){
    if (stk->top == stk->capacity) double_size(stk);
    stk->data[stk->top++] = val;
}

void pop(SqStack stk){
    if (stk->top == 0) return;
    stk->top--;
}

int empty(SqStack stk){
    if (stk->top == 0) return 1;
    else return 0;
}

int top(SqStack stk){
    if (stk->top == 0) return 0;
    return stk->data[stk->top - 1];
}

int size(SqStack stk){
    return stk->top;
}

void printSqStack(SqStack stk){
    for (int i = 0; i < stk->top; ++i){
        printf("%d ", stk->data[i]);
    }
}

void freeSqStack(SqStack stk){
    free(stk->data);
    if (stk != NULL){
        free(stk);
    }
    stk = NULL;
}

int main(){
    SqStack stk = creat_sqstack();
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
    printSqStack(stk);
    freeSqStack(stk);
}



