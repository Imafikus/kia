#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Graf
{
    vector<list<int> > lista_povezanosti;
    vector<bool> posecen;

    /**
     * Ucitava graf sa n elemenata
     * 
     * Popunjava lista_povezanosti i posecen
     */
    void ucitaj_graf(int n)
    {
        init(n);

        for(int i = 0; i < n; i++)
        {
            posecen[i] = false;

            int m;
            cout << "Broj suseda cvora " << i << endl;
            cin >> m;

            for(int j = 0; j < m; j++)
            {
                int sused;
                cin >> sused;
                lista_povezanosti[i].push_back(sused);
            }
        }
    }

    void preorder_dfs(int cvor = 0)
    {
        cout << "Dolazna enumeracija: " << cvor << " " << endl;
        
        poseti(cvor);
        
        for(auto it = lista_povezanosti[cvor].begin(); it != lista_povezanosti[cvor].end(); it++)
        {
            if(nije_posecen(cvor))
                preorder_dfs(*it);
        }
    }
    
    void postorder_dfs(int cvor)
    {        
        poseti(cvor);
        
        for(auto it = lista_povezanosti[cvor].begin(); it != lista_povezanosti[cvor].end(); it++)
        {
            if(nije_posecen(*it))
                preorder_dfs(*it);
        }
        cout << "Odlazna enumeracija: " << cvor << " " << endl;
    }

    /**
     * inicijalizuje kontejnere
     * 
     * @param velicina na koju treba da se postave kontejneri
     */
    void init(int n)
    {
        
        for(int i = 0; i < lista_povezanosti.size(); i++)
            lista_povezanosti[i].clear();
        
        lista_povezanosti.clear();
        posecen.clear();

        lista_povezanosti.resize(n);
        posecen.resize(n);
    }

    // oznacava da je odredjeni cvor posecen
    void poseti(int cvor)
    {
        posecen[cvor] = true;
    }

    //proverava da li odredjeni cvor nije posecen
    bool nije_posecen(int cvor)
    {
        return !posecen[cvor]; 
    }
};
int main()
{
    Graf g;
    
    int n;
    cout << "Unesi broj elemenata grafa" << endl;
    cin >> n;

    g.ucitaj_graf(n);
    g.preorder_dfs(0);

    return 0;
}