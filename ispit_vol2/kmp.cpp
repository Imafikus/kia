#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<int> napraviPrefixTable(string pattern)
{
    vector<int> prefix(pattern.size() + 1);
    prefix[0] = -1;

    for(int i = 1; i <= pattern.size(); i++)
    {
        char trenutniKarakter = pattern[i - 1];
        int trLenPrefixa = prefix[i - 1];

        while(trLenPrefixa != -1 && trenutniKarakter != pattern[trLenPrefixa])
        {
            trLenPrefixa = prefix[trLenPrefixa];
        }
        prefix[i] = trLenPrefixa + 1;
    }
    return prefix;
}

vector<int> nadjiPojavljivanja(string text, string pattern)
{
    vector<int> prefix = napraviPrefixTable(pattern);
    int i = 0;
    int j = 0;

    for(int e : prefix)
        cout << e << endl;

    vector<int> pojavljivanja;

    while(i + pattern.size() - j <= text.size())
    {
        bool match = true;
        while(match && j < pattern.size())
        {
            if(text[i] != pattern[j])
            {
                match = false;
            }
            else
            {
                i++;
                j++;
            }
        }
        if(match)
        {
            pojavljivanja.push_back(i - pattern.size());
        }

        if(j == 0) i++;
        else j = prefix[j];
    }
    return pojavljivanja;
}

int main()
{
    string text, pattern;
    cin >> text >> pattern;

    vector<int> pojavljivanja = nadjiPojavljivanja(text, pattern);
    for(int e : pojavljivanja)
        cout << "Pojavljivanje na indeksu: " << e << endl;
}