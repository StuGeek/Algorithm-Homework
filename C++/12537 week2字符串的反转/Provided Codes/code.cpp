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

string reverseWords(string s){
    int n = s.size();
    int i = 0;
    while(i < n){
        int start = i;
        while(i < n && s[i] != ' ') {
            i++;
        }
        int end = i - 1;
        while(start < end){
            char c = s[start];
            s[start] = s[end];
            s[end] = c;
            start++;
            end--;
        }
        while(i < n && s[i] == ' '){
            i++;
        }
    }
    return s;
}

int main() {
    string s;
    getline(cin, s);
    cout << reverseWords(s) << endl;
}