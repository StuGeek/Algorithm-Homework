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
#include "Customer.h"

using namespace std;

vector<int> accessArray(const vector<Customer> & table) {
    vector<string> name;
    int n = table.size();
    for(int i = 0; i < n; ++i) {
        name.push_back(table[i].name);
    }
    sort(name.begin(), name.end());
    unordered_map<string, int> themap;
    for(int i = 0; i < n; ++i) {
        themap[name[i]] = i;
    }
    vector<int> v;
    for(int i = 0; i < n; ++i) {
        v.push_back(themap[table[i].name]);
    }
    return v;
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int T;
    ifs >> T;
    vector<Customer> table;
    while(T--){
        Customer t;
        ifs >> t.name >> t.phone >> t.address;
        table.push_back(t);
    }
    vector<int> v = accessArray(table);
    int n = v.size();
    for(int i = 0; i < n; ++i) {
        ofs << v[i] << endl;
    }
}