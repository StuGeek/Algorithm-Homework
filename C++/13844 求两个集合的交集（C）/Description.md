# 求两个集合的交集（C）

假定用下列顺序结构存储一个集合，集合元素按照从小到大顺序存储：
```
typedef int ElemType;
typedef struct
{
    ElemType elem[MAXSIZE];  // 线性表占用的数组空间
    int last;  /*记录线性表中最后一个元素在数组 elem[ ] 中的位置（下标值），空表置为-1*/
} SeqList;
```
请实现下面求集合交集的函数：
```
//LC是LA和LB表示集合的交集
void merge(SeqList *LA, SeqList *LB, SeqList *LC);
```
###提醒：
1. 请先写伪代码算法
2. 只提交该函数的实现，不需要提交main函数