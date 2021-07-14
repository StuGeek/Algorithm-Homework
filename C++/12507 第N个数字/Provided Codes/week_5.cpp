#include <iostream>

using namespace std;

int orderOfNumber(int n)
{
    int digits = 1;
    int range = 9;
    int sum = 9;
    while(n > sum)
    {
        digits++;
        range *= 10;
        sum += digits * range;
    }
    sum -= digits * range;
    n -= sum;
    int num = 1;
    for (int i = 1; i < digits; ++i)
    {
        num *= 10;
    }
    int number = num + (n - 1) / digits;
    int index = (n - 1) % digits + 1;
    for(int i = index; i < digits; ++i)
    {
        number /= 10;
    }
    return number % 10;
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int N;
        cin >> N;
        cout << orderOfNumber(N) << endl;
    }
}