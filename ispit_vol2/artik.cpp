#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void dodajGranu(int u, int v, vector<vector<int>>& ls)
{
    ls[u].push_back(v);
    ls[v].push_back(u);
}


void artik(int cvor, int& id, vector<vector<int>>& ls, vector<bool>& posecen, vector<int>& roditelj, vector<int>& ids, vector<int>& lowLink)
{
    posecen[cvor] = true;
    ids[cvor] = id;
    lowLink[cvor] = id;
    id++;

    int brojDece = 0;

    for(int sused : ls[cvor])
    {
        if(!posecen[sused])
        {
            brojDece++;
            roditelj[sused] = cvor;
            artik(sused, id, ls, posecen, roditelj, ids, lowLink);

            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);

            if(roditelj[cvor] == -1 && brojDece > 1)
                cout << cvor << endl;
            
            if(roditelj[cvor] != -1 && ids[cvor] <= lowLink[sused])
                cout << cvor << endl;
        }
        else if(roditelj[cvor] != sused)
        {
            lowLink[cvor] = min(lowLink[cvor], ids[sused]);
        }
    }
}

int main()
{
    int brojCvorova, brojGrana;
    cin >> brojCvorova >> brojGrana;

    vector<vector<int>> ls(brojCvorova);
    vector<int> roditelj(brojCvorova, -1);
    vector<int> ids(brojCvorova);
    vector<int> lowLink(brojCvorova);
    vector<bool> posecen(brojCvorova, false);
    int id = 0;

    for(int i = 0; i < brojGrana; i++)
    {
        int u, v;
        cin >> u >> v;
        dodajGranu(u, v, ls);
    } 
    cout << "Prosao dodavanje grana" << endl;

    artik(0, id, ls, posecen, roditelj, ids, lowLink);
}