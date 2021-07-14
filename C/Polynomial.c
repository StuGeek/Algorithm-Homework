#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR -1
#define INITIAL_SIZE 30

int const null = -1;

/*表示一元多项式的每个项*/
typedef struct var
{
	float coef; // 系数部分
	int expn;	// 指数部分
	struct var *next;
} Var;

/*表示一元多项式*/
typedef struct
{
	int store_index;
	Var *head;
} Poly;

/*存储空闲下标的栈*/
typedef struct Node
{
	int index;
	struct Node *next;
} node;

typedef struct
{
	int size;
	node *top;
} Stack;

/*存储一元多项式的静态链表*/
typedef struct
{
	Poly *poly;
	int next_node;
} List;

typedef struct{
	List *list;
	int list_head;
	int capacity;
	Stack *stk;
} Lists;

/*创建一个一元多项式*/
Poly *creat_Poly()
{
	Poly *poly = (Poly *)malloc(sizeof(Poly));
	poly->head = (Var *)malloc(sizeof(Var));
	poly->head->next = NULL;
	return poly;
}

/*将元素添加到一元多项式中，并按指数从大到小排序*/
void addToPoly(Poly *mypoly, float coef, int expn)
{
	if (coef == 0)
		return;
	Var *pre = mypoly->head;
	Var *curr = mypoly->head->next;
	while (curr)
	{
		if (curr->expn == expn)
		{
			if (curr->coef + coef == 0)
			{
				pre->next = curr->next;
				free(curr);
				return;
			}
			else
			{
				curr->coef += coef;
				return;
			}
		}
		else if (curr->expn < expn)
		{
			Var *newNode = (Var *)malloc(sizeof(Var));
			newNode->coef = coef;
			newNode->expn = expn;
			pre->next = newNode;
			newNode->next = curr;
			return;
		}
		else
		{
			curr = curr->next;
			pre = pre->next;
		}
	}
	Var *newNode = (Var *)malloc(sizeof(Var));
	newNode->coef = coef;
	newNode->expn = expn;
	pre->next = newNode;
	newNode->next = NULL;
	return;
}

void printPoly(Poly *myPoly)
{
	Var *p = myPoly->head->next;
	while (p)
	{
		printf("%.2fx^%d", p->coef, p->expn);
		if (p->next != NULL && p->next->coef > 0)
		{
			printf("+");
		}
		p = p->next;
	}
	printf("\n");
}

/*释放一元多项式所申请的动态内存*/
void freePoly(Poly *myPoly)
{
	Var *t = myPoly->head;
	while (t != NULL)
	{
		Var *temp = t->next;
		free(t);
		t = temp;
	}
	if (myPoly != NULL)
		free(myPoly);
}

/*将两个一元多项式相加，得到一个新的一元多项式*/
Poly *add_poly(Poly *La, Poly *Lb)
{
	// 将以La，Lb为头指针表示的一元多项式相加
	if (La->head->next == NULL && Lb->head->next == NULL)
		return NULL;
	Poly *Lc = creat_Poly();
	Var *pc, *pa, *pb;
	pc = Lc->head;
	pa = La->head->next;
	pb = Lb->head->next;
	while (pa != NULL || pb != NULL)
	{
		if (pa == NULL)
		{
			Var *newNode = (Var *)malloc(sizeof(Var));
			newNode->coef = pb->coef;
			newNode->expn = pb->expn;
			newNode->next = NULL;
			pc->next = newNode;
			pb = pb->next;
			pc = pc->next;
		}
		else if (pb == NULL)
		{
			Var *newNode = (Var *)malloc(sizeof(Var));
			newNode->coef = pa->coef;
			newNode->expn = pa->expn;
			newNode->next = NULL;
			pc->next = newNode;
			pa = pa->next;
			pc = pc->next;
		}
		else if (pa->expn == pb->expn)
		{
			float coef = pa->coef + pb->coef;
			if (coef == 0)
			{
				pa = pa->next;
				pb = pb->next;
			}
			else
			{
				Var *newNode = (Var *)malloc(sizeof(Var));
				newNode->coef = coef;
				newNode->expn = pa->expn;
				newNode->next = NULL;
				pc->next = newNode;
				pa = pa->next;
				pb = pb->next;
				pc = pc->next;
			}
		}
		else if (pa->expn > pb->expn)
		{
			Var *newNode = (Var *)malloc(sizeof(Var));
			newNode->coef = pa->coef;
			newNode->expn = pa->expn;
			newNode->next = NULL;
			pc->next = newNode;
			pa = pa->next;
			pc = pc->next;
		}
		else
		{
			Var *newNode = (Var *)malloc(sizeof(Var));
			newNode->coef = pb->coef;
			newNode->expn = pb->expn;
			newNode->next = NULL;
			pc->next = newNode;
			pb = pb->next;
			pc = pc->next;
		}
	}
	pc->next = NULL;
	return Lc;
}

/*进栈*/
void push(Stack *stk, int unused_index)
{
	node *newNode = (node *)malloc(sizeof(node));
	newNode->index = unused_index;
	newNode->next = stk->top;
	stk->top = newNode;
	stk->size += 1;
}

/*出栈*/
void pop(Stack *stk)
{
	if (stk->top == NULL)
		return;
	node *temp = stk->top;
	stk->top = temp->next;
	stk->size -= 1;
	free(temp);
	temp = NULL;
}

/*按照随机的方式初始化一个栈，里面放静态链表中未使用的下标*/
Stack *InitiateStack()
{
	Stack *stk = (Stack *)malloc(sizeof(Stack));
	stk->top = NULL;
	stk->size = 0;
	int visited[INITIAL_SIZE] = {0};
	for (int i = 0; i < INITIAL_SIZE;)
	{
		int unused_index = rand() % INITIAL_SIZE;
		if (!visited[unused_index])
		{
			visited[unused_index] = 1;
			push(stk, unused_index);
			++i;
		}
	}
	return stk;
}

/*判断栈是否为空*/
int empty(const Stack *stk)
{
	if (stk->size == 0)
		return 1;
	else
		return 0;
}

/*取栈顶元素*/
int top(const Stack *stk)
{
	if (empty(stk))
		return ERROR;
	return stk->top->index;
}

/*释放栈申请的动态内存*/
void freeStack(Stack *stk)
{
	while(!empty(stk))
	{
		pop(stk);
	}
	if (stk != NULL)
		free(stk);
}

/*将栈顶和还未使用的元素下标打印出来*/
void printStack(Stack *stk)
{
	if (empty(stk))
	{
		printf("Stack is empty\n");
		return;
	}
	node *t = stk->top;
	printf("Stack: top = %d\n", t -> index);
	printf("Unused units in the stack: ");
	while (t)
	{
		printf("%d ", t->index);
		t = t->next;
	}
	printf("\n");
	printf("\n");
}

/*创建静态链表*/
Lists *creat_Lists()
{
	Lists *lists = (Lists *)malloc(sizeof(Lists));
	lists->list = (List *)malloc(INITIAL_SIZE * sizeof(List));
	lists->capacity = INITIAL_SIZE;
	lists->stk = InitiateStack();
	lists->list_head = null;
	return lists;
}

/*当静态链表放满之后，容量扩充*/
void double_size(Lists *lists)
{
	int add_size = lists->capacity;
	lists->capacity *= 2;
	List *list = (List *)malloc(lists->capacity * sizeof(List));
	for(int i = 0; i < add_size; ++i)
	{
		list[i] = lists->list[i];
	}
	free(lists->list);
	lists->list = list;
	int *visited = (int *)malloc(add_size * sizeof(int));
	for(int i = 0; i < add_size; ++i)
	{
		visited[i] = 0;
	}
	for(int i = 0; i < add_size; )
	{
		int index = rand() % add_size + add_size;
		if (!visited[index - add_size])
		{
			push(lists->stk, index);
			visited[index - add_size] = 1;
			++i;
		}
	}
}

/*将多项式从表头加入静态链表*/
void push_front(Lists *lists, Poly *poly)
{
	if(empty(lists->stk)) double_size(lists);
	int index = top(lists->stk);
	pop(lists->stk);
	lists->list[index].poly = poly;
	lists->list[index].next_node = lists->list_head;
	lists->list_head = index;
	poly->store_index = index;
}

/*从静态链表中删除特定的多项式*/
void erase(Lists *lists, Poly *poly)
{
	push(lists->stk, poly->store_index);
	int pre = lists->list_head;
	int next = lists->list[lists->list_head].next_node;
	if (pre == poly->store_index)
	{
		freePoly(lists->list[pre].poly);
		lists->list_head = next;
		return;
	}
	while(1)
	{
		if (next == poly -> store_index)
		{
			lists->list[pre].next_node = lists->list[next].next_node;
			freePoly(lists->list[next].poly);
			return;
		}
		pre = next;
		next = lists->list[next].next_node;
	}
}

/*将链表中的多项式和它们的下标打印出来*/
void printLists(Lists *lists)
{
	if (lists->list_head == -1) return;
	int pre = lists->list_head;
	int next = lists->list[lists->list_head].next_node;
	printf("In the array: \n");
	while(1)
	{
		printf("Index %d:", pre);
		printPoly(lists->list[pre].poly);
		pre = next;
		next = lists->list[next].next_node;
		if (pre == -1) return;
	}
	printf("\n");
	printf("\n");
}

/*释放静态链表中所申请的动态内存*/
void freeLists(Lists *lists)
{
	free(lists->stk);
	while(lists->list_head != -1)
	{
		int next = lists->list[lists->list_head].next_node;
		freePoly(lists->list[lists->list_head].poly);
		lists->list_head = next;
	}
	free(lists->list);
	free(lists);
}

/*打印静态链表和栈之间的映射关系*/
void showMap(Lists *lists)
{
	printLists(lists);
	printStack(lists->stk);
}

/*输入两个多项式*/
void input(Poly *lp, Poly *lq)
{
	int n1, n2;
	printf("请输入第一个多项式的项的个数：");
	scanf("%d", &n1);
	printf("\n");
	for (int i = 1; i <= n1; ++i)
	{
		float coef;
		int expn;
		printf("请输入第%d项的系数和指数：", i);
		scanf("%f %d", &coef, &expn);
		addToPoly(lp, coef, expn);
		printf("\n");
	}
	printf("第一个输入的多项式为：");
	printPoly(lp);
	printf("\n");
	printf("请输入第二个多项式的项的个数：");
	scanf("%d", &n2);
	printf("\n");
	for (int i = 1; i <= n2; ++i)
	{
		float coef;
		int expn;
		printf("请输入第%d项的系数和指数：", i);
		scanf("%f %d", &coef, &expn);
		addToPoly(lq, coef, expn);
		printf("\n");
	}
	printf("第二个输入的多项式为：");
	printPoly(lq);
	printf("\n");
}

int main()
{
	/*两个多项式LP，LQ*/
	Poly *LP = creat_Poly();
	Poly *LQ = creat_Poly();
	input(LP, LQ);
	/*用来放多项式的静态链表*/
	Lists *lists = creat_Lists();
	/*将LP，LQ加入静态链表*/
	push_front(lists, LP);
	push_front(lists, LQ);
	printf("合并前：\n");
	/*打印合并前的映射关系*/
	showMap(lists);
	/*将多项式LP，LQ相加得到多项式LPQ*/
	Poly *LPQ = add_poly(LP, LQ);
	/*将LPQ加入静态链表*/
	push_front(lists, LPQ);
	/*从静态链表中删除LP，LQ*/
	erase(lists, LP);
	erase(lists, LQ);
	/*打印合并后的映射关系*/
	printf("合并后：\n");
	showMap(lists);
	freeLists(lists);
}

/*
测试样例：
输入1：
3
3 2
4 3
5 4
3
-4 3
3 5
2 1

输出1：
请输入第一个多项式的项的个数：3

请输入第1项的系数和指数：3 2

请输入第2项的系数和指数：4 3

请输入第3项的系数和指数：5 4

第一个输入的多项式为：5.00x^4+4.00x^3+3.00x^2

请输入第二个多项式的项的个数：3

请输入第1项的系数和指数：-4 3

请输入第2项的系数和指数：3 5

请输入第3项的系数和指数：2 1

第二个输入的多项式为：3.00x^5-4.00x^3+2.00x^1

合并前：
In the array:
Index 0:3.00x^5-4.00x^3+2.00x^1
Index 7:5.00x^4+4.00x^3+3.00x^2
Stack: top = 13
Unused units in the stack: 13 15 12 20 16 28 23 19 9 8 26 3 24 21 6 2 25 27 1 5 14 22 18 29 10 4 17 11

合并后：
In the array:
Index 13:3.00x^5+5.00x^4+3.00x^2+2.00x^1
Stack: top = 0
Unused units in the stack: 0 7 15 12 20 16 28 23 19 9 8 26 3 24 21 6 2 25 27 1 5 14 22 18 29 10 4 17 11

输入2：
2
1 1
2 2
3
1 2
2 3
3 4

输出2：
请输入第一个多项式的项的个数：2

请输入第1项的系数和指数：1 1

请输入第2项的系数和指数：2 2

第一个输入的多项式为：2.00x^2+1.00x^1

请输入第二个多项式的项的个数：3

请输入第1项的系数和指数：1 2

请输入第2项的系数和指数：2 3

请输入第3项的系数和指数：3 4

第二个输入的多项式为：3.00x^4+2.00x^3+1.00x^2

合并前：
In the array:
Index 0:3.00x^4+2.00x^3+1.00x^2
Index 7:2.00x^2+1.00x^1
Stack: top = 13
Unused units in the stack: 13 15 12 20 16 28 23 19 9 8 26 3 24 21 6 2 25 27 1 5 14 22 18 29 10 4 17 11

合并后：
In the array:
Index 13:3.00x^4+2.00x^3+3.00x^2+1.00x^1
Stack: top = 0
Unused units in the stack: 0 7 15 12 20 16 28 23 19 9 8 26 3 24 21 6 2 25 27 1 5 14 22 18 29 10 4 17 11

输入3：
1
5 7
1
1 -3

输出3：
请输入第一个多项式的项的个数：1

请输入第1项的系数和指数：5 7

第一个输入的多项式为：5.00x^7

请输入第二个多项式的项的个数：1

请输入第1项的系数和指数：1 -3

第二个输入的多项式为：1.00x^-3

合并前：
In the array:
Index 0:1.00x^-3
Index 7:5.00x^7
Stack: top = 13
Unused units in the stack: 13 15 12 20 16 28 23 19 9 8 26 3 24 21 6 2 25 27 1 5 14 22 18 29 10 4 17 11

合并后：
In the array:
Index 13:5.00x^7+1.00x^-3
Stack: top = 0
Unused units in the stack: 0 7 15 12 20 16 28 23 19 9 8 26 3 24 21 6 2 25 27 1 5 14 22 18 29 10 4 17 11
*/
