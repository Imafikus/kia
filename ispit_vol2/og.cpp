#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void dodajGranu(int u, int v, int t, vector<vector<pair<int, int>>>& ls)
{
    ls[u].push_back({v, t});
    ls[v].push_back({u, t});
}

int findK(int x, vector<int>& ids)
{
    int koren = x;
    while (koren != ids[x])
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

void unionK(int x, int y, vector<int>& ids, vector<int>& vk)
{
    int kx = findK(x, ids);
    int ky = findK(y, ids);

    if(kx == ky) return;

    if(vk[x] < vk[y])
    {
        ids[kx] = ky;
        vk[ky] += vk[kx];
    }
    else
    {
        ids[ky] = kx;
        vk[kx] += vk[ky];
    }
}

void kruskal(vector<vector<pair<int, int>>> ls, vector<int>& ids, vector<int>& vk)
{
    vector<pair<int, pair<int, int>>> grane;
    for(int cvor = 0; cvor < ls.size(); cvor++)
    {
        for(pair<int, int> sused : ls[cvor])
        {
            grane.push_back({sused.second, {cvor, sused.first}});
        }
    }

    sort(grane.begin(), grane.end());
    int brojGrana = 0;

    for(auto grana : grane)
    {
        if(brojGrana == ls.size() - 1) break;

        int u = grana.second.first;
        int v = grana.second.second;

        int korenU = findK(u, ids);
        int korenV = findK(v, ids);

        if(korenU != korenV)
        {
            unionK(u, v, ids, vk);
            cout << u << " " << v << endl;
            brojGrana++;
        }
    }
}

int main()
{
    int brojCvorova = 6;
    vector<vector<pair<int, int>>> ls(brojCvorova);
    vector<int> ids(brojCvorova);
    for(int i = 0; i < brojCvorova; i++)
        ids[i] = i;

    vector<int> vk(brojCvorova, 1);

    dodajGranu(0, 1, 7, ls);
    dodajGranu(0, 2, 9, ls);
    dodajGranu(0, 5, 14, ls);
    dodajGranu(1, 3, 15, ls);
    dodajGranu(1, 2, 10, ls);
    dodajGranu(2, 3, 11, ls);
    dodajGranu(2, 5, 2, ls);
    dodajGranu(5, 4, 9, ls);
    dodajGranu(4, 3, 6, ls);

    kruskal(ls, ids, vk);

}