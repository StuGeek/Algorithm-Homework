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

void print_Distances(EDGE_TYPE *dis, int numOfNodes){
    for(int i = 0; i < numOfNodes; ++i) {
        printf("1到%d的最短路径长度为%d\n", i + 1, dis[i]);
    }
    printf("\n");
}

void initDistanceINF(EDGE_TYPE *dis, int numOfNodes){
    for (int i = 0; i < numOfNodes; ++i){
        dis[i] = INF;
    }
}

//求单源最短路径的Bellman_Ford算法
EDGE_TYPE* Bellman_Ford(Adjacency_List list, int numOfNodes, int numOfEdges){
    //如果为空图，返回NULL
    if (list == NULL || list->head[0] == NULL || list->head[0]->next == NULL) return NULL;
    //创建距离数组，记录每个点到起始点最短路径距离
    EDGE_TYPE *dis = (EDGE_TYPE *)malloc(sizeof(EDGE_TYPE) * numOfNodes);
    //将距离数组的元素，全部初始化为INF无限远状态
    initDistanceINF(dis, numOfNodes);
    dis[0] = 0;
    for(int i = 0; i < numOfNodes; ++i){
        for(int j = 0; j < numOfNodes; ++j){
            List t = list->head[j]->next;
            while(t != NULL){
                if (dis[t->to] > dis[t->from] + t->dis) dis[t->to] = dis[t->from] + t->dis;
                t = t->next;
            }
        }
    }
    print_Distances(dis, numOfNodes);
    return dis;
}

int main() {
    int numOfNodes, numOfEdges;
    scanf("%d %d", &numOfNodes, &numOfEdges);
    Adjacency_List list = create_Adjacency_List(numOfNodes, numOfEdges);
    EDGE_TYPE *distance = Bellman_Ford(list, numOfNodes, numOfEdges);
    free(distance);
    free_Adjacency_List(list, numOfNodes);
}

/*
5 5
1 2 3
2 3 4
2 4 5
1 5 6
4 5 1
*/