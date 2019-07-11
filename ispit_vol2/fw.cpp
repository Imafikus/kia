#include <vector>
#include <iostream>
#include <algorithm>

#define MAX (100000)

using namespace std;

void dodajGranu(int u, int v, int tezina, vector<vector<int>>& fwMatrica)
{
    fwMatrica[u][v] = tezina;
}

void initMatrice(int brojCvorova, vector<vector<int>> & fwMatrica)
{
    fwMatrica.resize(brojCvorova);
    for(int i = 0; i < brojCvorova; i++)
        fwMatrica[i].resize(brojCvorova);


    for(int i = 0; i < brojCvorova; i++)
    {
        for(int j = 0; j < brojCvorova; j++)
        {
            if(i == j)
                fwMatrica[i][j] = 0;
            else
                fwMatrica[i][j] = MAX;
        }
    }
}

void fw(vector<vector<int>>& fwMatrica)
{
    int n = fwMatrica.size();

    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(fwMatrica[i][k] + fwMatrica[k][j] < fwMatrica[i][j])
                {
                    fwMatrica[i][j] = fwMatrica[i][k] + fwMatrica[k][j];
                }
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        if(fwMatrica[i][i] < 0)
        {
            cout << "Negativan ciklus!" << endl;
            return;
        }
    }
}

void stampajMatricu(vector<vector<int>> fwMatrica)
{
    int n = fwMatrica.size();
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << fwMatrica[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int brojCvorova;
    brojCvorova = 4;
    vector<vector<int>> fwMatrica;
    initMatrice(brojCvorova, fwMatrica);

    cout << "Prosao init matrice" << endl;

    dodajGranu(0, 3, 1, fwMatrica);
    dodajGranu(0, 1, 8, fwMatrica);
    dodajGranu(1, 2, 1, fwMatrica);
    dodajGranu(2, 0, 4, fwMatrica);
    dodajGranu(3, 2, 9, fwMatrica);
    dodajGranu(3, 1, 2, fwMatrica);

    cout << "Prosao dodavanje grana" << endl;

    fw(fwMatrica);

    stampajMatricu(fwMatrica);
}