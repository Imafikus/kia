#include <vector>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
void stampajVektor(vector<T> v)
{
    for(T e : v)
        cout << e << " ";
    cout << endl;
}

vector<int> dfs(vector<vector<int>> listaPovezanosti, vector<bool>& posecen)
{
    vector<int> dfsObilazak;
    stack<int> s;
    s.push(0);

    while(!s.empty())
    {
        int cvor = s.top();
        posecen[cvor] = true;
    
        s.pop();
        dfsObilazak.push_back(cvor);

        for(int sused : listaPovezanosti[cvor])
        {
            if(!posecen[sused])
            {
                s.push(sused);
            }
        }
    }
    return dfsObilazak;
}

int main()
{
    vector<vector<int>> listaPovezanosti = {{1, 3, 4}, {0, 2}, {1, 3}, {0, 2}, {0, 5}, {4}};
    vector<bool> posecen(listaPovezanosti.size(), false);

    stampajVektor(dfs(listaPovezanosti, posecen));



}
