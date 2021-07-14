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

int minSteps(int n){
    int res = 0;
    int d = 2;
    while(n > 1){
        while(n % d == 0){
            res += d;
            n /= d;
        }
        d++;
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
        ofs << minSteps(n) << endl;
    }
}