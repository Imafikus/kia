#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Graf
{
public:
    Graf(int brojCvorova)
    {
        this->brojCvorova = brojCvorova;

        listaPovezanosti.resize(brojCvorova);
        
        poseceniCvorovi.resize(brojCvorova, false);

        vremePosecivanja.resize(brojCvorova, -1);

        vreme = 0;

        roditeljCvora.resize(brojCvorova, -1);

        najranijePosecenSused.resize(brojCvorova, -1);


        ulazniStepen.resize(brojCvorova, 0);
    }

    void dodajGranu(int u, int v, bool usmeren = false)
    {
        listaPovezanosti[u].push_back(v);
        if(!usmeren)
            listaPovezanosti[v].push_back(u);
        
        ulazniStepen[v]++;
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

    void topSort()
    {
        //? Trazimo cvorove koji imaju ulazni stepen 0
        queue<int> neobradjeniCvorovi;
        for(int cvor = 0; cvor < brojCvorova; cvor++)
        {
            if(ulazniStepen[cvor] == 0)
                neobradjeniCvorovi.push(cvor);
        }

        while(!neobradjeniCvorovi.empty())
        {
            //? uzimamo jedan od cvorova koji imaju stepen 0
            int trenutniCvor = neobradjeniCvorovi.front();
            neobradjeniCvorovi.pop();

            topoloskoUredjenje.push_back(trenutniCvor);

            //?prolazimo kroz susede cvora i skidamo grane koje vode od
            //?trenutno uzetog cvora do njih, ako se ispostavi da posle skidanja
            //?neki cvor takodje ima ulazni stepen 0, njega guramo u red
        
            for(int cvor : listaPovezanosti[trenutniCvor])
            {
                ulazniStepen[cvor]--;

                if(ulazniStepen[cvor] == 0)
                    neobradjeniCvorovi.push(cvor);
            }

        }
    }

    void stampajTopoloskoUredjenje()
    {
        for(int cvor : topoloskoUredjenje)
            cout << cvor << " ";
        cout << endl;
    }

private:
    int brojCvorova;
    vector<vector<int>> listaPovezanosti;
    vector<bool> poseceniCvorovi;    
    vector<int> vremePosecivanja;
    int vreme;
    vector<int> roditeljCvora;
    vector<int> artikTacke;
    vector<int> najranijePosecenSused;
    vector<int> topoloskoUredjenje;
    vector<int> ulazniStepen;

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
    Graf graf(6);

    graf.dodajGranu(0, 1);
    graf.dodajGranu(1, 4);
    graf.dodajGranu(2, 4);
    graf.dodajGranu(3, 0);
    graf.dodajGranu(3, 2);
    graf.dodajGranu(5, 2);
    graf.dodajGranu(5, 4);

    cout << "Prosao grane" << endl;

    graf.topSort();
    graf.stampajTopoloskoUredjenje();
    
}