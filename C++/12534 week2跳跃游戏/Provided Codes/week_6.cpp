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

int JumpTime(vector<int> &nums){
    int n = nums.size();
    if (n == 1) return 0;
    int last_rightmost = 0;
    int rightmost = 0;
    int res = 0;
    for(int i = 0; i < n; ++i) {
        if (i <= rightmost){
            if (rightmost < i + nums[i]){
                rightmost = i + nums[i];
            }
            if (rightmost >= n - 1){
                return res + 1;
            }
            if (i == last_rightmost){
                last_rightmost = rightmost;
                res++;
            }
        }
        else return 0;
    }
    return 0;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int T;
    ifs >> T;
    while(T--){
        int n;
        ifs >> n;
        vector<int> nums;
        for(int i = 0; i < n; ++i){
            int num;
            ifs >> num;
            nums.push_back(num);
        }
        ofs << JumpTime(nums) << endl; 
    }
}