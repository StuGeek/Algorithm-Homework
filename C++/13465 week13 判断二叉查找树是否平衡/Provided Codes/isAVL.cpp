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

typedef int T;
struct BinaryNode{
  T data;
  BinaryNode *left, *right;
  BinaryNode(T d, BinaryNode *l=NULL, BinaryNode* r=NULL):data(d), left(l), right(r) {};
};

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

bool isAVL(BinaryNode *root, int & height) {
    if (!root) {
        height = 0;
        return true;
    }
    int left_height, right_height;
    bool isLeftAVL = isAVL(root->left, left_height);
    bool isRightAVL = isAVL(root->right, right_height);
    height = max(left_height, right_height) + 1;
    if (isLeftAVL && isRightAVL && abs(left_height - right_height) <= 1) {
        return true;
    }
    else {
        return false;
    }
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
    int T;
    ifs >> T;
    while (T--) {
        int n;
        ifs >> n;
        BinaryNode *root = nullptr;
        for (int i = 0; i < n; ++i) {
            int num;
            ifs >> num;
            BSTree_insert(root, num);
        }
        int height;
        if (isAVL(root, height)) ofs << "YES" << endl;
        else ofs << "NO" << endl;
        clear(root);
    }
}