#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <list>

using namespace std;

bool getval(char c, map<char, bool> f){
    if (c == '0') return false;
    else if (c == '1') return true;
    else return f[c];
}

bool eval_BE(const string & exp, map<char, bool> f){
    int n = exp.size();
    if (n == 0) return true;
    vector<char> the_stack(n);
    int top = 0;
    bool res = f[exp[0]];
    for (int i = 0; i < n; ++i){
        if ((exp[i] >= 'a' && exp[i] <= 'z') || 
                exp[i] == '0' || exp[i] == '1'){
            the_stack[top++] = exp[i];
        }
        else if (exp[i] == '-'){
            res = !res;
        }
        else{
            bool temp1 = getval(the_stack[--top], f);
            bool temp2 = getval(the_stack[--top], f);
            if (exp[i] == '+'){
                res = temp1 || temp2;
            }
            else if (exp[i] == '*'){
                res = temp1 && temp2;
            }
        }
    }
    return res;
}

int main() {
   int T;
   cin >> T;
   while(T--){
       string exp;
       cin >> exp;
       map<char, bool> f;
       f['a'] = true;
       f['b'] = false;
       if (eval_BE(exp, f)){
           cout << "True" << endl;
       }
       else{
           cout << "False" << endl;
       }
   }
}