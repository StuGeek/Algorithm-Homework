#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int N;
        cin >> N;
        int t;
        cin >> t;
        int count = 0;
        for (int i = 1; i < N; ++i)
        {
            int temp;
            cin >> temp;
            if (t % 2 != temp % 2)
            {
                count++;
            }
        }
        count = count > N - count ? N - count : count;
        cout << count << endl;
    }
}