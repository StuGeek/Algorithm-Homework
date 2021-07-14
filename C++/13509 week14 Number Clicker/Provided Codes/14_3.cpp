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

long long int quick_pow(long long int base, long long int n, long long int mod) {
    long long int ans = 1;
    while (n > 0) {
        if (n & 1) {
            ans = (base * ans) % mod;
        }
        base = (base * base) % mod;
        n >>= 1;
    }
    return ans;
}

long long int buttonPress(long long int u, long long int v, long long int p) {
    if (u == v) return 0;
    queue<long long int> q1;
    queue<long long int> q2;
    vector<long long int> vis1(1000000);
    vector<long long int> vis2(1000000);
    q1.push(u);
    q2.push(v);
    while (true) {
        long long int num1 = q1.front();
        q1.pop();
        long long int num2 = q2.front();
        q2.pop();
        long long int num = (num1 + 1) % p;
        if (vis2[num] || num == v) return vis1[num1] + vis2[num] + 1;
        if (!vis1[num] && num != u) {
            vis1[num] = vis1[num1] + 1;
            q1.push(num);
        }
        num = (num1 + p - 1) % p;
        if (vis2[num] || num == v) return vis1[num1] + vis2[num] + 1;
        if (!vis1[num] && num != u) {
            vis1[num] = vis1[num1] + 1;
            q1.push(num);
        }
        num = quick_pow(num1, p - 2, p);
        if (vis2[num] || num == v) return vis1[num1] + vis2[num] + 1;
        if (!vis1[num] && num != u) {
            vis1[num] = vis1[num1] + 1;
            q1.push(num);
        }
        num = (num2 + p - 1) % p;
        if (vis1[num] || num == u) return vis1[num] + vis2[num2] + 1;
        if (!vis2[num] && num != v) {
            vis2[num] = vis2[num2] + 1;
            q2.push(num);
        }
        num = (num2 + 1) % p;
        if (vis1[num] || num == u) return vis1[num] + vis2[num2] + 1;
        if (!vis2[num] && num != v) {
            vis2[num] = vis2[num2] + 1;
            q2.push(num);
        }
        num = quick_pow(num2, p - 2, p);
        if (vis1[num] || num == u) return vis1[num] + vis2[num2] + 1;
        if (!vis2[num] && num != v) {
            vis2[num] = vis2[num2] + 1;
            q2.push(num);
        }
    }
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    long long int u, v, p;
    ifs >> u >> v >> p;
    ofs << buttonPress(u, v, p) << endl;
}