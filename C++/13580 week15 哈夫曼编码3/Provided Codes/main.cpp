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

struct HuffmanNode {
    char data;
    int weight;
    int parent, Lchild, Rchild;
};

bool compare (HuffmanNode & a, HuffmanNode & b) {
    return a.weight < b.weight;
}

void Create_Huffman(vector<HuffmanNode> & tree, int n) {
    tree.resize(2 * n - 1);
    for (int i = n; i < 2 * n - 1; ++i) {
        tree[i].weight = 0;
        tree[i].parent = -1;
        tree[i].Lchild = -1;
        tree[i].Rchild = -1;
    }
    for (int i = n; i < 2 * n - 1; ++i) {
        unsigned w1 = 32767, w2 = w1;
        int p1 = 0, p2 = 0;
        for (int j = 0; j < i; j++) {
            if (tree[j].parent == -1) {
                if (tree[j].weight < w1) {
                    w2 = w1;
                    p2 = p1;
                    w1 = tree[j].weight;
                    p1 = j;

                } else if (tree[j].weight < w2) {
                    w2 = tree[j].weight;
                    p2 = j;
                }
            }
        }
        tree[i].Lchild = p1;
        tree[i].Rchild = p2;
        tree[i].weight = w1 + w2;
        tree[p1].parent = i;
        tree[p2].parent = i;
    }
}

void dfs(vector<HuffmanNode> & tree, unordered_map<char, int> & themap, int & height, int index) {
    if (tree[index].Lchild == -1 && tree[index].Rchild == -1) {
        int t = height;
        themap[tree[index].data] = t;
        return;
    }
    height++;
    dfs(tree, themap, height, tree[index].Lchild);
    dfs(tree, themap, height, tree[index].Rchild);
    height--;
}

int main() {
	ifstream ifs("../Tests/in1", ios::in);
	ofstream ofs("out", ios::out);
	string s;
	ifs >> s;
	vector<HuffmanNode> tree;
    vector<int> v(26);
    int n = s.size();
    for(int i = 0; i < n; ++i) {
        v[s[i] - 'a']++;
    }
	for(int i = 0; i < 26; ++i) {
        if (v[i]) {
            HuffmanNode t;
            t.data = i + 'a';
            t.weight = v[i];
            t.Lchild = -1;
            t.Rchild= -1;
            t.parent = -1;
            tree.push_back(t);
        }
	}
    int t = tree.size();
    sort(tree.begin(), tree.begin() + t, compare);
    Create_Huffman(tree, t);
    unordered_map<char, int> themap;
    int height = 0;
    dfs(tree, themap, height, 2 * t - 2);
    int res = 0;
    for(int i = 0; i < n; ++i) {
        res += themap[s[i]];
    }
    ofs << res << endl;
}