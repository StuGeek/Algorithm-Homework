#include "stdio.h"
#include "stdlib.h"
#define MAXSIZE 100 /*此处的宏定义常量表示线性表可能达到的最大长度*/

typedef int ElemType;
typedef struct
{
    ElemType elem[MAXSIZE];  // 线性表占用的数组空间
    int last;  /*记录线性表中最后一个元素在数组 elem[ ] 中的位置（下标值），空表置为-1*/
} SeqList;

