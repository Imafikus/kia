#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string dopuni(const string &s)
{
    string d = "^";
    for (int i = 0; i < s.size(); i++)
    {
        d += "|" + s.substr(i, 1);
    }
    d += "|$";
    return d;
}

string nadjiPalindromDopunom(const string &stariString, const string &dopunjenString)
{
    int maxDuzina = 0;
    int maxCentar;

    for (int centar = 1; centar < dopunjenString.size() - 1; centar++)
    {
        int d = 0;
        while (dopunjenString[centar - d - 1] == dopunjenString[centar + d + 1])
        {
            d++;
        }
        if (d > maxDuzina)
        {
            maxDuzina = d;
            maxCentar = centar;
        }
    }
    int maxPocetak = (maxCentar - maxDuzina) / 2;
    return stariString.substr(maxPocetak, maxDuzina);
}

string manacher(const string &stariString, const string &dopunjenString)
{
    // d[i] je najveci broj takav da je [i - d[i], i + d[i]] palindrom
    // to je ujedno i duzina najduzeg palindroma ciji je centar na
    // poziciji i (pozicije su ili slova originalnih reci, ili su izmedju njih)
    vector<int> d(dopunjenString.size());

    // leva granica ce biti L = C - (R - C)
    int C = 0;
    int R = 0;
    int L = 0;

    for (int i = 1; i < dopunjenString.size() - 1; i++)
    {
        // karakter simetrican trenutnom i
        int i_sim = C - (i - C);

        if (i < R && i_sim > L)
        {
            // nalazimo se unutar palindroma [L, R], ciji je centar C

            // palindrom sa centrom u i_sim i palindrom sa centrom u i su
            // celokupno smesteni u palindrom (L, R)
            d[i] = d[i_sim];
        }
        else
        {
            // ili se ne nalazimo u okviru nekog prethodnog palindroma ili
            // se nalazimo unutar palindroma [L, R], ali je palindrom sa
            // centrom u i_sim takav da nije celokupno smesten u (L, R) - u
            // tom slucajmo znamo da je duzina palindroma sa centrom u i bar
            // R-i, a da li je vise od toga, treba proveriti
            d[i] = i <= R ? R - i : 0;

            // prosirujemo palindrom dok god je to moguce krajnji karakteri
            // ^$ obezbedjuju da nije potrebno proveravati granice
            while (dopunjenString[i - d[i] - 1] == dopunjenString[i + d[i] + 1])
                d[i]++;
        }
        // ako palindrom sa centrom u i prosiruje desnu granicu
        // onda njega uzimamo za palindrom [L, R] sa centrom u C
        if (i + d[i] > R)
        {
            C = i;
            R = i + d[i];
        }
    }
    // pronalazimo najvecu duzinu palindroma i pamtimo njegov centar
    int maxDuzina = 0, maxCentar;
    for (int i = 1; i < dopunjenString.size() - 1; i++)
        if (d[i] > maxDuzina)
        {
            maxDuzina = d[i];
            maxCentar = i;
        }
    int maxPocetak = (maxCentar - maxDuzina) / 2;
    return stariString.substr(maxPocetak, maxDuzina);

}

string boljiManacher(const string &stariString)
{
    string dopunjenString = dopuni(stariString);
    vector<int> P(dopunjenString.size(), 0);

    int C = 0;
    int R = 0;

    for(int i = 1; i < dopunjenString.size() - 1; i++)
    {
        // karakter koji je "preko puta" u odnosu na nas trenutni karakter u odnosu na centar
        int sim = 2 * C - i;

        // ako smo i dalje u granicama trenutnog opsega proveravamo da li imamo situaciju da 
        // duzina palindroma u ondosu na centar sim ispada iz trenutnog opsega, ili je manja
        // uzimamo minimum jer uvek zelimo da ostanemo u opsegu
        if(i < R)
        {
            // ovo ce nam omoguciti da izbegnemo setanje redom da bi ponovo nasli gde je palindrom
            // vec cemo samo nastaviti od dela koji sigurno znamo da pripada palindromu
            P[i] = min(R - i, P[sim]);
        }

        // proveravamo da li mozemo da prosirimo palindrom, i radimo to koliko god mozemo
        while(dopunjenString[i - (1 + P[i])] == dopunjenString[i + (1 + P[i])])
        {
            P[i]++;
        }

        // ako smo izleteli iz opsega, to znaci da moramo da pomerimo taman toliko da nam staje to dokle smo izleteli
        if(i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }
    }
    
    int maxDuzina = 0;
    int maxC = 0;

    for(int i = 1; i < dopunjenString.size() - 1; i++)
    {
        if(P[i] > maxDuzina)
        {
            maxDuzina = P[i];
            maxC = i;
        }
    }

    string palindrom;
    for(int i = maxC - maxDuzina + 1; i <= 2 * maxDuzina; i+=2)
        palindrom += dopunjenString.substr(i, 1);
    
    return palindrom;
    // int maxPocetak = (maxC - maxDuzina) / 2;
    // return stariString.substr(maxPocetak, maxDuzina);
}

int main()
{
    string s = "ananabcana";
    string dopunjen = dopuni(s);

    // string najveciPalindrom = manacher(s, dopunjen);

    string najveciPalindrom = boljiManacher(s);    
    cout << "najveci palindrom je: " << najveciPalindrom << endl;
}