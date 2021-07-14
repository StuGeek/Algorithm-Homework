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

bool isRegularBST (vector<int> & nums, int begin, int end) {
    if (begin == end) return true;
    if ((end - begin + 1) % 2 == 0) return false;
    int i;
    for (i = begin + 1; i <= end; ++i) {
        if (nums[i] > nums[begin]) break;
    }
    if (isRegularBST(nums, begin + 1, i - 1) && isRegularBST(nums, i, end)) 
        return true;
    else return false;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int T;
    ifs >> T;
    while (T--) {
        int n;
        ifs >> n;
        vector<int> nums;
        for (int i = 0; i < n; ++i) {
            int num;
            ifs >> num;
            nums.push_back(num);
        }
        if (isRegularBST(nums, 0, n - 1)) ofs << "YES" << endl;
        else ofs << "NO" << endl;
    }
}