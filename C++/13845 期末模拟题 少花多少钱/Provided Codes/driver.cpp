#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <list>

#define INF 0X3F3F3F3F
#define MAXVEX 1000

using namespace std;

// 边表节点
class EdgeNode {
 public:
    int from;
	int adjvex; //边指向哪个顶点的索引
	int weight;
	EdgeNode* next;
};
// 顶点表结构
class VertexNode {
 public:
	int value; //顶点的值，为了简化与序号相同，第一个是0
	EdgeNode *firstedge;
};
// 图结构
class GraphList {
 public:
	VertexNode adjList[MAXVEX];
	int numVertex;
	int numEdges;
};

ifstream ifs("../Tests/in1", ios::in);
ofstream ofs("out", ios::out);

void addEdge(GraphList* g, int from, int to, int weight) {
    EdgeNode *t = new EdgeNode;
    t->from = from;
    t->adjvex = to;
    t->weight = weight;
    EdgeNode *temp = g->adjList[from].firstedge;
    t->next = nullptr;
    if (temp == nullptr) g->adjList[from].firstedge = t;
    else {
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = t;
    }
}

void createGraph(GraphList* g, int n, int m, int k) {
    g->numVertex = n + m;
    g->numEdges = 2 * k;
    for (int i = 0; i < n + m; ++i) {
        g->adjList[i].value = i;
        g->adjList[i].firstedge = nullptr;
    }
    for (int i = 0; i < k; ++i) {
        int from, to, weight;
        ifs >> from >> to >> weight;
        addEdge(g, from, to + n, -weight);
        addEdge(g, to + n, from, -weight);
    }
}

void clear(GraphList* g) {
    int n = g->numVertex;
    for(int i = 0; i < n; ++i) {
        EdgeNode *t = g->adjList[i].firstedge;
        EdgeNode *temp = t;
        while (t != nullptr) {
            temp = t->next;
            delete [] t;
            t = temp;
        }
    }
}

bool compare(EdgeNode * a , EdgeNode * b) {
    return a->weight < b->weight;
}

int quick_find(vector<int> & a, int n) {
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

int Kruskal(GraphList *g){
    int n = g->numVertex;
    vector<int> disjoint_set(n);
    for(int i = 0; i < n; ++i) {
        disjoint_set[i] = i;
    }
    vector<EdgeNode *> v;
    for(int i = 0; i < n; ++i) {
        EdgeNode *t = g->adjList[i].firstedge;
        while (t != nullptr) {
            v.push_back(t);
            t = t->next;
        }
    }
    sort(v.begin(), v.end(), compare);
    int res = 0;
    for(int i = 0; i < g->numEdges; ++i){
        EdgeNode *t = v[i];
        int j = quick_find(disjoint_set, t->from);
        int k = quick_find(disjoint_set, t->adjvex);
        if (j != k){
            res -= t->weight;
            disjoint_set[j] = k;
        }
    }
    return res;
}

int main() {
    int T;
    ifs >> T;
    while(T--){
        GraphList g;
        int n, m, k;
        ifs >> n >> m >> k;
	    createGraph(&g, n, m, k);
        ofs << 10000 * (n + m) - Kruskal(&g) << endl;
        clear(&g);
    }
}