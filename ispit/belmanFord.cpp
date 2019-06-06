#include <vector>
#include <iostream>

using namespace std;

vector<vector<pair<int, int>>> listaSuseda;
vector<int> udaljenost;
vector<int> roditelj;

void belmanFord(int cvor, int kraj)
{
    udaljenost[cvor] = 0;
    int brojCvorova = listaSuseda.size();

    for(int v = 0; v < brojCvorova; v++)
    {
        for(int trCvor = 0; trCvor < brojCvorova; trCvor++)
        {
            for(pair<int, int> obilazak : listaSuseda[trCvor])
            {
                int sused = obilazak.first;
                int grana = obilazak.second;
                
                if(udaljenost[trCvor] + grana < udaljenost[sused])
                {
                    udaljenost[sused] = udaljenost[trCvor] + grana;
                    roditelj[sused] = trCvor;
                }
            }
        }
    }

    for(int trCvor = 0; trCvor < brojCvorova; trCvor++)
        {
            for(pair<int, int> obilazak : listaSuseda[trCvor])
            {
                int sused = obilazak.first;
                int grana = obilazak.second;
                
                if(udaljenost[trCvor] + grana < udaljenost[sused])
                {
                    cout << "NEGATIVAN CIKLUS" << endl;
                }
            }
        }
    
    for(int t = kraj; t != -1; t = roditelj[t])
        cout << t << " ";
    cout << endl;
}

int main()
{
    listaSuseda = {
        {{1, 2}, {3, 4}},
        {{0, 2}, {2, 1}},
        {{1, 1}, {3, 3}},
        {{0, 4}, {2, 3}}
    };
    roditelj.resize(listaSuseda.size(), -1);
    udaljenost.resize(listaSuseda.size(), 100000);

    belmanFord(0, 2);
}