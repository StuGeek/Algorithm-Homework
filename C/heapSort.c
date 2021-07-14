#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initial_max_heap(int *number, int n){
    for (int i = n / 2 - 1; i >= 0; --i){
        int temp = number[i];
        int p = i;
        int child = (i << 1) + 1;
        while(child < n){
            //选择儿子结点中较大的那个结点
            if (child + 1 < n && number[child] < number[child + 1]){
                child = child + 1;
            }
            //如果分支结点的值更小，进行调整
            if (temp < number[child]){
                number[p] = number[child];
                p = child;
                child = (p << 1) + 1;
            }
            else break;
        }
        number[p] = temp;
    }
}

void pop(int *number, int n){
    //大顶堆为空，直接返回
    if (n == 0) return;
    int high, low;
    //获取大顶堆数组的最后一个元素，并把顶部最大的元素放到数组最后
    int temp = number[--n];
    number[n] = number[0];
    for (high = 0; (high << 1) + 1 < n; high = low){
        //从根结点开始，high为父亲结点的位置，low为左儿子的位置
        low = (high << 1) + 1;
        //选择儿子结点中较大的那个结点
        if (low != n - 1 && number[low] < number[low + 1]){
            low += 1;
        }
        //如果这个结点比大顶堆数组的最后一个元素大，那么将这个结点放到它的父亲结点
        if (number[low] > temp){
            number[high] = number[low];
        }
        else break;
    }
    //比较结束后直接将最后一个元素放到最后一次比较比最后一个元素小的结点的父亲结点的位置
    number[high] = temp;
}

//堆排序
void heap_sort(int *number, int n){
    initial_max_heap(number, n);
    for (int i = n; i > 0; i--){
        pop(number, i);
    }
}

//打印数组数据
void print(int *number, int n){
    for (int i = 0; i < n; ++i){
        printf("%d ", number[i]);
    }
    printf("\n");
}

int main() {
    int a[20];
    //输入20个随机整数
    /*printf("请输入20个整数：");
    for (int i = 0; i < 20; ++i){
        scanf("%d", &a[i]);
    }*/
    //随机生成20个整数
    srand((unsigned) time(NULL));
    for (int i = 0; i < 20; ++i){
        int num = rand() % 100;
        a[i] = num;
    }
    printf("排序前：\n");
    print(a, 20);
    heap_sort(a, 20);
    printf("排序后：\n");
    print(a, 20);
}