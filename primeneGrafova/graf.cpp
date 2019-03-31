#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

class Graf
{

public:
    Graf(int brojCvorova)
    {
        this->brojCvorova = brojCvorova;
        listaPovezanosti.resize(brojCvorova);
        jePosecen.resize(brojCvorova, false);
        ulazniStepen.resize(brojCvorova, 0);
    }

    void dfs(int cvor, bool dozvoljenoPisanje = true)
    {
        jePosecen[cvor] = true;
        if(dozvoljenoPisanje)
            cout << cvor << " ";

        
        for(int sused : listaPovezanosti[cvor])
        {
            if(!jePosecen[sused])
                dfs(sused, dozvoljenoPisanje);
        }

        topSortStack.push(cvor);
    }

    void bfs(int cvor)
    {
        queue<int> neobradjeni;
        jePosecen[cvor] = true;
        neobradjeni.push(cvor);

        while(!neobradjeni.empty())
        {
            int trenutniCvor = neobradjeni.front();
            neobradjeni.pop();
            cout << trenutniCvor  << " ";

            for(int sused : listaPovezanosti[trenutniCvor])
                if(!jePosecen[sused])
                {
                    neobradjeni.push(sused);
                    jePosecen[sused] = true;
                }
        }
    }

    void dodajGranu(int u, int v)
    {
        listaPovezanosti[u].push_back(v);
        ulazniStepen[v]++;
    }

    vector<int> topSort()
    {
        queue<int> neobradjeniCvorovi;
        for(int v = 0; v < brojCvorova; v++)
        {
            if(ulazniStepen[v] == 0)
                neobradjeniCvorovi.push(v);
        }

        while(!neobradjeniCvorovi.empty())
        {
            int trenutniCvor = neobradjeniCvorovi.front();
            neobradjeniCvorovi.pop();

            topoloskoUredjenje.push_back(trenutniCvor);

            for(int sused : listaPovezanosti[trenutniCvor])
            {
                ulazniStepen[sused]--;
                if(ulazniStepen[sused] == 0)
                    neobradjeniCvorovi.push(sused);
            }
        }
        return topoloskoUredjenje;
    }

    void dfsTopSort()
    {
        for(int cvor = 0; cvor < brojCvorova; cvor++)
        {
            if(!jePosecen[cvor])
                dfs(cvor, false);
        }

        while(!topSortStack.empty())
        {
            cout << topSortStack.top() << " ";
            topSortStack.pop();
        }
        cout << endl;
    }

private:
    //? Osnovne inicijalizacije
    int brojCvorova;
    vector<vector<int>> listaPovezanosti;
    vector<bool> jePosecen;
    vector<int> ulazniStepen;

    //? dfs topSort
    stack<int> topSortStack;

    //? topSort - Kahn
    vector<int> topoloskoUredjenje;

};

int main()
{
    Graf graf(6);

    graf.dodajGranu(0, 1);
    graf.dodajGranu(3, 0);
    graf.dodajGranu(3, 4);
    graf.dodajGranu(1, 4);
    graf.dodajGranu(5, 4);
    graf.dodajGranu(2, 4);
    graf.dodajGranu(5, 2);

    vector<int> sortirani = graf.topSort();
    for(int cvor : sortirani)
        cout << cvor << " ";
    cout << endl;
}