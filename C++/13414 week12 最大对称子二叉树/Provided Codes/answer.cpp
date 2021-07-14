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
    int weight;
    int Lchild, Rchild;
};

pair<bool, int> sumOfTree(vector<Node> & tree, int index) {
    int l = tree[index].Lchild;
    int r = tree[index].Rchild;
    if(l == -1 && r == -1) return {true, 1};
    if(l == -1 || r == -1) return {false, 1};
    pair<bool, int> left = sumOfTree(tree, tree[index].Lchild);
    pair<bool, int> right = sumOfTree(tree, tree[index].Rchild);
    if (left.first && right.first && tree[l].weight == tree[r].weight) {
        int res = 1 + left.second + right.second;
        return {true, res};
    }
    else return {false, max(left.second, right.second)};
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int n;
    ifs >> n;
    vector<Node> tree(n + 1);
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; ++i) {
        int num;
        ifs >> num;
        tree[i].weight = num;
    }
    for(int i = 1; i <= n; ++i) {
        int num1, num2;
        ifs >> num1 >> num2;
        tree[i].Lchild = num1;
        tree[i].Rchild = num2;
        if (num1 != -1) vis[num1] = 1;
        if (num2 != -1) vis[num2] = 1;
    }
    int index = 0;
    for(index = 1; index <= n; ++index) {
        if (vis[index] == 0) break;
    }
    pair<bool, int> t = sumOfTree(tree, index);
    ofs << t.second << endl;
}