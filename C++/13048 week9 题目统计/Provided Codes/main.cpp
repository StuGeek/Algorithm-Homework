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

int main() {
    ifstream ifs("../Tests/in3", ios::in);
    ofstream ofs("out", ios::out);
    int A, B;
    ifs >> A >> B;
    unordered_map<int, vector<pair<int, int>>> themap;
    for(int i = 1; i <= A; ++i) {
        vector<pair<int, int>> t(B, {0, 0});
        themap[i] = t;
    }
    int M, N, T;
    while(!ifs.eof()){
        ifs >> M >> N >> T;
        if (T == 1) themap[M][N - 1].first++;
        else themap[M][N - 1].second++;
    }
    for(int i = 1; i <= A; ++i) {
        for(int j = 0; j < B; ++j) {
            ofs << themap[i][j].first << " " << themap[i][j].second << " ";
        }
        ofs << endl;
    }
}