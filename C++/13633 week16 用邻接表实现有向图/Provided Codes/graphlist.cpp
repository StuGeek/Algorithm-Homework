#include <iostream>
#include "graphlist.h"

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