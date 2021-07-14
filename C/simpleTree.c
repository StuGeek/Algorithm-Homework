#include <stdio.h>
#include <stdlib.h>

#define TYPE int

//普通有序根树
typedef struct simple_tree{
	TYPE node_value;
	struct simple_tree *first_child_tree;
	struct simple_tree *next_sibling_tree;
} *Simple_tree;

//创建带结点值的普通有序根树结点
Simple_tree creat_Simple_tree(TYPE val){
	Simple_tree tree = (Simple_tree)malloc(sizeof(struct simple_tree));
	tree->node_value = val;
	tree->first_child_tree = NULL;
	tree->next_sibling_tree = NULL;
	return tree;
}

Simple_tree first_child(Simple_tree tree){
	return tree->first_child_tree;
}

Simple_tree next_sibling(Simple_tree tree){
	return tree->next_sibling_tree;
}

int degree(Simple_tree tree){
    int count = 0;
    for (Simple_tree t = tree->first_child_tree; t != NULL; t = t->next_sibling_tree){
        count++;
    }
    return count;
}

int is_leaf(Simple_tree tree){
    return tree->first_child_tree == NULL;
}

Simple_tree child(Simple_tree tree, int n){
    if (tree == NULL) return NULL;
    Simple_tree t = tree->first_child_tree;
    while(n--){
        if (t == NULL) return NULL;
        t = t->next_sibling_tree;
    }
    return t;
}

int height(Simple_tree tree){
    int h = 0;
    for (Simple_tree t = tree->first_child_tree; t != NULL; t = t->next_sibling_tree){
        int temp = height(t);
        h = h > 1 + temp ? h : 1 + temp;
    }
    return h;
}

//向普通有序根树的结点添加儿子结点
void Simple_tree_append(Simple_tree tree, TYPE val){
	//如果结点没有儿子，那么新添加的结点作为该结点的第一个儿子
	if (tree->first_child_tree == NULL){
		tree->first_child_tree = creat_Simple_tree(val);
	}
	//如果结点有儿子，那么新添加的结点作为该结点的最后一个儿子
	else{
		Simple_tree p = tree->first_child_tree;
		while(p->next_sibling_tree != NULL){
			p = p->next_sibling_tree;
		}
		p->next_sibling_tree = creat_Simple_tree(val);
	}
}

//释放普通有序根树所申请的动态内存
void Simple_tree_clear(Simple_tree tree){
	if (tree != NULL){
		if (tree->first_child_tree != NULL){
			Simple_tree p = tree->first_child_tree;
			Simple_tree next = p->next_sibling_tree;
			while(p != NULL){
				Simple_tree_clear(p);
				p = next;
				if (p == NULL) break;
				next = p->next_sibling_tree;
			}
		}
		free(tree);
		tree = NULL;
	}
}

int size(Simple_tree tree){
    if (tree == NULL) return 0;
    int count = 1;
    if (tree->first_child_tree != NULL){
        count += size(tree->first_child_tree);
    }
    if (tree->next_sibling_tree != NULL){
        count += size(tree->next_sibling_tree);
    }
    return count;
}

//前序遍历普通有序根树
void preOrderOfSimpleTree(Simple_tree simple_tree){
	if (simple_tree != NULL){
		printf("%d ", simple_tree->node_value);
		for (Simple_tree t = simple_tree->first_child_tree; t != NULL; t = t->next_sibling_tree){
			preOrderOfSimpleTree(t);
		}   
	}
}

//中序遍历普通有序根树
void inOrderOfSimpleTree(Simple_tree simple_tree){
	if (simple_tree != NULL){
		if (simple_tree->first_child_tree == NULL){
			printf("%d ", simple_tree->node_value);
		}
		else{
			inOrderOfSimpleTree(simple_tree->first_child_tree);
			printf("%d ", simple_tree->node_value);
			for (Simple_tree t = simple_tree->first_child_tree->next_sibling_tree; t != NULL; t = t->next_sibling_tree){
				inOrderOfSimpleTree(t);
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
		}
	}
}

//后序遍历普通有序根树
void postOrderOfSimpleTree(Simple_tree simple_tree){
	if (simple_tree != NULL){
		if (simple_tree->first_child_tree == NULL){
			printf("%d ", simple_tree->node_value);
		}
		else{
			for (Simple_tree t = simple_tree->first_child_tree; t != NULL; t = t->next_sibling_tree){
				postOrderOfSimpleTree(t);
			}
			printf("%d ", simple_tree->node_value);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
		}
	}
}

int main(){
    Simple_tree tree = creat_Simple_tree(6);
	Simple_tree_append(tree, 1);
	Simple_tree_append(tree, 3);
	Simple_tree_append(tree, 4);
	Simple_tree_append(tree, 5);
	Simple_tree_append(tree, 2);
	printf("%d\n", size(tree));
	printf("%d\n", height(tree));
	printf("%d\n", degree(tree));
	printf("%d\n", first_child(tree)->node_value);
	printf("%d\n", next_sibling(first_child(tree))->node_value);
	printf("%d\n", next_sibling(next_sibling(first_child(tree)))->node_value);
	printf("%d\n", is_leaf(tree));
	printf("%d\n", is_leaf(first_child(tree)));
    clear(tree);
}