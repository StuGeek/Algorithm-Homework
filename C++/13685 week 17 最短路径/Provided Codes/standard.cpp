#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int minLengthOfDis(vector<vector<int>> adjeacency_matrix, int sx, int sy, int tx, int ty) {
    queue<pair<int, int>> q;
    pair<int, int> begin(sx, sy);
    int rows = adjeacency_matrix.size();
    int columns = adjeacency_matrix[0].size();
    vector<vector<int>> dis(rows, vector<int>(columns, -1));
    dis[sx][sy] = 0;
    q.push(begin);
    while(!q.empty()) {
        pair<int, int> t = q.front();
        q.pop();
        for(int i = 0; i < 4; ++i) {
            int dx = t.first + dir[i][0];
            int dy = t.second + dir[i][1];
            if (dx < 0 || dx >= rows || dy < 0 || dy >= columns || 
                    dis[dx][dy] != -1 || adjeacency_matrix[dx][dy] == 1) continue;
            dis[dx][dy] = dis[t.first][t.second] + 1;
            if (dx == tx && dy == ty) return dis[dx][dy];
            q.push({dx, dy});
        }
    }
    return -1;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int n, m;
    ifs >> n >> m;
    vector<vector<int>> adjeacency_matrix(n);
    for(int i = 0; i < n; ++i) {
        adjeacency_matrix[i].resize(m);
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            ifs >> adjeacency_matrix[i][j];
        }
    }
    int sx, sy, tx, ty;
    ifs >> sx >> sy >> tx >> ty;
    int res = minLengthOfDis(adjeacency_matrix, sx - 1, sy - 1, tx - 1, ty - 1);
    if (res != -1) ofs << res << endl;
    else ofs << "No" << endl;
}