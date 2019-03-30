#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graf
{
public:
    Graf(int brojCvorova)
    {
        listaPovezanosti.resize(brojCvorova);
        
        poseceniCvorovi.resize(brojCvorova, false);

        vremePosecivanja.resize(brojCvorova, -1);

        vreme = 0;

        roditeljCvora.resize(brojCvorova, -1);

        najranijePosecenSused.resize(brojCvorova, -1);
    }

    void dodajGranu(int u, int v, bool usmeren = false)
    {
        listaPovezanosti[u].push_back(v);
        if(!usmeren)
            listaPovezanosti[v].push_back(u);
    }

    void dfs(int pocetniCvor)
    {
        posetiCvor(pocetniCvor);
        cout << pocetniCvor << " ";
        for(int sused : listaPovezanosti[pocetniCvor])
        {
            if(!vecPosecen(sused))
                dfs(sused);
        }
    }

    void nadjiArtikTacke(int pocetniCvor)
    {
        posetiCvor(pocetniCvor);

        vremePosecivanja[pocetniCvor] = vreme;
        najranijePosecenSused[pocetniCvor] = vreme;

        vreme++;

        int decaTrenutnogCvora = 0;

        auto begin = listaPovezanosti[pocetniCvor].begin();
        auto end = listaPovezanosti[pocetniCvor].end();

        while(begin != end)
        {
            if(!vecPosecen(*begin))
            {
                roditeljCvora[*begin] = pocetniCvor;
                nadjiArtikTacke(*begin);

                decaTrenutnogCvora++;

                if(najranijePosecenSused[*begin] < najranijePosecenSused[pocetniCvor])
                    najranijePosecenSused[pocetniCvor] = najranijePosecenSused[*begin];

                //? Proveri da li je koreni cvor, i ako jeste, da li je artik tacka
                if(roditeljCvora[pocetniCvor] == -1 && decaTrenutnogCvora > 1)
                    artikTacke.push_back(pocetniCvor);
                
                //? ovo se desava kada cvor nije koren, gledamo pocetni cvor i njegove susede, ne postoji sused takav
                //? da on za svog suseda ima neki cvor koji se pojavio pre pocetnog, onda ce pocetni cvor biti artikulaciona tacka
                if(roditeljCvora[pocetniCvor] != -1 && vremePosecivanja[pocetniCvor] <= najranijePosecenSused[*begin])
                    artikTacke.push_back(pocetniCvor);
                
            }
            //? proveravamo da li sused trenutnog cvora ima mozda neki cvor
            //? koji je ranije posecen a do kog moze da dodje, ako ima, to znaci
            //? i da nas trenutni cvor moze da dodje do njega pa radimo update
            else if(*begin != roditeljCvora[pocetniCvor])
            {
                if(najranijePosecenSused[pocetniCvor] >= najranijePosecenSused[*begin])
                    najranijePosecenSused[pocetniCvor] = najranijePosecenSused[*begin];
            }

            begin++;
        }
    }

    void ispisiArtikTacke()
    {
        int size = artikTacke.size();
        if(size == 0) cout << "Nema artikulacionih tacaka" << endl;
        
        for(int i : artikTacke)
        {
            cout << i << endl;
        }
    }

private:
    vector<vector<int>> listaPovezanosti;
    
    vector<bool> poseceniCvorovi;
    
    vector<int> vremePosecivanja;
    
    int vreme;
    
    vector<int> roditeljCvora;

    vector<int> artikTacke;

    vector<int> najranijePosecenSused;

    void posetiCvor(int cvor)
    {
        poseceniCvorovi[cvor] = true;
    }

    bool vecPosecen(int cvor)
    {
        return poseceniCvorovi[cvor];
    }
};

int main()
{
    int brojCvorova = 6;
    Graf graf(brojCvorova);

    graf.dodajGranu(0, 2);
    graf.dodajGranu(0, 3);
    graf.dodajGranu(1, 0);
    graf.dodajGranu(2, 1);
    graf.dodajGranu(3, 4);

    graf.nadjiArtikTacke(0);
    graf.ispisiArtikTacke();

}