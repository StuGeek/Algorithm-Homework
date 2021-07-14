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

using namespace std;

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int bfs(vector<vector<int>> & v) {
    int n = v.size();
    if (n == 1) return 1;
    vector<vector<int>> vis(n, vector<int>(n, 0));
    queue<pair<int, int>> q;
    q.push({0, 0});
    vis[0][0] = 1;
    while (!q.empty()) {
        pair<int, int> t = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int dx = t.first + dir[i][0];
            int dy = t.second + dir[i][1];
            if (dx == n - 1 && dy == n - 1) return vis[t.second][t.first] + 1;
            if (dx < 0 || dy < 0 || dx >= n || dy >= n || vis[dy][dx] || v[dy][dx]) continue;
            else {
                q.push({dx, dy});
                vis[dy][dx] = vis[t.second][t.first] + 1;
            }
        }
    }
    return 0;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    while(true){
        int n;
        ifs >> n;
        if (n == 0) break;
        vector<vector<int>> v(n, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                ifs >> v[i][j];
            }
        }
        int res = bfs(v);
        ofs << res << endl;
    }
}