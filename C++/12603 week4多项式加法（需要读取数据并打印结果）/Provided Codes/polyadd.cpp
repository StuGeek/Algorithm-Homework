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

struct Poly{
    int coef;
    int expn;
    Poly(int coef, int expn): coef(coef), expn(expn) {};
};

int main() {
   ifstream ifs("../Tests/in6", ios::in);
   ofstream ofs("out", ios::out);
   int T;
   ifs >> T;
   while(T--){
       int n;
       ifs >> n;
       vector<Poly> poly1;
       for (int i = 0; i < n; ++i){
           int coef, expn;
           ifs >> coef >> expn;
           poly1.push_back(Poly(coef, expn));
       }
       cout << endl;
       int m;
       ifs >> m;
       for (int i = 0; i < m; ++i){
           int coef, expn;
           ifs >> coef >> expn;
           bool isIn = false;
           vector<Poly>::iterator it;
           for (it = poly1.begin(); it != poly1.end(); ++it){
               if (it->expn == expn){
                   it->coef += coef;
                   if (it->coef == 0) it = poly1.erase(it);
                   isIn = true;
                   break;
               }
               if (it->expn < expn){
                   poly1.insert(it, Poly(coef, expn));
                   isIn = true;
                   break;
               }
           }
           if (!isIn) poly1.push_back(Poly(coef, expn));
       }
       vector<Poly>::iterator it;
       ofs << poly1.size() << endl;
       for (it = poly1.begin(); it != poly1.end(); ++it){
           if (it->coef != 0){
               ofs << it->coef << " " << it->expn << endl;
           }
       }
   }
}