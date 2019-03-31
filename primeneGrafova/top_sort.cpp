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
        this->brojCvorova = brojCvorova;

        listaPovezanosti.resize(brojCvorova);
        
        poseceniCvorovi.resize(brojCvorova, false);

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
        //cout << cvor << " ";
        for(int sused : listaPovezanosti[cvor])
        {
            if(!vecPosecen(sused))
                dfs(sused);
        }
        topSortStack.push(cvor);
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
    void dfsTopSort()
    {
        for(int cvor = 0; cvor < brojCvorova; cvor++)
            if(!vecPosecen(cvor))
                dfs(cvor);
        
        while(!topSortStack.empty())
        {
            cout << topSortStack.top() << " ";
            topSortStack.pop();
        }
        cout << endl;
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
    vector<int> topoloskoUredjenje;
    vector<int> ulazniStepen;
    stack<int> topSortStack;

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

    graf.dodajGranu(0, 1, true);
    graf.dodajGranu(1, 4, true);
    graf.dodajGranu(2, 4, true);
    graf.dodajGranu(3, 0, true);
    graf.dodajGranu(3, 2, true);
    graf.dodajGranu(5, 2, true);
    graf.dodajGranu(5, 4, true);

    cout << "Prosao grane" << endl;

    graf.dfsTopSort();
    
}