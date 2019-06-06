#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> ids;
vector<int> lowLink;
vector<int> roditelj;
vector<bool> posecen;
int id = 1;
set<int> artikulacioneTacke;


void nadjiArtikulacioneTacke(int cvor, vector<vector<int>> listaPovezanosti)
{
    posecen[cvor] = true;
    
    ids[cvor] = id;
    lowLink[cvor] = id;
    id++;

    int decaCvora = 0;

    for(int sused : listaPovezanosti[cvor])
    {   
        if(!posecen[sused])
        {
            roditelj[sused] = cvor;
            decaCvora++;

            nadjiArtikulacioneTacke(sused, listaPovezanosti);

            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);

            if(roditelj[cvor] == -1 && decaCvora > 1)
                artikulacioneTacke.insert(cvor);

            if(roditelj[cvor] != -1 && lowLink[sused] >= ids[cvor])
                artikulacioneTacke.insert(cvor);
        }
        else if(sused != roditelj[cvor])
        {
            lowLink[cvor] = min(lowLink[cvor], ids[sused]);
        }
    }
}

template<typename T>
void stampajSet(set<T> v)
{
    for(auto it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;
}
./
int main()
{
    vector<vector<int>> listaPovezanosti = {{1, 3, 4}, {0, 2}, {1}, {0, 6}, {0, 5}, {4}, {3}};

    ids.resize(listaPovezanosti.size());
    lowLink.resize(listaPovezanosti.size());
    
    roditelj.resize(listaPovezanosti.size(), -1);
    posecen.resize(listaPovezanosti.size(), false);

    nadjiArtikulacioneTacke(0, listaPovezanosti);

    stampajSet(artikulacioneTacke);
}