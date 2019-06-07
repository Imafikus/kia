#include <vector>
#include <iostream>

using namespace std;

vector<int> rastavniNaProsteCinioce(int n)
{
    vector<int> prostiCinioci(n * n);

    for(int i = 2; i * i < n * n; i++)
    {
        prostiCinioci[i] = i;
    }

    for(int i = 2; i * i < n * n; i++)
    {
        if(prostiCinioci[i] == i)
        {
            for(int k = i; k < n * n; k += i)
            {
                prostiCinioci[k] = i;
            }
        }
    }

    vector<int> cinioci;
    while(n != 1)
    {
        cinioci.push_back(prostiCinioci[n]);
        n = n / prostiCinioci[n];
    }
    return cinioci;
}

void stampajVektor(vector<int> v)
{
    for(int e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main ()
{
    stampajVektor(rastavniNaProsteCinioce(140));
}
