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

typedef struct{
    int number;
    int count;
} dice;

bool compare(dice &a, dice &b){
    return a.count > b.count;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int m, n;
    ifs >> m;
    ifs >> n;
    dice *t = new dice[m];
    for (int i = 0; i < m; ++i){
        t[i].count = 0;
        t[i].number = i + 1;
    }
    for (int i = 0; i < n; ++i){
        int num;
        ifs >> num;
        t[num - 1].count++;
    }
    sort(t, t + m, compare);
    for (int i = 0; i < m; ++i){
        ofs << t[i].number << ":" << t[i].count << endl;
    }
}