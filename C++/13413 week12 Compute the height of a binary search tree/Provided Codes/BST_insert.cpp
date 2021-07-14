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
#include "BST.h"

using namespace std;

void BSTree_insert(BinaryNode *&root, const T &target) {
    if (!root) {
        root = new BinaryNode(target);
        return;
    }
    BinaryNode *t = root;
    while (1) {
        if (t->data == target)
            return;
        else if (t->data > target) {
            if (!t->left) {
                t->left = new BinaryNode(target);
                return;
            }
            t = t->left;
        } else {
            if (!t->right) {
                t->right = new BinaryNode(target);
                return;
            }
            t = t->right;
        }
    }
}

int height(BinaryNode *root) {
    if (root == nullptr) return 0;
    int h = 0;
    if (root->left == nullptr){
        if (root->right != nullptr){
            h = 1 + height(root->right);
        }
    }
    else{
        h = 1 + height(root->left);
        if (root->right != nullptr) {
            int t = 1 + height(root->right);
            h = h > t ? h : t;
        }
    }
    return h;
}

void clear(BinaryNode *root) {
    if (!root) return;
    if (root->left) clear(root->left);
    if (root->right) clear(root->right);
    delete [] root;
    root = nullptr;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int n;
    ifs >> n;
    BinaryNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        int num;
        ifs >> num;
        BSTree_insert(root, num);
    }
    ofs << height(root) << endl;
    clear(root);
}