#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> listaSuseda = {{1, 3, 4}, {0, 2}, {1}, {0, 6}, {0, 5}, {4}, {3}};
int vreme = 1;
vector<bool> posecen;
vector<int> dolazna;
vector<int> min_pretka;
vector<int> roditelj;
vector<bool> artikulacionaTacka;


vector<int> test;

void dfs(int cvor)
{
    posecen[cvor] = true;
    dolazna[cvor] = min_pretka[cvor] = vreme;
    vreme++;
    int broj_dece = 0;
    for (auto sused : listaSuseda[cvor])
    {
        if (!posecen[sused])
        {
            broj_dece++;
            roditelj[sused] = cvor;
            dfs(sused);

            min_pretka[cvor] = min(min_pretka[cvor], min_pretka[sused]);
            // if (min_pretka[sused] < min_pretka[cvor])
            //     min_pretka[cvor] = min_pretka[sused];

            if (roditelj[cvor] == -1 && broj_dece > 1)
                // artikulacionaTacka[cvor] = true;
                test.push_back(cvor);
            
            if (roditelj[cvor] != -1 && min_pretka[sused] >= dolazna[cvor])
                // artikulacionaTacka[cvor] = true;
                test.push_back(cvor);

        }
        else
            // posecen[sused]
            if (sused != roditelj[cvor])
                min_pretka[cvor] = min(min_pretka[cvor], dolazna[sused]);
            // if (dolazna[sused] < min_pretka[cvor])
            //     min_pretka[cvor] = dolazna[sused];
    }
}

void ispisi_artikulacione_tacke(int cvor)
{
    int brojCvorova = listaSuseda.size();
    posecen.resize(brojCvorova, false);
    dolazna.resize(brojCvorova);
    min_pretka.resize(brojCvorova);
    roditelj.resize(brojCvorova, -1);
    artikulacionaTacka.resize(brojCvorova, false);
    dfs(cvor);
    cout << "Artikulacione tacke u grafu su: ";
    // for (int i = 0; i < artikulacionaTacka.size(); i++)
    // {
    //     if (artikulacionaTacka[i])
    //         cout << i << " ";
    // }
    for (int i : test)
    {
        cout << i << " ";
    }
    cout << endl;
};

int main()
{
    ispisi_artikulacione_tacke(0);
    return 0;
}