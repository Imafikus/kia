#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

bool prost(int b)
{
    for(int i = 2; i < sqrt(b) + 1; i++)
    {
        if(b % i == 0) return false;
    }
    return true;
}
void buildSeg(const vector<int> &v, vector<int> &segTree, int k, int left, int right)
{
    if(left == right)
    {
        segTree[k] = v[right];
        return;
    }

    int mid = (left + right) / 2;

    buildSeg(v, segTree, 2 * k, left, mid);
    buildSeg(v, segTree, 2 * k + 1, mid + 1, right);

    segTree[k] = segTree[2 * k] + segTree[2 * k + 1];
}

void buildSegTree(const vector<int> &v, vector<int> &segTree, int k, int left, int right, unordered_map<int, bool> prosti)
{
    if(left == right)
    {
        segTree[k] = prosti[k];
        return;
    }

    int mid = (left + right) / 2;
    buildSegTree(v, segTree,2 * k, left, mid, prosti);
    buildSegTree(v, segTree,2 * k + 1, mid + 1, right, prosti);

    segTree[k] = segTree[2 * k] + segTree[2 * k + 1];
}

#define MAX 25

int main()
{
    unordered_map<int, bool> prosti;
    prosti[1] = true;
    
    for(int i = 2; i < MAX; i++)
        prosti[i] = prost(i);
    
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    
    int n = v.size();

    int height = ceil(log2(n));
    int size = pow(2, height) * 2;

    vector<int> segT(size);
    buildSeg(v, segT, 1, 0, n-1);

    for(int e : segT)
    {
        cout << e << " ";
    }
    cout << endl;

    vector<int> segTree(size);
    buildSegTree(v, segTree, 1, 0, n-1, prosti);

    for(int e : segTree)
    {
        cout << e << " ";
     //   e ? cout << "prost je\n" : cout << "nije prost\n";
    }
    cout << endl;
}