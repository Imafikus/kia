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
int main()
{
    string s = "alabalacdwww";
    string dopunjen = dopuni(s);

    string najveciPalindrom = manacher(s, dopunjen);
    cout << "najveci palindrom je: " << najveciPalindrom << endl;
}