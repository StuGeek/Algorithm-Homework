# week8 归并排序

请完成以下类的定义：
```
template <class Record>
struct Node
{
	Record entry;
	Node<Record> *next;
};

template <class Record>
class Sortable_list
{
public:
	Sortable_list();
	~Sortable_list();
	
	// 在第position个位置插入值为entry的元素，如果position为0则插入在链表头，以此类推
	// 输入数据中，position满足 0 <= position <= 链表元素数量
	void insert(int position, const Record &entry);

	// 输出链表的内容，每两个元素之间用一个空格隔开，最后一个元素之后没有空格，并且需要换行
	void print();

	// 对链表进行归并排序，你可以添加一些辅助函数，但不能改动类的成员变量
	void merge_sort();
private:
	Node<Record> *head;				// 链表头指针
};
```
