#include <stdio.h>
#include <stdlib.h>

typedef int TYPE;

typedef struct queue{
    TYPE *data;
    int front;
    int rear;
    int size;
    int capacity;
} *Queue;

Queue creat_Queue(){
    Queue que = (Queue)malloc(sizeof(struct queue));
    que->data = (TYPE *)malloc(100 * sizeof(TYPE));
    que->front = 0;
    que->rear = -1;
    que->size = 0;
    que->capacity = 100;
    return que;
}

void double_size(Queue que){
    TYPE *t;
    t = (TYPE *)malloc(que->capacity * 2 * sizeof(TYPE));
    int j = 0;
    for (int i = que->front; i < que->rear + 1; i = (i + 1) % que->capacity){
        t[j++] = que->data[i];
    }
    free(que->data);
    que->data = t;
    que->rear = (que->capacity + que->rear - que->front) % que->capacity;
    que->front = 0;
    que->capacity *= 2;
}

void push_back(Queue que, TYPE val){
    if (que->size == que->capacity) double_size(que);
    que->rear = (que->rear + 1) % que->capacity;
    que->data[que->rear] = val;
    que->size++;
}

void pop_back(Queue que){
    if (que->size == 0) return;
    que->front = (que->front + 1) % que->capacity;
    que->size--;
}

int empty(Queue que){
    if (que->size == 0) return 1;
    else return 0;
}

int front(Queue que){
    if (que->size == 0) return 0;
    return que->data[que->front];
}

int size(Queue que){
    return que->size;
}

void printQueue(Queue que){
    int i = que->front;
    int size = que->size;
    while(size--){
        printf("%d ", que->data[i]);
        i = (i + 1) % que->capacity;
    }
}

void freeQueue(Queue que){
    free(que->data);
    if (que != NULL){
        free(que);
    }
    que = NULL;
}

int main(){
    Queue que = creat_Queue();
    push_back(que, 1);
    push_back(que, 3);
    push_back(que, 4);
    push_back(que, 5);
    push_back(que, 6);
    push_back(que, 2);
    pop_back(que);
    pop_back(que);
    printQueue(que);
    freeQueue(que);
}



