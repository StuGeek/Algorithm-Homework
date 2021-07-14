#include "SeqList.h"

void merge(SeqList *LA, SeqList *LB, SeqList *LC) {
    int i = 0;
    int j = 0;
    LC->last = -1;
    while (i <= LA->last && j <= LB->last) {
        if (LA->elem[i] < LB->elem[j]) i++;
        else if (LA->elem[i] > LB->elem[j]) j++;
        else {
            LC->elem[++LC->last] = LA->elem[i];
            i++;
            j++;
        }
    }
}