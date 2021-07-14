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
#include "md5.h"

using namespace std;

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    unordered_map<string, string> themap;
    int n;
    ifs >> n;
    for(int i = 0; i < n; ++i) {
        string user, password;
        ifs >> user >> password;
        themap[user] = password;
    }
    int m;
    ifs >> m;
    for (int i = 0; i < m; ++i) {
        string user, password;
        ifs >> user >> password;
        if (md5(password) == themap[user]) {
            ofs << user << ":OK" << endl;
        }
        else {
            ofs << user << ":Invalid user name or password" << endl;
        }
    }
}