# week6 二分查找的比较次数

 给定二分查找
 ```
bool binary_search(list, target)
//input: list[1..n] 是按照关键字有序的数组，n是非负整数，target 是一个关键字
//output: 如果target在list在中出现，则返回true, 否则返回false.
    if list 空 then
         return false
    if list只含一个元素x 
        if x = target then
            return true
       else return false
    else
        令 x 为list的中间元素，即x = list[mid], mid = (bot+top)/2
        if  target > x then 
              return binary_search(list[mid+1..n], target) //后半部分查找
       else
             return binary_search(list[1..mid], target) //前半部分查找
```
根据以上算法，实现下列返回查找是否成功以及关键字比较次数的函数：

```

pair<bool, int> binary_search(vector<int> list, int target)；
//input: list[1..n] 是按照关键字有序的数组，n是非负整数，target 是一个关键字
//output: 如果target在list在中出现，则返回true以及关键字比较次数, 否则返回false以及关键字比较次数.
```
只需提交函数的实现。
