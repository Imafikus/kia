#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std; 

void tarjan(int cvor, int& id, stack<int>& slcStack, vector<vector<int>>& ls, vector<bool>& posecen, vector<int>& lowLink, vector<int>& ids, vector<bool>& uSteku)
{
    posecen[cvor] = true;
    lowLink[cvor] = id;
    ids[cvor] = id;
    id++;

    slcStack.push(cvor);
    uSteku[cvor] = true;

    for(int sused : ls[cvor])
    {
        if(!posecen[sused])
            tarjan(sused, id, slcStack, ls, posecen, lowLink, ids, uSteku);
        
        if(uSteku[sused])
            lowLink[cvor] = min(lowLink[cvor], lowLink[sused]);
    }

    if(ids[cvor] == lowLink[cvor])
    {
        while(true)
        {
            int deoKomp = slcStack.top();
            slcStack.pop();
            uSteku[deoKomp] = false;
            cout << deoKomp << endl;

            if(cvor == deoKomp)
            {
                cout << endl;
                break;
            }
        }
    }
}

void mostovi(int cvor, vector<vector<int>>& ls, vector<int>& ids, vector<int>& lowLink, vector<bool>& posecen, int& id, vector<int>& roditelj)
{
    posecen[cvor] = true;
    ids[cvor] = id;
    lowLink[cvor] = id;
    id++;

    for(int sused : ls[cvor])
    {
        if(!posecen[sused])
        {
            posecen[sused] = true;
            roditelj[sused] = cvor;
            mostovi(sused, ls, ids, lowLink, posecen, id, roditelj);

            lowLink[cvor] = min(lowLink[sused], lowLink[cvor]);
            
            if(ids[cvor] < lowLink[sused])
                cout << cvor << " " << sused << endl;
        }
        else if(sused != roditelj[cvor])
            lowLink[cvor] = min(lowLink[sused], lowLink[cvor]);
    }
}
void dodajGranu(int u, int v, vector<vector<int>>& ls)
{
    ls[u].push_back(v);
}

void reset(int brojCvorova, int brojGrana, vector<bool>& posecen, vector<int>& lowLink, vector<int>& ids, vector<bool>& uSteku, vector<int>& roditelj)
{
    posecen.resize(brojCvorova, false);
    lowLink.resize(brojCvorova);
    ids.resize(brojCvorova);
    uSteku.resize(brojCvorova, false);
    roditelj.resize(brojCvorova, -1);
}

int main()
{
    int brojCvorova, brojGrana;
    cin >> brojCvorova >> brojGrana;

    vector<vector<int>> ls(brojCvorova);
    vector<bool> posecen(brojCvorova, false);
    vector<int> lowLink(brojCvorova);
    vector<int> ids(brojCvorova);
    vector<bool> uSteku(brojCvorova, false);
    vector<int> roditelj(brojCvorova, -1);

    for(int i = 0; i < brojGrana; i++)
    {
        int u, v;
        cin >> u >> v;
        dodajGranu(u, v, ls);

    }

    cout << "Prosao dodavanje grane" << endl;
    int id = 0;
    stack<int> slcStack;
    tarjan(0, id, slcStack, ls, posecen, lowLink, ids, uSteku);

    // int id = 0;
    // reset(brojCvorova, brojGrana, ls, posecen, lowLink, ids, uSteku);
    // mostovi(0, ls, ids, lowLink, posecen, id, roditelj);



}