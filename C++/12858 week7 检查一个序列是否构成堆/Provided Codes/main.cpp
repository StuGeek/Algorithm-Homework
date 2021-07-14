#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int judge_heap(vector<int> number){
    bool isMaxheap = false;
    bool isAllEqual = true;
    int size = number.size();
    for (int i = (size - 2) / 2; i >= 0; --i){
        int child = i * 2 + 1;
        if (child + 1 == size) {
            if (number[i] == number[child]) continue;
            else if (number[i] > number[child]) {
                isMaxheap = true;
                isAllEqual = false;
            }
            else isAllEqual = false;
        }
        else {
            if (isAllEqual){
                if (number[i] == number[child] && number[i] == number[child + 1]) continue;
                else if (number[i] >= number[child] && number[i] >= number[child + 1]) {
                    isMaxheap = true;
                    isAllEqual = false;
                }
                else if (number[i] <= number[child] && number[i] <= number[child + 1]) isAllEqual = false;
                else return -1;
            }
            else {
                if (isMaxheap) {
                    if (number[i] >= number[child] && number[i] >= number[child + 1]) continue;
                    else return -1;
                }
                else {
                    if (number[i] <= number[child] && number[i] <= number[child + 1]) continue;
                    else return -1;
                }
            }
        }
    }
    if (isAllEqual) return 0;
    else if (isMaxheap) return 2;
    else return 1;
}

int main(){
    ifstream ifs("../Tests/in4", ios::in);
    ofstream ofs("out", ios::out);
    int n;
    vector<int> heap;
    ifs >> n;
    for (int i = 0; i < n; ++i) {
        int num;
        ifs >> num;
        heap.push_back(num);
    }
    int res = judge_heap(heap);
    if (res == 2){
        ofs << "max heap" << endl;
    }
    else if (res == 1) {
        ofs << "min heap" << endl;
    }
    else if (res == 0) {
        ofs << "both" << endl;
    }
    else {
        ofs << "no" << endl;
    }
}