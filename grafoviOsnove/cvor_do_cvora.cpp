#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graf
{
public:

    Graf(int br_cvorova)
    {
        this->br_cvorova = br_cvorova;
        
        poseceni_cvorovi.resize(br_cvorova);
        fill(poseceni_cvorovi.begin(), poseceni_cvorovi.end(), false);

        lista.resize(br_cvorova);
        
        nadjen_cvor = false;
    }

    void dodaj_granu(int u, int v)
    {
        lista[u].push_back(v);
        //lista[v].push_back(u); //ako pravimo neusmeren graf ide ovako
    }

    void dfs(int u, int v, vector<int> &putanja)
    {
        // ako smo dosetali do trazenog cvora
        if(u == v)
        {
            putanja.push_back(v);
            nadjen_cvor = true;
            return;
        }

        poseceni_cvorovi[u] = true;
        putanja.push_back(u);

        for(auto it = lista[u].begin(); it != lista[u].end(); it++)
        {
            if(!poseceni_cvorovi[*it] && !nadjen_cvor)
                dfs(*it, v, putanja);
        }
    }

        bool get_nadjen_cvor()
        {
            return nadjen_cvor;
        }

private:
    vector<vector<int>> lista;
    vector<bool> poseceni_cvorovi;
    
    int br_cvorova;
    bool nadjen_cvor; 
};

int main()
{
    Graf g(5);

    g.dodaj_granu(0, 1);
    g.dodaj_granu(0, 2);
    g.dodaj_granu(1, 3);
    g.dodaj_granu(2, 4);
    
    int u, v;
    cout << "Unesite cvorove do kojih zelite da nadjete put" << endl;
    cin >> u >> v;

    vector<int> putanja;
    g.dfs(u, v, putanja);

    if(!g.get_nadjen_cvor())
        cout << "Nema puta" << endl;
    
    else
    {
        for(int i = 0; i < putanja.size(); i++)
            cout << putanja[i] << " ";
        cout << endl;
    }
    

    
    return 0;
}