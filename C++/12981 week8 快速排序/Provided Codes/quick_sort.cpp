#include <iostream>

using std::cout;
using std::endl;

template <class Record> 
void quick_sort(Record* startPointer, Record* endPointer){
    if (startPointer >= endPointer) return;
    Record pivot = *startPointer;
    Record *l = startPointer;
    Record *r = endPointer - 1;
    while(l < r){
        while(l < r && *r >= pivot){
            r--;
        }
        if (l < r){
            *l = *r;
            l++;
        }
        while(l < r && *l <= pivot){
            l++;
        }
        if (l < r){
            *r = *l;
            r--;
        }
    }
    *l = pivot;
    quick_sort(startPointer, l);
    quick_sort(l + 1, endPointer);
}