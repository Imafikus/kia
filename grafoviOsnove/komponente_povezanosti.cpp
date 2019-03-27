#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>


#define NEMA_NEPOSECENIH (INT_MAX)  

using namespace std;

class Graf
{

public:
    int brKompPovezanosti;

    void ucitajCvorove(int brojCvorova)
    {
        init(brojCvorova);

        for(int cvor = 0; cvor < brojCvorova; cvor++)
        {
            cout << "Unesi broj suseda za cvor " << cvor << endl;
            int brojSuseda;
            cin >> brojSuseda;

            cout << "Unesi susede cvora " << cvor << endl;
            for(int j = 0; j < brojSuseda; j++)
            {
                int sused;
                cin >> sused;
                listaPovezanosti[cvor].push_back(sused);
            }
            cout << endl;
        }
    }

    void dfs(int pocetniCvor)
    {
        obeleziPosecenCvor(pocetniCvor);

        cout << "Preorder: " << pocetniCvor << endl;

        auto pocetak = listaPovezanosti[pocetniCvor].begin();
        auto kraj = listaPovezanosti[pocetniCvor].end();

        while(pocetak != kraj)
        {
            int sledeciCvor = *pocetak;
            
            if(!jestePosecen(sledeciCvor))
                dfs(sledeciCvor);
            
            pocetak++;
        }
    }

    void odrediBrojKompPovezanosti()
    {
        int neposeceniCvor;
        while(odaberiNeposecenCvor() != NEMA_NEPOSECENIH)
        {
            neposeceniCvor = odaberiNeposecenCvor();
            dfs(neposeceniCvor);
            brKompPovezanosti++;
        }
    }

    bool jestePosecen(int cvor)
    {
        return poseceniCvorovi[cvor];
    }

    void obeleziPosecenCvor(int cvor)
    {
        poseceniCvorovi[cvor] = true;
    }

    
private:

    vector<vector<int> > listaPovezanosti;
    vector<bool> poseceniCvorovi;
    int brojKomponenataPovezanosti;

    int odaberiNeposecenCvor()
    {
        for(int cvor = 0; cvor < poseceniCvorovi.size(); cvor++)
        {
            if(!jestePosecen(cvor)) return cvor;
        }
        return NEMA_NEPOSECENIH;
    }

    void init(int brojCvorova)
    {
        listaPovezanosti.resize(brojCvorova);
        
        poseceniCvorovi.resize(brojCvorova);
        fill(poseceniCvorovi.begin(), poseceniCvorovi.end(), false);

        brKompPovezanosti = 0;
    }

};

int main()
{
    cout << "Unesite broj cvorova grafa" << endl;
    
    int brojCvorovaGrafa;
    cin >> brojCvorovaGrafa;

    Graf probniGraf;
    probniGraf.ucitajCvorove(brojCvorovaGrafa);
    
    probniGraf.odrediBrojKompPovezanosti();

    cout << "Broj komponenti povezanosti je: " << probniGraf.brKompPovezanosti << endl;

}