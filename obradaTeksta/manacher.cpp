#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string dopuni(const string &s)
{
    string d = "^";
    for(int i = 0; i < s.size(); i++)
    {
        d += "|" + s.substr(i, 1); 
    }
    d += "|$";
    return d;
}

string nadjiPalindromDopunom(const string& stariString, const string& dopunjenString)
{
    int maxDuzina = 0;
    int maxCentar;

    for(int centar = 1; centar < dopunjenString.size() - 1; centar++)
    {
        int d = 0;
        while(dopunjenString[centar - d - 1] == dopunjenString[centar + d + 1])
        {
            d++;
        }
        if(d > maxDuzina)
        {
            maxDuzina = d;
            maxCentar = centar;
        }
    }
    int maxPocetak = (maxCentar - maxDuzina) / 2;
    return stariString.substr(maxPocetak, maxDuzina);
}

int main()
{
    string s = "alabalacdwww";
    string dopunjen = dopuni(s);

    string najveciPalindrom = nadjiPalindromDopunom(s, dopunjen);
    cout << "najveci palindrom je: " << najveciPalindrom << endl;

}