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
    int duzinaNajkracePutanje = INT_MAX;

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

    void svePutanjeIzmedjuDvaCvora(int pocetniCvor, int krajnjiCvor, vector<int> putanja)
    {

        if(pocetniCvor == krajnjiCvor)
        {
            putanja.push_back(krajnjiCvor);
            stampajVektor(putanja);
            return;
        }

        obeleziPosecenCvor(pocetniCvor);
        putanja.push_back(pocetniCvor);

        auto pocetak = listaPovezanosti[pocetniCvor].begin();
        auto kraj = listaPovezanosti[pocetniCvor].end();

        while(pocetak != kraj)
        {
            int sledeciCvor = *pocetak;
            
            if(!jestePosecen(sledeciCvor))
                svePutanjeIzmedjuDvaCvora(sledeciCvor, krajnjiCvor, putanja);
            
            pocetak++;
        }
        poseceniCvorovi[pocetniCvor] = false;
    }

    void najkracaPutanjaIzmedjuDvaCvora(int pocetniCvor, int krajnjiCvor, int putDoSad)
    {

        if(pocetniCvor == krajnjiCvor)
        {
            if(putDoSad < duzinaNajkracePutanje)
                duzinaNajkracePutanje = putDoSad;
            return;
        }

        obeleziPosecenCvor(pocetniCvor);
        putDoSad++;
        
        auto pocetak = listaPovezanosti[pocetniCvor].begin();
        auto kraj = listaPovezanosti[pocetniCvor].end();

        while(pocetak != kraj)
        {
            int sledeciCvor = *pocetak;
            
            if(!jestePosecen(sledeciCvor))
                najkracaPutanjaIzmedjuDvaCvora(sledeciCvor, krajnjiCvor, putDoSad);
            
            pocetak++;
        }
        poseceniCvorovi[pocetniCvor] = false;
    }

    bool imaCikulsNeusmeren(int pocetniCvor, int roditeljPocetnogCvora)
    {

        obeleziPosecenCvor(pocetniCvor);
        
        auto pocetak = listaPovezanosti[pocetniCvor].begin();
        auto kraj = listaPovezanosti[pocetniCvor].end();

        while(pocetak != kraj)
        {
            int sledeciCvor = *pocetak;
            
            if(jestePosecen(sledeciCvor) && sledeciCvor != roditeljPocetnogCvora)
                return true;
            
            else if(imaCikulsNeusmeren(sledeciCvor, pocetniCvor))
                return true;

            pocetak++;
        }
        return false;
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

    void stampajVektor(vector<int> v)
    {
        for(int e : v)
            cout << e << " ";
        cout << endl;
        
    }

};

int main()
{
    cout << "Unesite broj cvorova grafa" << endl;
    
    int brojCvorovaGrafa;
    cin >> brojCvorovaGrafa;

    Graf probniGraf;
    probniGraf.ucitajCvorove(brojCvorovaGrafa);
    

    bool imaCiklus = probniGraf.imaCikulsNeusmeren(0, -1);
    if(imaCiklus)
        cout << "Graf ima ciklus" << endl;
    else
        cout << "Graf nema ciklus" << endl;
}