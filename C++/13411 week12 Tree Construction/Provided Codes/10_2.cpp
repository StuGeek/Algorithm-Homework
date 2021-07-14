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

ifstream ifs("../Tests/in1", ios::in);
ofstream ofs("out", ios::out);

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
                ofs << t->entry << " ";
                t->left = new Node<Entry>(target);
                return;
            }
            t = t->left;
        } else {
            if (!t->right) {
                ofs << t->entry << " ";
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

int main() {
    int n;
    ifs >> n;
    Node<int> *root = nullptr;
    for (int i = 0; i < n; ++i) {
        int num;
        ifs >> num;
        BSTree_insert(root, num);
    }
    clear(root);
}