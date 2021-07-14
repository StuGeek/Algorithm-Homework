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
  int height;
  BinaryNode(T d, BinaryNode *l=NULL, BinaryNode* r=NULL):data(d), left(l), right(r), height(0) {};
};

int height(BinaryNode *root) {
    if (root == nullptr) return -1;
    else return root->height;
}

BinaryNode *Left_Left_Rotation(BinaryNode *root){
    BinaryNode *b = root->left;
    BinaryNode *BR = b->right;
    b->right = root;
    root->left = BR;
    root->height = 1 + max(height(root->left), height(root->right));
    b->height = 1 + max(height(b->left), height(b->right));
    return b;
}

BinaryNode *Right_Right_Rotation(BinaryNode *root){
    BinaryNode *b = root->right;
    BinaryNode *BR = b->left;
    b->left = root;
    root->right = BR;
    root->height = 1 + max(height(root->left), height(root->right));
    b->height = 1 + max(height(b->left), height(b->right));
    return b;
}

BinaryNode *Left_Right_Rotation(BinaryNode *root){
    BinaryNode *b = root->left;
    BinaryNode *d = b->right;
    BinaryNode *DL = d->left;
    BinaryNode *DR = d->right;
    d->left = b;
    d->right = root;
    b->right = DL;
    root->left = DR;
    root->height = 1 + max(height(root->left), height(root->right));
    b->height = 1 + max(height(b->left), height(b->right));
    d->height = 1 + max(height(d->left), height(d->right));
    return d;
}

BinaryNode *Right_Left_Rotation(BinaryNode *root){
    BinaryNode *b = root->right;
    BinaryNode *d = b->left;
    BinaryNode *DL = d->left;
    BinaryNode *DR = d->right;
    d->right = b;
    d->left = root;
    b->left = DR;
    root->right = DL;
    root->height = 1 + max(height(root->left), height(root->right));
    b->height = 1 + max(height(b->left), height(b->right));
    d->height = 1 + max(height(d->left), height(d->right));
    return d;
}

BinaryNode *AVLTree_insert(BinaryNode *&root, const T &target) {
    if (root == nullptr){
        root = new BinaryNode(target);
        return root;
    }
    else if (root->data == target) return nullptr;
    else if (root->data > target){
        root->left = AVLTree_insert(root->left, target);
        if (height(root->left) - height(root->right) > 1){
            if (root->left->data > target){
                root = Left_Left_Rotation(root);
            }
            else root = Left_Right_Rotation(root);
        }
    }
    else{
        root->right = AVLTree_insert(root->right, target);
        if (height(root->right) - height(root->left) > 1){
            if (root->right->data > target){
                root = Right_Left_Rotation(root);
            }
            else root = Right_Right_Rotation(root);
        }
    }
    root->height = 1 + max(height(root->left), height(root->right));
    return root;
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
        root = AVLTree_insert(root, num);
    }
    queue<BinaryNode *> q;
    q.push(root);
    while (!q.empty()) {
        BinaryNode *t = q.front();
        q.pop();
        ofs << t->data << " ";
        if (t->left) q.push(t->left);
        if (t->right) q.push(t->right);
    }
    ofs << endl;
    clear(root);
}