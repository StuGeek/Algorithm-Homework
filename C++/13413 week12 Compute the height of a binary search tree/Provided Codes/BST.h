#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>


using namespace std;


typedef int T;
struct BinaryNode{
  T data;
  BinaryNode *left, *right;
  BinaryNode(T d, BinaryNode *l=NULL, BinaryNode* r=NULL):data(d), left(l), right(r) {};
};
