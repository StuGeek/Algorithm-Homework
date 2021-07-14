#include "bfs.h"

using namespace std;

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
    cin >> k >> m;
    for (int i = 0; i < k; ++i) {
        int num;
        cin >> num;
        g->adjList[i].value = num;
        g->adjList[i].firstedge = nullptr;
    }
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
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

void BFSTraverse(GraphList* g) {
    int n = g->numVertex;
    vector<int> vis(n, 0);
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    while(!q.empty()) {
        int temp = q.front();
        cout << temp << " ";
        q.pop();
        EdgeNode *t = g->adjList[temp].firstedge;
        while (t != nullptr) {
            if (!vis[t->adjvex]) {
                q.push(t->adjvex);
                vis[t->adjvex] = 1;
            }
            t = t->next;
        }
    }
    clear(g);
}