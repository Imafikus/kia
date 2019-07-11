#include <vector>
#include <iostream>
#include <stack>

using namespace std;

void dfs(int cvor, stack<int>& topSort, vector<bool>& posecen, vector<vector<int>> ms)
{
    posecen[cvor] = true;
    for(int i = 0; i < ms.size(); i++)
    {
        if(ms[cvor][i] != 0 && !posecen[i])
        {
            dfs(i, topSort, posecen, ms);
        }
    }
    topSort.push(cvor);
    cout << cvor << " ";
}

void dodajGranu(int u, int v, vector<vector<int>>& ms)
{
    ms[u][v] = 1;
}

int main()
{
    vector<vector<int>> ms;
    int brojCvorova = 6;
    ms.resize(brojCvorova);
    for(int i = 0; i < brojCvorova; i++)
        ms[i].resize(brojCvorova, 0);

    dodajGranu(0, 4, ms);
    dodajGranu(0, 1, ms);
    dodajGranu(0, 3, ms);
    dodajGranu(1, 2, ms);
    dodajGranu(3, 2, ms);
    dodajGranu(4, 5, ms);

    cout << "Dodao grane" << endl;

    stack<int> topSort;
    vector<bool> posecen(brojCvorova, false);
    dfs(0, topSort, posecen, ms);
    cout << endl;

    cout << "top sort:" << endl;
    while(topSort.size() > 1)
    {
        int prvi = topSort.top();
        topSort.pop();
        int drugi = topSort.top();
        if(ms[prvi][drugi] == 0)
        {
            cout << "NEMA PUTA" << endl;
            return 0;
        }
    }
    cout << "IMA PUTA" << endl;
    cout << endl;
}