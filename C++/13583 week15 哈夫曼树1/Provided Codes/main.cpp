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

void postOrderOfHuffmanTree(vector<HuffmanNode> & tree, vector<char> & v, int index) {
    if (index == -1) return;
    postOrderOfHuffmanTree(tree, v, tree[index].Lchild);
    postOrderOfHuffmanTree(tree, v, tree[index].Rchild);
    if (tree[index].Lchild == -1 && tree[index].Rchild == -1) {
        v.push_back(tree[index].data);
    }
}

int main() {
	ifstream ifs("../Tests/in1", ios::in);
	ofstream ofs("out", ios::out);
	int n;
	ifs >> n;
	vector<HuffmanNode> tree(2 * n - 1);
	for(int i = 0; i < n; ++i) {
		ifs >> tree[i].data >> tree[i].weight;
        tree[i].Lchild = -1;
        tree[i].Rchild = -1;
        tree[i].parent = -1;
	}
    sort(tree.begin(), tree.begin() + n, compare);
    Create_Huffman(tree, n);
    vector<char> v;
    postOrderOfHuffmanTree(tree, v, 2 * n - 2);
    for(int i = n - 1; i >= 0; --i) {
        ofs << v[i] << endl;
    }
}