#include <iostream>

using namespace std;

int sumOfMethod(int n)
{
    if (n == 1) return 1;
    if (n == 2) return 2;
    else
    {
        return sumOfMethod(n - 1) + sumOfMethod(n - 2);
    }
    
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int N;
        cin >> N;
        cout << sumOfMethod(N) << endl;
    }
}