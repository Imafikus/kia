#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template <typename T>
void stampajStek(stack<T> s)
{
    while(!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}


void topSort(int cvor, vector<vector<int>> listaPovezanosti, vector<bool>& posecen, stack<int>& ts)
{
    posecen[cvor] = true;
    for(int sused : listaPovezanosti[cvor])
    {
        if(!posecen[sused])
        {
            topSort(sused, listaPovezanosti, posecen, ts);
        }
    }

    ts.push(cvor);
}

int main()
{
    vector<vector<int>> listaPovezanosti = {{1, 3, 4}, {2}, {}, {2}, {5}, {}};
    vector<bool> posecen(listaPovezanosti.size(), false);

    stack<int> ts;
    topSort(0, listaPovezanosti, posecen, ts);
    stampajStek(ts);
}