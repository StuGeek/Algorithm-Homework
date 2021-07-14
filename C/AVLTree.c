#include <stdio.h>
#include <stdlib.h>

#define TYPE int
#define BOOL int
#define TRUE 1
#define FALSE 0

int max(int a, int b){
    return a > b ? a : b;
}

typedef struct AVLNode{
    TYPE node_value;
    struct AVLNode *left_tree;
    struct AVLNode *right_tree;
    int height;
} *AVLTree;

AVLTree creat_AVLTree(TYPE val){
    AVLTree tree = (AVLTree)malloc(sizeof(struct AVLNode));
    tree->node_value = val;
    tree->left_tree = NULL;
    tree->right_tree = NULL;
    tree->height = 0;
    return tree;
}

AVLTree left_tree(AVLTree node){
    return node->left_tree;
}

AVLTree right_tree(AVLTree node){
    return node->right_tree;
}

//利用AVL树结点的结点域中的高度值可以直接判断高度
int height(AVLTree tree){
    //如果结点为空，直接返回-1
    if (tree == NULL) return -1;
    else return tree->height;
}

//如果利用递归算法判断高度，可以省去结点域中的高度值，但会付出额外的时间
/*int height(AVLTree tree){
    if (tree == NULL) return 0;
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
}*/

//求AVL树中某个结点的平衡因子
int getBalancedFactor(AVLTree node){
    if (node != NULL) {
        return height(node->left_tree) - height(node->right_tree);
    }
    else return -1;
}

//不平衡情况为左-左的情况，进行单旋转
AVLTree Left_Left_Rotation(AVLTree tree){
    AVLTree b = tree->left_tree;
    AVLTree BR = b->right_tree;
    b->right_tree = tree;
    tree->left_tree = BR;
    //旋转完后重新判断结点高度
    tree->height = 1 + max(height(tree->left_tree), height(tree->right_tree));
    b->height = 1 + max(height(b->left_tree), height(b->right_tree));
    return b;
}

//不平衡情况为右-右的情况，进行单旋转
AVLTree Right_Right_Rotation(AVLTree tree){
    AVLTree b = tree->right_tree;
    AVLTree BR = b->left_tree;
    b->left_tree = tree;
    tree->right_tree = BR;
    tree->height = 1 + max(height(tree->left_tree), height(tree->right_tree));
    b->height = 1 + max(height(b->left_tree), height(b->right_tree));
    return b;
}

//不平衡情况为左-右的情况，进行双旋转
AVLTree Left_Right_Rotation(AVLTree tree){
    AVLTree b = tree->left_tree;
    AVLTree d = b->right_tree;
    AVLTree DL = d->left_tree;
    AVLTree DR = d->right_tree;
    d->left_tree = b;
    d->right_tree = tree;
    b->right_tree = DL;
    tree->left_tree = DR;
    tree->height = 1 + max(height(tree->left_tree), height(tree->right_tree));
    b->height = 1 + max(height(b->left_tree), height(b->right_tree));
    d->height = 1 + max(height(d->left_tree), height(d->right_tree));
    return d;
}

//不平衡情况为右-左的情况，进行双旋转
AVLTree Right_Left_Rotation(AVLTree tree){
    AVLTree b = tree->right_tree;
    AVLTree d = b->left_tree;
    AVLTree DL = d->left_tree;
    AVLTree DR = d->right_tree;
    d->right_tree = b;
    d->left_tree = tree;
    b->left_tree = DR;
    tree->right_tree = DL;
    tree->height = 1 + max(height(tree->left_tree), height(tree->right_tree));
    b->height = 1 + max(height(b->left_tree), height(b->right_tree));
    d->height = 1 + max(height(d->left_tree), height(d->right_tree));
    return d;
}

BOOL is_leaf(AVLTree tree){
    return tree->left_tree == NULL && tree->right_tree == NULL;
}

TYPE front(AVLTree tree){
    if (tree == NULL) return 0;
    AVLTree t = tree;
    while(t->left_tree != NULL){
        t = t->left_tree;
    }
    return t->node_value;
}

TYPE back(AVLTree tree){
    if (tree == NULL) return 0;
    AVLTree t = tree;
    while(t->right_tree != NULL){
        t = t->right_tree;
    }
    return t->node_value;
}

BOOL find(AVLTree tree, TYPE val){
    AVLTree t = tree;
    while(t != NULL){
        if (t->node_value == val) return 1;
        else if (t->node_value > val){
            t = t->left_tree;
        }
        else t = t->right_tree;
    }
    return 0;
}

//向AVL树中插入一个结点
AVLTree insert(AVLTree tree, TYPE val){
    //如果结点为空，说明找到了该插入的位置，直接插入结点
    if (tree == NULL){
        tree = creat_AVLTree(val);
        return tree;
    }
    //如果树中已经有了该结点值的结点，则插入失败
    else if (tree->node_value == val){
        printf("插入%d失败，AVL树中已有该值\n", tree->node_value);
        return NULL;
    }
    //如果插入的结点值小于该结点值，则利用递归在该结点的左子树中寻找插入位置
    else if (tree->node_value > val){
        tree->left_tree = insert(tree->left_tree, val);
        //插入完成后，因为使用的是递归算法，所以会从叶子向根结点结束递归，如果在这个过程中发现有不平衡的结点，则进行相应旋转
        if (height(tree->left_tree) - height(tree->right_tree) > 1){
            //因为是向该结点的左子树插入结点，所以进行的旋转只有可能是左-左，左-右两种情况
            if (tree->left_tree->node_value > val){
                //如果该结点的左子树的结点值大于插入值，说明是向左子树的左子树插入结点，为左-左的情况
                tree = Left_Left_Rotation(tree);
            }
            //否则为左-右的情况
            else tree = Left_Right_Rotation(tree);
        }
    }
    //如果插入的结点值大于该结点值，则利用递归在该结点的右子树中寻找插入位置
    else{
        tree->right_tree = insert(tree->right_tree, val);
        //因为是向该结点的右子树插入结点，所以进行的旋转只有可能是右-左，右-右两种情况
        if (height(tree->right_tree) - height(tree->left_tree) > 1){
            //如果该结点的右子树的结点值大于插入值，说明是向右子树的左子树插入结点，为右-左的情况
            if (tree->right_tree->node_value > val){
                tree = Right_Left_Rotation(tree);
            }
            //否则为右-右的情况
            else tree = Right_Right_Rotation(tree);
        }
    }
    //重新调整结点的高度
    tree->height = 1 + max(height(tree->left_tree), height(tree->right_tree));
    return tree;
}

/*BOOL insert(AVLTree tree, TYPE val){
    if (tree == NULL){
        tree = creat_AVLTree(val);
        return 1;
    }
    AVLTree t = tree;
    while(1){
        if (t->node_value == val) return 0;
        else if (t->node_value > val){
            if (t->left_tree == NULL){
                t->left_tree = creat_AVLTree(val);
                return 1;
            }
            t = t->left_tree;
        }
        else{
            if (t->right_tree == NULL){
                t->right_tree = creat_AVLTree(val);
                return 1;
            }
            t = t->right_tree;
        }
    }
}*/

/*BOOL erase(AVLTree tree, TYPE val){
    if (tree == NULL) return 0;
    if (tree->node_value == val){
        free(tree);
        tree = NULL;
    }
    AVLTree pre = tree;
    AVLTree t = NULL;
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
                AVLTree temp = t->right_tree;
                while(temp->left_tree != NULL){
                    temp = temp->left_tree;
                }
                AVLTree p = temp;
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
}*/

int size(AVLTree tree){
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

TYPE at(AVLTree tree, int k){
    int left_tree_size = size(tree->left_tree);
    if (left_tree_size == k){
        return tree->node_value;
    }
    else if (left_tree_size > k){
        return at(tree->left_tree, k);
        
    }
    else return at(tree->right_tree, k - left_tree_size - 1);
}

TYPE next(AVLTree tree, TYPE val){
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

//释放AVL树所申请的动态内存
void clear(AVLTree tree){
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

//前序遍历AVL树
void preOrderTraverse(AVLTree tree){
    if (tree != NULL){
        printf("%d ", tree->node_value);
        preOrderTraverse(tree->left_tree);
        preOrderTraverse(tree->right_tree);
    }
}

//中序遍历AVL树
void inOrderTraverse(AVLTree tree){
    if (tree != NULL){
        inOrderTraverse(tree->left_tree);
        printf("%d ", tree->node_value);
        inOrderTraverse(tree->right_tree);
    }
}

//后序遍历AVL树
void postOrderTraverse(AVLTree tree){
    if (tree != NULL){
        postOrderTraverse(tree->left_tree);
        postOrderTraverse(tree->right_tree);
        printf("%d ", tree->node_value);
    }
}

int main(){
    AVLTree tree = NULL;
    tree = insert(tree, 6);
	tree = insert(tree, 1);
	tree = insert(tree, 3);
	tree = insert(tree, 4);
	tree = insert(tree, 5);
	tree = insert(tree, 2);
    preOrderTraverse(tree);
    printf("\n");
    inOrderTraverse(tree);
    printf("\n");
    postOrderTraverse(tree);
    printf("\n");
    clear(tree);
}