#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Graf
{
    vector<vector<int> > matrica;
    vector<bool> oznaceni;

    void ucitaj_graf(int n)
    {

        inicijalizacija(n);
        for(int i = 0; i < n; i++)
        {
            matrica[i].resize(n);
            oznaceni[i] = false;
            for(int j = 0; j < n; j++)
                cin >> matrica[i][j];

        }
    }

    void DFS(int cvor)
    {
         if(cvor < 0 || cvor >= oznaceni.size())
         {
             cerr << "Neispravan pocetni cvor!";
             exit(EXIT_FAILURE);
         }

        cout << "Dolazna numeracija: " << cvor << " " << endl;
        oznaci(cvor);

        // Rekurzivno pozivanje DFS za sve neoznacene susede cvora
        for(int j = 0; j < matrica[cvor].size(); j++)
            if(postoji_grana(cvor, j) && neoznacen(j))
                DFS(j);
       // cout << "Odlazna numeracija: " << cvor << " " << endl;
    }

    void inicijalizacija(int n)
    {
        for(int i = 0; i < matrica.size(); i++)
            matrica[i].clear();

        matrica.clear();
        oznaceni.clear();

	    matrica.resize(n);
        oznaceni.resize(n);
    }

    void oznaci(int cvor)
    {
        oznaceni[cvor] = true;
    }

    bool neoznacen(int cvor)
    {
        return !oznaceni[cvor];
    }

    bool postoji_grana(int i, int j)
    {
        return matrica[i][j];
    }

};

int main()
{
    Graf g;
    int n;
    cin >> n;
    g.ucitaj_graf(n);
    g.DFS(0);
    return 0;
}
