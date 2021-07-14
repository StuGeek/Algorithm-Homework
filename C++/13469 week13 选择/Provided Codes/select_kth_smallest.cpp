#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <list>

using namespace std;

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

int position(vector<int> & v, int start, int end) {
    int pivot = v[start];
    int t = start;
    for (int i = start + 1; i <= end; ++i) {
        if (v[i] < pivot) {
            t += 1;
            swap(v[i], v[t]);
        }
    }
    swap(v[start], v[t]);
    return t;
}

int select(vector<int> & v, size_t k, int start, int end) {
    int index = position(v, start, end);
    if (index == start + k - 1) return v[index];
    else if (index > start + k - 1) return select(v, k, start, index - 1);
    else return select(v, k + start - index - 1, index + 1, end);
}

int select_kth_smallest(vector<int> v, size_t k) {
    int n = v.size();
    return select(v, k, 0, n - 1);
}