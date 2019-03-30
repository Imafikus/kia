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

    void dfs(int cvor)
    {
        posetiCvor(cvor);
        cout << cvor << " ";
        for(int sused : listaPovezanosti[cvor])
        {
            if(!vecPosecen(sused))
                dfs(sused);
        }
    }

    void nadjiArtikTacke(int cvor)
    {
        posetiCvor(cvor);

        vremePosecivanja[cvor] = vreme;
        najranijePosecenSused[cvor] = vreme;

        vreme++;

        int decaTrenutnogCvora = 0;

        auto begin = listaPovezanosti[cvor].begin();
        auto end = listaPovezanosti[cvor].end();

        while(begin != end)
        {
            if(!vecPosecen(*begin))
            {
                roditeljCvora[*begin] = cvor;
                nadjiArtikTacke(*begin);

                decaTrenutnogCvora++;

                if(najranijePosecenSused[*begin] < najranijePosecenSused[cvor])
                    najranijePosecenSused[cvor] = najranijePosecenSused[*begin];

                //? Proveri da li je koreni cvor, i ako jeste, da li je artik tacka
                if(roditeljCvora[cvor] == -1 && decaTrenutnogCvora > 1)
                    artikTacke.push_back(cvor);
                
                //? ovo se desava kada cvor nije koren, gledamo pocetni cvor i njegove susede, ne postoji sused takav
                //? da on za svog suseda ima neki cvor koji se pojavio pre pocetnog, onda ce pocetni cvor biti artikulaciona tacka
                if(roditeljCvora[cvor] != -1 && vremePosecivanja[cvor] <= najranijePosecenSused[*begin])
                    artikTacke.push_back(cvor);
                
            }
            //? proveravamo da li sused trenutnog cvora ima mozda neki cvor
            //? koji je ranije posecen a do kog moze da dodje, ako ima, to znaci
            //? i da nas trenutni cvor moze da dodje do njega pa radimo update
            //? pitamo da li je taj sused razlicit od roditelja ovog cvora jer ne zelimo da idemo na tu stranu
            else if(*begin != roditeljCvora[cvor])
            {
                if(najranijePosecenSused[*begin] < najranijePosecenSused[cvor])
                    najranijePosecenSused[cvor] = najranijePosecenSused[*begin];
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

    void nadjiMostove(int cvor)
    {
        posetiCvor(cvor);

        vremePosecivanja[cvor] = vreme;
        najranijePosecenSused[cvor] = vreme;

        vreme++;

        int decaTrenutnogCvora = 0;

        auto begin = listaPovezanosti[cvor].begin();
        auto end = listaPovezanosti[cvor].end();

        while(begin != end)
        {
            if(!vecPosecen(*begin))
            {
                roditeljCvora[*begin] = cvor;
                nadjiMostove(*begin);

                decaTrenutnogCvora++;

                if(najranijePosecenSused[*begin] < najranijePosecenSused[cvor])
                    najranijePosecenSused[cvor] = najranijePosecenSused[*begin];

                //? Proveravamo da li je trenutni cvor najraniji posecen od svih svojih suseda, ako jeste, onda je ova grana most
                if(vremePosecivanja[cvor] < najranijePosecenSused[*begin])
                    cout << cvor << "->" << *begin << endl;
            }
            
            else if(*begin != roditeljCvora[cvor])
            {
                if(najranijePosecenSused[cvor] >= najranijePosecenSused[*begin])
                    najranijePosecenSused[cvor] = najranijePosecenSused[*begin];
            }

            begin++;
        }
    }
    
    void stampajVremePosecivanja()
    {
        for(int i : vremePosecivanja)
            cout << i << " ";
        cout << endl;
    }

    void stampajNajranije()
    {
        for(int i : najranijePosecenSused)
            cout << i << " ";
        cout << endl;
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
    Graf graf(5);

    graf.dodajGranu(0, 2);
    graf.dodajGranu(0, 3);
    graf.dodajGranu(1, 0);
    graf.dodajGranu(2, 1);
    graf.dodajGranu(3, 4);

    graf.nadjiArtikTacke(0);
    graf.ispisiArtikTacke();

    graf.stampajVremePosecivanja();
    graf.stampajNajranije();
    graf.nadjiMostove(0);

}