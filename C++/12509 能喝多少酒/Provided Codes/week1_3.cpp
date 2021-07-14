#include <iostream>

using namespace std;

int sumOfBottle(int numBottles, int numExchange)
{
    return numBottles >= numExchange ? numBottles + (numBottles - numExchange) / (numExchange - 1) + 1 : numBottles;
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int numBottles, numExchage;
        cin >> numBottles >> numExchage;
        cout << sumOfBottle(numBottles, numExchage) << endl;
    }
}