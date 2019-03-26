/*
 Dat je usmereni graf G=(V,E) i cvor v skupa V. 
 Konstruisati algoritam slozenosti O(|E| + |V|) koji ispituje da li G jeste korensko stablo sa korenom v. 
 Smatrati da su u korenskom stablu grane usmerene od korena ka listovima.
*/
#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <queue>

using namespace std;

struct Graf
{
    vector<list<int> > lista;
    vector<bool> oznaceni;
    
    void ucitaj_graf(int n)
    {
        if(n <= 0)
        {
            cerr << "Neispravna dimenzija!";
            exit(EXIT_FAILURE);
        }
        
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
                
                if(sused < 0 || sused >= n)
                {
                    cerr << "Neispravna grana!";
                    exit(EXIT_FAILURE);
                }
                
                lista[i].push_back(sused); 
            }  
            cout << endl;
                
        }
  
        
    }
    
    bool proveri_stablo(int cvor, int &broj)
    {

        oznaci(cvor);
        broj++;        
        
        bool rezultat = true;
        
        for(auto it = lista[cvor].begin(); it != lista[cvor].end(); it++)
            if(neoznacen(*it))
            {
                rezultat = rezultat && proveri_stablo(*it, broj);
            }
            else // Ako cvor ima oznacenog suseda znaci da postoji grana do njega a samim tim i ciklus
            {
                return false;
            }
        
        return rezultat;
       
    }
    
    bool stablo_sa_korenom_v(int v)
    {
        if(v < 0 || v >= oznaceni.size())
         {
             cerr << "Neispravan pocetni cvor!";
             exit(EXIT_FAILURE);
         }
         
         int broj;
        
        if(proveri_stablo(v, broj) == false)
        {
            cout << "Graf ima ciklus!" << endl;
            return false;
        }
        
        else if(broj != oznaceni.size())
        {
            cout << "Graf nije povezan!" << endl;
            return false;
        }
        
        return true;
         
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
    int v;
    
    cin >> n;
    
    g.ucitaj_graf(n);
    
    cout << "Cvor v za proveru: ";
    cin >> v;

    
    if(g.stablo_sa_korenom_v(v))
        cout << "Cvor v jeste koren stabla" << endl;
    else
        cout << "Cvor v nije koren stabla" << endl;

    return 0;
}