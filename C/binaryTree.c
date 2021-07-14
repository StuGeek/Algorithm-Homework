#include <stdio.h>
#include <stdlib.h>

#define TYPE int

//二叉树
typedef struct binary_tree{
	TYPE node_value;
	struct binary_tree *left_tree;
	struct binary_tree *right_tree;
} *Binary_tree;

//创建带结点的二叉树结点
Binary_tree creat_Binary_tree(TYPE val){
	Binary_tree tree = (Binary_tree)malloc(sizeof(struct binary_tree));
	tree->node_value = val;
	tree->left_tree = NULL;
	tree->right_tree = NULL;
	return tree;
}

Binary_tree left_tree(Binary_tree tree){
    return tree->left_tree;
}

Binary_tree right_tree(Binary_tree tree){
    return tree->right_tree;
}

int is_leaf(Binary_tree tree){
    return tree->left_tree == NULL && tree->right_tree == NULL;
}

int height(Binary_tree tree){
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

//释放二叉树所申请的动态内存
void Binary_tree_clear(Binary_tree tree){
	if (tree->left_tree != NULL){
		Binary_tree_clear(tree->left_tree);
	}
	if (tree->right_tree != NULL){
		Binary_tree_clear(tree->right_tree);
	}
	free(tree);
	tree = NULL;
}

void attach(Binary_tree tree, TYPE val){
    if (tree->left_tree == NULL){
        tree->left_tree = creat_Binary_tree(val);
    }
    else{
        Binary_tree t = tree->left_tree;
        while(t->right_tree != NULL){
            t = t->right_tree;
        }
        t->right_tree = creat_Binary_tree(val);
    }
}

int size(Binary_tree tree){
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

//前序遍历二叉树
void preOrderOfBinaryTree(Binary_tree binary_tree){
	if (binary_tree != NULL){
		printf("%d ", binary_tree->node_value);
		preOrderOfBinaryTree(binary_tree->left_tree);
		preOrderOfBinaryTree(binary_tree->right_tree);
	}
}

//中序遍历二叉树
void inOrderOfBinaryTree(Binary_tree binary_tree){
	if (binary_tree != NULL){
		inOrderOfBinaryTree(binary_tree->left_tree);
		printf("%d ", binary_tree->node_value);
		inOrderOfBinaryTree(binary_tree->right_tree);
	}
}

//后序遍历二叉树
void postOrderOfBinaryTree(Binary_tree binary_tree){
	if (binary_tree != NULL){
		postOrderOfBinaryTree(binary_tree->left_tree);
		postOrderOfBinaryTree(binary_tree->right_tree);
		printf("%d ", binary_tree->node_value);
	}
}

int main(){
    Binary_tree tree = creat_Binary_tree(6);
	tree->left_tree = creat_Binary_tree(1);
	tree->right_tree = creat_Binary_tree(3);
	tree->left_tree->left_tree = creat_Binary_tree(4);
	tree->left_tree->right_tree = creat_Binary_tree(5);
	tree->right_tree->left_tree = creat_Binary_tree(2);
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