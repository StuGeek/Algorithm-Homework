# week4多项式加法（需要读取数据并打印结果）

###问题###

假定多项式按降幂排列， 并用其系数指数对的序列表示，试实现多项式的加法。

###输入###
第一行是测试样例数n, 接下来是n个测试样例。
每个测试样例包含两个多项式，每个多项式的第一行是一个非负整数，表示多项式的项数，然后是按照降幂排列的多项式各项系数及指数对，系数和指数间用空格分隔。
###输出###
对每个测试样例，计算并输出两个多项式的和，第一行输出多项式和的项数，然后按照降幂排列输出各项系数和指数对，每对系数和指数各占一行，中间用一个空格分隔。
###输入样例###
```
2
2
1 2
-1 0
0
3
1 2
2 1
9 0
3
-1 2
-1 1
-8 0
```
###输出样例###
```
2
1 2
-1 0
2
1 1
1 0
```