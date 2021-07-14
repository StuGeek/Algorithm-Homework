#ifndef NODE
#define NODE

#include <iostream>

using namespace std;

template <class Entry>
struct Node
{
	Entry entry;
	Node<Entry> *left;
	Node<Entry> *right;

	Node(const Entry &en)
	{
		entry = en;
		left = NULL;
		right = NULL;
	}
};

#endif