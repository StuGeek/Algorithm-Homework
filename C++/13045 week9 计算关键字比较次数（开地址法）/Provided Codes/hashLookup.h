#include "hashTypes.h"

pair<pair<bool, size_t>, int> lookup(const Table& t, const Key k) {
    int M = t.size();
    size_t index = h(k, M);
    size_t temp = index;
    if (t[index].first == k && !t[index].second) return {{true, index}, 1};
    else {
        int res = 1;
        while(t[index].first != k || t[index].second) {
            index = (index + 1) % M;
            if (index == 0) index = 1;
            res++;
            if (index == temp) return {{false, index}, res};
        }
        return {{true, index}, res};
    }
}