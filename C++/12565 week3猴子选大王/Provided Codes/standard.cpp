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

int getMonketKing(int n, int m){
    queue<int> que;
    for (int i = 1; i <= n; ++i){
        que.push(i);
    }
    while(que.size() != 1){
        for (int i = 0; i < m; ++i){
            int temp = que.front();
            que.pop();
            if (i != m - 1) que.push(temp);
        }
    }
    return que.front();
}

int main() {
   int T;
   cin >> T;
   while(T--){
       int n, m;
       cin >> n >> m;
       cout << getMonketKing(n, m) << endl;
   }
}