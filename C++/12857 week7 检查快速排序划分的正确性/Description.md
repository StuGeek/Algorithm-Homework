# week7 检查快速排序划分的正确性

问题：对给定的快速排序划分算法，给定一个整数序列，以及该序列若干置换，检查哪些是一次划分的正确结果，哪些不是。

输入：第一行是序列元素个数n，然后是n个整数。接下来是一个正整数m, 然后是以上序列的m种置换。

输出：对输入的每个置换，如果是正确的划分结果，则打印"Yes", 否则打印"No"。每个输出占一行。

输入样例：
```
3
2 1 3
4
1 2 3
1 2 3
3 1 2
3 2 1
```
输出样例：
```
Yes
Yes
No
No
```

划分算法：

```
//对数组A[low..high]进行划分
partition(A, low, high):
    pivot := A[low]
    last_small :=  low
		for i := low+1 to high:
		    if pivot> A[i]:
				    last_small := last_small + 1
				    swap(A[last_samll], A[i])
   swap(A[low], A[last_small])
```

	
	