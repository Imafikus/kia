#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

class Graf
{

public:
    Graf(int brojCvorova)
    {
        //? Osnovne stvari
        this->brojCvorova = brojCvorova;
        listaPovezanosti.resize(brojCvorova);
        jePosecen.resize(brojCvorova, false);
        ulazniStepen.resize(brojCvorova, 0);

        //? mostovi i artikulacione tacke (ids, lowLink koristi i Tarjan)
        id = 0;
        ids.resize(brojCvorova);
        lowLink.resize(brojCvorova);
        roditelj.resize(brojCvorova, -1);

        //? SLC Tarjan
        uSteku.resize(brojCvorova, false);
    }


    void dfs(int cvor, bool dozvoljenoPisanje = true)
    {
        jePosecen[cvor] = true;
        if(dozvoljenoPisanje)
            cout << cvor << " ";

        
        for(int sused : listaPovezanosti[cvor])
        {
            if(!jePosecen[sused])
                dfs(sused, dozvoljenoPisanje);
        }

        topSortStack.push(cvor);
    }

    void bfs(int cvor)
    {
        queue<int> neobradjeni;
        jePosecen[cvor] = true;
        neobradjeni.push(cvor);

        while(!neobradjeni.empty())
        {
            int trenutniCvor = neobradjeni.front();
            neobradjeni.pop();
            cout << trenutniCvor  << " ";

            for(int sused : listaPovezanosti[trenutniCvor])
                if(!jePosecen[sused])
                {
                    neobradjeni.push(sused);
                    jePosecen[sused] = true;
                }
        }
    }

    void dodajGranu(int u, int v)
    {
        listaPovezanosti[u].push_back(v);
        ulazniStepen[v]++;
    }

    vector<int> topSort()
    {
        queue<int> neobradjeniCvorovi;
        for(int v = 0; v < brojCvorova; v++)
        {
            if(ulazniStepen[v] == 0)
                neobradjeniCvorovi.push(v);
        }

        while(!neobradjeniCvorovi.empty())
        {
            int trenutniCvor = neobradjeniCvorovi.front();
            neobradjeniCvorovi.pop();

            topoloskoUredjenje.push_back(trenutniCvor);

            for(int sused : listaPovezanosti[trenutniCvor])
            {
                ulazniStepen[sused]--;
                if(ulazniStepen[sused] == 0)
                    neobradjeniCvorovi.push(sused);
            }
        }
        return topoloskoUredjenje;
    }

    void dfsTopSort()
    {
        for(int cvor = 0; cvor < brojCvorova; cvor++)
        {
            if(!jePosecen[cvor])
                dfs(cvor, false);
        }

        while(!topSortStack.empty())
        {
            cout << topSortStack.top() << " ";
            topSortStack.pop();
        }
        cout << endl;
    }

    void nadjiMostove(int cvor)
    {
        jePosecen[cvor] = true;

        ids[cvor] = id;
        lowLink[cvor] = id;
        id++;

        int decaCvora = 0;

        for(int sused : listaPovezanosti[cvor])
        {
            if(sused == roditelj[cvor]) continue;

            if(!jePosecen[sused])
            {
                roditelj[sused] = cvor;
                nadjiMostove(sused);
                decaCvora++;

                lowLink[cvor] = min(lowLink[sused], lowLink[cvor]);

                if(ids[cvor] < lowLink[sused])
                    cout << cvor << " -> " << sused << endl;
            }
            else 
                lowLink[cvor] = min(lowLink[sused], lowLink[cvor]);        
        }
    }

    void nadjiArkTacke(int cvor)
    {
        jePosecen[cvor] = true;

        ids[cvor] = id;
        lowLink[cvor] = id;
        id++;

        int decaCvora = 0;

        for(int sused : listaPovezanosti[cvor])
        {
            if(sused == roditelj[cvor]) continue;

            roditelj[sused] = cvor;
            decaCvora++;
            if(!jePosecen[sused])
                nadjiArkTacke(sused);
            
            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);

            if(roditelj[cvor] == -1 && decaCvora > 1)
                cout << cvor << " ";
            
            if(roditelj[cvor] != -1 && ids[cvor] <= lowLink[sused])
                cout << cvor << " ";
        else
            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);
        }
        cout << endl;
    }

    void slcTarjan(int cvor)
    {
        slcStack.push(cvor);
        uSteku[cvor] = true;

        ids[cvor] = id;
        lowLink[cvor] = id;
        id++;

        jePosecen[cvor] = true;

        for(int sused : listaPovezanosti[cvor])
        {
            if(!jePosecen[sused]) 
                slcTarjan(sused);
        
            if(uSteku[sused]) 
                lowLink[cvor] = min(lowLink[sused], lowLink[cvor]);
            
        }
        
        if(ids[cvor] == lowLink[cvor])
        {
            while(true)
            {
                int cvorKomponente = slcStack.top();
                cout << cvorKomponente << " ";
                
                slcStack.pop();
                uSteku[cvorKomponente] = false;

                lowLink[cvorKomponente] = ids[cvor];

                if(cvorKomponente == cvor)
                {
                    cout << endl;
                    break;
                }
            } 
        }
    }

private:
    //? Osnovne inicijalizacije
    int brojCvorova;
    vector<vector<int>> listaPovezanosti;
    vector<bool> jePosecen;
    vector<int> ulazniStepen;

    //? dfs topSort
    stack<int> topSortStack;

    //? topSort - Kahn
    vector<int> topoloskoUredjenje;


    //? mostovi i artikulacione tacke (ids i lowLink koristi i Tarjan)
    int id;
    vector<int> ids;
    vector<int> lowLink;
    vector<int> roditelj;

    //? komponente jake povezanosti - Tarjan
    vector<bool> uSteku;
    stack<int> slcStack;
};

int main()
{
    Graf graf(9);

    // graf.dodajGranu(0, 1);
    // graf.dodajGranu(2, 0);
    // graf.dodajGranu(3, 4);
    // graf.dodajGranu(1, 4);
    // graf.dodajGranu(5, 4);
    // graf.dodajGranu(2, 4);
    // graf.dodajGranu(5, 2);

    graf.dodajGranu(0, 1);
    graf.dodajGranu(1, 3);
    graf.dodajGranu(1, 4);
    graf.dodajGranu(4, 6);
    graf.dodajGranu(6, 1);
    graf.dodajGranu(0, 7);
    graf.dodajGranu(0, 2);
    graf.dodajGranu(2, 5);
    graf.dodajGranu(5, 8);
    graf.dodajGranu(8, 0);


    graf.slcTarjan(0);
    
    
}