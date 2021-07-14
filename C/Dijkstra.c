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
    int from;
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
void addAtHead(List myList, int from, int to, EDGE_TYPE dis) {
    List new_Node = (List)malloc(sizeof(struct node));
    new_Node->from = from;
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
void push_heap(min_Heap t, int *dis, List node){
    //向数组的第一个无元素的位置插入数据，数组存放元素个数加一
    t->min_heap[t->size++] = node;
    //记录此时插入元素的位置
    int temp = t->size - 1;
    //如果此时插入元素的权值比它的父亲大，同时插入数据还没有成为根结点，那么将它的父亲保存到小顶堆的位置，插入元素继续向上比较
    while(node->dis + dis[node->from] < t->min_heap[(temp - 1) / 2]->dis + 
            dis[t->min_heap[(temp - 1) / 2]->from] && temp > 0){
        t->min_heap[temp] = t->min_heap[(temp - 1) / 2];
        temp = (temp - 1) / 2;
    }
    //比较结束后直接将插入元素放到最后一次比较大于这个插入元素的权值的父亲的位置
    t->min_heap[temp] = node;
}

//从小顶堆中删除根结点的数据
void pop_heap(min_Heap t, int *dis){
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
        if (low != t->size - 1 && t->min_heap[low]->dis + dis[t->min_heap[low]->from] > 
            t->min_heap[low + 1]->dis + dis[t->min_heap[low]->from]){
            low += 1;
        }
        //如果这个结点比小顶堆数组的最后一个元素的权值小，那么将这个结点放到它的父亲结点
        if (t->min_heap[low]->dis + dis[t->min_heap[low]->from] < temp->dis + dis[temp->from]){
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
void add_edge(Adjacency_List list, int from, int to, EDGE_TYPE dis) {
    addAtHead(list->head[from], from, to, dis);
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

void print_path(int *path, int index){
    if (index != 0) print_path(path, path[index]);
    printf("%d->", index + 1);
}

void print_Distances(EDGE_TYPE *dis, int *path, int numOfNodes){
    for(int i = 0; i < numOfNodes; ++i) {
        printf("1到%d的最短路径长度为%d,", i + 1, dis[i]);
        printf("最短路径为:");
        print_path(path, i);
        printf("over\n");
    }
    printf("\n");
}

void initDistanceINF(EDGE_TYPE *dis, int numOfNodes){
    for (int i = 0; i < numOfNodes; ++i){
        dis[i] = INF;
    }
}

//求单源最短路径的Dijkstra算法
EDGE_TYPE* Dijkstra(Adjacency_List list, int numOfNodes, int numOfEdges){
    //如果为空图，返回NULL
    if (list == NULL || list->head[0] == NULL || list->head[0]->next == NULL) return NULL;
    //创建访问数组，如果点已经被访问过，设置为TRUE
    int *vis = (int *)malloc(sizeof(int) * numOfNodes);
    //创建路径数组，用来保存每个点路径中的上一个点
    int *path = (int *)malloc(sizeof(int) * numOfNodes);
    //创建距离数组，记录每个点到起始点最短路径距离
    EDGE_TYPE *dis = (EDGE_TYPE *)malloc(sizeof(EDGE_TYPE) * numOfNodes);
    //将访问数组的元素，全部初始化为0未访问状态
    memset(vis, FALSE, sizeof(int) * numOfNodes);
    //将距离数组的元素，全部初始化为INF无限远状态
    initDistanceINF(dis, numOfNodes);
    //创建小顶堆
    min_Heap heap = creat_Heap(numOfEdges);
    //将起始点的所有邻接边都添加到小顶堆中，并把起始点的访问状态设置为TRUE
    List t = list->head[0]->next;
    vis[0] = TRUE;
    path[0] = 0;
    //起始点的最短路径距离为0
    dis[0] = 0;
    while(t != NULL){
        if (t->dis < dis[t->to]){
            push_heap(heap, dis, t);
            dis[t->to] = t->dis;
        }
        t = t->next;
    }
    //记录访问过的结点
    int numOfVisited = 1;
    //当所有结点都被访问过，说明生成成功
    while(numOfVisited < numOfNodes){
        //如果所有结点还未访问完，堆已经为空，那么说明没有有的点没有最短路径，为INF
        if (isEmpty_heap(heap)) break;
        //每次取出小顶堆的堆顶元素
        t = top_heap(heap);
        pop_heap(heap, dis);
        //如果最短距离的邻接点没有被访问过
        if (!vis[t->to]){
            path[t->to] = t->from;
            List temp = list->head[t->to]->next;
            while(temp != NULL){
                if (!vis[temp->to] && temp->dis + dis[temp->from] < dis[temp->to]){
                    //将这个点的所有未被访问过且到中转点的距离小于距离数组中的数值的邻接点加入小顶堆
                    push_heap(heap, dis, temp);
                    dis[temp->to] = temp->dis + dis[temp->from];
                }
                temp = temp->next;
            }
            //同时标记邻接点被访问过
            vis[t->to] = TRUE;
            numOfVisited += 1;
        }
    }
    print_Distances(dis, path, numOfNodes);
    free(vis);
    free(path);
    free_min_heap(heap);
    return dis;
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
    EDGE_TYPE *distance = Dijkstra(list, numOfNodes, numOfEdges);
    free(distance);
    free_Adjacency_List(list, numOfNodes);
}

/*
5 5
1 2 3
1 3 4
1 4 5
1 5 6
2 4 1
*/