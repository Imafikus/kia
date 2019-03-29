#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>


#define NEPROHODNO (-1)
#define PROHODNO (1)
#define IMA_KROFNU (2)

using namespace std;

void dodajGranu(int v, int u, vector<vector<int>> &listaPovezanosti)
{
    listaPovezanosti[v].push_back(u);
    listaPovezanosti[u].push_back(v);

}

void bfs(vector<vector<int>> listaPovezanosti, int pocetniCvor, vector<int> vrednostiPolja)
{

    int brojKrofni = 0;
    // int maxUdaljenostOdPocetka = 0;

    int maxUdaljenost = -1;

    vector<bool> poseceniCvorovi(listaPovezanosti.size());
    fill(poseceniCvorovi.begin(), poseceniCvorovi.end(), false);

    queue<int> cekajuPosecivanje;
    queue<int> udaljenosti;

    udaljenosti.push(0);
    cekajuPosecivanje.push(pocetniCvor);


    while(!cekajuPosecivanje.empty())
    {
        int upravoPosecen = cekajuPosecivanje.front();
        int udaljenost = udaljenosti.front();
        
        cekajuPosecivanje.pop();
        udaljenosti.pop();
        
        poseceniCvorovi[upravoPosecen] = true;


        if(vrednostiPolja[upravoPosecen] == IMA_KROFNU)
        {
            // ovde
            brojKrofni++;
            
            if (udaljenost > maxUdaljenost)
                maxUdaljenost = udaljenost;
        }
        
        cout << upravoPosecen << " " << udaljenost << endl;
        for(auto sused = listaPovezanosti[upravoPosecen].begin(); sused != listaPovezanosti[upravoPosecen].end(); sused++)
        {
            if(!poseceniCvorovi[*sused] && vrednostiPolja[*sused] != NEPROHODNO)
            {
                
                poseceniCvorovi[*sused] = true;
                
                // maxUdaljenostOdPocetka++;
                udaljenosti.push(udaljenost + 1);
                cekajuPosecivanje.push(*sused);
            }
        }
    }
    cout << endl;

    cout << "Broj nadjenih krofni je: " << brojKrofni << endl;
    cout << "Udaljenost od najdalje krofne je: " << maxUdaljenost << endl;
}

int main()
{   
    int brojCvorova = 8;
    //cin >> brojCvorova;

    vector<vector<int>> lista(brojCvorova);
    vector<int> vrednostiPolja(brojCvorova);

    vrednostiPolja[0] = PROHODNO;
    
    dodajGranu(0, 1, lista);
    vrednostiPolja[1] = PROHODNO;

    dodajGranu(0, 2, lista);
    vrednostiPolja[2] = PROHODNO;

    dodajGranu(0, 3, lista);
    vrednostiPolja[3] = NEPROHODNO;

    dodajGranu(1, 4, lista);
    vrednostiPolja[4] = IMA_KROFNU;

    dodajGranu(2, 5, lista);
    vrednostiPolja[5] = PROHODNO;

    dodajGranu(3, 6, lista);
    vrednostiPolja[6] = IMA_KROFNU;

    dodajGranu(2, 6, lista);
    vrednostiPolja[6] = IMA_KROFNU;

    dodajGranu(6, 7, lista);
    vrednostiPolja[7] = IMA_KROFNU;

    dodajGranu(5, 7, lista);
    vrednostiPolja[7] = IMA_KROFNU;

    bfs(lista, 0, vrednostiPolja);
}