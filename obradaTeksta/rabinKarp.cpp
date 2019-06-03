#include <vector>
#include <iostream>
#include <algorithm>
#include <algorithm>

using namespace std;

vector<int> rabinKarp(string pattern, string tekst)
{
    int P = 31;
    int M = 1e9;

    int lenUzorak = pattern.size();
    int lenTekst = tekst.size();

    vector<long long> stepenP(lenTekst);

    // stepenP[i] == P^i (mod M)

    stepenP[0] = 1;
    for (int i = 1; i < stepenP.size(); i++)
    {
        // P^i = P^(i-1) * P
        stepenP[i] = (stepenP[i - 1] * P) % M;
    }

    //? Racunamo hash vrednosti svih prefiksa datog niza
    //? Radi se inkremnetalno, refer to formula u donjoj for petlji
    vector<long long> hashTeksta(lenTekst + 1, 0);
    for (int i = 0; i < lenTekst; i++)
    {
        // hashTeksta[n] = Sum[c[i] * P^i, i = [0 .. n-1]
        hashTeksta[i + 1] = (hashTeksta[i] + tekst[i] * stepenP[i]) % M;
    }

    long long hashUzorka = 0;
    for (int i = 0; i < lenUzorak; i++)
    {
        hashUzorka = (hashUzorka + pattern[i]  * stepenP[i]) % M;
    }

    vector<int> pojavljivanja;
    for (int i = 0; i <= (lenTekst - lenUzorak); i++)
    {
        // [5, 10] = [0, 10] - [0, 4], dodaje se M da ne odemo u negativan modul
        long long tekuciHash = (hashTeksta[i + lenUzorak] - hashTeksta[i] + M) % M;

        // tekuciHash = hash[i .. i+lenUzorak] = hash[0 .. i+lenUzorak] - hash[0 .. i]
        //            = c[i] * P^i + c[i+1] * P^i+1 + ..... + c[i+lenUzorak-1] * P^(i+lenUzorak-1)

        // hashUzorka = u[0] * P^0 + u[1]   * P^1   + ..... + u[lenUzorak-1]   * P^(lenUzorak-1)
        // mnozimo sa P^i gornju formulu
        if (tekuciHash == (hashUzorka * stepenP[i]) % M)
        {
            // dodatna brute force provera da li su jednaki, ako je mozda doslo do promasaja
            // u hesiranju
            if (equal(tekst.begin() + i, tekst.begin() + i + lenUzorak, pattern.begin()))
            {
                pojavljivanja.push_back(i);
            }
        }
    }

    return pojavljivanja;
}

int main()
{
    vector<int> pojavljivanja = rabinKarp("TEST", "TdRT");

    for (int i : pojavljivanja)
    {
        cout << "Podstring pocinje na indeksu: " << i << endl;
    }
}