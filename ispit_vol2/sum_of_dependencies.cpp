#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        int n, e;
        cin >> n >> e;

        vector<vector<int>> lp(n);

        for(int j = 0; j < e; j++)
        {
            int u, v;
            cin >> u >> v;
            lp[u].push_back(v);
        }

        cout << e << endl;
    }
}