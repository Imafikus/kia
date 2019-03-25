#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void makeSegTreeRec(vector<int> &v, vector<int> &segTree, int left, int right, int k)
{
    if(left == right)
    {
        segTree[k] = v[left];
        return;
    }

    int mid = (left + right) / 2;

    makeSegTreeRec(v, segTree, left, mid, 2 * k);
    makeSegTreeRec(v, segTree, mid + 1, right, 2 * k + 1);

    segTree[k] = segTree[2 * k] + segTree[2 * k + 1];
}

int sumOfRange(vector<int> segTree, int k, int a, int b, int x, int y)
{
    // ceo trenutni niz [x, y] je unutar [a, b]
    if(x >= a  && y <= b)
        return segTree[k];
    
    // [x, y] i [a, b] se uopste ne poklapaju
    if(x > b || y < a)
        return 0;
    
    int mid = (x + y) / 2;
    
    return sumOfRange(segTree, 2 * k, a, b, x, mid) + sumOfRange(segTree, 2 * k + 1, a, b, mid + 1, y); 
    
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = v.size();

    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<int> segTree(size);
    makeSegTreeRec(v, segTree, 0, n-1, 1);

    cout << sumOfRange(segTree, 1, 1, 4, 0, n-1) << endl;
}
