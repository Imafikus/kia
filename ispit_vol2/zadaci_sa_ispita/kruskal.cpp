#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void dodajGranu(int u, int v, int t, vector<vector<pair<int, int>>>& ls)
{
    ls[u].push_back({v, t});
    ls[v].push_back({u, t});

}

int findK(int x, vector<int>& ids)
{
    int koren = x;
    while(koren != ids[koren])
    {
        koren = ids[koren];
    }
    while(x != koren)
    {
        int sledeci = ids[x];
        ids[x] = koren;
        x = sledeci;
    }
}

void unionK(int x, int y, vector<int>& vk, vector<int>& ids)
{
    int kx = findK(x, ids);
    int ky = findK(y, ids);

    if(vk[x] < vk[y])
    {
        ids[kx] = ky;
        vk[y] += vk[x];
    }
    else 
    {
        ids[ky] = kx;
        vk[x] += vk[y];
    }
}

void kruskal(vector<vector<pair<int, int>>> &ls, vector<int>& ids, vector<int>& vk)
{
    vector<pair<int, pair<int, int>>> grane;
    for(int cvor = 0; cvor < ls.size(); cvor++)
    {
        for(pair<int, int> sused : ls[cvor])
        {
            grane.push_back({sused.second, {cvor, sused.first}});
        }
        cout << "Trenutni cvor: " << cvor << endl;

    }

    cout << "Prosao ovo ovde sranje" << endl;

    sort(grane.begin(), grane.end());
    int brojGrana = 0;
    int ukupnaTezina = 0;
    for(pair<int, pair<int, int>> grana : grane)
    {
        if(brojGrana == ls.size() - 1) break;
        int tezina = grana.first;
        int u = grana.second.first;
        int v = grana.second.second;

        int korenU = findK(u, ids);
        int korenV = findK(v, ids);

        if(korenU != korenV)
        {
            unionK(u, v, vk, ids);
            brojGrana++;
            ukupnaTezina += tezina; 
        }
    }
    cout << "ukupnaTezina: " << ukupnaTezina << endl;
}
int main()
{
    int brojCvorova, brojGrana;
    cin >> brojCvorova >> brojGrana;
    
    vector<vector<pair<int, int>>> ls(brojCvorova);
    vector<int> vk(brojCvorova, 1);
    vector<int> ids(brojCvorova);
    for(int i = 0; i < brojCvorova; i++)
        ids[i] = i;
    
    for(int i = 0; i < brojGrana; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        dodajGranu(u - 1, v - 1, t, ls);
    }
    kruskal(ls, ids, vk);
    

    // dodajGranu(0, 1, 7, ls);
    // dodajGranu(0, 2, 9, ls);
    // dodajGranu(0, 5, 14, ls);
    // dodajGranu(1, 3, 15, ls);
    // dodajGranu(1, 2, 10, ls);
    // dodajGranu(2, 3, 11, ls);
    // dodajGranu(2, 5, 2, ls);
    // dodajGranu(5, 4, 9, ls);
    // dodajGranu(4, 3, 6, ls);



}