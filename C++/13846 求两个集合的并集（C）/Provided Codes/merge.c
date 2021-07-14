#include "SeqList.h"

void merge(SeqList *LA, SeqList *LB, SeqList *LC) {
    int i = 0;
    int j = 0;
    LC->last = -1;
    while (i <= LA->last && j <= LB->last) {
        if (LA->elem[i] < LB->elem[j]) {
            LC->elem[++LC->last] = LA->elem[i++];
        }
        else if (LA->elem[i] > LB->elem[j]) {
            LC->elem[++LC->last] = LB->elem[j++];
        }
        else {
            i++;
            j++;
        }
    }
    while (i <= LA->last) {
        LC->elem[++LC->last] = LA->elem[i++];
    }
    while (j <= LB->last) {
        LC->elem[++LC->last] = LB->elem[j++];
    }
}