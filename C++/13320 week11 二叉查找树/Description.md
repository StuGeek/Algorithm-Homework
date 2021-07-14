# week11 二叉查找树

### 题目描述
请完成以下二叉查找树的查找和插入函数的定义：
```
#ifndef NODE
#define NODE

template <class Entry>
struct Node
{
	Entry entry;
	Node<Entry> *left;
	Node<Entry> *right;

	Node(const Entry &en)
	{
		entry = en;
		left = NULL;
		right = NULL;
	}
};

#endif

// 二叉查找树的查找函数
// 查找target所在的位置，如果target存在二叉查找树中，则返回该结点的指针
// 否则返回NULL
template <class Entry>
Node<Entry>* BSTree_search(Node<Entry> *root, Entry &target);

// 二叉查找树的插入函数
// 将target插入到二叉查找树中，二叉查找树的结点满足以下条件：
// 1、任意结点的左子树中的元素小于该结点的元素
// 2、任意结点的右子树中的元素大于该结点的元素
// 3、同一个元素在二叉查找树中只会出现一次
template <class Entry>
void BSTree_insert(Node<Entry> *&root, const Entry &target);

```

### 注意
只需要提交函数实现，不需要提交main函数
