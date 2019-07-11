#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

void dodajGranu(int u, int v, vector<vector<int>>& ls)
{
    ls[u].push_back(v);
    ls[v].push_back(u);
}

void mostovi(int cvor, const vector<vector<int>>& ls, vector<int>& ids, vector<int>& lowLink, int& id, vector<int>& roditelj, vector<bool>& posecen)
{
    posecen[cvor] = true;
    lowLink[cvor] = id;
    ids[cvor] = id;
    id++;
    cout << "Dosao ovde" << endl;

    for(int sused : ls[cvor])
    {
        if(!posecen[sused])
        {
            roditelj[sused] = cvor;
            mostovi(sused, ls, ids, lowLink, id, roditelj, posecen);

            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);
            if(ids[cvor] < lowLink[sused])
            {
                cout << cvor << " " << sused << endl;
            }
        }
        else if(roditelj[cvor] != sused)
        {
            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);
        }
    }
}

void artikulacioneTacke(int cvor, vector<vector<int>>& ls, vector<bool>& posecen, vector<int>& lowLink, vector<int>& ids, vector<int>& roditelj, int& id)
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
            roditelj[sused] = cvor;
            brojDece++;
            artikulacioneTacke(sused, ls, posecen, lowLink, ids, roditelj, id);

            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);

            if(roditelj[cvor] == -1 && brojDece > 1)
                cout << cvor << endl;

            if(roditelj[cvor] != -1 && ids[sused] >= lowLink[cvor])
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
    int brojCvorova = 6;
    vector<vector<int>> ls(brojCvorova);// = {{1, 3, 4}, {0, 2}, {1, 3}, {0, 2}, {0, 5}, {4}};
    // vector<vector<int>> ls(brojCvorova);
    vector<int> roditelj(brojCvorova, -1);
    vector<bool> posecen(brojCvorova, false);

    vector<int> lowLink(brojCvorova);
    vector<int> ids(brojCvorova);

    dodajGranu(0, 4, ls);
    dodajGranu(0, 1, ls);
    dodajGranu(0, 3, ls);
    // dodajGranu(1, 2, ls);
    dodajGranu(3, 2, ls);
    dodajGranu(4, 5, ls);

    int id = 0;
    artikulacioneTacke(0, ls, posecen, lowLink, ids, roditelj, id);

}