#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <float.h>

#define TYPE int
#define BOOL int
#define TRUE 1
#define FALSE 0
#define QUEUE_SIZE 100

const int M = 8;

//有序队列
typedef struct ordered_queue{
    TYPE queue[QUEUE_SIZE];
    int front;
    int rear;
}*Ordered_Queue;

int compare(const void*a,const void*b){
    return *(int*)a-*(int*)b;
}

//根据一个有序数组创建一个有序队列
Ordered_Queue creat_Ordered_Queue(TYPE *data, int n){
    Ordered_Queue q = (Ordered_Queue)malloc(n * sizeof(struct ordered_queue));
    for (int i = 0; i < n; ++i){
        q->queue[i] = data[i];
    }
    //有序队列的队首为0
    q->front = 0;
    //队尾与元素个数相同
    q->rear = n;
    return q;
}

//当队首和队尾相同时，有序队列为空
BOOL empty(Ordered_Queue q){
    if (q->front == q->rear) return TRUE;
    else return FALSE;
}

//弹出队首元素，即删除最小元素
void pop_back(Ordered_Queue q){
    if (empty(q)) return;
    else q->front++;
}

//取有序队列的队首元素，即最小值
TYPE top(Ordered_Queue q){
    return q->queue[q->front];
}

//将有序队列组初始化为小顶堆，堆结点的值是其对应队列的队首元素的值
void initial_min_heap(Ordered_Queue *queues, int n){
    for (int i = n / 2 - 1; i >= 0; --i){
		Ordered_Queue q = queues[i];
        //取有序队列的队首值，即最小值
        TYPE q_top = top(q);
        int p = i;
        int child = (i << 1) + 1;
        while(child < n){
            //选择儿子结点中较小的那个结点
            if (child + 1 < n && top(queues[child]) > top(queues[child + 1])){
                child = child + 1;
            }
            //如果分支结点的值更大，进行调整
            if (q_top > top(queues[child])){
                queues[p] = queues[child];
                p = child;
                child = (p << 1) + 1;
            }
            else break;
        }
        queues[p] = q;
    }
}

//如果队列为空，删除堆顶结点，将堆尾结点作为新的堆顶
void pop(Ordered_Queue *queues, int n){
    //小顶堆为空，直接返回
    if (n == 0) return;
    int high, low;
    //获取小顶堆数组的最后一个元素
	Ordered_Queue q = queues[--n];
    queues[n] = queues[0];
	TYPE q_top = top(q);
    for (high = 0; (high << 1) + 1 < n; high = low){
        //从根结点开始，high为父亲结点的位置，low为左儿子的位置
        low = (high << 1) + 1;
        //选择儿子结点中较小的那个结点
        if (low != n - 1 && top(queues[low]) > top(queues[low + 1])){
            low += 1;
        }
        //如果这个结点比小顶堆数组的最后一个元素小，那么将这个结点放到它的父亲结点
        if (top(queues[low]) < q_top){
            queues[high] = queues[low];
        }
        else break;
    }
    //比较结束后直接将最后一个元素放到最后一次比较比最后一个元素大的结点的父亲结点的位置
    queues[high] = q;
}

//成功时队首元素被更新并仍然由堆顶结点描述,失败时队列为空，此时删除堆顶结点，将堆尾结点作为新的堆顶
BOOL Dequeue(Ordered_Queue *queues, int n){
    pop_back(queues[0]);
    if (empty(queues[0])){
        pop(queues, n);
        return FALSE;
    }
    return TRUE;
}

//统计有序队列组的总大小，方便确定归并排序后的数组的大小
int sumOfSize(Ordered_Queue *queues){
    int res = 0;
    for (int i = 0; i < M; ++i){
        res += queues[i]->rear;
    }
    return res;
}

//M路归并排序返回有序数组
TYPE* M_way_mergeSort(Ordered_Queue *queues, int sumofSize){
    int n = M;
    TYPE *t = (TYPE *)malloc(sumofSize * sizeof(TYPE));
    initial_min_heap(queues, n);
    int i = 0;
    while(n != 0){
        //堆顶结点的值即为当前的最小值
        t[i++] = top(queues[0]);
        //队列为空后将结点删除
        if (!Dequeue(queues, n)){
            n--;
        }
        //重新初始化小顶堆
        initial_min_heap(queues, n);
    }
    return t;
}

//打印归并排序后的数组元素
void print(int *a, int n){
    for (int i = 0; i < n; ++i){
        printf("%d ", a[i]);
    }
    printf("\n");
}

//释放有序队列组的动态内存
void free_Ordered_Queue(Ordered_Queue *q){
    if (q != NULL){
        for (int i = 0; i < M; ++i){
            if (q[i] != NULL){
                free(q[i]);
                q[i] = NULL;
            }
        }
    }
}

int main() {
    //创建有序队列组
    Ordered_Queue *q = (Ordered_Queue *)malloc(M * sizeof(Ordered_Queue));
    srand((unsigned) time(NULL));
    int sumofSize = 0;
    for (int i = 0; i < M; ++i){
        //随机生成8个长度为1~10，数据范围为0~99的有序队列
        q[i] = (Ordered_Queue)malloc(sizeof(struct ordered_queue));
        int n = rand() % 10 + 1;
        sumofSize += n;
        for (int j = 0; j < n; ++j){
            int num = rand() % 100;
            q[i]->queue[j] = num;
        }
        q[i]->front = 0;
        q[i]->rear = n;
        qsort(q[i]->queue, n, sizeof(int), compare);
        printf("ordered queue %d : ", i + 1);
        for (int j = 0; j < n; ++j){
            printf("%d ", q[i]->queue[j]);
        }
        printf("\n");
    }
    //M路归并排序后打印数据
    int *a = M_way_mergeSort(q, sumofSize);
    printf("after M-way Merge Sort:\n");
    print(a, sumofSize);
    free(a);
    a = NULL;
    free_Ordered_Queue(q);
}