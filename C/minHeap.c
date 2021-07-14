#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEAP_SIZE 1024

//创建一个小顶堆，数组的第一个位置用来保存小顶堆的存放元素个数大小值，其它位置用来存元素
int *creat_Heap(){
    int *t = (int *)malloc(sizeof(int) * HEAP_SIZE);
    t[0] = 0;
    return t;
}

//初始化小顶堆
int *initial_min_heap(int *number, int n){
    int *t = (int *)malloc(sizeof(int) * HEAP_SIZE);
    t[0] = n;
    //将数按照顺序放入小顶堆中
    for (int i = 1; i <= n; ++i){
        t[i] = number[i - 1];
    }
    //从最后一个分支结点开始到根，依次对每个分支结点进行调整
    for (int i = n / 2; i >= 1; --i){
        int temp = t[i];
        int p = i;
        int child = i << 1;
        while(child <= n){
            //选择儿子结点中较小的那个结点
            if (child + 1 <= n && t[child] > t[child + 1]){
                child = child + 1;
            }
            //如果分支结点的值更大，进行调整
            if (temp > t[child]){
                t[p] = t[child];
                p = child;
                child = p << 1;
            }
            else break;
        }
        t[p] = temp;
    }
    return t;
}

//向小顶堆中插入数据
void push(int *min_Heap, int n){
    //向数组的第一个无元素的位置插入数据，数组存放元素个数加一
    min_Heap[++min_Heap[0]] = n;
    //记录此时插入元素的位置
    int t = min_Heap[0];
    //如果此时插入元素比它的父亲大，同时插入数据还没有成为根结点，那么将它的父亲保存到小顶堆的位置，插入元素继续向上比较
    while(n < min_Heap[t >> 1] && t > 1){
        min_Heap[t] = min_Heap[t >> 1];
        t >>= 1;
    }
    //比较结束后直接将插入元素放到最后一次比较大于这个插入元素的父亲的位置
    min_Heap[t] = n;
}

//从小顶堆中删除根结点的数据
void pop(int *min_Heap){
    //小顶堆为空，直接返回
    if (min_Heap[0] == 0) return;
    int high, low;
    //获取小顶堆数组的最后一个元素，同时数组存放元素个数减一
    int temp = min_Heap[min_Heap[0]--];
    for (high = 1; high << 1 <= min_Heap[0]; high = low){
        //从根结点开始，high为父亲结点的位置，low为左儿子的位置
        low = high << 1;
        //选择儿子结点中较小的那个结点
        if (low != min_Heap[0] && min_Heap[low] > min_Heap[low + 1]){
            low += 1;
        }
        //如果这个结点比小顶堆数组的最后一个元素小，那么将这个结点放到它的父亲结点
        if (min_Heap[low] < temp){
            min_Heap[high] = min_Heap[low];
        }
        else break;
    }
    //比较结束后直接将最后一个元素放到最后一次比较比最后一个元素大的结点的父亲结点的位置
    min_Heap[high] = temp;
}

//从小顶堆返回最小元素
int top(int *min_Heap){
    return min_Heap[1];
}

//将小顶堆中存入的数据打印出来
void display(int *min_Heap){
    if (min_Heap[0] == 0) printf("小顶堆为空！\n");
    for (int i = 1; i <= min_Heap[0]; ++i){
        printf("min_Heap[%d]: %d\n", i, min_Heap[i]);
    }
}

//释放小顶堆所申请的动态内存
void free_min_heap(int *min_Heap){
    if (min_Heap != NULL){
        free(min_Heap);
        min_Heap = NULL;
    }
}

/*typedef struct heap{
    int *min_heap;
    int size;
} *min_Heap;

//创建一个小顶堆
min_Heap creat_Heap(){
    min_Heap t = (min_Heap)malloc(sizeof(struct heap));
    t->min_heap = (int *)malloc(sizeof(int) * HEAP_SIZE);
    t->size = 0;
    return t;
}

//初始化小顶堆
min_Heap initial_min_heap(int *number, int n){
    min_Heap t = (min_Heap)malloc(sizeof(struct heap));
    t->min_heap = (int *)malloc(sizeof(int) * HEAP_SIZE);
    t->size = n;
    //将数按照顺序放入小顶堆中
    for (int i = 0; i < n; ++i){
        t->min_heap[i] = number[i];
    }
    //从最后一个分支结点开始到根，依次对每个分支结点进行调整
    for (int i = n / 2 - 1; i >= 0; --i){
        int temp = t->min_heap[i];
        int p = i;
        int child = i * 2 + 1;
        while(child < n){
            //选择儿子结点中较小的那个结点
            if (child + 1 < n && t->min_heap[child] > t->min_heap[child + 1]){
                child = child + 1;
            }
            //如果分支结点的值更大，进行调整
            if (temp > t->min_heap[child]){
                t->min_heap[p] = t->min_heap[child];
                p = child;
                child = p * 2 + 1;
            }
            else break;
        }
        t->min_heap[p] = temp;
    }
    return t;
}

//向小顶堆中插入数据
void push(min_Heap t, int n){
    //向数组的第一个无元素的位置插入数据，数组存放元素个数加一
    t->min_heap[t->size++] = n;
    //记录此时插入元素的位置
    int temp = t->size - 1;
    //如果此时插入元素比它的父亲大，同时插入数据还没有成为根结点，那么将它的父亲保存到小顶堆的位置，插入元素继续向上比较
    while(n < t->min_heap[(temp - 1) / 2] && temp > 0){
        t->min_heap[temp] = t->min_heap[(temp - 1) / 2];
        temp = (temp - 1) / 2;
    }
    //比较结束后直接将插入元素放到最后一次比较大于这个插入元素的父亲的位置
    t->min_heap[temp] = n;
}

//从小顶堆中删除根结点的数据
void pop(min_Heap t){
    //小顶堆为空，直接返回
    if (t->size == 0) return;
    int high, low;
    //获取小顶堆数组的最后一个元素，同时数组存放元素个数减一
    int temp = t->min_heap[--t->size];
    for (high = 0; high * 2 + 1 < t->size; high = low){
        //从根结点开始，high为父亲结点的位置，low为左儿子的位置
        low = high * 2 + 1;
        //选择儿子结点中较小的那个结点
        if (low != t->size - 1 && t->min_heap[low] > t->min_heap[low + 1]){
            low += 1;
        }
        //如果这个结点比小顶堆数组的最后一个元素小，那么将这个结点放到它的父亲结点
        if (t->min_heap[low] < temp){
            t->min_heap[high] = t->min_heap[low];
        }
        else break;
    }
    //比较结束后直接将最后一个元素放到最后一次比较比最后一个元素大的结点的父亲结点的位置
    t->min_heap[high] = temp;
}

//从小顶堆返回最小元素
int top(min_Heap t){
    return t->min_heap[0];
}

//将小顶堆中存入的数据打印出来
void display(min_Heap t){
    if (t->size == 0) printf("小顶堆为空！\n");
    for (int i = 0; i < t->size; ++i){
        printf("min_Heap[%d]: %d\n", i, t->min_heap[i]);
    }
}

//释放小顶堆所申请的动态内存
void free_min_heap(min_Heap t){
    if (t != NULL){
        if (t->min_heap != NULL){
            free(t->min_heap);
            t->min_heap = NULL;
        }
        free(t);
        t = NULL;
    }
}*/

int main() {
    int a[20];
    //输入20个随机整数
    /*printf("请输入20个整数：");
    for (int i = 0; i < 20; ++i){
        scanf("%d", &a[i]);
    }*/
    //随机生成20个整数
    srand((unsigned) time(NULL));
    for (int i = 0; i < 20; ++i){
        int num = rand() % 100;
        a[i] = num;
    }
    int *min_Heap = initial_min_heap(a, 20);
    printf("生成的完全小顶堆为：\n");
    display(min_Heap);
    printf("\n");
    printf("\n第1次弹出后：\n");
    pop(min_Heap);
    display(min_Heap);
    printf("\n第2次弹出后：\n");
    pop(min_Heap);
    display(min_Heap);
    printf("\n第3次弹出后：\n");
    pop(min_Heap);
    display(min_Heap);
    free_min_heap(min_Heap);
    /*min_Heap t = initial_min_heap(a, 20);
    printf("生成的完全小顶堆为：\n");
    display(t);
    printf("\n");
    printf("\n第1次弹出后：\n");
    pop(t);
    display(t);
    printf("\n第2次弹出后：\n");
    pop(t);
    display(t);
    printf("\n第3次弹出后：\n");
    pop(t);
    display(t);
    free_min_heap(t);*/
}