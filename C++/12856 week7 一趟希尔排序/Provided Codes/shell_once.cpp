#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <list>

using namespace std;

void shell_once(vector<int> &v, int increment){
    int size = v.size();
    for (int i = increment; i < size; ++i){
        for (int j = i; j >= increment; j -= increment){
            if (v[j] < v[j - increment]) {
                int temp = v[j];
                v[j] = v[j - increment];
                v[j - increment] = temp;
            }
        }
    }
}

int main() {
    vector<int> a = {10, 8, 9, 7, 5, 6, 4, 2, 3, 1};
    shell_once(a, 3);
    bool sort = true;
    for (int i = 0; i < 10; ++i) {
        if (a[i] != i + 1){
            sort = false;
            break;
        }
    }
    if (sort) printf("Good\n");
}