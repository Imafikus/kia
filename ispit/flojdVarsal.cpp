#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> matricaPovezanosti;

void dodajGranu(int u, int v, int tezina)
{
    matricaPovezanosti[u][v] = tezina;
    matricaPovezanosti[v][u] = tezina;
}

void flojdVarsal()
{
    int brojCvorova = matricaPovezanosti.size();
    for(int m = 0; m < brojCvorova; m++)
    {
        for(int i = 0; i < brojCvorova; i++)
        {
            for(int j = 0; j < brojCvorova; j++)
            {
                if(matricaPovezanosti[i][m] + matricaPovezanosti[m][j] < matricaPovezanosti[i][j])
                {
                    matricaPovezanosti[i][j] = matricaPovezanosti[i][m] + matricaPovezanosti[m][j];
                }
            }
        }
    }

    for(int i = 0; i < brojCvorova; i++)
    {
        if(matricaPovezanosti[i][i] < 0)
        {
            cout << "Negativan ciklus" << endl;
            return;
        }
    }
}

void stampajMatricu()
{
    for(int i = 0; i < matricaPovezanosti.size(); i++)
    {
        for(int j = 0; j < matricaPovezanosti.size(); j++)
        {
            cout << matricaPovezanosti[i][j] << " ";
        }
        cout << endl;
    }
}
void initMatricu()
{
    for(int i = 0; i < matricaPovezanosti.size(); i++)
    {
        for(int j = 0; j < matricaPovezanosti.size(); j++)
        {
            if(i == j)
                matricaPovezanosti[i][j] = 0;
            else
                matricaPovezanosti[i][j] = 100000;
        }
    }
}

int main()
{
    int brojCvorova = 4;
    matricaPovezanosti.resize(brojCvorova);
    for(int i = 0; i < brojCvorova; i++)
    {
        matricaPovezanosti[i].resize(brojCvorova);
    }

    initMatricu();

    dodajGranu(0, 1, -1);
    dodajGranu(0, 3, -1);
    dodajGranu(1, 2, 3);
    dodajGranu(1, 3, -1);
    dodajGranu(2, 3, 2);
    
    stampajMatricu();

    cout << endl;

    flojdVarsal();

    stampajMatricu();

    cout << matricaPovezanosti[0][2] << endl;

}
