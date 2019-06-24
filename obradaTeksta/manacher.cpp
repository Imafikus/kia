#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

string dopuni(string& text)
{
    string dop = "^|";
    for(int i = 0; i < text.size(); i++)
    {
        dop += text.substr(i, 1) + "|";
    }

    dop +="$";
    return dop; 
}
string manacher(string& text)
{
    string dop = dopuni(text);
    vector<int> P(dop.size());

    int C = 0;
    int R = 0;

    for(int i = 1; i < dop.size() - 1; i++)
    {
        int sim = 2 * C - i;
        if(i < R)
        {
            P[i] = min(R - i, P[sim]);
        }

        while(dop[i - (1 + P[i])] == dop[i + (1 + P[i])])
            P[i]++;
        
        if(i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }
    }

    int maxCentar = 0;
    int maxDuzina = 0;
    for(int i = 1; i < P.size() - 1; i++)
    {
        if(P[i] > maxDuzina)
        {
            maxDuzina = P[i];
            maxCentar = i;
        }
    }
    int pocetak = abs(maxCentar - maxDuzina) / 2;
    return text.substr(pocetak, maxDuzina);
}


int main()
{
    string text;
    cin >> text;
    cout << dopuni(text) << endl;

    cout << manacher(text) << endl;


}