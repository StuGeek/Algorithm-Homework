#include <stdio.h>
#include <stdlib.h>

#define TYPE int

typedef struct Binary_search_node{
    TYPE node_value;
    struct Binary_search_node *left_tree;
    struct Binary_search_node *right_tree;
} *Binary_search_tree;

Binary_search_tree creat_BST(TYPE val){
    Binary_search_tree tree = (Binary_search_tree)malloc(sizeof(struct Binary_search_node));
    tree->node_value = val;
    tree->left_tree = NULL;
    tree->right_tree = NULL;
    return tree;
}

Binary_search_tree left_tree(Binary_search_tree tree){
    return tree->left_tree;
}

Binary_search_tree right_tree(Binary_search_tree tree){
    return tree->right_tree;
}

int is_leaf(Binary_search_tree tree){
    return tree->left_tree == NULL && tree->right_tree == NULL;
}

Binary_search_tree front(Binary_search_tree tree){
    if (tree == NULL) return NULL;
    Binary_search_tree t = tree;
    while(t->left_tree != NULL){
        t = t->left_tree;
    }
    return t;
}

Binary_search_tree back(Binary_search_tree tree){
    if (tree == NULL) return NULL;
    Binary_search_tree t = tree;
    while(t->right_tree != NULL){
        t = t->right_tree;
    }
    return t;
}

Binary_search_tree find(Binary_search_tree tree, TYPE val){
    Binary_search_tree t = tree;
    while(t != NULL){
        if (t->node_value == val) return t;
        else if (t->node_value > val){
            t = t->left_tree;
        }
        else t = t->right_tree;
    }
    return NULL;
}

int insert(Binary_search_tree tree, TYPE val){
    if (tree == NULL){
        tree = creat_BST(val);
        return 1;
    }
    Binary_search_tree t = tree;
    while(1){
        if (t->node_value == val) return 0;
        else if (t->node_value > val){
            if (t->left_tree == NULL){
                t->left_tree = creat_BST(val);
                return 1;
            }
            t = t->left_tree;
        }
        else{
            if (t->right_tree == NULL){
                t->right_tree = creat_BST(val);
                return 1;
            }
            t = t->right_tree;
        }
    }
}

int erase(Binary_search_tree tree, TYPE val){
    if (tree == NULL) return 0;
    if (tree->node_value == val){
        Binary_search_tree t = tree;
        if (tree->right_tree != NULL) t = front(tree->right_tree);
        else t = back(tree->left_tree);
        if (t == NULL){
            free(tree);
            tree = NULL;
            return 1;
        }
        TYPE p = tree->node_value;
        tree->node_value = t->node_value;
        t->node_value = p;
        erase(t, val);
        return 1;
    }
    Binary_search_tree pre = tree;
    Binary_search_tree t = NULL;
    if (pre->node_value > val) t = pre->left_tree;
    else t = pre->right_tree;
    while(t != NULL){
        if (t->node_value == val){
            if (t->left_tree == NULL && t->right_tree == NULL){
                if (pre->left_tree == t){
                    pre->left_tree = NULL;
                }
                else pre->right_tree = NULL;
                free(t);
                t = NULL;
            }
            else if (t->left_tree == NULL || t->right_tree == NULL){
                if (pre->left_tree == t){
                    pre->left_tree = t->left_tree == NULL ? t->right_tree : t->left_tree;
                }
                else pre->right_tree = t->left_tree == NULL ? t->right_tree : t->left_tree;
                free(t);
                t = NULL;
            }
            else{
                Binary_search_tree temp = t->right_tree;
                while(temp->left_tree != NULL){
                    temp = temp->left_tree;
                }
                TYPE p = temp->node_value;
                temp->node_value = t->node_value;
                t->node_value = p;
                erase(pre, val);
            }
            return 0;
        }
        else if (t->node_value > val){
            pre = t;
            t = t->left_tree;
        }
        else{
            pre = t;
            t = t->right_tree;
        }
    }
    return 0;
}

int height(Binary_search_tree tree){
    int h = 0;
    if (tree->left_tree == NULL){
        if (tree->right_tree != NULL){
            h += 1 + height(tree->right_tree);
        }
    }
    else{
        h += 1 + height(tree->left_tree);
        if (tree->right_tree != NULL) {
            int t = 1 + height(tree->right_tree);
            h = h > t ? h : t;
        }
    }
    return h;
}

int size(Binary_search_tree tree){
    if (tree == NULL) return 0;
    int count = 1;
    if (tree->left_tree != NULL){
        count += size(tree->left_tree);
    }
    if (tree->right_tree != NULL){
        count += size(tree->right_tree);
    }
    return count;
}

TYPE at(Binary_search_tree tree, int k){
    int left_tree_size = size(tree->left_tree);
    if (left_tree_size == k){
        return tree->node_value;
    }
    else if (left_tree_size > k){
        return at(tree->left_tree, k);
        
    }
    else return at(tree->right_tree, k - left_tree_size - 1);
}

TYPE next(Binary_search_tree tree, TYPE val){
    if (tree == NULL) return val;
    else if (tree->node_value == val){
        return tree->right_tree == NULL ? val : front(tree->right_tree);
    }
    else if (tree->node_value > val){
        TYPE t = next(tree->left_tree, val);
        return t == val ? tree->node_value : t;
    }
    else return next(tree->right_tree, val);
}

void clear(Binary_search_tree tree){
    if (tree != NULL){
        if (tree->left_tree != NULL){
            clear(tree->left_tree);
        }
        if (tree->right_tree != NULL){
            clear(tree->right_tree);
        }
        free(tree);
        tree = NULL;
    }
}

void preOrderTraverse_none_recursive(Binary_search_tree tree){
    Binary_search_tree stack[100];
    Binary_search_tree p = tree;
    int top = 0;
    if (tree == NULL) return;
    else{
        do{
            printf("%d ", p->node_value);
            if (p->right_tree != NULL) stack[++top] = p->right_tree;
            p = p->left_tree;
            if (p == NULL) p = stack[top--];
        }
        while(top != 0);
    }
}

void preOrderTraverse(Binary_search_tree tree){
    if (tree != NULL){
        printf("%d ", tree->node_value);
        preOrderTraverse(tree->left_tree);
        preOrderTraverse(tree->right_tree);
    }
}

void inOrderTraverse_non_recursive(Binary_search_tree tree){
    Binary_search_tree stack[100];
    Binary_search_tree p = tree;
    int top = 0;
    if (tree == NULL) return;
    else{
        do{
            while(p != NULL){
                stack[top++] = p;
                p = p->left_tree;
            }
            if (top != 0){
                p = stack[--top];
                printf("%d ", p->node_value);
                p = p->right_tree;
            }
        }
        while(top != 0);
    }
}

void inOrderTraverse(Binary_search_tree tree){
    if (tree != NULL){
        inOrderTraverse(tree->left_tree);
        printf("%d ", tree->node_value);
        inOrderTraverse(tree->right_tree);
    }
}

void postOrderTraverse(Binary_search_tree tree){
    if (tree != NULL){
        postOrderTraverse(tree->left_tree);
        postOrderTraverse(tree->right_tree);
        printf("%d ", tree->node_value);
    }
}

int main(){
    Binary_search_tree tree = creat_BST(6);
	insert(tree, 1);
	insert(tree, 3);
    insert(tree, 5);
	insert(tree, 4);
	insert(tree, 2);
    preOrderTraverse(tree);
    printf("\n");
    preOrderTraverse_none_recursive(tree);
    printf("\n");
    inOrderTraverse_non_recursive(tree);
	printf("%d\n", size(tree));
	printf("%d\n", height(tree));
    printf("%d\n", at(tree, 3));
    printf("%d\n", next(tree, 1));
	printf("%d\n", left_tree(tree)->node_value);
	printf("%d\n", right_tree(left_tree(tree))->node_value);
	printf("%d\n", front(tree));
	printf("%d\n", back(tree));
    clear(tree);
}

/*
    6
  1
   3
  2 5
   4
*/