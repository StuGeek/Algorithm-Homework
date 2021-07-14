#include <iostream>
#include <vector>

using namespace std;

int find_and_insert(vector<int> & table, int k){
    int t = 1;
    int index = k % table.size();
    if (table[index] == -1){
        table[index] = k;
        return 1;
    }
    else{
        while(table[index] != -1){
            index = (index + 1) % table.size();
            t++;
        }
        table[index] = k;
        return t;
    }
}

int main(){
    int size;
    cin >> size;
    vector<int> table(size, -1);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        int num;
        cin >> num;
        cout << find_and_insert(table, num) << " ";
    }
}