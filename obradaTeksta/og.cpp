#include <string>
#include <iostream>
#include <vector>

using namespace std;

void kmpPreprocesiraj(const string &p, vector<int> &b)
{
    int m = b.size();
    int i = 0;
    int j = -1;
    // prazna niska nema prefiks-sufikse
    b[i] = j;
    // za svaki prefiks polazne niske
    // racunamo najduzi prefiks-sufiks
    while (i < m)
    {
        // proveravamo da li se najduzi prefiks-sufiks
        // prefiksa uzorka koji se zavrsava na prethodnoj poziciji
        // moze prosiriti: to vazi ako je p[i]=p[j]
        while (j >= 0 && p[i] != p[j])
            j = b[j];
        i++;
        j++;
        b[i] = j;
    }
}

void kmpTrazi(string tekst, string pattern, vector<int> pmTable)
{
    int i = 0; // trenutni karakter u tekstu
    int j = 0; // trenutni karakter u paternu

    while (i < tekst.size())
    {
        // dok god ne matchujemo samo shiftuj u desno
        while (j >= 0 && tekst[i] != pattern[j])
        {
            j = pmTable[j];
        }
        
        // ako smo dosli do poklapanja (ili nam je j == -1) oba pomerimo unapred
        i++;
        j++;

        if (j == pattern.size())
        {
            cout << "Pocetni indeks uzorka u tekstu je: " << i - j << endl;
            j = pmTable[j];
        }
    }
}
int main()
{
    string tekst = "nestonestonesto";
    string uzorak = "stonest";
    
    int m = uzorak.size();
    
    vector<int> b(m + 1);
    kmpPreprocesiraj(uzorak, b);
    
    int n = tekst.size();
    
    kmpTrazi(tekst, uzorak, b);
    return 0;
}