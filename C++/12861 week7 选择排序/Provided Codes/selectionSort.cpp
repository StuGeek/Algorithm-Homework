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

ifstream ifs("../Tests/in1", ios::in);
ofstream ofs("out", ios::out);

void SelectSort(vector<int> &v){
    int n = v.size();
    for(int i = 0; i < n - 1; ++i) {
        int index = i;
        for (int j = i + 1; j < n; ++j){
            if (v[j] < v[index]) index = j;
        }
        if (i != index){
            int temp = v[i];
            v[i] = v[index];
            v[index] = temp;
        }
        for(int i = 0; i < n; ++i) {
            ofs << v[i] << " ";
        }
        ofs << endl;
    }
}

int main() {
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
        SelectSort(v);
    }
}