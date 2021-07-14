#include <stdio.h>
#include <stdlib.h>

#define TYPE int

typedef struct biThrTree{
    TYPE node_value;
    struct biThrTree *left_tree;
    struct biThrTree *right_tree;
    int left_tag;
    int right_tag;
} *BiThrTree;

BiThrTree creat_BiThrTree(TYPE val){
    BiThrTree tree = (BiThrTree)malloc(sizeof(BiThrTree));
    tree->node_value = val;
    tree->left_tree = NULL;
    tree->right_tree = NULL;
    tree->left_tag = 1;
    tree->right_tag = 1;
    return tree;
}

BiThrTree left_tree(BiThrTree tree){
    return tree->left_tree;
}

BiThrTree right_tree(BiThrTree tree){
    return tree->right_tree;
}

int is_leaf(BiThrTree tree){
    return tree->left_tree == NULL && tree->right_tree == NULL;
}

int height(BiThrTree tree){
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

void clear(BiThrTree tree){
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

void attach(BiThrTree tree, TYPE val){
    if (tree->left_tree == NULL){
        tree->left_tree = creat_BiThrTree(val);
    }
    else{
        BiThrTree t = tree->left_tree;
        while(t->right_tree != NULL){
            t = t->right_tree;
        }
        t->right_tree = creat_BiThrTree(val);
    }
}

int size(BiThrTree tree){
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

void inorder_Threading(BiThrTree tree) {
    BiThrTree stack[100];
    BiThrTree last = NULL, p = tree;
    int top = 0;
    while (p != NULL || top > 0){
        if (p != NULL) {
            stack[++top] = p;
            p = p->left_tree;
        }
        else {
            p = stack[top--];
            if (p->left_tree != NULL) p->left_tag = 0;
            else {
                p->left_tag = 1;
                p->left_tree = last;
            }
            if (last != NULL){
                if (last->right_tree != NULL) last->right_tag = 0;
                else {
                    last->right_tag = 1;
                    last->right_tree =p;
                }
            }
            last=p;
            p = p->right_tree;
        }
        last->right_tag = 1;
    }
}

void preOrderTraverse(BiThrTree tree){
    if (tree != NULL){
        printf("%d ", tree->node_value);
        preOrderTraverse(tree->left_tree);
        preOrderTraverse(tree->right_tree);
    }
}

void preOrderTraverse_none_recursive(BiThrTree tree){
    if (tree == NULL) return;
    BiThrTree t = tree;
    BiThrTree stack[100];
    int top = 1;
    if ()
}

void inOrderTraverse(BiThrTree tree){
    if (tree != NULL){
        inOrderTraverse(tree->left_tree);
        printf("%d ", tree->node_value);
        inOrderTraverse(tree->right_tree);
    }
}

void postOrderTraverse(BiThrTree tree){
    if (tree != NULL){
        postOrderTraverse(tree->left_tree);
        postOrderTraverse(tree->right_tree);
        printf("%d ", tree->node_value);
    }
}

int main(){
    BiThrTree tree = creat_BiThrTree(6);
	tree->left_tree = creat_BiThrTree(1);
	tree->right_tree = creat_BiThrTree(3);
	tree->left_tree->left_tree = creat_BiThrTree(4);
	tree->left_tree->right_tree = creat_BiThrTree(5);
	tree->right_tree->left_tree = creat_BiThrTree(2);
    preOrderTraverse(tree);
    printf("\n");
    inOrderTraverse(tree);
    printf("\n");
    postOrderTraverse(tree);
    printf("\n");
	printf("%d\n", size(tree));
	printf("%d\n", height(tree));
	printf("%d\n", left_tree(tree)->node_value);
	printf("%d\n", right_tree(left_tree(tree))->node_value);
	printf("%d\n", right_tree(left_tree(tree))->node_value);
	printf("%d\n", is_leaf(tree));
	printf("%d\n", is_leaf(left_tree(tree)));
    clear(tree);
}