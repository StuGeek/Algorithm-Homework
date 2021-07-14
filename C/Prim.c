#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <float.h>

#define EDGE_TYPE int
#define VERTEX_TYPE int
#define BOOL int
#define TRUE 1
#define FALSE 0
#define INF 0x3F3F3F3F

typedef struct node{
    int to;
    EDGE_TYPE dis;
    struct node *next;
} *List;

typedef struct adjacency_list{
    List *head;
    VERTEX_TYPE data;
} *Adjacency_List;

typedef struct heap{
    List *min_heap;
    int size;
} *min_Heap;

//创建空链表
List creat_List() {
    List head = (List)malloc(sizeof(struct node));
    head->next = NULL;
    return head;
}

//在链表的头添加元素
void addAtHead(List myList, int to, EDGE_TYPE dis) {
    List new_Node = (List)malloc(sizeof(struct node));
    new_Node->to = to;
    new_Node->dis = dis;
    new_Node->next = myList->next;
    myList->next = new_Node;
}

//释放链表所申请的动态内存
void freeList(List myList) {
    List t = myList;
    while(t != NULL){
        myList = myList->next;
        free(t);
        t = myList; 
    }
}

//创建一个小顶堆
min_Heap creat_Heap(int numOfEdges){
    min_Heap t = (min_Heap)malloc(sizeof(struct heap));
    t->min_heap = (List *)malloc(sizeof(List) * numOfEdges);
    t->size = 0;
    return t;
}

//向小顶堆中插入数据
void push_heap(min_Heap t, List node){
    //向数组的第一个无元素的位置插入数据，数组存放元素个数加一
    t->min_heap[t->size++] = node;
    //记录此时插入元素的位置
    int temp = t->size - 1;
    //如果此时插入元素的权值比它的父亲大，同时插入数据还没有成为根结点，那么将它的父亲保存到小顶堆的位置，插入元素继续向上比较
    while(node->dis < t->min_heap[(temp - 1) / 2]->dis && temp > 0){
        t->min_heap[temp] = t->min_heap[(temp - 1) / 2];
        temp = (temp - 1) / 2;
    }
    //比较结束后直接将插入元素放到最后一次比较大于这个插入元素的权值的父亲的位置
    t->min_heap[temp] = node;
}

//从小顶堆中删除根结点的数据
void pop_heap(min_Heap t){
    //小顶堆为空，直接返回
    if (t->size == 0) return;
    int high, low;
    //获取小顶堆数组的最后一个元素，同时数组存放元素个数减一
    List temp = t->min_heap[--t->size];
    t->min_heap[t->size] = t->min_heap[0];
    for (high = 0; high * 2 + 1 < t->size; high = low){
        //从根结点开始，high为父亲结点的位置，low为左儿子的位置
        low = high * 2 + 1;
        //选择儿子结点中权值较小的那个结点
        if (low != t->size - 1 && t->min_heap[low]->dis > t->min_heap[low + 1]->dis){
            low += 1;
        }
        //如果这个结点比小顶堆数组的最后一个元素的权值小，那么将这个结点放到它的父亲结点
        if (t->min_heap[low]->dis < temp->dis){
            t->min_heap[high] = t->min_heap[low];
        }
        else break;
    }
    //比较结束后直接将最后一个元素放到最后一次比较比最后一个元素的权值大的结点的父亲结点的位置
    t->min_heap[high] = temp;
}

//从小顶堆返回最小元素
List top_heap(min_Heap t){
    return t->min_heap[0];
}

//判断小顶堆是否为空
BOOL isEmpty_heap(min_Heap t){
    return t->size == 0;
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
}

//向邻接链表中添加边
void add_edge(Adjacency_List list, int from, int to, int dis) {
    addAtHead(list->head[from], to, dis);
    addAtHead(list->head[to], from, dis);
}

//根据点的个数和边的个数创建邻接链表
Adjacency_List create_Adjacency_List(int numOfNodes, int numOfEdges) {
    if (numOfNodes == 0) return NULL;
    Adjacency_List list = (Adjacency_List)malloc(sizeof(struct adjacency_list));
    list->head = (List *)malloc(numOfNodes * sizeof(List));
    for (int i = 0; i < numOfNodes; ++i){
        list->head[i] = creat_List();
    }
    //根据起始点、邻接点、边权值添加边
    for (int i = 0; i < numOfEdges; ++i) {
        int from, to, dis;
        scanf("%d %d %d", &from, &to, &dis);
        //点从0~n-1
        /*add_edge(list, from, to, dis);*/
        //点从1~n
        add_edge(list, from - 1, to - 1, dis);
    }
    return list;
}

//打印邻接链表
void print_Adjacency_List(Adjacency_List list, int n) {
    for (int i = 0; i < n; ++i){
        printf("%d:", i);
        List t = list->head[i]->next;
        while(t != NULL){
            printf("point:%d, dis:%d->", t->to, t->dis);
            t = t->next;
        }
        printf("NULL\n");
    }
}

void initDistanceINF(EDGE_TYPE *dis, int numOfNodes){
    for (int i = 0; i < numOfNodes; ++i){
        dis[i] = INF;
    }
}

//求最小生成树的Prim算法
int Prim(Adjacency_List list, int numOfNodes, int numOfEdges){
    printf("最小生成树的路径为：\n");
    //如果为空图，返回0
    if (list == NULL || list->head[0] == NULL){
        printf("null\n");
        return 0;
    }
    if (list->head[0]->next == NULL){
        printf("null\n");
        return INF;
    }
    //创建访问数组，如果边已经被添加到最小生成树的边集中，设置为TRUE
    int *vis = (int *)malloc(sizeof(int) * numOfNodes);
    //创建距离数组，记录当前未被添加到最小生成树的点集中的点里最小生成树的最短距离
    int *dis = (int *)malloc(sizeof(int) * numOfNodes);
    //将访问数组的元素，全部初始化为0未访问状态
    memset(vis, FALSE, sizeof(int) * numOfNodes);
    //将距离数组的元素，全部初始化为INF无限远状态
    initDistanceINF(dis, numOfNodes);
    //创建小顶堆
    min_Heap heap = creat_Heap(numOfEdges);
    printf("start point:1->");
    //将起始点的所有邻接边都添加到小顶堆中，并把起始点的访问状态设置为TRUE
    List t = list->head[0]->next;
    vis[0] = TRUE;
    //起始点到最小生成树的距离为0
    dis[0] = 0;
    while(t != NULL){
        if (t->dis < dis[t->to]){
            push_heap(heap, t);
            dis[t->to] = t->dis;
        }
        t = t->next;
    }
    //记录访问过的结点
    int numOfVisited = 1;
    int sumOfDistance = 0;
    //当所有结点都被访问过，说明生成成功
    while(numOfVisited < numOfNodes){
        //如果所有结点还未访问完，堆已经为空，那么说明没有最小生成树，返回INF
        if (isEmpty_heap(heap)){
            printf("null\n");
            return INF;
        }
        //每次取出小顶堆的堆顶元素
        t = top_heap(heap);
        pop_heap(heap);
        //如果结点的邻接点没有被访问过
        if (!vis[t->to]){
            printf("point:%d, dis:%d->", t->to + 1, t->dis);
            //总距离加上边权值
            sumOfDistance += t->dis;
            List temp = list->head[t->to]->next;
            while(temp != NULL){
                if (!vis[temp->to] && temp->dis < dis[temp->to]){
                    //将这个点的所有未被访问过且到最小生成树的距离小于距离数组中的数值的邻接点加入小顶堆
                    push_heap(heap, temp);
                    dis[temp->to] = temp->dis;
                }
                temp = temp->next;
            }
            //同时标记邻接点被访问过
            vis[t->to] = TRUE;
            numOfVisited += 1;
        }
    }
    printf("null\n");
    free(vis);
    free(dis);
    free_min_heap(heap);
    return sumOfDistance;
}

//释放邻接链表所申请的动态内存
void free_Adjacency_List(Adjacency_List list, int n){
    if (list != NULL){
        if (list->head != NULL){
            for (int i = 0; i < n; ++i){
                freeList(list->head[i]);
            }
            free(list->head);
            list->head = NULL;
        }
        free(list);
        list = NULL;
    }
}

int main() {
    int numOfNodes, numOfEdges;
    scanf("%d %d", &numOfNodes, &numOfEdges);
    Adjacency_List list = create_Adjacency_List(numOfNodes, numOfEdges);
    EDGE_TYPE sumOfDistance = Prim(list, numOfNodes, numOfEdges);
    if (sumOfDistance == INF) printf("最小生成树生成失败\n");
    else printf("最小生成树的权值为：%d\n", sumOfDistance);
    free_Adjacency_List(list, numOfNodes);
}

/*
测试样例：
输入1：
3 7
1 2 19
2 3 11
3 1 7
1 3 5
2 3 89
3 1 91
1 2 32

输出1：
最小生成树的路径为：
start point:1->point:3, dis:5->point:2, dis:11->null
最小生成树的权值为：16

输入2：
5 7
1 2 5
2 3 7
2 4 8
4 5 11
3 5 10
1 5 6
4 2 12

输出2：
最小生成树的路径为：
start point:1->point:2, dis:5->point:5, dis:6->point:3, dis:7->point:4, dis:8->null
最小生成树的权值为：26

输入3：
8 12
1 2 3
1 3 2
2 3 3
2 4 6
3 5 5
3 6 5
4 5 2
4 8 2
5 6 4
5 7 3
6 7 4
7 8 6

输出3：
最小生成树的路径为：
start point:1->point:3, dis:2->point:2, dis:3->point:6, dis:5->point:7, dis:4->point:5, dis:3->point:4, dis:2->point:8, dis:2->null
最小生成树的权值为：21

输入4：
3 2
1 2 1
2 1 7

输出4：
最小生成树的路径为：
start point:1->point:2, dis:1->null
最小生成树生成失败

输入5：
0 0

输出5：
最小生成树的路径为：
null
最小生成树的权值为：0
*/