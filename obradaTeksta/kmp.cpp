#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void kmpPreprocesiraj(string p, vector<int> &b)
{
    int i = 0;
    int j = -1;

    //? Prazna nisika nema prefiks-sufiks
    b[i] = j;

    //? Za svaki prefiks trazimo njegov najduzi prefiks-sufiks
    while (i < p.size())
    {
        while (j >= 0 && p[i] != p[j])
        {
            j = b[j];
        }
        j++;
        i++;
        b[i] = j;
    }
}

void kmpTrazi(string tekst, string uzorak, vector<int> b)
{
    int i = 0;
    int j = 0;

    while (i < tekst.size())
    {
        while (j >= 0 && tekst[i] != uzorak[j])
            j = b[j];

        i++;
        j++;
        if (j == uzorak.size())
        {
            cout << "Pocetni indeks uzorka u tekstu je: " << i - j << endl;
            j = b[j];
        }
    }
}

int main()
{
    string tekst = "abrakadabra";
    string uzorak = "ra";
    
    int m = uzorak.size();
    vector<int> b(m + 1);
    
    kmpPreprocesiraj(uzorak, b);
    
    int n = tekst.size();
    kmpTrazi(tekst, uzorak, b);
}