#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <queue>
#include <unordered_map>

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

Node<char> *BinaryTree_rebuild(string & preoder, string & inorder, int prebegin, int preend, int inbegin, int inend) {
    if (prebegin > preend) return nullptr;
    Node<char> *new_node = new Node<char>(preoder[prebegin]);
    int index = inorder.find(preoder[prebegin]);
    if (index == -1) return nullptr;
    new_node->left = BinaryTree_rebuild(preoder, inorder, prebegin + 1, prebegin + index - inbegin, inbegin, index - 1);
    new_node->right = BinaryTree_rebuild(preoder, inorder, prebegin + index - inbegin + 1, preend, index + 1, inend);
    return new_node;
}

template <class Entry>
void clear(Node<Entry> *root) {
    if (!root) return;
    if (root->left) clear(root->left);
    if (root->right) clear(root->right);
    delete [] root;
    root = nullptr;
}

string bfs(Node<char> *root) {
    if (root == nullptr) return "";
    string res = "";
    queue<Node<char> *> q;
    q.push(root);
    while(!q.empty()) {
        Node<char> *t = q.front();
        q.pop();
        res += t->entry;
        if (t->left) q.push(t->left);
        if (t->right) q.push(t->right);
    }
    return res;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int t;
    ifs >> t;
    while (t--) {
        string preorder, inorder;
        ifs >> preorder >> inorder;
        int n = preorder.size();
        Node<char> *root = BinaryTree_rebuild(preorder, inorder, 0, n - 1, 0, n - 1);
        ofs << bfs(root) << endl;
        clear(root);
    }
}