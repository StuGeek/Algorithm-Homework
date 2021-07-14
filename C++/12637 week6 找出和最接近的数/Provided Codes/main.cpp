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

int threeSumClosest(vector<int>& nums, int target){
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int res = 1e7;
    for (int i = 0; i < n; ++i){
        if (i > 0 && nums[i] == nums[i - 1]){
            continue;
        }
        int j = i + 1;
        int k = n - 1;
        while(j < k){
            int num = nums[i] + nums[j] + nums[k];
            if (num == target) return num;
            if (abs(num - target) < abs(res - target)) res = num;
            if (num > target){
                while(j < k && nums[k] == nums[k - 1]){
                    k--;
                }
                k--;
            }
            else{
                while(j < k && nums[j] == nums[j + 1]){
                    j++;
                }
                j++;
            }
        }
    }
    return res;
}

int main() {
   ifstream ifs("../Tests/in4", ios::in);
   ofstream ofs("out", ios::out);
    int n;
    ifs >> n;
    vector<int> v;
    for (int i = 0; i < n; ++i){
        int num;
        ifs >> num;
        v.push_back(num);
    }
    int target;
    ifs >> target;
    ofs << threeSumClosest(v, target) << endl;
}