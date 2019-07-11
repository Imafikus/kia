#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct cmp
{
    bool operator()(pair<int, int> p1, pair<int ,int> p2)
    {
        return(p1.second > p2.second);
    }
};

void dijkstra(int start, int end, vector<vector<pair<int, int>>> ls, vector<int> udaljenost, vector<int> roditelj, vector<bool> postojiPut)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heap;
    udaljenost[start] = 0;
    heap.push({start, udaljenost[start]});

    while(!heap.empty())
    {
        pair<int, int> cvor = heap.top();
        heap.pop();

        if(postojiPut[cvor.first]) continue;
        postojiPut[cvor.first] = true;

        for(pair<int, int> sused : ls[cvor.first])
        {
            if(udaljenost[cvor.first] + sused.second <= udaljenost[sused.first])
            {
                udaljenost[sused.first] = udaljenost[cvor.first] + sused.second;
                roditelj[sused.first] = cvor.first;
                heap.push({sused.first, udaljenost[sused.first]});
            }
        }
    }

    cout << "Najkraci put izmedju " << start << " i " << end << endl; 
    for(int cvor = end; cvor != -1; cvor = roditelj[cvor])
    {
        cout << cvor << endl;
    }
}

int main()
{
    vector<vector<pair<int, int>>> listaSuseda = 
    {
        {{1, 7}, {5, 14}, {2, 9}},
        {{2, 10}, {3, 15}},
        {{5, 2}, {3, 11}},
        {{4, 6}},
        {{}},
        {{4, 9}}
    };
    int brojCvorova = listaSuseda.size();

    int start = 0;
    for(int end = 1; end < brojCvorova; end++)
    {
        vector<int> udaljenost(brojCvorova, 100000);
        vector<int> roditelj(brojCvorova, -1);
        vector<bool> postojiPut(brojCvorova, false);

        dijkstra(start, end, listaSuseda, udaljenost, roditelj, postojiPut);
    }

}