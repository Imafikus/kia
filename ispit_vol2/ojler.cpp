#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

void dodajGranu(int u, int v, vector<vector<int>> &ls)
{
    ls[u].push_back(v);
    ls[v].push_back(u);
}

void ispisiOjlerovCiklus(vector<vector<int>> ls)
{
    stack<int> tekuciCvor;
    tekuciCvor.push(0);

    while(!tekuciCvor.empty())
    {
        int trCvor = tekuciCvor.top();
        tekuciCvor.pop();

        if(!ls[trCvor].empty())
        {
            int sledeciCvor = ls[trCvor].back();
            ls[trCvor].pop_back();
            cout << trCvor << " " << sledeciCvor << endl;
            tekuciCvor.push(sledeciCvor);
        }
    } 
}

int main()
{
    int brojCvorova;
    cin >> brojCvorova;
    
    int brojGrana;
    cin >> brojGrana;

    vector<vector<int>> ls(brojCvorova);

    for(int i = 0; i < brojGrana; i++)
    {
        int u, v;
        cin >> u >> v;
        dodajGranu(u, v, ls);
    }

    ispisiOjlerovCiklus(ls);
    
}