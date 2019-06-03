#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// i = trenutni indeks
// k = koliki prefix gledam
// int rekkmp(int i, int k) {
//     //int k = prefix[i - 1];
//     char trenutniKarakter = pat.charAt(i - 1); // x
//     char karakterZaProduzetak = pat.charAt(k) // ovo drugo

//     if (trenutniKarakter == karakterZaProduzetak) { // x == y
//         return k + 1; // produzi za jedan
//     }
//     else if (k == -1) {
//         return 0;
//     }
//     else {
//         return rekkmp(i, prefix[k])
//     }
// }

// ABCEestoABCDasdjhflkjsdfhABCEestoABCE   asfladkjshfad
// ===~~~~~===^             ===~~~~~===^    




vector<int> napraviPrefixTable(string pattern)
{
    vector<int> prefix(pattern.size() + 1);
    prefix[0] = -1;
    for(int i = 1; i <= pattern.size(); i++)
    {
        char trenutniKarakter = pattern[i - 1];
        int trLenPrefix = prefix[i - 1]; // trenutna duzina prefiksa
        
        // ako nismo nasli prefiks+1 duzinu
        while(trLenPrefix >= 0 && trenutniKarakter != pattern[trLenPrefix])
        {
            // ako ne mogu trenutni, onda baci pogled na taj karakter
            // i vidi kolika je duzina prefiksa tu
            // mi znamo da je taj karakter udaljen za trLenPrefix (trenutnu duzinu prefiksa)
            // od pockta
            trLenPrefix = prefix[trLenPrefix];
        }
        prefix[i] = trLenPrefix + 1; 
    }
    return prefix;
}

vector<int> pronadjiBebicev(string txt, string pattern, vector<int> prefix)
{
    int i = 0; // dokle smo u tekstu
    int j = 0; // dokle smo u patternu
    
    vector<int> pojavljivanja;

    while (i + pattern.size() - j <= txt.size())
    {
        bool match = true;
        // oremo text i pattern, dok ili ne zavrsimo ili nadjemo missmatch
        while (match && j < pattern.size()) 
        {
            if (pattern[j] != txt[i])
            {
                match = false;
            } 
            else
            {
                j++; i++;
            }
        }

        if (match) 
        {
            pojavljivanja.push_back(i - pattern.size());
        } 

        if (j == 0) i++; // na pocetku patterna smo, samo se mrdnemo za 1
        else j = prefix[j]; // SHIFT ---> 
        
    }
    return pojavljivanja;
}

vector<int> pronadji(string tekst, string pattern, vector<int> pmTable)
{
    int i = 0; // trenutni karakter u tekstu
    int j = 0; // trenutni karakter u paternu

    vector<int> pojavljivanja;

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
            pojavljivanja.push_back(i - j);
            j = pmTable[j];
        }
    }
    return pojavljivanja;
}
int main()
{
    string text = "banana";
    string pattern = "ana";
    
    vector<int> prefix = napraviPrefixTable(pattern);

    cout << "prefix tabela: " << endl;
    for (int pf : prefix) 
    {
        cout <<  "  " <<pf << endl;
    }

    vector<int> pojavljivanja = pronadjiBebicev(text, pattern, prefix);
    
    if(pojavljivanja.size() == 0)
    {
        cout << "Nema poklapanja!" << endl;    
    }
    else
    {
        for(int e : pojavljivanja)
        {
            cout << "Pattern pocinje na poziciji: " << e << endl;
        }
    }
}