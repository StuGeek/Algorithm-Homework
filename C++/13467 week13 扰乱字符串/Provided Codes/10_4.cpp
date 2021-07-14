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

bool isScramble(string & s1, string & s2) {
    if (s1.size() != s2.size()) return false;
    if (s1 == s2) return true;
    int n = s1.size();
    vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (s1[i] == s2[j]) dp[i][j][1] = true;
            else dp[i][j][1] = false;
        }
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            for (int j = 0; j <= n - len; ++j) {
                for (int k = 1; k < len; ++k) {
                    if ((dp[i][j][k] && dp[i + k][j + k][len - k]) || (dp[i + k][j][len - k] && dp[i][j + len - k][k])) {
                        dp[i][j][len] = true;
                    }
                }
            }
        }
    }
    return dp[0][0][n];
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    string s1, s2;
    ifs >> s1 >> s2;
    if (isScramble(s1, s2)) ofs << "1" << endl;
    else ofs << "0" << endl;
}