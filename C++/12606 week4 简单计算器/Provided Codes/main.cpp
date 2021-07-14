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

int priority(char c){
	switch (c){
		case '+' : return 1;
		case '-' : return 1;
		case '*' : return 2;
		case '/' : return 2;
		default : return 0;
	}
}

bool isNumber(char c) {
    if (c >= '0' && c <= '9') return true;
    else return false;
}

string InfixToPostfix(string & exp) {
    stack<char> symbol;
    string res = "";
    int n = exp.size();
    for (int i = 0; i < n; ++i) {
        if (isNumber(exp[i])) {
            res += exp[i];
            if (i == n - 1 || !isNumber(exp[i + 1])) {
                res += " ";
            }
        }
        else if (exp[i] == '(') {
            if (exp[i + 1] == '-') {
                res += "0 ";
            }
            symbol.push(exp[i]);
        }
        else if (exp[i] == ')') {
            while(symbol.top() != '(') {
                res += symbol.top();
                symbol.pop();
            }
            symbol.pop();
        }
        else {
            while (!symbol.empty() && priority(exp[i]) < priority(symbol.top())) {
                res += symbol.top();
                symbol.pop();
            }
            symbol.push(exp[i]);
        }
    }
    while (!symbol.empty()) {
        res += symbol.top();
        symbol.pop();
    }
    return res;
}

int EvaOfPostfix(string & exp) {
    int n = exp.size();
    stack<int> number;
    for (int i = 0; i < n; ++i) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            int num = 0;
            while(exp[i] != ' ') {
                num *= 10;
                num += exp[i] - '0';
                i++;
            }
            number.push(num);
        }
        else {
            int num1 = number.top();
            number.pop();
            int num2 = number.top();
            number.pop();
            switch (exp[i]) {
                case '+':
                    number.push(num1 + num2);
                    break;
                case '-':
                    number.push(num2 - num1);
                    break;
                case '*':
                    number.push(num1 * num2);
                    break;
                case '/':
                    number.push(num2 / num1);
                    break;
                default:
                    break;
            }
        }
    }
    return number.top();
}

int main() {
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    string s;
    ifs >> s;
    string exp = InfixToPostfix(s);
    ofs << EvaOfPostfix(exp) << endl;
}