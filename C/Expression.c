#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*栈的每个结点包括一个char值和指向下一结点的指针*/
typedef struct Node{
	char val;
	struct Node* next;
}node;

/*栈的结构，包括栈目前的的大小和指向栈的头结点的一个指针*/
typedef struct{
	int size;
	node *top;
} Stack;

/*初始化栈，为栈申请空间并把头结点指向NULL，大小设为0*/
Stack *InitiateStack(){
	Stack *stk = (Stack *)malloc(sizeof(Stack));
	stk -> top = NULL;
	stk -> size = 0;
	return stk;
}

/*压栈*/
void push(Stack *stk, char val){
	node *new_node = (node *)malloc(sizeof(node));
	new_node -> val = val;
	new_node -> next = stk -> top;
	stk -> top = new_node;
	stk -> size++;
}

/*弹栈*/
void pop(Stack *stk){
	if (stk -> top == NULL) return;
	node *temp = stk -> top;
	stk -> top = temp -> next;
	stk -> size--;
	free(temp);
}

/*判断栈是否为空*/
int empty(Stack *stk){
	if (stk -> size == 0) return 1;
	else return 0;
}

/*取栈顶元素*/
char top(Stack *stk){
	if(empty(stk)) return 0;
	else return stk -> top -> val;
}

/*取栈当前的大小*/
int size(Stack *stk){
	return stk -> size;
}

/*释放栈申请的动态内存*/
void freeStack(Stack *stk){
	while(!empty(stk)){
		pop(stk);
	}
	if (stk != NULL){
		free(stk);
	}
}

/*判断符号优先级*/
int priority(char c){
	switch (c){
		case '+' : return 1;
		case '-' : return 1;
		case '*' : return 2;
		case '/' : return 2;
		default : return 0;
	}
}

/*判断字符是否为数字*/
int isNumber(char c){
	if (c >= '0' && c <= '9') return 1;
	else return 0;
}

/*将中序表达式转换为后序表达式*/
char *InfixToPostfix(char *expression){
	Stack *symbol = InitiateStack();
	char *new_expression = (char *)malloc(1000 * sizeof(char));
	int i = 0;
	int j = 0;
	while (expression[i] != '\0'){
		//当为数字时，直接将数字添加到后序表达式
		if (isNumber(expression[i])){
			new_expression[j++] = expression[i];
		}
		else{
			//当为左括号时，直接将左括号压进符号栈中
			if (expression[i] == '('){
				push(symbol, '(');
			}
			/*当为右括号时，将符号栈中的元素依次弹出加入后序表达式中，
			直到碰到左括号将左括号弹出后终止*/
			else if(expression[i] == ')'){
				while(top(symbol) != '('){
					new_expression[j++] = top(symbol);
					pop(symbol);
				}
				pop(symbol);
			}
			else{
				/*当为一般符号时，利用优先级函数判断优先级，
				当符号栈不为空且遍历到的元素优先级小于栈顶元素时，不断将栈顶元素弹栈加入到后序表达式中，
				直到遇到优先级更大的栈顶元素或栈为空，直接将符号加入栈里面*/
				while(!empty(symbol) && (priority(expression[i]) < priority(top(symbol)))){
					new_expression[j++] = top(symbol);
					pop(symbol);
				}
				push(symbol, expression[i]);
			}
		}
		i++;
	}
	//最后将符号栈里面剩下的元素全部加入到后序表达式中
	while(!empty(symbol)){
		new_expression[j++] = top(symbol);
		pop(symbol);
	}
	new_expression[j] = '\0';
	freeStack(symbol);
	return new_expression;
}

/*计算后序表达式的结果*/
int EvaOfPostfix(char *expression){
	Stack *number = InitiateStack();
	int i = 0;
	while (expression[i] != '\0'){
		//当为数字时，将数字加入数字栈里面
		if (isNumber(expression[i])){
			push(number, expression[i]);
		}
		else{
			//当不是数字时，弹出两个数字，并按照操作符进行运算，将结果重新加入栈里面
			int num1 = top(number) - '0';
			pop(number);
			int num2 = top(number) - '0';
			pop(number);
			int result = 0;
			if (expression[i] == '+'){
				result = num1 + num2;
			}
			else if(expression[i] == '-'){
				result = num2 - num1;
			}
			else if(expression[i] == '*'){
				result = num1 * num2;
			}
			else if(expression[i] == '/'){
				result = num2 / num1;
			}
			push(number, result + '0');
		}
		i++;
	}
	//最后栈里面只剩下一个元素，这个最后的元素就是结果
	int result = top(number) - '0';
	freeStack(number);
	return result;
}

int main(){
	char Infix[1000];
	printf("请输入中序表达式：");
	scanf("%s", Infix);
	char *Postfix = InfixToPostfix(Infix);
	printf("后序表达式为：%s\n", Postfix);
	printf("后序表达式的结果为：%d\n", EvaOfPostfix(Postfix));
	free(Postfix);
}