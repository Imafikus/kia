#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Cvor
{
    bool krajReci = false;
    unordered_map<char, Cvor*> grane;
};

bool nadjiRec(Cvor* trie, string trazenaRec, int i = 0)
{
    if(i == trazenaRec.size())
        return trie->krajReci;
    
    auto it = trie->grane.find(trazenaRec[i]);
    if(it != trie->grane.end())
        return nadjiRec(it->second, trazenaRec, i+1);

    return false;
}

void umetniRec(Cvor* trie, string rec, int i = 0)
{
    if(i == rec.size())
    {
        trie->krajReci = true;
        return;
    }

    auto it = trie->grane.find(rec[i]);
    if(it == trie->grane.end())
    {
        trie->grane[rec[i]] = new Cvor();
    }
    umetniRec(trie->grane[rec[i]], rec, i+1);
}

int main()
{
    Cvor* trie = new Cvor();

    vector<string> postoje = {"vas","vasa","vasilije","vatra","da","dan","dud","duz"};
    vector<string> nePostoje = {"", "v", "d", "vasiona", "trava", "drvo"};

    for(string r : postoje)
    {
        umetniRec(trie, r);
    }

    for(auto r : postoje)
    {
        if(nadjiRec(trie, r))
            cout << r << " je u trie-u" << endl;
        else
            cout << r << " nije u trie-u" << endl;
    }

    for(auto r : nePostoje)
    {
        if(nadjiRec(trie, r))
            cout << r << " je u trie-u" << endl;
        else
            cout << r << " nije u trie-u" << endl;
    }

}
