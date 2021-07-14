#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define INF 0X3F3F3F3F
#define MAXVEX 10000
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
    int k, m;
    ifs >> k >> m;
    for (int i = 0; i < k; ++i) {
        g->adjList[i].value = i;
        g->adjList[i].firstedge = nullptr;
    }
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        ifs >> from >> to >> weight;
        addEdge(g, from - 1, to - 1, weight);
    }
    g->numVertex = k;
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

struct compare {
    bool operator() (VertexNode & a, VertexNode & b) {
        return a.value < b.value;
    }
};

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

void print(vector<int> & d, VertexNode & source) {
    int n = d.size();
    int value = source.value;
    for(int i = 0; i < n; ++i) {
        if (d[i] != INF) {
            ofs << value + 1 << "-" << i + 1 << ":" << d[i] << endl;
        }
    }
}

int main() {
    int T;
    ifs >> T;
    while(T--){
        GraphList g;
        createGraph(&g);
        int s;
        ifs >> s;
        vector<int> dis = dijkstra(&g, g.adjList[s - 1]);
        print(dis, g.adjList[s - 1]);
        clear(&g);
    }
}