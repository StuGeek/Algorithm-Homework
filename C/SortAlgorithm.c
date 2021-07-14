#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <float.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void SelectSort(int *a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int index = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[index]) index = j;
        }
        if (index != i) swap(&a[i], &a[index]);
    }
}

void InsertSort(int *a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j > 0; --j) {
            if (a[j] < a[j - 1]) swap(&a[j], &a[j - 1]);
        }
    }
}

void BubbleSort(int *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) swap(&a[j], &a[j + 1]);
        }
    }
}

void ShellSort(int *a, int n) {
    for (int increasement = n / 2; increasement > 0; increasement /= 2) {
        for (int i = increasement; i < n; ++i) {
            for (int j = i; j >= increasement; j -= increasement) {
                if (a[j] < a[j - increasement]) swap(&a[j], &a[j - increasement]);
            }
        }
    }
}

void QuickSort(int *a, int l, int r) {
    if (l >= r) return;
    int i = l;
    int j = r;
    int key = a[l];
    while (i < j) {
        while (i < j && a[j] >= key) {
            j--;
        }
        if (i < j) {
            a[i] = a[j];
            i++;
        }
        while (i < j && a[i] < key) {
            i++;
        }
        if (i < j) {
            a[j] = a[i];
            j--;
        }
    }
    a[i] = key;
    QuickSort(a, l, i - 1);
    QuickSort(a, i + 1, r);
}

void Merge(int *a, int l, int m, int r) {
    int i = l;
    int j = m + 1;
    int k = 0;
    int *temp = (int *)malloc((r - l + 1) * sizeof(int));
    while (i <= m && j <= r) {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= m) {
        temp[k++] = a[i++];
    }
    while (j <= r) {
        temp[k++] = a[j++];
    }
    for (i = 0; i < r - l + 1; ++i) {
        a[l + i] = temp[i];
    }
    free(temp);
}

void MergeSort(int *a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    MergeSort(a, l, m);
    MergeSort(a, m + 1, r);
    Merge(a, l, m, r);
}

void InitialMaxHeap(int *number, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        int temp = number[i];
        int p = i;
        int child = i * 2 + 1;
        while (child < n) {
            if (child + 1 < n && number[child] < number[child + 1]) {
                child = child + 1;
            }
            if (temp < number[child]) {
                number[p] = number[child];
                p = child;
                child = p * 2 + 1;
            } else
                break;
        }
        number[p] = temp;
    }
}

void Pop(int *number, int n) {
    if (n == 0) return;
    int high, low;
    int temp = number[--n];
    number[n] = number[0];
    for (high = 0; high * 2 + 1 < n; high = low) {
        low = high * 2 + 1;
        if (low != n - 1 && number[low] < number[low + 1]) {
            low += 1;
        }
        if (number[low] > temp) {
            number[high] = number[low];
        } else
            break;
    }
    number[high] = temp;
}

void HeapSort(int *number, int n) {
    InitialMaxHeap(number, n);
    for (int i = n; i > 0; i--) {
        Pop(number, i);
    }
}

int maxnum(int *number, int n){
    int maxData = 0;
    for(int i = 0; i < n; ++i){
        if (number[i] > maxData){
            maxData = number[i];
        }
    }
    return maxData;
}

void BucketSort(int *number, int n){
    int maxData = maxnum(number, n);
    int *t = (int *)malloc(sizeof(int) * maxData);
    memset(t, 0, maxData * sizeof(int));
    for (int i = 0; i < n; ++i){
        t[number[i] - 1]++;
    }
    int j = 0;
    for (int i = 0; i < maxData; ++i){
        while(t[i] > 0){
            number[j++] = i + 1;
            t[i]--;
        }
    }
    free(t);
}

int maxbit(int *number, int n){
    int d = 0;
    int maxData = 0;
    for(int i = 0; i < n; ++i){
        if (number[i] > maxData){
            maxData = number[i];
        }
    }
    while(maxData > 0){
        d++;
        maxData /= 10;
    }
    return d;
}

void RadixSort(int *number, int n) {
    int d = maxbit(number, n);
    int *t = (int *)malloc(n * sizeof(int));
    int count[10];
    int radix = 1;
    while(d--){
        memset(count, 0, 10 * sizeof(int));
        for (int i = 0; i < n; ++i){
            int j = (number[i] / radix) % 10;
            count[j]++;
        }
        for (int i = 1; i < 10; ++i){
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; --i){
            int j = (number[i] / radix) % 10;
            t[--count[j]] = number[i];
        }
        for (int i = 0; i < n; ++i){
            number[i] = t[i];
        }
        radix *= 10;
    }
    free(t);
}

int main() {
    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    BucketSort(a, 10);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", a[i]);
    }
}