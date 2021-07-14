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
        int pre;
        cin >> pre;
        int nmb = 1;
        int result = nmb;
        for (int i = 1; i < N; ++i)
        {
            int num;
            cin >> num;
            if (num > pre)
            {
                nmb++;
                if (nmb > result) result = nmb;
            }
            else nmb = 1;
            pre = num;
        }
        cout << result << endl;
    }
}