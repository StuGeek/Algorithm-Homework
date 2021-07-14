# week6 二分查找的实现（midterm 2019）

 实现下列二分查找函数
 ```
bool binary_search(vector<int> list, int bot, int top, int target);
//input: list元素按照关键字有序（从小到大），bot<= top是vector的合法下标，target 是一个关键字
//output: 如果target在list[bot..top]中出现，则返回true, 否则返回false.
```

注意：

1. 只需提交函数的实现；
2. 当然要直接实现，不可使用STL的算法，包括binary_search，否则得负分，而且属于“欺骗”！
