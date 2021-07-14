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

string minNumber(vector<string> &s){
    sort(s.begin(), s.end());
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
        string str;
        vector<string> s;
        while(ifs >> str){
            s.push_back(str);
            if (ifs.get() == '\n') break;
        }
        ofs << minNumber(s) << endl;
    }
}