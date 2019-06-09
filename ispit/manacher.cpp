#include <string>
#include <vector>
#include <iostream>

using namespace std;

string dopuniString(string text)
{
    string dop = "ˆ";
    for(int i = 0; i < text.size(); i++)
    {
        dop += "|" + text.substr(i, 1);
    }
    dop += "|$";
    return dop;
}
string manacher(string text)
{
    string dop = dopuniString(text);
    cout << dop << endl;
    
    vector<int> P(dop.size());

    int C = 0;
    int R = 0;

    P[0] = 0;

    for(int i = 1; i < dop.size() - 1; i++)
    {
        int sim = 2 * C - i;
        if(i < R)
        {
            P[i] = P[sim];
        }
        else
        {
            if(i > R)
            {
                P[i] = 0;
            }
            else
            {
                P[i] = R - i;
            }
        } 
        while(dop[i - (P[i] + 1)] == dop[i + (P[i] + 1)])
        {
            P[i]++;
        }
        if(P[i] + i > R)
        {
            R = P[i] + i;
            C = i;
        }
    }
    int maxCentar;
    int maxDuzina = 0;

    for(int i = 1; i < dop.size() - 1; i++)
    {
        if(P[i] > maxDuzina)
        {
            maxDuzina = P[i];
            maxCentar = i;
        }
    }

    int pocetak = abs(maxCentar - maxDuzina) / 2 - 1;
    return text.substr(pocetak, maxDuzina);
}

int main()
{
    string s = "anavolimennennenne";
    cout << manacher(s) << endl;    
}
