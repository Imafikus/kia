#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void dodajGranu(int u, int v, vector<vector<int>>& ls)
{
    ls[u].push_back(v);
    ls[v].push_back(u);
}

void mostovi(int cvor, int& id, vector<vector<int>>& ls, vector<int>& roditelj, vector<int>& ids, vector<int>& lowLink, vector<bool>& posecen)
{
    posecen[cvor] = true;
    ids[cvor] = id;
    lowLink[cvor] = id;
    id++;

    for(int sused: ls[cvor])
    {
        if(!posecen[sused])
        {
            roditelj[sused] = cvor;
            mostovi(sused, id, ls, roditelj, ids, lowLink, posecen);

            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);

            if(ids[cvor] < lowLink[sused])
                cout << cvor << " " << sused << endl;
        }
        else if(roditelj[cvor] != sused)
        {
            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);
        }
    }
}

int main()
{
    int brojCvorova, brojGrana;
    cin >> brojCvorova >> brojGrana;

    vector<vector<int>> ls(brojCvorova);
    vector<bool> posecen(brojCvorova, false);
    vector<int> roditelj(brojCvorova, -1);
    vector<int> ids(brojCvorova);
    vector<int> lowLink(brojCvorova);
    int id = 0;

    for(int i = 0; i < brojGrana; i++)
    {
        int u;
        int v;

        cin >> u >> v;
        dodajGranu(u, v, ls);
    }
    cout << "Prosao dodavanje grana" << endl;

    mostovi(0, id, ls, roditelj, ids, lowLink, posecen);
}