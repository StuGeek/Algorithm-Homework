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

int main() {
    ifstream ifs("../Tests/in4", ios::in);
    ofstream ofs("out", ios::out);
    int n;
    ifs >> n;
    unordered_map<int, int> themap;
    for (int i = 0; i < n; ++i){
        int num;
        ifs >> num;
        themap[num]++;
        if (themap[num] > n / 2) {
            ofs << num << endl;
            break;
        }
    }
}