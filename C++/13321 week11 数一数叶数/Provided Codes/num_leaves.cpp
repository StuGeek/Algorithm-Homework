#include "BinaryNode.h"
#include <queue>

int leave(const BinaryNode* root) {
    if (!root) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    else return leave(root->left) + leave(root->right);
}