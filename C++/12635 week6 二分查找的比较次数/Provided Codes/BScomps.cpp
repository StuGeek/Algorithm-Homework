#include <iostream>
#include <vector>

using namespace std;

pair<bool, int> binary_search(vector<int> list, int bot, int top, int target){
    if (list.size() == 0) return {false, 0};
    if (list.size() == 1) return {true, 1};
    if (bot < top){
        int m = bot + (top - bot) / 2;
        cout << m << " " << list[m] << endl;
        if (list[m] == target) return {true, 1};
        else if (list[m] < target) {
            pair<bool, int> t = binary_search(list, m + 1, top, target);
            return {t.first, t.second + 1};
        }
        else {
            pair<bool, int> t = binary_search(list, bot, m - 1, target);
            return {t.first, t.second + 1};
        }
    }
    return {false, 1};
}

pair<bool, int> binary_search(vector<int> list, int target){
    return binary_search(list, 0, list.size(), target);
}