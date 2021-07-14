#include <iostream>
#include <stack>

using namespace std;

bool match(string line){
    stack<char> brackets;
    int n = line.size();
    for(int i = 0; i < n; ++i){
        if(line[i] == '(' || line[i] == '[' || line[i] == '{'){
            brackets.push(line[i]);
        }
        else if (line[i] == ')'){
            if (brackets.empty() || brackets.top() != '(') return false;
            else brackets.pop();
        }
        else if (line[i] == ']'){
            if (brackets.empty() || brackets.top() != '[') return false;
            else brackets.pop();
        }
        else if (line[i] == '}'){
            if (brackets.empty() || brackets.top() != '{') return false;
            else brackets.pop();
        }
    }
    if (brackets.empty()) return true;
    else return false;
}

int main() {
    string s;
    getline(cin, s);
    if (match(s)){
        cout << "True" << endl;
    }
    else{
        cout << "False" << endl;
    }
}