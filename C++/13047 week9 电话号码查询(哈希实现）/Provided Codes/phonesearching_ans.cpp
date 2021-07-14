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

string capitalize (string s) {
    int n = s.size();
    for(int i = 0; i < n; ++i) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] += 32;
        }
    }
    return s;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    unordered_map<string, string> themap;
    int n;
    ifs >> n;
    for(int i = 0; i < n; ++i) {
        string user_phone;
        ifs >> user_phone;
        string user, phone;
        int n = user_phone.size();
        bool flag = false;
        for (int i = 0; i < n; ++i) {
            if (user_phone[i] == ',') flag = true;
            else if (!flag) user += user_phone[i];
            else phone += user_phone[i];
        }
        themap[capitalize(user)] = phone;
    }
    int m;
    ifs >> m;
    for (int i = 0; i < m; ++i) {
        string user;
        ifs >> user;
        string phone = themap[capitalize(user)];
        if (phone == "") {
            ofs << user << ":No" << endl;
        }
        else {
            ofs << user << ":" << phone << endl;
        }
    }
}