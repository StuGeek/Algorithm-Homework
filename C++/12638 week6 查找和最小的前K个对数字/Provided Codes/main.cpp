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

struct cmp{
    bool operator () (pair<int, int> &a, pair<int, int> &b) const{
        return a.first + a.second > b.first + b.second;
    }
};

int main() {
   ifstream ifs("../Tests/in1", ios::in);
   ofstream ofs("out", ios::out);
   int k, m, n;
   ifs >> k >> m >> n;
   vector<int> v;
   priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> p;
   for(int i = 0; i < m; ++i){
       int num;
       ifs >> num;
       v.push_back(num);
    }
   for(int i = 0; i < n; ++i) {
       int num;
       ifs >> num;
        for (int j = 0; j < m; ++j){
            p.push({v[j], num});
        }
    }
    for (int i = 0; i < k && !p.empty(); ++i){
        pair<int, int> t = p.top();
        p.pop();
        ofs << t.first << "," << t.second << " ";
    }
}