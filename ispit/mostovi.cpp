#include <vector>
#include <iostream>

using namespace std;

void nadjiMostove(int cvor, vector<vector<int>> listaPovezanosti, vector<bool> posecen, vector<int>& roditelj, vector<int>& ids, vector<int>& lowLink, int& id, vector<pair<int, int>>& mostovi)
{
    posecen[cvor] = true;

    ids[cvor] = id;
    lowLink[cvor] = id;
    id++;

    for(int sused : listaPovezanosti[cvor])
    {
        if(!posecen[sused])
        {
            roditelj[sused] = cvor;
            nadjiMostove(sused, listaPovezanosti, posecen, roditelj, ids, lowLink, id, mostovi);

            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);
            if(ids[cvor] < lowLink[sused])
            {
                mostovi.push_back({cvor, sused});
            }
        }
        else if(roditelj[cvor] != sused)
        {
            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);
        }
    }

}

void stampajMostove(vector<pair<int, int>> v)
{
    for(pair<int, int> most : v)
    {
        cout << most.first << " " << most.second << endl;
    }
}

int main()
{
    vector<vector<int>> listaPovezanosti = {{1, 3, 4}, {0, 2}, {1, 3}, {0, 2}, {0, 5}, {4}};
    
    vector<bool> posecen(listaPovezanosti.size(), false);
    vector<int> roditelj(listaPovezanosti.size(), -1);    
    
    vector<int> ids(listaPovezanosti.size());
    vector<int> lowLink(listaPovezanosti.size());

    vector<pair<int, int>> mostovi;
    int id = 0;
    nadjiMostove(0, listaPovezanosti, posecen, roditelj, ids, lowLink, id, mostovi);

    cout << mostovi.size() << endl;
    stampajMostove(mostovi);
}