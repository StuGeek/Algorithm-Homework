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

ifstream ifs("../Tests/in1", ios::in);
ofstream ofs("out", ios::out);

void dfs(vector<int> & nums, Node<int> *root, int & sum, int & target, int & res) {
    if (!root) return;
    if (!root->left && !root->right) {
        if (sum + root->entry != target) return;
        else {
            int n = nums.size();
            for(int i = 0; i < n; ++i) {
                ofs << nums[i] << "->";
            }
            ofs << root->entry << endl;
            res++;
            return;
        }
    }
    nums.push_back(root->entry);
    sum += root->entry;
    if (root->left) dfs(nums, root->left, sum, target, res);
    if (root->right) dfs(nums, root->right, sum, target, res);
    nums.pop_back();
    sum -= root->entry;
}

int main() {
    while (!ifs.eof()) {
        int n, m;
        ifs >> n >> m;
        Node<int> *root = nullptr;
        for (int i = 0; i < n; ++i) {
            int num;
            ifs >> num;
            BSTree_insert(root, num);
        }
        vector<int> nums;
        int sum = 0;
        int res = 0;
        dfs(nums, root, sum, m, res);
        if (res == 0) ofs << "NULL" << endl;
        clear(root);
    }
}