#include <iostream>
#include <vector>

using namespace std;

void dodajGranu(int u, int v, vector<vector<int>> lp, vector<int>& ulazniStepen)
{
    lp[u].push_back(v);
    ulazniStepen[v]++;
}

int nadjiSlobodanCvor(int brojCvorova, vector<int> ulazniStepen, vector<bool> posecen)
{
    for(int cvor = 0; cvor < brojCvorova; cvor++)
    {
        if(ulazniStepen[cvor] == 0 && !posecen[cvor])
            return cvor;
    }
    return -1;
}

void topSort(vector<vector<int>> lp, vector<int> ulazniStepen,  vector<int>& ts)
{
    int brojCvorova = lp.size();
    vector<bool> posecen(brojCvorova, false);

    int brojPosecenih = 0;
    while(true)
    {
        int slobodan = nadjiSlobodanCvor(brojCvorova, ulazniStepen, posecen);
        if(slobodan == -1) break;

        posecen[slobodan] = true;
        brojPosecenih++;

        ts.push_back(slobodan);

        for(int sused : lp[slobodan])
        {
            ulazniStepen[sused]--;
        }
    }

    cout << "broj posecenih: " << brojPosecenih << endl;
    if(brojPosecenih != brojCvorova)
        cout << "NE POSTOJI TOP SORT" << endl;
}

int main()
{
    int brojCvorova = 6;
    vector<vector<int>> listaSuseda(brojCvorova);
    vector<int> ulazniStepen(brojCvorova, 0);
    vector<bool> posecen(brojCvorova, false);

    dodajGranu(0, 4, listaSuseda, ulazniStepen);
    dodajGranu(0, 1, listaSuseda, ulazniStepen);
    dodajGranu(0, 3, listaSuseda, ulazniStepen);
    dodajGranu(1, 2, listaSuseda, ulazniStepen);
    dodajGranu(3, 2, listaSuseda, ulazniStepen);
    dodajGranu(4, 5, listaSuseda, ulazniStepen);

    vector<int> ts;
    topSort(listaSuseda, ulazniStepen, ts);

    for(int e : ts)
    {
        cout << e << " ";
    }
    cout << endl;
}