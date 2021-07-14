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

bool compare(const string &s1, const string &s2) {
    return s1 + s2 < s2 + s1;
}

string minChar(vector<string> &s){
    sort(s.begin(), s.end(), compare);
    string res = "";
    int size = s.size();
    for (int i = 0; i < size; ++i){
        res += s[i];
    }
    return res;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int T;
    ifs >> T;
    while(T--){
        int n;
        ifs >> n;
        string str;
        vector<string> s;
        for(int i = 0; i < n; ++i) {
            ifs >> str;
            s.push_back(str);
        }
        ofs << minChar(s) << endl;
    }
}