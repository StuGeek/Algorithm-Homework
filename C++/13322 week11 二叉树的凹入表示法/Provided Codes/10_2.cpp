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

template <class Entry>
struct Node {
    Entry entry;
    Node<Entry> *left;
    Node<Entry> *right;

    Node(const Entry &en) {
        entry = en;
        left = NULL;
        right = NULL;
    }
};

int dfs(string & preoder, string & inorder, int prebegin, int preend, int inbegin, int inend, vector<int> & h) {
    if (prebegin == preend) {
        h[prebegin] = 1;
        return 1;
    }
    int index = inorder.find(preoder[prebegin]);
    if (inbegin < index) {
        h[prebegin] += dfs(preoder, inorder, prebegin + 1, prebegin + index - inbegin, inbegin, index - 1, h);
    }
    if (inend > index) {
        h[prebegin] += dfs(preoder, inorder, prebegin + index - inbegin + 1, preend, index + 1, inend, h);
    }
    return h[prebegin];
}

int main() {
    ifstream ifs("../Tests/in3", ios::in);
    ofstream ofs("out", ios::out);
    string preorder, inorder;
    ifs >> preorder >> inorder;
    int n = preorder.size();
    vector<int> h(n);
    dfs(preorder, inorder, 0, n - 1, 0, n - 1, h);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < h[i]; ++j) {
            ofs << preorder[i];
        }
        ofs << endl;
    }
}