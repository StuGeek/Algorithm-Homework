#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int dir[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

int numOfOne(vector<vector<int>> adjeacency_matrix) {
    int rows = adjeacency_matrix.size();
    int columns = adjeacency_matrix[0].size();
    vector<vector<int>> vis(rows, vector<int>(columns));
    int res = 0;
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if (!vis[i][j] && adjeacency_matrix[i][j] == 1) {
                vis[i][j] = 1;
                queue<pair<int, int>> q;
                q.push({i, j});
                while (!q.empty()) {
                    pair<int, int> t = q.front();
                    q.pop();
                    for(int i = 0; i < 8; ++i) {
                        int dx = t.first + dir[i][0];
                        int dy = t.second + dir[i][1];
                        if (dx < 0 || dx >= rows || dy < 0 || dy >= columns || 
                                vis[dx][dy] == 1 || adjeacency_matrix[dx][dy] == 0) continue;
                        vis[dx][dy] = 1;
                        q.push({dx, dy});
                    }
                }
                res++;
            }
        }
    }
    return res;
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
    int res = numOfOne(adjeacency_matrix);
    ofs << res << endl;
}