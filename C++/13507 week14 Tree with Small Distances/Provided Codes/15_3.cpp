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
    int from;
    int to;
    int weight;
};

bool compare(Node & a, Node & b) {
    return a.weight > b.weight;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int n;
    ifs >> n;
    vector<int> v(n);
    vector<Node> t(n);
    for(int i = 0; i < n; ++i) {
        int num1, num2;
        ifs >> num1 >> num2;
        v[num2 - 1] = v[num1 - 1] + 1;
        t[i].from = num1 - 1;
        t[i].to = num2 - 1;
    }
    for(int i = 0; i < n; ++i) {
        t[i].weight = v[i];
    }
    sort(t.begin(), t.end(), compare);
    int res = 0;
    for(int i = 0; i < n; ++i) {
        if (v[t[i].from] > 1) {
            v[t[i].from] = 1;
            res++;
        }
    }
    ofs << res << endl;
}