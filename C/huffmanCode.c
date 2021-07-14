#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE int

typedef struct treeNode{
	TYPE node_value;
	unsigned int weight;
	unsigned int parent, Lchild, Rchild;
} *Huffman_tree;

int cmp(const void *a, const void *b)
{
   	return (*(int*)a - *(int*)b);
}

//获取输入的整数序列，并排序按照从小到大的顺序存储
int* getIntegerSequence(unsigned int n){
	if (n == 0) return NULL;
	int *a = (int *)malloc(n * sizeof(int));
	printf("请输入整数序列：");
	for (int i = 0; i < n; ++i){
		scanf("%d", &a[i]);
	}
	qsort(a, n, sizeof(int), cmp);
	return a;
}

//获取整数序列中不重复的元素个数
unsigned int getNumOfNotRepeatElement(int *a, unsigned int n){
	if (n == 0) return 0;
	unsigned int count = 1;
	for (int i = 1; i < n; ++i){
		if (a[i] == a[i - 1]) continue;
		count++;
	}
	return count;
}

//创建哈夫曼树
Huffman_tree Create_Huffman(int *a, unsigned int n) {
	//如果没有点，直接返回
	if (n == 0) return NULL;
	//获取整数数组中不重复的元素个数count
	unsigned int count = getNumOfNotRepeatElement(a, n);
	//创建一棵叶子结点数为count的Huffman树
	Huffman_tree tree = (Huffman_tree )malloc((2 * count - 1) * sizeof(struct treeNode));
	tree[0].node_value = a[0];
	tree[0].weight = 1;
	tree[0].parent = -1;
	tree[0].Lchild = -1;
	tree[0].Rchild = -1;
	int j = 0;
	for (int i = 1; i < n; ++i){
		//相同整数同一叶子结点权加1
		if (a[i] == a[i - 1]) tree[j].weight++;
		//不同整数则开辟另一叶子结点，权为1
		else{
			tree[++j].node_value = a[i];
			tree[j].weight = 1;
		}
		//每个叶子结点都被初始化
		tree[j].parent = -1;
		tree[j].Lchild = -1;
		tree[j].Rchild = -1;
	}
	//内部结点初始化
	for (int i = count; i < 2 * count - 1; ++i){
		tree[i].weight = 0;
		tree[i].parent = -1;
		tree[i].Lchild = -1;
		tree[i].Rchild = -1;
	}
	for (int i = count; i < 2 * count - 1; ++i) {
		//w1, w2分别保存权值最小的两个权值
		unsigned w1 = 32767, w2 = w1;
		//p1 , p2保存两个最小权值的下标
		int p1 = 0, p2 = 0;
		for (int j = 0; j < i; j++) {
			//寻找尚未合并的结点
			if (tree[j].parent == -1) {
				// 找到权值最小的两个值及其下标
				if (tree[j].weight < w1) {
					w2 = w1;
					p2 = p1;
					w1 = tree[j].weight;
					p1 = j;
				} else if (tree[j].weight < w2) {
					w2 = tree[j].weight;
					p2 = j;
				}
			} 
		}
		//合并结点
		tree[i].Lchild = p1;
		tree[i].Rchild = p2;
		tree[i].weight = w1 + w2;
		tree[p1].parent = i;
		tree[p2].parent = i;
  	}
	return tree;
}

//打印哈夫曼编码
void Huff_coding(Huffman_tree tree, unsigned n) {
	unsigned int *stack = (unsigned int *)malloc(n * sizeof(unsigned int));
	int top = 0;
	//逐个求字符的编码
    for (int i = 0; i < n; ++i) {
		int child_node = i;
		//从叶子结点到根逆向求编码
		for (unsigned int parent_node = tree[child_node].parent; parent_node != -1; parent_node = tree[parent_node].parent){
			if (tree[parent_node].Lchild == child_node){
				stack[top++] = 0;
			}
			else stack[top++] = 1;
			child_node = tree[child_node].parent;
		}
		//打印每个结点的哈夫曼编码
		printf("整数%d:", tree[i].node_value);
		while(top > 0){
			printf("%d", stack[--top]);
		}
		printf("\n");
    }
	free(stack);
}

//前序遍历二叉树
void preOrderOfHuffmanTree(Huffman_tree tree, unsigned n){
	if (tree == NULL) return;
	if (n != -1){
		printf("%d", tree[n].weight);
		if (tree[n].Lchild == -1 && tree[n].Rchild == -1) printf("(%d) ", tree[n].node_value);
		else printf(" ");
		preOrderOfHuffmanTree(tree, tree[n].Lchild);
		preOrderOfHuffmanTree(tree, tree[n].Rchild);
	}
}

//中序遍历二叉树
void inOrderOfHuffmanTree(Huffman_tree tree, unsigned n){
	if (tree == NULL) return;
	if (n != -1){
		inOrderOfHuffmanTree(tree, tree[n].Lchild);
		printf("%d", tree[n].weight);
		if (tree[n].Lchild == -1 && tree[n].Rchild == -1) printf("(%d) ", tree[n].node_value);
		else printf(" ");
		inOrderOfHuffmanTree(tree, tree[n].Rchild);
	}
}

int main(){
	unsigned int n;
	printf("请输入整数个数：");
	scanf("%d", &n);
	int *a = getIntegerSequence(n);
	unsigned int count = getNumOfNotRepeatElement(a, n);
	Huffman_tree tree = Create_Huffman(a, n);
	unsigned int root = 2 * count - 2;
	printf("哈夫曼树的前序遍历次序为（括号内为叶结点的结点值）：\n");
	preOrderOfHuffmanTree(tree, root);
	printf("\n");
	printf("哈夫曼树的中序遍历次序为（括号内为叶结点的结点值）：\n");
	inOrderOfHuffmanTree(tree, root);
	printf("\n");
	printf("每个整数对应哈夫曼编码的原型为:\n");
	Huff_coding(tree, count);
	if (a != NULL) free(a);
	if (tree != NULL) free(tree);
}