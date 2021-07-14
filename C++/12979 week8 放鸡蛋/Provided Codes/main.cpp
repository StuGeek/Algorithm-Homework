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

ifstream ifs("../Tests/in1", ios::in);
ofstream ofs("out", ios::out);

void dfs(vector<int>& nums, int m, int n, int sum) {
    if (n >= sum)
        return;
    if (n == 0 || nums[n] <= nums[n - 1]) {
        for (int i = 0; i <= n; ++i) {
            ofs << nums[i];
        }
        for (int i = n + 1; i < sum; ++i) {
            ofs << "0";
        }
        ofs << endl;
    }
    for (int i = m - 1; i > 0; --i) {
        nums[n] = i;
        nums[n + 1] = m - i;
        if (n == 0 || nums[n] <= nums[n - 1]) {
            dfs(nums, m - i, n + 1, sum);
        }
    }
}

int main() {
    int T;
    ifs >> T;
    while (T--) {
        int m, n;
        ifs >> m >> n;
        vector<int> nums(n);
        nums[0] = m;
        dfs(nums, m, 0, n);
    }
}