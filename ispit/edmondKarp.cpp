#include <vector>
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

vector<vector<pair<int, int>>> listaSuseda;
vector<int> roditelj;
vector<vector<int>> rezidualniGraf;


template<typename T>
void stampajMatricu (vector<vector<T>> matrica)
{
    for(int i = 0; i < matrica.size(); i++)
    {
        for(int j = 0; j < matrica.size(); j++)
        {
            cout << matrica[i][j] << " ";
        }   
        cout << endl;
    }
}

bool bfs(int izvor, int ponor)
{
    vector<bool> posecen(listaSuseda.size(), false);

    queue<int> neobradjeni;
    neobradjeni.push(izvor);
    posecen[izvor] = true;

    while(!neobradjeni.empty())
    {
        int cvor = neobradjeni.front();
        neobradjeni.pop();

        for(pair<int, int> sused : listaSuseda[cvor])
        {
            if(!posecen[sused.first] && rezidualniGraf[cvor][sused.first] > 0)
            {
                neobradjeni.push(sused.first);
                roditelj[sused.first] = cvor;
                posecen[sused.first] = true;
            }
        }
    }
    return(posecen[ponor] == true);
}

void edmondKarp(int izvor, int ponor)
{
    int brojCvorova = listaSuseda.size();
    
    //? postavimo rezidualni graf da bude isti kao pocetni
    for(int i = 0; i < brojCvorova; i++)
    {
        for(int j = 0; j < brojCvorova; j++)
        {
            rezidualniGraf[i][j] = 0;
        }
    }

    stampajMatricu(rezidualniGraf);

    for(int cvor = 0; cvor < brojCvorova; cvor++)
    {
        for(pair<int, int> sused : listaSuseda[cvor])
        {
            rezidualniGraf[cvor][sused.first] = sused.second;
        }
    }

    stampajMatricu(rezidualniGraf);

    int maxTok = 0;
    
    //? Dok god mozemo da pustimo neki put od izvora do ponora mozemo
    //? da unapredjujemo maxTok
    while(bfs(izvor, ponor))
    {
        //cout << "Usao u while" << endl;

        //? Nalazimo bottleneck na putu
        int bottleneck = numeric_limits<int>::max();

        for(int cvor = ponor; cvor != izvor; cvor = roditelj[cvor])
        {
            int u = roditelj[cvor];
            if(rezidualniGraf[u][cvor] < bottleneck)
                bottleneck = rezidualniGraf[u][cvor];
        }

        for(int cvor = ponor; cvor != izvor; cvor = roditelj[cvor])
        {
            int u = roditelj[cvor];
            rezidualniGraf[u][cvor] -= bottleneck;
            rezidualniGraf[cvor][u] += bottleneck;
        }        
        maxTok += bottleneck;

        cout << endl;
        stampajMatricu(rezidualniGraf);
    }
    cout << "Optimalni tok je: " << maxTok << endl;   
}


int main()
{
    listaSuseda = {
        {{1, 5}, {2, 7}, {3, 6}}, 
        {{4, 4}, {5, 3}}, 
        {{5, 4}, {6, 1}}, 
        {{6, 5}}, 
        {{7, 3}}, 
        {{7, 7}}, 
        {{5, 4}, {7, 6}}, 
        {}};
    
    int brojCvorova = listaSuseda.size(); 
    roditelj.resize(brojCvorova, -1);

    rezidualniGraf.resize(brojCvorova);
    for(int i = 0; i < brojCvorova; i++)
        rezidualniGraf[i].resize(brojCvorova);

    edmondKarp(0, 7);
}