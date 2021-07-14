#include <stdio.h>
#include <stdlib.h>

#define TYPE int
#define KEYTYPE int
#define RECTYPE int
#define M 5

typedef struct bTree{
    int keynum;
    struct bTree *parent;
    KEYTYPE key[M + 1];
    struct bTree *ptr[M + 1];
    RECTYPE *recptr[M + 1];
} *BTree;

BTree creat_BTree(TYPE val){
    BTree tree = (BTree)malloc(sizeof(struct bTree));
    tree->node_value = val;
    tree->left_tree = NULL;
    tree->right_tree = NULL;
    return tree;
}

int search(BTree T, KEYTYPE K, BTree p) {
    BTree q = T;
    int i;
    while (q != NULL) {
		p = q;
		q->key[0] = K;
		for (i = q->keynum; K < q->key[i]; i--){
			if (i > 0 && q->key[i] == K)) return i;
		}
		q = q->ptr[i];
    }
    return 0;
}

int is_leaf(BTree tree){
    return tree->left_tree == NULL && tree->right_tree == NULL;
}

TYPE front(BTree tree){
    if (tree == NULL) return 0;
    BTree t = tree;
    while(t->left_tree != NULL){
        t = t->left_tree;
    }
    return t->node_value;
}

TYPE back(BTree tree){
    if (tree == NULL) return 0;
    BTree t = tree;
    while(t->right_tree != NULL){
        t = t->right_tree;
    }
    return t->node_value;
}

int find(BTree tree, TYPE val){
    BTree t = tree;
    while(t != NULL){
        if (t->node_value == val) return 1;
        else if (t->node_value > val){
            t = t->left_tree;
        }
        else t = t->right_tree;
    }
    return 0;
}

int insert(BTree tree, TYPE val){
    if (tree == NULL){
        tree = creat_BTree(val);
        return 1;
    }
    BTree t = tree;
    while(1){
        if (t->node_value == val) return 0;
        else if (t->node_value > val){
            if (t->left_tree == NULL){
                t->left_tree = creat_BTree(val);
                return 1;
            }
            t = t->left_tree;
        }
        else{
            if (t->right_tree == NULL){
                t->right_tree = creat_BTree(val);
                return 1;
            }
            t = t->right_tree;
        }
    }
}

int erase(BTree tree, TYPE val){
    if (tree == NULL) return 0;
    if (tree->node_value == val){
        free(tree);
        tree = NULL;
    }
    BTree pre = tree;
    BTree t = NULL;
    if (pre->node_value > val) t = pre->left_tree;
    else t = pre->right_tree;
    while(t != NULL){
        if (t->node_value == val){
            if (t->left_tree == NULL && t->right_tree == NULL){
                free(t);
                t = NULL;
            }
            else if (t->left_tree == NULL || t->right_tree == NULL){
                if (pre->left_tree == t){
                    pre->left_tree = t->left_tree == NULL ? t->right_tree : t->left_tree;
                }
                else pre->right_tree = t->left_tree == NULL ? t->right_tree : t->left_tree;
            }
            else{
                BTree temp = t->right_tree;
                while(temp->left_tree != NULL){
                    temp = temp->left_tree;
                }
                BTree p = temp;
                temp = t;
                t = p;
                erase(temp, temp->node_value);
            }
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
}

int height(BTree tree){
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

int size(BTree tree){
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

TYPE at(BTree tree, int k){
    int left_tree_size = size(tree->left_tree);
    if (left_tree_size == k){
        return tree->node_value;
    }
    else if (left_tree_size > k){
        return at(tree->left_tree, k);
        
    }
    else return at(tree->right_tree, k - left_tree_size - 1);
}

TYPE next(BTree tree, TYPE val){
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

void clear(BTree tree){
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

void preOrderTraverse(BTree tree){
    if (tree != NULL){
        printf("%d ", tree->node_value);
        preOrderTraverse(tree->left_tree);
        preOrderTraverse(tree->right_tree);
    }
}

void inOrderTraverse(BTree tree){
    if (tree != NULL){
        inOrderTraverse(tree->left_tree);
        printf("%d ", tree->node_value);
        inOrderTraverse(tree->right_tree);
    }
}

void postOrderTraverse(BTree tree){
    if (tree != NULL){
        postOrderTraverse(tree->left_tree);
        postOrderTraverse(tree->right_tree);
        printf("%d ", tree->node_value);
    }
}

int main(){
    BTree tree = creat_BTree(6);
	insert(tree, 1);
	insert(tree, 3);
	insert(tree, 4);
	insert(tree, 5);
	insert(tree, 2);
    preOrderTraverse(tree);
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