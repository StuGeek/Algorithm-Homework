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

int compare(const void*a,const void*b){
    List *t1 = (List *)a;
    List *t2 = (List *)b;
    return (*t1)->dis > (*t2)->dis;
}

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

void init(int *a, int n){
    for (int i = 0; i < n; ++i){
        a[i] = i;
    }
}

int quick_find(int *a, int n) {
    int temp = n;
    while (a[temp] != temp) {
        temp = a[temp];
    }
    while (n != temp) {
        int t = a[n];
        a[n] = temp;
        n = t;
    }
    return temp;
}

void set_union(int *a, int num1, int num2){
    int j = quick_find(a, num1);
    int k = quick_find(a, num2);
    if (j != k){
        a[j] = k;
    }
}

void print_disjoint_set(int *a, int n){
    for(int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int *creat_disjoint_set(int n){
    int *a = (int *)malloc(sizeof(int) * n);
    init(a, n);
    return a;
}

BOOL isConnected(int *a, int num1, int num2){
    int j = quick_find(a, num1);
    int k = quick_find(a, num2);
    return j == k;
}

//向邻接链表中添加边
void add_edge(Adjacency_List list, int from, int to, EDGE_TYPE dis) {
    addAtHead(list->head[from], from, to, dis);
    /*addAtHead(list->head[to], to, from, dis);*/
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

//求最小生成树的Prim算法
int Kruskal(Adjacency_List list, int numOfNodes, int numOfEdges){
    printf("最小生成树为：\n");
    //如果为空图，返回0
    if (list == NULL || list->head[0] == NULL){
        printf("null\n");
        return 0;
    }
    if (list->head[0]->next == NULL){
        printf("null\n");
        return INF;
    }
    int *disjoint_set = creat_disjoint_set(numOfNodes);
    List *edges = (List *)malloc(sizeof(List) * numOfEdges);
    int j = 0;
    for(int i = 0; i < numOfNodes; ++i){
        List t = list->head[i]->next;
        while(t != NULL){
            edges[j++] = t;
            t = t->next;
        }
    }
    qsort(edges, numOfEdges, sizeof(List), compare);
    //记录访问过的边
    int numOfVisited = 0;
    int sumOfDistance = 0;
    //当所有边都被访问过，生成最小生成树结束
    for(int i = 0; i < numOfEdges; ++i){
        List t = edges[i];
        j = quick_find(disjoint_set, t->from);
        int k = quick_find(disjoint_set, t->to);
        if (j != k){
            sumOfDistance += t->dis;
            disjoint_set[j] = k;
            printf("start point:%d end point: %d weight:%d->", t->from, t->to, t->dis);
            numOfVisited++;
        }
        if (numOfVisited == numOfNodes - 1) break;
    }
    printf("null\n");
    free(disjoint_set);
    if (numOfVisited != numOfNodes - 1) return INF;
    else return sumOfDistance;
}

int main() {
    int numOfNodes, numOfEdges;
    scanf("%d %d", &numOfNodes, &numOfEdges);
    Adjacency_List list = create_Adjacency_List(numOfNodes, numOfEdges);
    EDGE_TYPE sumOfDistance = Kruskal(list, numOfNodes, numOfEdges);
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