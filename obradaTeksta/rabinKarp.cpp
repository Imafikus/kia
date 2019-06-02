#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> rabinKarp(string uzorak, string tekst)
{
    int P = 31;
    int M = 1e9;

    int lenUzorak = uzorak.size();
    int lenTekst = tekst.size();

    vector<long long> stepenP(max(lenUzorak, lenTekst));
    stepenP[0] = 1;
    for (int i = 1; i < stepenP.size(); i++)
    {
        stepenP[i] = (stepenP[i - 1] * P) % M;
    }

    //? Racunamo hash vrednosti svih prefiksa datog niza
    vector<long long> hashTeksta(lenTekst + 1, 0);
    for (int i = 0; i < lenTekst; i++)
    {
        hashTeksta[i + 1] = (hashTeksta[i] + (tekst[i] - 'a' + 1) * stepenP[i]) % M;
    }

    long long hashUzorka = 0;
    for (int i = 0; i < lenUzorak; i++)
    {
        hashUzorka = (hashUzorka + (uzorak[i] - 'a' + 1) * stepenP[i]) % M;
    }

    vector<int> pojavljivanja;
    for (int i = 0; i <= (lenTekst - lenUzorak); i++)
    {
        long long tekuciHash = (hashTeksta[i + lenUzorak] + M - hashTeksta[i]) % M;

        if (tekuciHash == (hashUzorka * stepenP[i]) % M)
        {
            pojavljivanja.push_back(i);
        }
    }

    return pojavljivanja;
}

int main()
{
    vector<int> pojavljivanja = rabinKarp("test", "testera_testerisati_testove");

    for (int i : pojavljivanja)
    {
        cout << "Podstring pocinje na indeksu: " << i << endl;
    }
}