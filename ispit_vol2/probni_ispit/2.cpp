#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string dopuni(string text)
{
    string dop = "^|";
    for(int i = 0; i < text.size(); i++)
    {
        dop += text.substr(i, 1) + "|";
    }
    dop += "$";
    return dop;
}

string najduziKojiSadrziPocetak(string text)
{
    string dop = dopuni(text);
    vector<int> P(dop.size());

    int R = 0;
    int C = 0;

    for(int i = 1; i < dop.size() - 1; i++)
    {
        int sim = 2 * C - i;

        if(i < R)
            P[i] = min(R - i, P[sim]);
        
        while(dop[i - (P[i] + 1)] == dop[i + (1 + P[i])])
            P[i]++;
        
        if(i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }
    }

    int maxCentar = 0;
    int maxDuzina = 0;

    for(int i = 1; i < dop.size() - 1; i++)
    {
        if(P[i] > maxDuzina && abs(P[i] - i) == 1)
        {
            maxDuzina = P[i];
            maxCentar = i;
        }
    }

    int pocetak = abs(maxDuzina - maxCentar) / 2;
    return text.substr(pocetak, maxDuzina);
}

int main()
{
    string text;
    cin >> text;

    string sol = najduziKojiSadrziPocetak(text);
    int ostatak = text.size() - sol.size();
    cout << "Ostatak: " << ostatak << endl;
    
    int k = text.size() - 1;
    int j = 0;
    int poklapanja = 0;

    cout << "sol[j]: " << sol[j] << endl;
    cout << "text[k]: " << text[k] << endl;
    while(j < sol.size() && k > 0 && (sol[j] == text[k]))
    {
        j++;
        k--;
        poklapanja++;
    }

    cout << "Broj poklapanja: " << poklapanja << endl;
}