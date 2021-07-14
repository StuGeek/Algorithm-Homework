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

bool isQueueToStack(vector<int> & stk, vector<int> & que){
    if (stk.size() == 0) return true;
    stack<int> s;
    int i = 0;
    int j = 0;
    int stk_size = stk.size();
    int que_size = que.size();
    while(i != stk_size){
        s.push(stk[i++]);
        while(!s.empty() && s.top() == que[j]){
            s.pop();
            j++;
        }
    }
    if (j == que_size) return true;
    else return false;
}

int main() {
   ifstream ifs("../Tests/in1", ios::in);
   ofstream ofs("out", ios::out);
   int T;
   ifs >> T;
   while(T--){
       int n;
       ifs >> n;
       vector<int> stk;
       vector<int> que;
        for(int i = 0; i < n; ++i) {
            int num;
            ifs >> num;
            stk.push_back(num);
        }
       for(int i = 0; i < n; ++i) {
            int num;
            ifs >> num;
            que.push_back(num);
        }
        if (isQueueToStack(stk, que)){
            ofs << "Yes" << endl;
        }
        else{
            ofs << "No" << endl;
        }
   }
}