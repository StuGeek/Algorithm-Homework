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

ifstream ifs("../Tests/in1", ios::in);
ofstream ofs("out", ios::out);

void BFSTraverse(vector<vector<int>> adjeacency_matrix, int s) {
    int n = adjeacency_matrix.size();
    vector<int> vis(n, 0);
    vis[s - 1] = 1;
    queue<int> q;
    q.push(s - 1);
    while(!q.empty()) {
        int temp = q.front();
        ofs << temp + 1 << " ";
        q.pop();
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                int num = adjeacency_matrix[temp][i];
                if (num == 1) {
                    q.push(i);
                    vis[i] = 1;
                }
            }
        }
    }
}

int main() {
    int n, s;
    ifs >> n >> s;
    vector<vector<int>> adjeacency_matrix(n);
    for(int i = 0; i < n; ++i) {
        adjeacency_matrix[i].resize(n);
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            ifs >> adjeacency_matrix[i][j];
        }
    }
    BFSTraverse(adjeacency_matrix, s);
}