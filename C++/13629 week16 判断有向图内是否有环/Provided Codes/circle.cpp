#include <iostream>
#include <fstream>
#include "circle.h"

using namespace std;

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
        int num;
        ifs >> num;
        g->adjList[i].value = num;
        g->adjList[i].firstedge = nullptr;
    }
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        ifs >> from >> to >> weight;
        addEdge(g, from, to, weight);
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

vector<int> indegree(GraphList* g){
    int n = g->numVertex;
    vector<int> res(n, 0);
    for(int i = 0; i < n; ++i){
        EdgeNode *t = g->adjList[i].firstedge;
        while(t != nullptr){
            res[t->adjvex]++;
            t = t->next;
        }
    }
    return res;
}

bool TopologicalSort(GraphList* g) {
    int n = g->numVertex;
    vector<int> vis(n, 0);
    vector<int> in_degree = indegree(g);
    cout << endl;
    queue<int> q;
    for(int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
            vis[i] = 1;
        }
    }
    int visited = 0;
    while(!q.empty()) {
        int temp = q.front();
        q.pop();
        visited++;
        EdgeNode *t = g->adjList[temp].firstedge;
        while (t != nullptr) {
            if (vis[t->adjvex]) return true;
            else {
                in_degree[t->adjvex]--;
                if (in_degree[t->adjvex] == 0) {
                    q.push(t->adjvex);
                    vis[t->adjvex] = 1;
                }
            }
            t = t->next;
        }
    }
    if (visited != n) return true;
    else return false;
}

void Graphcircle(GraphList *g) {
    bool isCircle = TopologicalSort(g);
    if (isCircle) {
        ofs << "has circle" << endl;
    }
    else {
        ofs << "no circle" << endl;
    }
    clear(g);
}