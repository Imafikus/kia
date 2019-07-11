#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void dodajGranu(int u, int v, vector<vector<int>>& ls)
{
    ls[u].push_back(v);
    ls[v].push_back(u);
}

void nadjiCikluseOdredjeneDuzine(int cvor, int end, int duzinaCiklusa, vector<vector<int>> ls, vector<bool>& posecen, int& brojCiklusa)
{
    posecen[cvor] = true;
    if(duzinaCiklusa == 0)
    {
        if(find(ls[cvor].begin(), ls[cvor].end(), end) != ls[cvor].end())
        {
            brojCiklusa++;
        }
        posecen[cvor] = false;
        return;
    }

    for(int sused : ls[cvor])
    {
        if(!posecen[sused])
        {
            nadjiCikluseOdredjeneDuzine(sused, end, duzinaCiklusa - 1, ls, posecen, brojCiklusa);
        }
    }
    posecen[cvor] = false;
}

int vratiCikluse(vector<vector<int>> ls, vector<bool>& posecen, int duzinaCiklusa)
{
    int brojCiklusa = 0;
    for(int pocetak = 0; pocetak < ls.size(); pocetak++)
    {
        nadjiCikluseOdredjeneDuzine(pocetak, pocetak, duzinaCiklusa - 1, ls, posecen, brojCiklusa);
        posecen[pocetak] = true;
    }
    return brojCiklusa;
}

int main()
{
    int brojCvorova = 7;
    vector<vector<int>> ls(brojCvorova);
    dodajGranu(0, 2, ls);
    dodajGranu(0, 1, ls);
    dodajGranu(1, 2, ls);
    dodajGranu(1, 4, ls);
    dodajGranu(4, 5, ls);
    dodajGranu(2, 5, ls);
    dodajGranu(5, 1, ls);
    dodajGranu(6, 0, ls);
    dodajGranu(6, 1, ls);
    vector<bool> posecen(brojCvorova, false);

    cout << "Broj ciklusa duzine 3 je: " << vratiCikluse(ls, posecen, 3) / 2<< endl;


}