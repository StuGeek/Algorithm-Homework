# week9 计算关键字比较次数（开地址法）

### 问题
假设构建哈希表使用线性探查法解决冲突，试计算每次查找的关键字比较次数。
0. 可能的关键字为正整数；
1.	使用哈希函数```h(k,M)= k % M```, M为哈希表的长度；
2.	因为0不是关键字，所以，假定用0表示空单元；
3.	为了区分空单元和删除后的“空单元”，给每个单元添加一个布尔型标识，表示该单元是否空；空单元设置为true，非空设置为false;
4.	假定删除关键字时，只将标识置为true,关键字域不变。
例如，一个哈希表可能是这样的：


| (0, true) | (1, false) | (6,true) | (7,false) | (0,true) |  
|---|---|---|---|---|


其中(0,true)表示一个空单元，(6,true)表示删除关键字6后的空单元，(7,false)表示一个非空单元。

请实现哈希表的查找函数lookup(table, key), 它返回查找是否成功、查找终止的下标以及关键字的比较次数。
例如，对于上面表长为5的哈希表，查找7需要2次关键字比较，并在第3单元终止，故返回（true, 3, 2)；又如，查找6失败，需要4次比较，并在第4单元终止，因此返回(false, 4, 4)。

The function returns a pair, where the first component is  a pair of  bool, indicating if the lookup is successful,  and the address where kookup terminates, and the second component is the number of key comparisons. 
```
pair<pair<bool, size_t>, int>  lookup(const Table& t, const Key k);
```



