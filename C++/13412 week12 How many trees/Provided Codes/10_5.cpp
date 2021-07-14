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

long long dp[100][100];

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int n, h;
    ifs >> n >> h;
    for (int i = 0; i <= n; ++i) {
        dp[0][i] = 1;
    }
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            for (int k = 0; k < i; ++k) {
                dp[i][j] += dp[k][j - 1] * dp[i - k - 1][j - 1];
            }
        }
    }
    ofs << dp[n][n] - dp[n][h - 1] << endl;
}