bool binary_search(vector<int> list, int bot, int top, int target){
    if (list.size() == 0) return false;
    if (list.size() == 1) return true;
    if (bot < top){
        int m = bot + (top - bot) / 2;
        if (list[m] == target) return true;
        else if (list[m] < target) return binary_search(list, m + 1, top, target);
        else return binary_search(list, bot, m - 1, target);
    }
    return false;
}