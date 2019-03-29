#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

struct Graf
{
    vector<list<int>> lista;
    vector<bool> poseceni_cvorovi;

    void ucitaj_graf()
    {
        int n;
        cout << "Unesi broj cvorova" << endl;
        cin >> n;

        init(n);

        for (int i = 0; i < n; i++)
        {
            int m;
            cout << "Koliko suseda ima cvor " << i << endl;
            cin >> m;

            cout << "Unesi susede za cvor" << endl;
            poseceni_cvorovi[i] = false;
            for (int j = 0; j < m; j++)
            {
                int e;
                cin >> e;
                lista[i].push_back(e);
            }
            cout << endl;
        }
    }

    void dfs(int cvor)
    {
        cout << "Preorder: " << cvor << endl;

        poseceni_cvorovi[cvor] = true;

        for (auto it = lista[cvor].begin(); it != lista[cvor].end(); it++)
        {
            if (!posecen(*it))
                dfs(*it);
        }
    }

    void bfs(int cvor)
    {
        queue<int> sledeci;
        sledeci.push(cvor);
        poseti(cvor);

        int trenutni;
        int kraj;

        while(sledeci.empty() != true)
        {
            trenutni = sledeci.front();
            sledeci.pop();

            cout << "Poseceni cvor: " << trenutni << endl;

            for(auto it = lista[trenutni].begin(); it != lista[trenutni].end(); it++)
            {
                if(!posecen(*it))
                {
                    poseti(*it);
                    sledeci.push(*it);
                }
            }
        }
    }

    bool posecen(int cvor)
    {
        return poseceni_cvorovi[cvor];
    }

    void poseti(int cvor)
    {
        poseceni_cvorovi[cvor] = true;
    }

    void init(int n)
    {
        for (int i = 0; i < lista.size(); i++)
            lista[i].clear();

        lista.clear();
        poseceni_cvorovi.clear();

        lista.resize(n);
        poseceni_cvorovi.resize(n);
    }
};
int main()
{
    Graf g;

    g.ucitaj_graf();

    cout << "Unesi pocetni cvor za pretragu: ";
    
    int pocetni_cvor;
    cin >> pocetni_cvor;
    
    //g.dfs(pocetni_cvor);
    g.bfs(pocetni_cvor);

    return 0;
}