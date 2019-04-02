#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

struct Cvor
{
    bool krajReci = false;
    unordered_map<char, Cvor*> grane;
};

//? i oznacava od kog dela stringa nastavljamo pretragu, na pocetku uvek hocemo od pocetka da idemo
//? tada nam je sufiks zapravo cela rec
bool nadjiRec(Cvor* trie, string trazenaRec, int i = 0)
{
    //? ako smo dosli do kraja, tj nemamo vise sufikse, onda samo vratimo sta stoji na tom poslednjem mestu
    //? jer ako je rec, krajReci ce biti postavljen na true
    if(i == trazenaRec.size())
        return trie->krajReci;

    //? pokusavamo da nadjemo sledece slovo u trie-u do kog treba da dodjemo
    //? ako ono ne postoji, znaci da trazena rec ne postoji ovde
    auto it = trie->grane.find(trazenaRec[i]);
    if(it != trie->grane.end())
        //? it->second ce biti value iz key, value para i on predstavlja granu koju odredjuje trenutno slovo
        return nadjiRec(it->second, trazenaRec, i+1);
    
    //? Ako nista ne returnuje sigurno znamo da nismo nasli rec
    return false;
}

//? Umece rec u trie, ako iz nekog razloga ne zelimo da umetnemo celu rec
//? nego zelimo samo od nekog dela, mozemo da damo proizvolljno i
void umetniRec(Cvor* trie, string rec, int i = 0)
{
    //? ako imamo situaciju da vec sve karaktere imamo u nizu, a da samo pre ovoga nisu oznacavali rec
    if(i == rec.size())
    {
        trie->krajReci = true;
        return;
    }

    //? trazimo da li vec postoji grana sa trenutnim karakterom
    //? ako ne postoji zelimo da je napravimo, da bi bili sigurni da postoji
    //? kada odemo u rekurziju
    auto it = trie->grane.find(rec[i]);
    if(it == trie->grane.end())
        trie->grane[rec[i]] = new Cvor();

    umetniRec(trie->grane[rec[i]], rec, i+1);
}

int main()
{
    Cvor* trie = new Cvor();
    
    vector<string> reci{"vas","vasa","vasilije","vatra","da","dan","dud","duz"};
    vector<string>reci_nema{"", "v", "d", "vasiona", "trava", "drvo"};
    
    for(auto w : reci)
        umetniRec(trie, w);
    
    for(auto w : reci)
        cout << w << ":" << (nadjiRec(trie, w) ? "da" : "ne") << endl; 
    
    for(auto w : reci_nema)
        cout << w << ":" << (nadjiRec(trie, w) ? "da" : "ne") << endl;
    
    return 0;
}
