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

string nextPermutation(string num) {
    if (num.size() == 1) return num;
    int i = num.size() - 2;
    int j = num.size() - 1;
    while (num[i] > num[i + 1]) {
        i--;
        if (i == -1) return num;
    }
    while (num[i] > num[j]) {
        j--;
    }
    swap(num[i], num[j]);
    int r = num.size() - 1;
    int s = i + 1;
    while (r > s) {
        swap(num[r], num[s]);
        r--;
        s++;
    }
    return num;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int T;
    ifs >> T;
    while (T--) {
        int n;
        ifs >> n;
        string res = "";
        for (int i = 1; i <= n; ++i) {
            res += i + '0';
        }
        ofs << res << endl;
        string num = nextPermutation(res);
        while (res != num) {
            res = num;
            num = nextPermutation(num);
            ofs << res << endl;
        }
    }
}