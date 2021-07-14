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

void partition(vector<int> & nums, int low, int high){
    int pivot = nums[low];
    int last_small = low;
    for (int i = low + 1; i < high; ++i){
        if (pivot > nums[i]){
            last_small = last_small + 1;
            swap(nums[last_small], nums[i]);
        }
    }
   swap(nums[low], nums[last_small]);
}

bool correctPartitiom(vector<int> & nums, vector<int> & v){
    int n = nums.size();
    for(int i = 0; i < n; ++i) {
        if (nums[i] != v[i]) return false;
    }
    return true;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int n;
    ifs >> n;
    vector<int> nums;
    for(int i = 0; i < n; ++i) {
        int num;
        ifs >> num;
        nums.push_back(num);
    }
    partition(nums, 0, nums.size());
    int m;
    ifs >> m;
    for(int i = 0; i < m; ++i) {
        vector<int> v;
        for (int i = 0; i < n; ++i){
            int num;
            ifs >> num;
            v.push_back(num);
        }
        if (correctPartitiom(nums, v)){
            ofs << "Yes" << endl;
        }
        else{
            ofs << "No" << endl;
        }
    }
}