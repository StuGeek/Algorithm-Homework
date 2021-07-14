#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <list>

using namespace std;

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool isMap(string & s) {
    map<pair<int, int>, int> themap;
    themap[{0, 0}] = 1;
    int n = s.size();
    int x = 0;
    int y = 0;
    for(int i = 0; i < n; ++i) {
        switch (s[i]) {
            case 'L':
                x--;
                break;
            case 'R':
                x++;
                break;
            case 'U':
                y--;
                break;
            case 'D':
                y++;
                break;
        }
        if (themap[{x, y}]) return false;
        themap[{x, y}] = 1;
        int t = 0;
        for(int i = 0; i < 4; ++i) {
            int dx = x + dir[i][0];
            int dy = y + dir[i][1];
            if (themap[{dx, dy}]) t++;
        }
        if (t != 1) return false;
    }
    return true;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    string s;
    ifs >> s;
    if (isMap(s)) ofs << "OK" << endl;
    else ofs << "BUG" << endl;
}