#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct cmp
{
    bool operator()(pair<int, int> p1, pair<int, int> p2)
    {
        return p1.second > p2.second;
    }
};

vector<vector<pair<int, int>>> listaSuseda;
vector<int> udaljenost;
vector<int> roditelj;
vector<bool> postojiPut;

void dijkstra(int start, int end)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heap;
    
    udaljenost[start] = 0;

    heap.push({start, udaljenost[start]});

    while(!heap.empty())
    {
        pair<int, int> cvor = heap.top();
        heap.pop();

        if(postojiPut[cvor.first])
            continue;
        
        postojiPut[cvor.first] = true;

        for(pair<int, int> sused : listaSuseda[cvor.first])
        {
            if(udaljenost[cvor.first] + sused.second <= udaljenost[sused.first])
            {
                udaljenost[sused.first] = udaljenost[cvor.first] + sused.second;
                
                roditelj[sused.first] = cvor.first;

                heap.push({sused.first, udaljenost[sused.first]});
            }
        }
    }

    for(int put = end; put != -1; put = roditelj[put])
    {
        cout << put << " ";
    }
    cout << endl;
}

int main()
{
    listaSuseda = {
        {{1, 2}, {3, 4}},
        {{0, 2}, {2, 1}},
        {{1, 1}, {3, 3}},
        {{0, 4}, {2, 3}}
    };
    udaljenost.resize(listaSuseda.size(), 100000);
    postojiPut.resize(listaSuseda.size(), false);
    roditelj.resize(listaSuseda.size(), -1);

    dijkstra(0, 2);

}

