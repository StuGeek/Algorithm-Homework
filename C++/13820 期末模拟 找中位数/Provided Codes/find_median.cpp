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

int partition(vector<int> & v, int left, int right) {
    int t = right;
    right--;
    while (left <= right) {
        while (left < t && v[left] <= v[t]) {
            left++;
        }
        while (right >= 0 && v[right] > v[t]) {
            right--;
        }
        if (left >= right) break;
        swap(v[left], v[right]);
    }
    swap(v[left], v[t]);
    return left;
}

int findMidNum(vector<int> & v) {
    int n = v.size();
    if (n == 0) return -1;
    int left = 0;
    int right = n - 1;
    int m = right / 2;
    int t = -1;
    while (t != m) {
        t = partition(v, left, right);
        if (t < m) {
            left = t + 1;
        }
        else if (t > m) {
            right = t - 1;
        }
        else break;
    }
    return v[t];
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int T;
    ifs >> T;
    while(T--){
        int n;
        ifs >> n;
        vector<int> v;
        for(int i = 0; i < n; ++i) {
            int num;
            ifs >> num;
            v.push_back(num);
        }
        ofs << findMidNum(v) << endl;
    }
}