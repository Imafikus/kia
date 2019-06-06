#include <vector>
#include <iostream>
#include <tuple>

using namespace std;


vector<vector<pair<int, int>>> listaSuseda;
vector<int> velicinaKomponente;
vector<int> ids;

int findK(int x)
{
    int koren = x;
    while(koren != ids[x])
    {
        koren = ids[koren];
    }

    while(x != koren)
    {
        int sledeci = ids[x];
        ids[x] = koren;
        x = sledeci;
    }

    return koren;
}

void unionK(int x, int y)
{
    int korenX = findK(x);
    int korenY = findK(y);

    if(korenX == korenY) return;

    if(velicinaKomponente[x] < velicinaKomponente[y])
    {
        velicinaKomponente[y] += velicinaKomponente[x];
        ids[korenX] = korenY;
    }
    else
    {
        velicinaKomponente[x] += velicinaKomponente[y];
        ids[korenY] = korenX;
    }
}

void kruskal(vector<tuple<int, int, int>>& mcst)
{
    vector<pair<int, pair<int, int>>> grane;
    for(int cvor = 0; cvor < listaSuseda.size(); cvor++)
    {
        for(pair<int, int> sused : listaSuseda[cvor])
        {
            int tezina = sused.second;
            grane.push_back({tezina, {cvor, sused.first}});
        }
    }
    sort(grane.begin(), grane.end());
    int brojGrana = 0;

    for(auto jednaGrana : grane)
    {
        if(brojGrana == listaSuseda.size() - 1) break;

        int tezina = jednaGrana.first;
        int u = jednaGrana.second.first;
        int v = jednaGrana.second.second;

        int skupU = findK(u);
        int skupV = findK(v);

        if(skupU != skupV)
        {
            unionK(u, v);
            mcst.push_back(make_tuple(u, v, tezina));
            brojGrana++;
        }
    }
}

void stampajMCST(vector<tuple<int, int, int> > mcst)
{
    for(tuple<int, int, int> e : mcst)
    {
        cout << get<0>(e) << " - " << get<1>(e) << " tezina grane: " << get<2>(e) << endl; 
    }
}

int main()
{
    listaSuseda = {
        {{1, 2}, {3, 4}},
        {{0, 2}, {2, 1}},
        {{1, 1}, {3, 3}},
        {{0, 4}, {2, 3}}
    };
    
    ids.resize(listaSuseda.size());
    for(int i = 0; i < listaSuseda.size(); i++)
    {
        ids[i] = i;
    }

    velicinaKomponente.resize(listaSuseda.size(), 1);
    vector<tuple<int, int, int> > mcst;

    kruskal(mcst);
    stampajMCST(mcst);

}