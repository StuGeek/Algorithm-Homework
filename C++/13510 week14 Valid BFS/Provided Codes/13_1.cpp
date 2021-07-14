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

using namespace std;

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

void createGraph(GraphList* g, int k) {
    for (int i = 0; i < k; ++i) {
        g->adjList[i].value = i;
        g->adjList[i].firstedge = nullptr;
    }
    for (int i = 0; i < k - 1; ++i) {
        int from, to;
        ifs >> from >> to;
        addEdge(g, from - 1, to - 1);
    }
    g->numVertex = k;
    g->numEdges = k - 1;
}

bool isValidBFS(GraphList* g, vector<int> & v) {
    if (v[0] != 0) return false;
    queue<int> q;
    q.push(v[0]);
    int i = 1;
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        vector<int> v1;
        vector<int> v2;
        EdgeNode *temp = g->adjList[t].firstedge;
        while (temp != nullptr) {
            v1.push_back(temp->adjvex);
            v2.push_back(v[i]);
            q.push(v[i++]);
            temp = temp->next;
        }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        int n = v1.size();
        for (int j = 0; j < n; ++j) {
            if (v1[j] != v2[j]) return false;
        }
    }
    return true;
}

int main() {
    int k;
    ifs >> k;
    GraphList g;
    createGraph(&g, k);
    vector<int> v;
    for (int i = 0; i < k; ++i) {
        int num;
        ifs >> num;
        v.push_back(num - 1);
    }
    if (isValidBFS(&g, v)) ofs << "Yes" << endl;
    else ofs << "No" << endl;
}