#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


vector<int> napraviPrefixTable(string pattern)
{
    vector<int> prefixTable(pattern.size() + 1);
    prefixTable[0] = -1;

    for(int i = 1; i <= pattern.size(); i++)
    {
        char trenutniKarakter = pattern[i - 1];
        int duzinaPrefiksa = prefixTable[i - 1];

        while(duzinaPrefiksa != -1 && trenutniKarakter != pattern[duzinaPrefiksa])
        {
            duzinaPrefiksa = prefixTable[duzinaPrefiksa];
        }
        prefixTable[i] = duzinaPrefiksa + 1;
    }
    return prefixTable;
}

vector<int> pronadji(string text, string pattern, vector<int> prefixTable)
{
    int i = 0;
    int j = 0;

    vector<int> pojavljivanja;

    while(i + pattern.size() - j <= text.size())
    {
        bool match = true;
        while(match && j < pattern.size())
        {
            if(pattern[j] != text[i])
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
        else j = prefixTable[j];
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
    cout << endl;
    
    vector<int> pojavljivanja = pronadji(text, pattern, prefix);

    for(int e : pojavljivanja)
        cout << e << " " << endl;
    
}