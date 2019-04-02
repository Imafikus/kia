#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>

#define INF (INT_MAX)
#define NEG_INF (INT_MIN)

using namespace std;

//? Struktura za poredenje pair<int, int>
struct compare
{
    bool operator()(pair<int, int> &p1, pair<int, int> &p2)
    {
        return p1.second > p2.second;
    }
};


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
        //? roditelje koristi i Dijkstra
        id = 0;
        ids.resize(brojCvorova);
        lowLink.resize(brojCvorova);
        roditeljCvora.resize(brojCvorova, -1);

        //? SLC Tarjan
        uSteku.resize(brojCvorova, false);

        //? Dijkstra
        listaSaTezinama.resize(brojCvorova);
        udaljenost.resize(brojCvorova, INF);
        najmanjeGranaDoCvora.resize(brojCvorova, INF);
        postojiPutDoCvora.resize(brojCvorova, false);
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
    void dfsStack(int cvor)
    {
        jePosecen[cvor] = true;
        
        stack<int> neobradjeni;
        neobradjeni.push(cvor);

        while(!neobradjeni.empty())
        {
            int trenutniCvor = neobradjeni.top();
            cout << trenutniCvor;        
            neobradjeni.pop();

            for(int sused : listaPovezanosti[trenutniCvor])
            {
                if(!jePosecen[sused])
                {
                    neobradjeni.push(sused);
                    jePosecen[sused] = true;
                }
            }
        }
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

        for(int sused : listaPovezanosti[cvor])
        {
            if(sused == roditeljCvora[cvor]) continue;

            if(!jePosecen[sused])
            {
                roditeljCvora[sused] = cvor;
                nadjiMostove(sused);

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
            if(sused == roditeljCvora[cvor]) continue;

            roditeljCvora[sused] = cvor;
            decaCvora++;
            
            if(!jePosecen[sused])
                nadjiArkTacke(sused);
            
            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);

            if(roditeljCvora[cvor] == -1 && decaCvora > 1)
                cout << cvor << " ";
            
            if(roditeljCvora[cvor] != -1 && ids[cvor] <= lowLink[sused])
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

    void dodajGranuSaTezinom(int u, int v, int tezina)
    {
        listaSaTezinama[u].push_back(make_pair(v, tezina));
    }

    void dijkstra(int cvor, int krajnjiCvor)
    {
        priority_queue< pair<int, int>, vector<pair<int, int>>, compare> heap;
        heap.push(make_pair(cvor, 0));
        
        udaljenost[cvor] = 0;
        najmanjeGranaDoCvora[cvor] = 0;

        pair<int, int> trenutniCvor;
        while(!heap.empty())
        {
            trenutniCvor = heap.top();
            heap.pop();

            if(postojiPutDoCvora[trenutniCvor.first])
                continue;
            
            postojiPutDoCvora[trenutniCvor.first] = true;

            for(pair<int, int> sused : listaSaTezinama[trenutniCvor.first])
            {
                //?Gledamo da li je sused manje udaljen ili da li je isto udaljen ali
                //? je potreban manji broj grana da se dodje do njega
                //? U oba slucaja hocemo da radimo update
                
                //? BITNO: Uvek prvo gledamo da li vazi da je udaljenost manja
                //? jer ce to uvek da padne (lenjo poredjenje), ako nije onda nas briga da li postoji
                //? neki drugi put koji nije najblizi a koji ima manje grana
                //? Tek kada znamo da je ovo najblizi put, onda hocemo da se interesujemo za grane

                //? +1 kod poredjenja ide jer kacimo novu granu pa nas interesuje da li ce tad da bude vece
                if(udaljenost[trenutniCvor.first] + sused.second < udaljenost[sused.first] &&
                    najmanjeGranaDoCvora[sused.first] > najmanjeGranaDoCvora[trenutniCvor.first] + 1)
                {
                    najmanjeGranaDoCvora[sused.first] = najmanjeGranaDoCvora[trenutniCvor.first] + 1;
                    
                    udaljenost[sused.first] = udaljenost[trenutniCvor.first] + sused.second;

                    roditeljCvora[sused.first] = trenutniCvor.first;

                    heap.push(make_pair(sused.first, udaljenost[sused.first]));
                }
            }
        }
        stampajNajkraciPut(krajnjiCvor);
    }

    void belmanFord(int pocetniCvor)
    {
        bool negativanCiklus = false;

        udaljenost[pocetniCvor] = 0;
        for(int br = 0; br < brojCvorova-1; br++)
            
            //? trenutniCvor prolazi kroz liste suseda za svaki cvor pojedinacno
            for(int trenutniCvor = 0; trenutniCvor < listaSaTezinama.size(); trenutniCvor++)
            {
                //? j prolazi kroz svakog suseda pojedinacno iz liste suseda
                //? nekog cvora
                for(int j = 0; j < listaSaTezinama[trenutniCvor].size(); j++)
                {
                    int sused = listaSaTezinama[trenutniCvor][j].first;
                    int grana = listaSaTezinama[trenutniCvor][j].second;


                    if(udaljenost[trenutniCvor] + grana < udaljenost[sused])
                    {
                        udaljenost[sused] = udaljenost[trenutniCvor] + grana;
                        roditeljCvora[sused] = trenutniCvor;
                    }
                }
            }

            //? Provere da li graf ima negativan ciklus.
            //? Apsolutno ista procedura, samo ako nadjemo cvor koji
            //? je moguce updateovati izlazimo
            for(int trenutniCvor = 0; trenutniCvor < listaSaTezinama.size(); trenutniCvor++)
            {
                for(int j = 0; j < listaSaTezinama[trenutniCvor].size(); j++)
                {
                    int sused = listaSaTezinama[trenutniCvor][j].first;
                    int grana = listaSaTezinama[trenutniCvor][j].second;

                    if(udaljenost[trenutniCvor] + grana < udaljenost[sused])
                    {
                        cout << "Graf ima negativan ciklus" << endl;
                        negativanCiklus = true;
                        return;
                    }
                }
            }
            cout << "Prosla druga petlja" << endl;
            //? Stampanje najkracih puteva
            if(!negativanCiklus)
            {
                for(int cvor = 0; cvor < brojCvorova; cvor++)
                    stampajNajkraciPut(cvor);
                cout << endl;
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

    //? mostovi i artikulacione tacke (ids i lowLink koristi i Tarjan   )
    //? roditelje koristi Dijkstra, Belman-Ford
    int id;
    vector<int> ids;
    vector<int> lowLink;
    vector<int> roditeljCvora;

    //? komponente jake povezanosti - Tarjan
    vector<bool> uSteku;
    stack<int> slcStack;

    //? Dijkstra, Belman-Ford
    vector<vector<pair<int, int> > > listaSaTezinama;
    vector<int> udaljenost;
    vector<int> najmanjeGranaDoCvora;
    vector<bool> postojiPutDoCvora;

    void stampajNajkraciPut(int krajnjiCvor)
    {
        cout << "stampajNajkraciPut" << endl;
        stack<int> najkraciPut;
        while(roditeljCvora[krajnjiCvor] != -1)
        {
            najkraciPut.push(krajnjiCvor);
            krajnjiCvor = roditeljCvora[krajnjiCvor];
        }
        //? pushujemo i pocetni cvor
        najkraciPut.push(krajnjiCvor);

        cout << "dosao pred while" << endl;
        while(!najkraciPut.empty())
        {
            int cvor = najkraciPut.top();
            najkraciPut.pop();

            //? ako je poslednji cvor koji treba da se stampa
            //? ne zelimo da imamo '->' posle njega
            if(najkraciPut.empty())
                cout << cvor;
            else
                cout << cvor << " -> ";
        }
        cout << endl;
        cout << "Zavrsio sa najkracim putem" << endl;
    }
};

int main()
{
    Graf graf(5);

    graf.dodajGranu(0, 2);
    graf.dodajGranu(0, 1);
    graf.dodajGranu(0, 3);
    graf.dodajGranu(3, 4);
    graf.dodajGranu(2, 1);

    cout << "Prosao grane" << endl;
    
    graf.dfsStack(0);
}