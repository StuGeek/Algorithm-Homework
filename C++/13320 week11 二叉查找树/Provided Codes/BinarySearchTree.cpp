#include "Node.h"
#include <iostream>

using namespace std;

template <class Entry>
Node<Entry>* BSTree_search(Node<Entry> *root, Entry &target){
    Node<Entry> *t = root;
    while(t != NULL){
        if (t->entry == target) return t;
        else if (t->entry > target){
            t = t->left_tree;
        }
        else t = t->right_tree;
    }
    return nullptr;
}

template <class Entry>
void BSTree_insert(Node<Entry> *&root, const Entry &target){
    if (!root){
        root = new Node<Entry>(target);
        return;
    }
    Node<Entry> *t = root;
    while(1){
        if (t->entry == target) return;
        else if (t->entry > target){
            if (!t->left){
                t->left = new Node<Entry>(target);
                return;
            }
            t = t->left;
        }
        else{
            if (!t->right){
                t->right = new Node<Entry>(target);
                return;
            }
            t = t->right;
        }
    }
}