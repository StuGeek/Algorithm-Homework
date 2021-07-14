#include <string.h>

void getNext(int next[], const char *s) {
    int j = 0;
    int k = -1;
    next[0] = -1;
    int length = strlen(s);
    while (j < length - 1) {
        if (k == -1 || s[j] == s[k]) {
            j++;
            k++;
            next[j] = k;
        }
        else k = next[k];
    }
}

int indexOf(const char *s1, const char *s2) {
    int length1 = strlen(s1);
    int length2 = strlen(s2);
    int i = 0;
    int j = 0;
    int next[100000];
    getNext(next, s1);
    while (i < length1 && j < length2) {
        if (i == -1 || s1[i] == s2[j]) {
            i++;
            j++;
        }
        else i = next[i];
    }
    if (i >= length1) {
        return j - length1;
    }
    else return -1;
}