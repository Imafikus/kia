#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>

#define INF (100000)
#define NEG_INF (-100000)

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
        postojiPutDoCvora.resize(brojCvorova, false);
    
    
        //? union-find
        velicinaKomponente.resize(brojCvorova, 1);
        kruskalIds.reserve(brojCvorova);
        for(int i = 0; i < brojCvorova; i++)
            kruskalIds[i] = i;

        //? flojd-varsal
        fwMatrica.resize(brojCvorova);
        for(int i = 0; i < brojCvorova; i++)
            fwMatrica[i].resize(brojCvorova);
        
        for(int i = 0; i < brojCvorova; i++)
            for(int j = 0; j < brojCvorova; j++)
            {
                if(i == j)
                    fwMatrica[i][j] = 0;
                else 
                    fwMatrica[i][j] = INF;
            }

        //? tranzitivno zatvorenje, tranzitivna redukcija
        tztrMatrica.resize(brojCvorova);
        for(int i = 0; i < brojCvorova; i++)
            tztrMatrica[i].resize(brojCvorova);
        
        for(int i = 0; i < brojCvorova; i++)
            for(int j = 0; j < brojCvorova; j++)
            {
                if(i == j)
                    tztrMatrica[i][j] = true;
                else 
                    tztrMatrica[i][j] = false;
            }
        
        rezidualniGraf.resize(brojCvorova);
        for(int i = 0; i < brojCvorova; i++)
            rezidualniGraf[i].resize(brojCvorova);

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

    void dodajGranuUsmeren(int u, int v)
    {
        listaPovezanosti[u].push_back(v);
        ulazniStepen[v]++;
    }

    void dodajGranuNeusmeren(int u, int v)
    {
        listaPovezanosti[u].push_back(v);
        listaPovezanosti[v].push_back(u);
        ulazniStepen[u]++;
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

    //! Moze da vrati isti element vise puta, koristiti set
    void nadjiArtTacke(int cvor)
    {
        jePosecen[cvor] = true;

        ids[cvor] = id;
        lowLink[cvor] = id;
        id++;

        int decaCvora = 0;

        for(int sused : listaPovezanosti[cvor])
        {
            if(!jePosecen[sused])
            {
                roditeljCvora[sused] = cvor;
                decaCvora++;
                
                nadjiArtTacke(sused);
            
                lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);

                //? pocetni cvor
                if(roditeljCvora[cvor] == -1 && decaCvora > 1)
                    cout << cvor << " ";
            
                //? Ili je most ili je ciklus
                if(roditeljCvora[cvor] != -1 && ids[cvor] <= lowLink[sused])
                    cout << cvor << " ";
            }
            else if(roditeljCvora[cvor] != sused)
            {
                lowLink[cvor] = min(lowLink[cvor], ids[sused]);
            }
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

    void fwDodajGranu(int u, int v, int tezina)
    {
        fwMatrica[u][v] = tezina;
    }
    void dodajGranuSaTezinom(int u, int v, int tezina)
    {
        listaSaTezinama[u].push_back(make_pair(v, tezina));
        listaSaTezinama[v].push_back(make_pair(u, tezina));

    }

    void dijkstra(int cvor, int krajnjiCvor)
    {
        priority_queue< pair<int, int>, vector<pair<int, int>>, compare> heap;
        heap.push(make_pair(cvor, 0));
        
        udaljenost[cvor] = 0;

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
                
                //? Gledamo da li je udaljenost od trenutnog cvora + udaljenost do suseda
                //? bolja nego predjasnja udaljenost od suseda, ako jeste, update-ujemo informacije
                if(udaljenost[trenutniCvor.first] + sused.second <= udaljenost[sused.first])
                {                    
                    udaljenost[sused.first] = udaljenost[trenutniCvor.first] + sused.second;

                    roditeljCvora[sused.first] = trenutniCvor.first;

                    heap.push(make_pair(sused.first, udaljenost[sused.first]));
                }
            }
        }
        stampajNajkraciPut(krajnjiCvor);
    }

    void prim()
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > heap;

        //?Stavljamo prvi cvor na heap i stavljamo da je rastojanje
        //? do njega 0
        //? BITNO: kako svakako moramo da prodjemo kroz sve cvorove,
        //? nebitno je koji uzmemo, tako da ne mora prvi(nulti)

        udaljenost[0] = 0;
        heap.push(make_pair(0, udaljenost[0]));

        //? Postavljamo udaljenosti od svih ostalih cvorova na INF
        for(int cvor = 1; cvor < brojCvorova; cvor++)
            heap.push(make_pair(cvor, INF));

        for(int i = 0; i < brojCvorova; i++)
        {
            pair<int, int> najbliziCvor = heap.top();
            heap.pop();

            int cvor = najbliziCvor.first;
            int duzinaPuta = najbliziCvor.second;

            //?rastojanje do ovog cvora ce biti tezina grane koja spaja taj i trenutni cvor
            if(!jePosecen[cvor])
            {
                jePosecen[cvor] = true;

                for(pair<int, int> sused: listaSaTezinama[cvor])
                {
                    if(!jePosecen[sused.first])
                    {
                        //? proveravamo da li se preko trenutnog cvora moze doci brze nego pre
                        //? tj. da li je nova grana kraca od prethodne najbolje, ako jeste
                        //? onda update-ujemo vrednost
                        if(sused.second < udaljenost[sused.first])
                        {
                            udaljenost[sused.first] = sused.second;
                            
                            roditeljCvora[sused.first] = cvor;
                            
                            heap.push(make_pair(sused.first, udaljenost[sused.first]));
                        }
                    }
                }
            }
            else 
                i--;
        }
        for(int cvor = 1; cvor < brojCvorova; cvor++)
        {
            cout << roditeljCvora[cvor] << " " << cvor << " tezina: "<< udaljenost[cvor] << endl;
        }
    }

    void kruskal()
    {
        vector<pair<int, pair<int, int>> >grane;
        for(int cvor = 0; cvor < brojCvorova; cvor++)
        {
            for(pair<int, int>sused : listaSaTezinama[cvor])
            {
                int tezinaGrane = sused.second;
                grane.push_back( {tezinaGrane, make_pair(cvor, sused.first)} );
            }
        }

        sort(grane.begin(), grane.end());
        int brojGrana = 0;

        for(pair<int, pair<int, int> > grana : grane)
        {
            if(brojGrana == brojCvorova-1) break;
            
            int tezinaGrane = grana.first;
            int u = grana.second.first;
            int v = grana.second.second;

            int skupU = findKruskal(u);
            int skupV = findKruskal(v);

            //? ako nam cvorovi ne pripadaju istom skupu, jer ne zelimo ciklus
            if(skupU != skupV)
            {
                cout << u << " " << v << " - tezina grane: " << tezinaGrane << endl;
                unionKruskal(u, v);
                brojGrana++;
            }
        }
    }

    void belmanFord()
    {

        udaljenost[0] = 0;

        for(int v = 0; v < brojCvorova; v++)
        {
            for(int trenutniCvor = 0; trenutniCvor < brojCvorova; trenutniCvor++)
            {
                for(int j = 0; j < listaSaTezinama[j].size(); j++)
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
        }

        for(int trenutniCvor = 0; trenutniCvor < brojCvorova; trenutniCvor++)
            {
                for(int j = 0; j < listaSaTezinama[j].size(); j++)
                {
                    int sused = listaSaTezinama[trenutniCvor][j].first;
                    int grana = listaSaTezinama[trenutniCvor][j].second;

                    if(udaljenost[trenutniCvor] + grana < udaljenost[sused])
                    {
                        cout << "NEGATIVAN CIKLUS" << endl;
                        return;
                    }
                }
            }
        for(int cvor = 1; cvor < brojCvorova; cvor++)
            stampajNajkraciPut(cvor);
    }

    void flojdVarsal()
    {
        for(int k = 0; k < brojCvorova; k++)
        {
            for(int i = 0; i < brojCvorova; i++)
            {
                for(int j = 0; j < brojCvorova; j++)
                {
                    if(fwMatrica[i][j] > fwMatrica[i][k] + fwMatrica[k][j])
                        fwMatrica[i][j] = fwMatrica[i][k] + fwMatrica[k][j];
                }
            }
        }

        for(int i = 0; i < brojCvorova; i++)
        {
            if(fwMatrica[i][i] < 0)
            {
                cout << "NEGATIVAN CIKLUS" << endl;
                return;
            }
        }
    }

    void nadjiTranzitivnoZatvorenje() 
    {
        //? Sigurno postoje putevi izmedju cvorova izmedju kojih je
        //? direktna grana
        for(int cvor = 0; cvor < brojCvorova; cvor++)
        {
            for(int sused : listaPovezanosti[cvor])
            {
                tztrMatrica[cvor][sused] = true;
            }
        }

        //? Gledamo da li postoji put od i do j preko nekog cvora m
        for(int m = 0; m < brojCvorova; m++)
        {
            for(int i = 0; i < brojCvorova; i++)
            {
                for(int j = 0; j < brojCvorova; j++)
                {
                    if(tztrMatrica[i][m] && tztrMatrica[m][j])
                        tztrMatrica[i][j] = true;
                }
            }
        }

        cout << "Tranzitivno zatvorenje:" << endl;
        for(int i = 0; i < brojCvorova; i++) 
        {
            for(int j = 0; j < brojCvorova; j++)
            {
                cout << tztrMatrica[i][j] << " ";
            }
            cout << endl;
        }
    }

    //! NE RADI BEZ TRANZITIVNOG ZATVORENJA
    void nadjiTranzitivnuRedukciju()
    {

        //? Moramo da ubijemo rastojanja cvora od samog sebe jer
        //? ne znamo da li mozemo da dodjemo do tog cvora ili ne
        for(int i = 0; i < brojCvorova; i++)
        {
            for(int j = 0; j < brojCvorova; j++)
            {
                tztrMatrica[i][j] = false;
            }
        }

        //? Sigurno postoje putevi izmedju cvorova koji su susedi
        for(int cvor = 0; cvor < brojCvorova; cvor++)
        {
            for(int sused: listaPovezanosti[cvor])
            {
                tztrMatrica[cvor][sused] = true;
            }
        }

        for(int m = 0; m < brojCvorova; m++)
        {
            for(int i = 0; i < brojCvorova; i++)
            {
                if(tztrMatrica[i][m] == true)
                {
                    for(int j = 0; j < brojCvorova; j++)
                    {
                        //? Ako postoji put izmedju cvorova (i, m) i cvorova (m, j) onda nam ne
                        //? treba put izmedju (i, j)

                        if(tztrMatrica[m][j] == true)
                            tztrMatrica[i][j] = false;
                    }
                }
            }
        }

        cout << "Tranzitivna redukcija:" << endl;
        for(int i = 0; i < brojCvorova; i++) 
        {
            for(int j = 0; j < brojCvorova; j++)
            {
                cout << tztrMatrica[i][j] << " ";
            }
            cout << endl;
        }
    }

    void nadjiOjlerovCiklusHircholer()
    {
        stack<int> tekuciPut;
        vector<int> ojlerovCiklus;

        int tekuciCvor = 0;
        tekuciPut.push(tekuciCvor);

        while(!tekuciPut.empty())
        {
            //? ako i dalje postoji neka grana iz trekuceg cvora ulecemo u nju
            //? BITNO: moze se desiti da iz jedne grane nadjemo vise ciklusa (kao primer u skripti)
            //? iz grane izlazimo tek kad smo obisli sve njene susede
            
            if(listaPovezanosti[tekuciCvor].size())
            {
                tekuciPut.push(tekuciCvor);

                //? dodajemo narednu granu i cvor od kog ce se nastaviti ciklus
                //? tu granu sklanjamo iz liste povezanosti kako je ne bismo ponovo racunali negde
                int naredniCvor = listaPovezanosti[tekuciCvor].back();
                obrisiNeusmerenuGranu(tekuciCvor, naredniCvor);
                tekuciCvor = naredniCvor;
            }
            else 
            {
                //? vracamo se nazad kroz grane da bismo nasli cvorove kod kojih postoje neposeceni
                //? susedi. Kako smo sklanjali sve grane kojima smo prosli, ovako cemo sigurno naleteti na neki ciklus ponovo

                ojlerovCiklus.push_back(tekuciCvor);
                
                tekuciCvor = tekuciPut.top();
                tekuciPut.pop();
            }
        }

        cout << "Ojlerov ciklus" << endl;
        cout << "Ojlerov ciklus velicina: " << ojlerovCiklus.size() << endl;

        for(int cvor : ojlerovCiklus)
        {
            cout << cvor << " ";
        }
        cout << endl;
    }

    void nadjiOjlerovCiklusFleri()
    {
        stack<int> tekuciPut;
        vector<int> ojlerovCiklus;

        int tekuciCvor = 0;
        tekuciPut.push(tekuciCvor);

        while(!tekuciPut.empty())
        {
            tekuciCvor = tekuciPut.top();

            if(listaPovezanosti[tekuciCvor].size())
            {
                int naredniCvor = listaPovezanosti[tekuciCvor].back();
                tekuciPut.push(naredniCvor);
                listaPovezanosti[tekuciCvor].pop_back();
            }
            else
            {
                ojlerovCiklus.push_back(tekuciCvor);
                tekuciPut.pop();
            }
        }

        cout << "Ojlerov ciklus" << endl;
        cout << "Ojlerov ciklus velicina: " << ojlerovCiklus.size() << endl;

        for(int cvor : ojlerovCiklus)
        {
            cout << cvor << " ";
        }
        cout << endl;
    }
    bool edmondKarpBfs(int izvor, int ponor)
    {
        queue<int> red;
        red.push(izvor);

        while(!red.empty())
        {
            cout << "usao u while" << endl;
            int cvor = red.front();
            red.pop();

            for(pair<int, int> sused : listaSaTezinama[cvor])
            {
                if(!jePosecen[sused.first] && rezidualniGraf[cvor][sused.first] > 0)
                {
                    red.push(sused.first);
                    roditeljCvora[sused.first] = cvor;
                    jePosecen[sused.first] = true;
                }
            }
        }
        return(jePosecen[ponor] == true);
    }
    void testiranje(int izvor, int ponor)
    {
        queue<int> red;
        red.push(izvor);

        while(!red.empty())
        {
            cout << "usao u while" << endl;
            int cvor = red.front();
            red.pop();

            for(pair<int, int> sused : listaSaTezinama[cvor])
            {
                if(!jePosecen[sused.first])
                {
                    red.push(sused.first);
                    roditeljCvora[sused.first] = cvor;
                    jePosecen[sused.first] = true;
                }
            }
        }
        if(jePosecen[ponor])
            cout << "POSECEN" << endl;
        else
            cout << "NEPOSECEN" << endl;

        return;
        for(int cvor = ponor; cvor != izvor; cvor = roditeljCvora[cvor])
            cout << cvor << " ";
        cout << izvor;
        cout << endl;
    }
    void edmondKarp(int izvor, int ponor)
    {
        //? izjednacavamo rezidualni graf i matricu susedstva pravog grafa
        for(int cvor = 0; cvor < brojCvorova; cvor++)
        {
            for(pair<int, int> sused : listaSaTezinama[cvor])
            {
                rezidualniGraf[cvor][sused.first] = sused.second;
            }
        }

        cout << "Polazni rezidualni graf je: " << endl;
        for(int i=0; i<brojCvorova; i++)
        {
            for(int j=0; j<brojCvorova; j++)
                cout << rezidualniGraf[i][j] << " ";
            cout << endl;
        }

        int maxTok = 0;
        bool postojiPut = true;
        while(postojiPut)
        {
            postojiPut = edmondKarpBfs(izvor, ponor);
            cout << "Usao u while" << endl;

            //? Trazimo bottleneck
            int tok = numeric_limits<int>::max();
            for(int cvor = ponor; cvor != izvor; cvor = roditeljCvora[cvor])
            {
                int u = roditeljCvora[cvor];
                if(rezidualniGraf[u][cvor] < tok)
                {
                    tok = rezidualniGraf[u][cvor];
                }
            }

            //? azuriramo kapacitete rezidualnog grafa
            for(int cvor = ponor; cvor != izvor; cvor = roditeljCvora[cvor])
            {
                int u = roditeljCvora[cvor];
                rezidualniGraf[u][cvor] -= tok;
                rezidualniGraf[cvor][u] += tok;
            }

            cout << "Rezidualni graf sada: " << endl;
            for(int i=0; i<brojCvorova; i++)
            {
                for(int j=0; j<brojCvorova; j++)
                    cout << rezidualniGraf[i][j] << " ";
                cout << endl;
            }

            maxTok += tok;
        }

        cout << "Optimalni tok ima vrednost: " << maxTok << endl;
    }   

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
    //? ids koristi union-find
    int id;
    vector<int> ids;
    vector<int> lowLink;
    vector<int> roditeljCvora;

    //? komponente jake povezanosti - Tarjan
    vector<bool> uSteku;
    stack<int> slcStack;

    //? Dijkstra, Prim, Belman-Ford, Edmond-Karp
    vector<vector<pair<int, int>> > listaSaTezinama;
    vector<int> udaljenost;
    vector<bool> postojiPutDoCvora;

    //? Union-Find - za Kruskala
    vector<int> velicinaKomponente;
    vector<int> kruskalIds;

    //?Flojd Varsal
    vector<vector<int>> fwMatrica;

    //? Edmond-Karp
    vector<vector<int>> rezidualniGraf;

    //? Tranzitivno zatvorenje, tranzitivna redukcija
    vector<vector<bool>> tztrMatrica;

    void stampajNajkraciPut(int krajnjiCvor)
    {
        stack<int> najkraciPut;

        while(roditeljCvora[krajnjiCvor] != -1)
        {
            najkraciPut.push(krajnjiCvor);
            krajnjiCvor = roditeljCvora[krajnjiCvor];
        }
        //? pushujemo i pocetni cvor
        najkraciPut.push(krajnjiCvor);

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
    }

    int findKruskal(int x)
    {
        //? Nalazimo ko je koren od x
        int koren = x;
        while(koren != kruskalIds[x])
            koren = kruskalIds[koren];

        //? radimo kompresiju puta od x do korena
        while(x != koren)
        {
            int sledeci = kruskalIds[x];
            kruskalIds[x] = koren;
            x = sledeci;
        }
        return koren;
    }
    void unionKruskal(int x, int y)
    {
        int koren1 = findKruskal(x);
        int koren2 = findKruskal(y);

        //? ako su vec u istoj komponenti ne zelimo nista da radimo
        if(koren1 == koren2) return;

        if(velicinaKomponente[koren1] < velicinaKomponente[koren2])
        {
            velicinaKomponente[koren2] += velicinaKomponente[koren1];
            kruskalIds[koren1] = koren2;
        }
        else
        {
            velicinaKomponente[koren1] += velicinaKomponente[koren2];
            kruskalIds[koren2] = koren1;
        }
    }

    void obrisiUsmerenuGranu(int u, int v) 
    {       
        auto it = find(listaPovezanosti[u].begin(), listaPovezanosti[u].end(), v);
        listaPovezanosti[u].erase(it);
    }

    void obrisiNeusmerenuGranu(int u, int v)
    {
        obrisiUsmerenuGranu(u, v);
        obrisiUsmerenuGranu(v, u);
    }

};

int main()
{
    Graf g(7);

    g.dodajGranuNeusmeren(0, 1);
    g.dodajGranuNeusmeren(0, 3);
    g.dodajGranuNeusmeren(0, 4);

    g.dodajGranuNeusmeren(2, 1);
    
    g.dodajGranuNeusmeren(6, 3);

    g.dodajGranuNeusmeren(4, 5);

    g.nadjiArtTacke(0);

    // g.dodajGranuSaTezinom(0, 1, 5);
    // g.dodajGranuSaTezinom(0, 2, 7);
    // g.dodajGranuSaTezinom(0, 3, 6);

    // g.dodajGranuSaTezinom(1, 4, 4);
    // g.dodajGranuSaTezinom(1, 5, 3);

    // g.dodajGranuSaTezinom(2, 5, 4);
    // g.dodajGranuSaTezinom(2, 6, 1);

    // g.dodajGranuSaTezinom(3, 6, 5);

    // g.dodajGranuSaTezinom(4, 7, 3);

    // g.dodajGranuSaTezinom(5, 7, 7);

    // g.dodajGranuSaTezinom(6, 5, 4);
    // g.dodajGranuSaTezinom(6, 7, 6);

    // g.edmondKarp(0, 7);

}