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

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int T;
    ifs >> T;
    while(T--){
        vector<int> v;
        int num;
        while(ifs >> num){
            if (num % 2 == 1) {
                ofs << num << " ";
            }
            else v.push_back(num);
            if (ifs.get() == '\n') {
                for (int i = 0; i < v.size(); ++i){
                    ofs << v[i] << " ";
                }
                ofs << endl;
                break;
            }
        }
    }
}