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

void pop(vector<int> & min_Heap){
    if (min_Heap[0] == 0) return;
    int high, low;
    int temp = min_Heap[min_Heap[0]--];
    for (high = 1; high << 1 <= min_Heap[0]; high = low){
        low = high << 1;
        if (low != min_Heap[0] && min_Heap[low] > min_Heap[low + 1]){
            low += 1;
        }
        if (min_Heap[low] < temp){
            min_Heap[high] = min_Heap[low];
        }
        else break;
    }
    min_Heap[high] = temp;
}

int main(){
    ifstream ifs("../Tests/in1", ios::in);
    ofstream ofs("out", ios::out);
    int t;
    ifs >> t;
    while(t--){
        int n;
        vector<int> heap;
        ifs >> n;
        heap.resize(n + 1);
        heap[0] = n;
        for (int i = 1; i < n + 1; ++i){
            ifs >> heap[i];
        }
        int t = heap[1];
        pop(heap);
        for(int i = 1; i < n; ++i){
            ofs << heap[i] << " ";
        }
        ofs << t << " " << endl;
    }
}