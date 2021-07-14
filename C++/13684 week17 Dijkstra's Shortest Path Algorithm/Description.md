# week17 Dijkstra's Shortest Path Algorithm

### Problem
Given a directed graph, compute all the shortest paths from the source to other vertices.

### Input
The first line is the number of test cases.

For every test case, the first line is the number of node n, meaning nodes are 1,2,...,n.

The next line is the number of edges m, then m lines are followed, where each line is in the form of u v w, meaning (u,v) is an edge and it has weight w (>0).

The last line is the source vertex.

### Output
 For each test case, print  all the shortest paths from the source s to other vertices (if the shortest path is finite) in the order of vertices in the following form （no spaces between）:

s-1:d1

s-2:d2

...

### Sample Input
```
2
2
1
1 2 5
1
5
6
1 2 4
1 3 6
2 3 1
4 5 1
3 1 1
5 4 2
2
```
### Sample Output
```
1-1:0
1-2:5
2-1:2
2-2:0
2-3:1
```
### Hint
 Suggested solution: again, write a few functions. 

1. A function which constructs the graph:

Graph mkGraph();

2. A function which computes all the shortest paths, for example, 

vector<int> dijkstra(Graph g, Vertex source);

3. A print function which prints the result as required.

void print(vector<int> d, Vertex source);

 