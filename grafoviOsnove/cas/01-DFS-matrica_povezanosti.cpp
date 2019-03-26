#include <iostream>
#include <vector>
using namespace std;

void DFS(vector<vector<int> > &matrica, vector<bool> &oznaceni, int cvor)
{
    oznaceni[cvor] = true;
    cout << cvor << " ";

    for(int j = 0; j < matrica[cvor].size(); j++)
        if(matrica[cvor][j] != 0 && oznaceni[j] == false)
            DFS(matrica, oznaceni, j);
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int> > matrica(n);
    vector<bool> oznaceni(n);

    for(int i = 0; i < n; i++)
        oznaceni[i] = false;

    for(int i = 0; i < n; i++)
    {
        matrica[i].resize(n);
        for(int j = 0; j < n; j++)
            cin >> matrica[i][j];
    }

    DFS(matrica, oznaceni, 0);

}
