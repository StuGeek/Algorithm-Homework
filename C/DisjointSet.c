#include <stdio.h>
#include <stdlib.h>

#define BOOL int

void init(int *a, int n){
    for (int i = 0; i < n; ++i){
        a[i] = i;
    }
}

int quick_find(int *a, int n) {
    int temp = n;
    while (a[temp] != temp) {
        temp = a[temp];
    }
    while (n != temp) {
        int t = a[n];
        a[n] = temp;
        n = t;
    }
    return temp;
}

void set_union(int *a, int num1, int num2){
    int j = quick_find(a, num1);
    int k = quick_find(a, num2);
    if (j != k){
        a[j] = k;
    }
}

void print_disjoint_set(int *a, int n){
    for(int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int *creat_disjoint_set(int n, int m){
    int *a = (int *)malloc(sizeof(int) * n);
    init(a, n);
    for(int i = 0; i < m; ++i) {
        int num1;
        int num2;
        scanf("%d %d", &num1, &num2);
        set_union(a, num1, num2);
        print_disjoint_set(a, n);
    }
    return a;
}

BOOL isConnected(int *a, int num1, int num2){
    int j = quick_find(a, num1);
    int k = quick_find(a, num2);
    return j == k;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = creat_disjoint_set(n, m);
    int num1, num2;
    while(scanf("%d %d", &num1, &num2) != EOF) {
        if (isConnected(a, num1, num2)) {
            printf("Connected!\n");
        }
        else {
            printf("Not connected!\n");
        }
    }
    free(a);
}