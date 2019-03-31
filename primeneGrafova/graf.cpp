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
        jestePosecen.resize(brojCvorova, false);
        ulazniStepen.resize(brojCvorova, 0);
    }

    void dodajGranu(int u, int v)
    {
        
    }

private:
    int brojCvorova;
    vector<vector<int>> listaPovezanosti;
    vector<bool> jestePosecen;
    vector<int> ulazniStepen;
}