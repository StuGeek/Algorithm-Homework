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

int mod = 1e9 + 7;

int climbStairs(int n){
    int p = 0, q = 0, r = 1;
    for (int i = 1; i <= n; ++i){
        p = q;
        q = r;
        r = (p + q) % mod;
    }
    return r;
}

int main() {
   int T;
   cin >> T;
   while(T--){
       int n;
       cin >> n;
       cout << climbStairs(n) << endl;
   }
}