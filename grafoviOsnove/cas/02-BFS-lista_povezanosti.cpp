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
    
    void DFS(int cvor)
    {

         if(cvor < 0 || cvor >= oznaceni.size())
         {
             cerr << "Neispravan pocetni cvor!";
             exit(EXIT_FAILURE);
         }
    
        cout << "Dolazna numeracija: " << cvor << " " << endl;        
        
        oznaci(cvor);
        
        // Za sve neoznacene susede poziva se rekurzivno DFS obilazak
        for(auto it = lista[cvor].begin(); it != lista[cvor].end(); it++)
            if(neoznacen(*it))
                DFS(*it);
            
       // cout << "Odlazna numeracija: " << cvor << " " << endl;        
    }
    
    void BFS(int cvor)
    {
        if(cvor < 0 || cvor >= oznaceni.size())
         {
             cerr << "Neispravan pocetni cvor!";
             exit(EXIT_FAILURE);
         }
         
         queue<int> red;
        red.push(cvor);
        oznaci(cvor);
        
        int kraj = cvor; // Opciono, ako hocemo ispis po nivoima, ne koristi se uvek
        int trenutni;
        
        while(red.empty() != true)
        {
            trenutni = red.front();
            red.pop();
            
            cout << trenutni << " "; // Obrada cvora, u ovom slucaju ispis
            
            for(auto it = lista[trenutni].begin(); it != lista[trenutni].end(); it++)
            {
                if(neoznacen(*it))
                {
                    oznaci(*it);
                    red.push(*it);
                }
            }
        }
        
        if(kraj == trenutni) // Opciono, ako hocemo ispis po nivoima, ne koristi se uvek
        {
            cout << endl;
            kraj = red.back();
        }
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
    
    g.BFS(0);

    return 0;
}