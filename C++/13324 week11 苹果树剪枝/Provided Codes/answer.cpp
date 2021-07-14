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

struct Node {
    int to;
    int weight;
};

int dp[102][102];

void dfs(vector<vector<Node>> & v, int n, int m, int x, int fa) {
    for (int i = 0; i < v[x].size(); i++) {
        int to = v[x][i].to;
        int weight = v[x][i].weight;
        if (to == fa) continue;
        dfs(v, n, m, to, x);
        for (int j = m; j > 0; j--) {
            for (int k = 0; k < j; k++) {
                dp[x][j] = max(dp[x][j], dp[x][k] + weight + dp[to][j - k - 1]);
            }
        }
    }
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int n, m;
    ifs >> n >> m;
    vector<vector<Node>> v(102);
    for (int i = 1; i < n; i++) {
        int from, to, weight;
        ifs >> from >> to >> weight;
        Node t;
        t.to = to;
        t.weight = weight;
        v[from].push_back(t);
        t.to = from;
        v[to].push_back(t);
    }
    dfs(v, n, m, 1, -1);
    ofs << dp[1][m] << endl;
}