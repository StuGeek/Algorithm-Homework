# week7 一趟希尔排序

实现下列一趟Shell sort的函数：
```
//对vector进行一趟希尔排序，步长为increment
void shell_once(vector<int> &v, int increment)；
```
例如，```shell_once(v, 3)```将v分为三个子序列：```v[0],v[3],v[6],...```；```v[1],v[4],v[7],...```以及```v[2],v[5],v[8],...```，并分别对三个子序列进行插入排序。