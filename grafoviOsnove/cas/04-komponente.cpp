#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Graf
{
    vector<vector<int> > lista;
    vector<bool> oznaceni;
    
    void ucitaj_graf(int n)
    {
        if(n <= 0)
        {
            cerr << "Neispravna dimenzija!";
            exit(EXIT_FAILURE);
        }
        
        inicijalizacija();
        
        lista.resize(n);
        oznaceni.resize(n);
        
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
                
        }
  
        
    }
    
    void DFS(int cvor)
    {
//         if(cvor < 0 || cvor >= oznaceni.size())
//         {
//             cerr << "Neispravan pocetni cvor!";
//             exit(EXIT_FAILURE);
//         }
    
      //  cout << "Dolazna numeracija: " << cvor << " " << endl;        
        
        oznaci(cvor);
        
        for(int j = 0; j < lista[cvor].size(); j++)
            if(neoznacen(lista[cvor][j]))
                DFS(lista[cvor][j]);
            
      //  cout << "Odlazna numeracija: " << cvor << " " << endl;        
    }
    
    void inicijalizacija()
    {
        for(int i = 0; i < lista.size(); i++)
            lista[i].clear();
        
        lista.clear();
        
        oznaceni.clear();
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
    
    int broj_komponenti = 0;
    
    for(int i = 0; i < g.oznaceni.size(); i++)
        if(g.oznaceni[i] == false)
        {
            broj_komponenti++;
            g.DFS(i);
        }
        
    cout << "Broj komponenti: " << broj_komponenti << endl;
    
    return 0;
}