#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Graf
{
    vector<vector<int> >matrica;
    vector<bool> poseceni_cvorovi;


    void ucitaj_graf()
    {
        int n;
        cout << "Unesi broj elemenata grafa" << endl;
        cin >> n;

        init(n);

        for(int i = 0; i < n; i++)
        {
            cout << "Unesi broj suseda cvora " << i << endl;
            int m;
            cin >> m;

            cout << "Unesi susede" << endl;
            for(int j = 0; j < m; j++)
            {
                int sused;
                cin >> sused;
                matrica[i][sused] = 1;
            }
            cout << endl;
        }
    }

    void dfs(int cvor)
    {   
        poseceni_cvorovi[cvor] = true;
        cout << "Preorder " << cvor << endl;
        for(int i = 0; i < matrica.size(); i++)
            if(matrica[cvor][i] && !posecen(i))
                dfs(i);
    }

    void stampaj_matricu()
    {
        for(int i = 0; i < matrica.size(); i++)
        {
            for(int j = 0; j < matrica.size(); j++)
            {
                cout << matrica[i][j] << " ";
            } 
            cout << endl;
        }
    }

    bool posecen(int cvor)
    {
        return poseceni_cvorovi[cvor];
    }

    void poseti_cvor(int cvor)
    {
        poseceni_cvorovi[cvor] = true;
    }

    void init(int n)
    {
        matrica.resize(n);
        for(int i = 0; i < n; i++)
            matrica[i].resize(n);

        poseceni_cvorovi.resize(n);
        fill(poseceni_cvorovi.begin(), poseceni_cvorovi.end(), false);
    }
};

int main()
{
    Graf g;

    g.ucitaj_graf();
    g.stampaj_matricu();
    
    g.dfs(0);
}