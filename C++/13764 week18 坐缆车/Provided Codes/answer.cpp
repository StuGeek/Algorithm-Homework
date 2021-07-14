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

void createGraph(GraphList* g) {
    int n;
    ifs >> n;
    g->numVertex = n;
    g->numEdges = 0;
    for (int i = 0; i < n; ++i) {
        g->adjList[i].value = i;
        g->adjList[i].firstedge = nullptr;
    }
    for (int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int weight;
            ifs >> weight;
            addEdge(g, i, j, weight);
            g->numEdges++;
        }
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

vector<int> dijkstra(GraphList* g, VertexNode & source) {
    int n = g->numVertex;
    vector<int> dis(n, INF);
    vector<int> vis(n, 0);
    dis[source.value] = 0;
    for(int i = 0; i < n; ++i) {
        int min_index = source.value;
        int num = INF;
        for(int j = 0; j < n; ++j) {
            if (!vis[j] && dis[j] < num) {
                min_index = j;
                num = dis[j];
            }
        }
        vis[min_index] = 1;
        EdgeNode *t = g->adjList[min_index].firstedge;
        while(t != nullptr) {
            if (dis[t->adjvex] > dis[min_index] + t->weight) {
                dis[t->adjvex] = dis[min_index] + t->weight;
            }
            t = t->next;
        }
    }
    return dis;
}

int main() {
    GraphList g;
	createGraph(&g);
    vector<int> dis = dijkstra(&g, g.adjList[0]);
    ofs << dis[g.numVertex - 1] << endl;
    clear(&g);
}