#include <iostream>
#include <fstream>
#include "quick_sort.cpp"

#define sort forbid
#define qsort forbid
#define qsort_s forbid
#define set forbid

template <class Record> 
void quick_sort(Record* startPointer, Record* endPointer);

using namespace std;

int main()
{
	ifstream ifs("../Tests/in2", ios::in);
	ofstream ofs("out", ios::out);
	int arr[1000], result[1000], num;
	while (ifs >> num)
	{
		for (int i=0; i<num; i++)
			ifs >> arr[i];

		quick_sort(arr, arr+num);

		for (int i=0; i<num; i++)
			ofs << arr[i] << " ";
		ofs << endl;
	}

	return 0;
}
