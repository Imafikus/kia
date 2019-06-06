#include <string>
#include <vector>
#include <iostream>

using namespace std;

string dopuniString(string text)
{
    string dopunjen = "^";
    for(int i = 0; i < text.size(); i++)
    {
        dopunjen += "|" + text.substr(i, 1);
    }
    dopunjen += "|$";

    return dopunjen;
}

string manacher(string text)
{
    string dopunjen = dopuniString(text);

    cout << "dopuniString: " << dopunjen << endl;
    int R = 0;
    int C = 0;

    vector<int> P(dopunjen.size(), 0);

    for(int i = 1; i < dopunjen.size() - 1; i++)
    {
        int sim = 2 * C - i;
        if(i < R)
        {
            P[i] = min(R - i, P[sim]);
        }

        while(dopunjen[i - (1 + P[i])] == dopunjen[i + (1 + P[i])])
        {
            P[i]++;
        }

        if(i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }
    }

    int maxDuzina = 0;
    int maxCentar = 0;

    for(int i = 1; i < dopunjen.size() - 1; i++)
    {
        if(P[i] > maxDuzina)
        {
            maxCentar = i;
            maxDuzina = P[i];
        }
    }

    string palindrom;
    for(int i = maxCentar - maxDuzina + 1; i <= 2 * maxDuzina; i += 2)
    {
        palindrom += dopunjen.substr(i, 1);
    }
    return palindrom;
}

int main()
{
    string s = "ananabccaana";
    cout << manacher(s) << endl; 
}