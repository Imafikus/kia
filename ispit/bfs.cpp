#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename T>
void stampajVektor(vector<T> v)
{
    for(T e : v)
        cout << e << " ";
    cout << endl;
}

vector<int> bfs(vector<vector<int>> listaPovezanosti, vector<bool> posecen)
{
    vector<int> bfsObilazak;
    
    queue<int> neposeceni;
    neposeceni.push(0);
    posecen[0] = true;

    while(!neposeceni.empty())
    {
        int cvor = neposeceni.front();
        bfsObilazak.push_back(cvor);
        neposeceni.pop();

        for(int sused : listaPovezanosti[cvor])
        {
            if(!posecen[sused])
            {
                neposeceni.push(sused);
                posecen[sused] = true;
            }
        }
    }
    return bfsObilazak;
}

int main()
{
    vector<vector<int>> listaPovezanosti = {{1, 3, 4}, {0, 2}, {1, 3}, {0, 2}, {0, 5}, {4}};
    vector<bool> posecen(listaPovezanosti.size(), false);

    stampajVektor(bfs(listaPovezanosti, posecen));

}