#include <iostream>
#include <vector>
using namespace std;

typedef int Key;
typedef pair<Key, bool>  Cell;
//a cell consists of a key and a flag of bool. If the cell is empty, the second component is set to true, otherwise false.
typedef vector<Cell> Table; //type of a hash table

//hash function, where M should be the hash table size.
size_t h(Key k, size_t M = 11){
    return k % M;
}

