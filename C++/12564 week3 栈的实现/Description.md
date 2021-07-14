# week3 栈的实现

请根据Stack.h中的定义实现栈。

注意：
1. 不可使用除数组和链表外的任何标准库工具如stack, deque,vector和list等。
2. 不可使用任何其他网站，不可使用U盘等设备。
3. 不可拷贝任何代码，包括自己过去写的代码。
4. 可以使用长度为100的静态数组，栈元素类型设置为int.
5. 请提交整个实现，包括类的定义和实现，并根据你的实现定义类型 Stack
	
### 	测试程序样例(可用于检查提交文件是否适当)
	
```
#include<iostream>
#include "MyStack.h"

using namespace std;


void print(Stack s){
  if (!s.empty()){
     cout <<"top:"<<s.top() << endl;
  }
  cout <<"size:"<<s.size()<<endl;
  cout <<"-------"<<endl;
}
     

int main(){
  
  Stack s;
  int N = 100;
  for (int i=1; i<=N; i++){
     s.push(3*i);
  }
  print(s);

  // more testing

  return 0;
}
	
```