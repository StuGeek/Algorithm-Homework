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

int search(vector<int> & nums, int n) {
    int temp = n;
    while (nums[temp] != temp) {
        temp = nums[temp];
    }
    while (n != temp) {
        int t = nums[n];
        nums[n] = temp;
        n = t;
    }
    return temp;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int n, m;
    ifs >> n >> m;
    vector<int> nums;
    vector<int> v(n, 0);
    for(int i = 0; i < n; ++i) {
        nums.push_back(i);
    }
    for(int i = 0; i < m; ++i) {
        int num1, num2;
        ifs >> num1 >> num2;
        int j = search(nums, num1 - 1);
        int k = search(nums, num2 - 1);
        if (j != k) {
            nums[j] = k;
        }
        v[num1 - 1]++;
        v[num2 - 1]++;
    }
    bool isNetwork = true;
    for (int i = 0; i < n; ++i) {
        if (v[i] != v[nums[i]]) {
            isNetwork = false;
            break;
        }
    }
    if (isNetwork) ofs << "YES" << endl;
    else ofs << "NO" << endl;
}