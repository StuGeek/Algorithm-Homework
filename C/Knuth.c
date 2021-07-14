#include <stdio.h>
#include <stdlib.h>

#define BOOL int
#define TYPE int
#define TRUE 1
#define FALSE 0

//普通有序根树
typedef struct simple_tree{
	TYPE node_value;
	struct simple_tree *first_child_tree;
	struct simple_tree *next_sibling_tree;
} *Simple_tree;

//二叉树
typedef struct binary_tree{
	TYPE node_value;
	struct binary_tree *left_tree;
	struct binary_tree *right_tree;
} *Binary_tree;

//创建带结点值的简单有序根树结点
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

//向简单有序根树的结点添加儿子结点
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

//释放简单有序根树所申请的动态内存
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

//创建带结点的二叉树结点
Binary_tree creat_Binary_tree(TYPE val){
	Binary_tree tree = (Binary_tree)malloc(sizeof(struct binary_tree));
	tree->node_value = val;
	tree->left_tree = NULL;
	tree->right_tree = NULL;
	return tree;
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

//将简单有序根树转化为LCRS树的Knuth算法
Binary_tree Knuth(Simple_tree simple_tree){
	//如果结点为空，直接返回NULL
	if (simple_tree == NULL) return NULL;
	//否则创建值相同的对应的二叉树结点
	Binary_tree binary_tree = creat_Binary_tree(simple_tree->node_value);
	//利用递归算法将简单有序根树结点的第一个子树转化为对应的二叉树结点的左子树
	binary_tree->left_tree = Knuth(simple_tree->first_child_tree);
	//如果简单有序根树没有儿子，直接返回对应的二叉树结点
	if (simple_tree->first_child_tree == NULL) return binary_tree;
	//否则利用递归算法将其所有的子树转化为对应的二叉树
	Binary_tree t = binary_tree->left_tree;
	Simple_tree temp = simple_tree->first_child_tree->next_sibling_tree;
	//简单有序根树除第一个子树之外的其它子树依次转化为前一个子树对应的二叉树的右子树
	while(temp != NULL){
		t->right_tree = Knuth(temp);
		t = t->right_tree;
		temp = temp->next_sibling_tree;
	}
	//返回对应的二叉树结点
	return binary_tree;
}

//前序遍历简单有序根树
void preOrderOfSimpleTree(Simple_tree simple_tree){
	if (simple_tree != NULL){
		printf("%d ", simple_tree->node_value);
		for (Simple_tree t = simple_tree->first_child_tree; t != NULL; t = t->next_sibling_tree){
			preOrderOfSimpleTree(t);
		}   
	}
}

//中序遍历简单有序根树
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

//后序遍历简单有序根树
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
	//example 1
	printf("Example1:\n");
	Simple_tree simple_tree1 = creat_Simple_tree(6);
	Simple_tree_append(simple_tree1, 1);
	Simple_tree_append(simple_tree1, 3);
	Simple_tree_append(simple_tree1->first_child_tree, 4);
	Simple_tree_append(simple_tree1->first_child_tree->next_sibling_tree, 5);
	Simple_tree_append(simple_tree1, 2);
	Binary_tree binary_tree1 = Knuth(simple_tree1);
	printf("原来的普通有序根树的前序遍历次序为: ");
	preOrderOfSimpleTree(simple_tree1);
	printf("\n");
	printf("原来的普通有序根树的中序遍历次序为: ");
	inOrderOfSimpleTree(simple_tree1);
	printf("\n");
	printf("原来的普通有序根树的后序遍历次序为: ");
	postOrderOfSimpleTree(simple_tree1);
	printf("\n");
	printf("经过Kunth转换后得到的二叉树的前序遍历次序为: ");
	preOrderOfBinaryTree(binary_tree1);
	printf("\n");
	printf("经过Kunth转换后得到的二叉树的中序遍历次序为: ");
	inOrderOfBinaryTree(binary_tree1);
	printf("\n");
	printf("原来的普通有序根树的后序遍历次序和经过Kunth转换后得到的二叉树的中序遍历次序相同\n");
	printf("\n");
	Simple_tree_clear(simple_tree1);
	Binary_tree_clear(binary_tree1);
	//example 2
	printf("Example2:\n");
	Simple_tree simple_tree2 = creat_Simple_tree(6);
	Simple_tree_append(simple_tree2, 1);
	Simple_tree_append(simple_tree2, 3);
	Simple_tree_append(simple_tree2, 2);
	Simple_tree_append(simple_tree2, 5);
	Simple_tree_append(simple_tree2, 4);
	Binary_tree binary_tree2 = Knuth(simple_tree2);
	printf("原来的普通有序根树的前序遍历次序为: ");
	preOrderOfSimpleTree(simple_tree2);
	printf("\n");
	printf("原来的普通有序根树的中序遍历次序为: ");
	inOrderOfSimpleTree(simple_tree2);
	printf("\n");
	printf("原来的普通有序根树的后序遍历次序为: ");
	postOrderOfSimpleTree(simple_tree2);
	printf("\n");
	printf("经过Kunth转换后得到的二叉树的前序遍历次序为: ");
	preOrderOfBinaryTree(binary_tree2);
	printf("\n");
	printf("经过Kunth转换后得到的二叉树的中序遍历次序为: ");
	inOrderOfBinaryTree(binary_tree2);
	printf("\n");
	printf("原来的普通有序根树的后序遍历次序和经过Kunth转换后得到的二叉树的中序遍历次序相同\n");
	printf("\n");
	Simple_tree_clear(simple_tree2);
	Binary_tree_clear(binary_tree2);
	//example 3
	printf("Example3:\n");
	Simple_tree simple_tree3 = creat_Simple_tree(6);
	Simple_tree_append(simple_tree3, 1);
	Simple_tree_append(simple_tree3, 3);
	Simple_tree_append(simple_tree3, 2);
	Simple_tree_append(simple_tree3->first_child_tree->next_sibling_tree->next_sibling_tree, 4);
	Simple_tree_append(simple_tree3->first_child_tree->next_sibling_tree->next_sibling_tree->first_child_tree, 5);
	Binary_tree binary_tree3 = Knuth(simple_tree3);
	printf("原来的普通有序根树的前序遍历次序为: ");
	preOrderOfSimpleTree(simple_tree3);
	printf("\n");
	printf("原来的普通有序根树的中序遍历次序为: ");
	inOrderOfSimpleTree(simple_tree3);
	printf("\n");
	printf("原来的普通有序根树的后序遍历次序为: ");
	postOrderOfSimpleTree(simple_tree3);
	printf("\n");
	printf("经过Kunth转换后得到的二叉树的前序遍历次序为: ");
	preOrderOfBinaryTree(binary_tree3);
	printf("\n");
	printf("经过Kunth转换后得到的二叉树的中序遍历次序为: ");
	inOrderOfBinaryTree(binary_tree3);
	printf("\n");
	printf("原来的普通有序根树的后序遍历次序和经过Kunth转换后得到的二叉树的中序遍历次序相同\n");
	printf("\n");
	Simple_tree_clear(simple_tree3);
	Binary_tree_clear(binary_tree3);
}
/*
example1:

简单有序根树:
      6
	/ | \ 
   1  3  2
  /  /
 4  5

经过Knuth转换后得到的二叉树:
       6
	  /
	 1
	/ \
   4   3
      / \
	 5   2

example2:

简单有序根树:
      6
  / / | \ \ 
 1 3  2  5 4

经过Knuth转换后得到的二叉树:
       6
	  /
	 1
	  \
       3
        \
	     2
		  \
		   5
		    \
			 4

example3:

简单有序根树:
      6
	/ | \ 
   1  3  2
        /
	   4
	  /
	 5
   

经过Knuth转换后得到的二叉树:
       6
	  /
	 1
	  \
       3
        \
	     2
		/
	   4
	  /
	 5  


*/