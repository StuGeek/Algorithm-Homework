#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <list>

using namespace std;

int InsertSort(vector<int> &v){
    int size = v.size();
    int res = 0;
    for(int i = 0; i < size - 1; ++i) {
        bool flag = false;
        for(int j = i + 1; j > 0; --j) {
            if (v[j] < v[j - 1]){
                flag = true;
                int temp = v[j];
                v[j] = v[j - 1];
                v[j - 1] = temp;
            }
        }
        if (flag) res += 5;
    }
    return res;
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
        v.resize(n);
        for(int i = 0; i < n; ++i) {
            ifs >> v[i];
        }
        ofs << InsertSort(v) << endl;
    }
}