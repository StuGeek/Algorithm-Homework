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
    int height;

    Node(const Entry &en) {
        entry = en;
        left = NULL;
        right = NULL;
    }
};

template <class Entry>
void BSTree_insert(Node<Entry> *&root, const Entry &target) {
    if (!root) {
        root = new Node<Entry>(target);
        return;
    }
    Node<Entry> *t = root;
    while (1) {
        if (t->entry == target)
            return;
        else if (t->entry > target) {
            if (!t->left) {
                t->left = new Node<Entry>(target);
                return;
            }
            t = t->left;
        } else {
            if (!t->right) {
                t->right = new Node<Entry>(target);
                return;
            }
            t = t->right;
        }
    }
}

template <class Entry>
void clear(Node<Entry> *root) {
    if (!root) return;
    if (root->left) clear(root->left);
    if (root->right) clear(root->right);
    delete [] root;
    root = nullptr;
}

int bfs(Node<int> *root) {
    if (root == nullptr) return 0;
    queue<Node<int> *> q;
    root->height = 0;
    q.push(root);
    int res = 0;
    int sum = 0;
    int temp = 0;
    while (!q.empty()) {
        Node<int> *t = q.front();
        q.pop();
        if (t->height != temp) {
            if (sum > res) res = sum;
            sum = 0;
            temp = t->height;
        }
        sum++;
        if (t->left) {
            t->left->height = t->height + 1;
            q.push(t->left);
        }
        if(t->right) {
            t->right->height = t->height + 1;
            q.push(t->right);
        }
    }
    if (sum > res) res = sum;
    return res;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int T;
    ifs >> T;
    while (T--) {
        int n;
        ifs >> n;
        Node<int> *root = nullptr;
        for (int i = 0; i < n; ++i) {
            int num;
            ifs >> num;
            BSTree_insert(root, num);
        }
        int res = bfs(root);
        ofs << res << endl;
        clear(root);
    }
}