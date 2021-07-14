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

#define MAXVEX 1000

using namespace std;

// 边表节点
class EdgeNode {
 public:
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

void addEdge(GraphList* g, int from, int to) {
    EdgeNode *t = new EdgeNode;
    t->adjvex = to;
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

void createGraph(GraphList* g) {
    int n, m;
    ifs >> n >> m;
    for (int i = 0; i < n; ++i) {
        g->adjList[i].value = i;
        g->adjList[i].firstedge = nullptr;
    }
    for (int i = 0; i < m; ++i) {
        int from, to;
        ifs >> from >> to;
        addEdge(g, from - 1, to - 1);
        addEdge(g, to - 1, from - 1);
    }
    g->numVertex = n;
    g->numEdges = m;
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

int numOfLines(GraphList *g){
    int n = g->numVertex;
    vector<int> vis(n);
    int res = 0;
    for(int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        vis[i] = 1;
        if (g->adjList[i].firstedge == nullptr) continue;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int j = q.front();
            q.pop();
            EdgeNode *t = g->adjList[j].firstedge;
            while (t != nullptr) {
                if (!vis[t->adjvex]) {
                    q.push(t->adjvex);
                    vis[t->adjvex] = 1;
                }
                t = t->next;
            }
        }
        res++;
    }
    return res;
}

int main() {
    GraphList g;
    createGraph(&g);
    ofs << numOfLines(&g) << endl;
    clear(&g);
}