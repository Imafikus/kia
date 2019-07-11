#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;


template<typename T>
void stampajMatricu (vector<vector<T>> matrica)
{
    for(int i = 0; i < matrica.size(); i++)
    {
        for(int j = 0; j < matrica.size(); j++)
        {
            cout << matrica[i][j] << " ";
        }   
        cout << endl;
    }
}

bool bfs(int izvor, int ponor, vector<vector<pair<int ,int>>> ls, vector<int>& roditelj, vector<vector<int>> rg)
{
    vector<bool> posecen(ls.size(), false);
    queue<int> neobradjeni;
    posecen[izvor] = true;
    neobradjeni.push(izvor);

    while(!neobradjeni.empty())
    {
        int cvor = neobradjeni.front();
        neobradjeni.pop();

        for(auto sused : ls[cvor])
        {
            if(!posecen[sused.first] && rg[cvor][sused.first] > 0)
            {
                roditelj[sused.first] = cvor;
                neobradjeni.push(sused.first);
                posecen[sused.first] = true;
            }
        }
    }

    return posecen[ponor];
}

void edmondKarp(int izvor, int ponor, vector<vector<pair<int ,int>>> ls)
{
    int n = ls.size();
    vector<vector<int>> rg(n);
    for(int i = 0; i < n; i++)
        rg[i].resize(n, 0);
    
    for(int i = 0; i < n; i++)
    {
        for(auto sused : ls[i])
            rg[i][sused.first] = sused.second;
    }

    vector<int> roditelj(n, -1);
    int maxTok = 0;

    while(bfs(izvor, ponor, ls, roditelj, rg))
    {
        int bottleneck = 10000;

        for(int cvor = ponor; cvor != izvor; cvor = roditelj[cvor])
        {
            int u = roditelj[cvor];
            bottleneck = min(bottleneck, rg[u][cvor]);
        }
        for(int cvor = ponor; cvor != izvor; cvor = roditelj[cvor])
        {
            int u = roditelj[cvor];
            rg[u][cvor] -= bottleneck;
            rg[cvor][u] += bottleneck;
        }
        maxTok += bottleneck;
    }
    cout << "Optimalni tok je: " << maxTok << endl;
}

int main()
{
    // int brojGrana, brojCvorova;
    // cin >> brojCvorova >> brojGrana;

    // vector<vector<pair<int, int>>> ls(brojCvorova);
    // for(int i = 0; i < brojGrana; i++)
    // {
    //     int u, v, t;
    //     cin >> u >> v >> t;
    //     ls[u].push_back({v, t});
    //     ls[v].push_back({u, t});
    // }

    vector<vector<pair<int, int>>> ls = {
        {{1, 5}, {2, 7}, {3, 6}}, 
        {{4, 4}, {5, 3}}, 
        {{5, 4}, {6, 1}}, 
        {{6, 5}}, 
        {{7, 3}}, 
        {{7, 7}}, 
        {{5, 4}, {7, 6}}, 
        {}};
    
    // int izvor, ponor;
    // cin >> izvor >> ponor;
    edmondKarp(0, 7, ls);
}