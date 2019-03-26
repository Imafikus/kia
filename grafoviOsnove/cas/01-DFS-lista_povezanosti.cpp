#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>

using namespace std;

struct Graf
{
    vector<list<int> > lista;
    vector<bool> oznaceni;

    void ucitaj_graf(int n)
    {
        inicijalizacija(n);

        for(int i = 0; i < n; i++)
        {

            oznaceni[i] = false;
            int m;
            cout << "Broj suseda cvora " << i << ": ";
            cin >> m;
            cout << "Susedi cvora " << i << ": ";
            for(int j = 0; j < m; j++)
            {
                int sused;
                cin >> sused;
                lista[i].push_back(sused);
            }
            cout << endl;
        }
    }

    void DFS(int cvor)
    {

         cout << "Dolazna numeracija: " << cvor << " " << endl;
        oznaci(cvor);
        // Za sve neoznacene susede poziva se rekurzivno DFS obilazak
        for(auto it = lista[cvor].begin(); it != lista[cvor].end(); it++)
            if(neoznacen(*it))
                DFS(*it);

      //  cout << "Odlazna numeracija: " << cvor << " " << endl;
    }

    // Inicijalizacija grafa; ciscenje liste i vektora sa oznakama i postavljanje novih velicina
    void inicijalizacija(int n)
    {
        for(int i = 0; i < lista.size(); i++)
            lista[i].clear();

        lista.clear();
        oznaceni.clear();

        lista.resize(n);
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
/*
0-> 1 2
1-> 0 3
2-> 0
3-> 1 4
4-> 3 5 6 7
5-> 4
6-> 4
7-> 4
*/
