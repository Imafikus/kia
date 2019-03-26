/*
 Cvor s usmerenog grafa G = (V,E) sa n cvorova se naziva ponor ako je ulazni stepen cvora s jednak n-1 
 i njegov izlazni stepen jednak 0. 
 Drugim recima, za svaki cvor x iz skupa V razlicit od s postoji grana (x, s) i ne postoji grana (s, x). 
 Precizno opisite algoritam vremenske slozenosti O(n) koji odreduje da li usmereni graf G predstavljen matricom susedstva sadrzi cvor koji je ponor.

*/
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Graf
{
    vector<vector<int> > matrica;
    int broj_cvorova;
    
    void ucitaj_graf(int n)
    {
        if(n <= 0)
        {
            cerr << "Neispravna dimenzija!";
            exit(EXIT_FAILURE);
        }
        
        broj_cvorova = n;
        
        inicijalizacija(n);       
        
        for(int i = 0; i < n; i++)
        {
            matrica[i].resize(n);
            
            for(int j = 0; j < n; j++)
            {
                cin >> matrica[i][j];
                if(matrica[i][j] < 0 || matrica[i][j] > 1)
                {
                    cerr << "Neispravna grana!";
                    exit(EXIT_FAILURE);
                }
            }   
                
        }
    }
    
    int ponor()
    {
       int i = 0;
       int j = 1;
       int next = 1;
       int kandidat;
       
       if(broj_cvorova == 0)
           return -1;
       
       else if(broj_cvorova == 1)
           return 0;
       
       do
       {
           next++;
           
           if(matrica[i][j] == 1)
           {
                i = next;
                kandidat = j;
           }
           else
           {
                j = next;
                kandidat = i;
           }
       } while(next < broj_cvorova);
       
       for(int k = 0; k < broj_cvorova; k++)
       {
            if(matrica[kandidat][k] == 1 || (matrica[k][kandidat] == 0 && k != kandidat))
                return -1;
       }
       
       return kandidat;
    }
    
    
    void inicijalizacija(int n)
    {
        for(int i = 0; i < matrica.size(); i++)
            matrica[i].clear();
        
        matrica.clear();

        matrica.resize(n);
    }
    
    
    
};

int main()
{
    Graf g;
    
    int n;
    
    cin >> n;
    
    g.ucitaj_graf(n);
    
    int v;
    if((v = g.ponor()) == -1)
        cout << "Nema ponora u grafu" << endl;
    else
        cout << "Cvor " << v << " je ponor u grafu" << endl;

    return 0;
}
