#include <iostream>
#include <stack>
#include <vector>

using namespace std;


vector<int> dfs(int start, vector<vector<int>> listaPovezanosti, vector<bool>& posecen) 
{
    vector<int> dfsObilazak;
    stack<int> neobradjeni;
    neobradjeni.push(start);
    posecen[start] = true;

    while(!neobradjeni.empty()) 
    {
        int cvor = neobradjeni.top();

        neobradjeni.pop();
        dfsObilazak.push_back(cvor);
        
        for(int sused : listaPovezanosti[cvor])
        {
            if(!posecen[sused])
            {
                neobradjeni.push(sused);
                posecen[sused] = true;
            }
        }
    }
    return dfsObilazak;
}

void dfsRek(int start, vector<vector<int>> lp, vector<bool>& posecen)
{
    posecen[start] = true;

    for(int sused : lp[start])
    {
        if(!posecen[sused])
        {
            dfsRek(sused, lp, posecen);
        }
    }
    cout << start << endl;

}

void stampajVektor(vector<int> v)
{
    for(int e : v)
        cout << e << " ";
    cout << endl;
}

int main() 
{
    vector<vector<int>> listaPovezanosti = {{1, 3, 4}, {0, 2}, {1, 3}, {0, 2}, {0, 5}, {4}};
    vector<bool> posecen(listaPovezanosti.size(), false);

//    stampajVektor(dfs(0, listaPovezanosti, posecen));
    cout << endl;

    dfsRek(0, listaPovezanosti, posecen);
}