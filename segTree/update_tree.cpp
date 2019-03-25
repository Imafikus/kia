#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

void buildSegTree(const vector<int> &v, vector<int> &segTree, int k, int left, int right)
{
    if(left == right)
    {
        segTree[k] = v[right];
        return;
    }

    int mid = (left + right) / 2;
    buildSegTree(v, segTree, 2 * k, left, mid);
    buildSegTree(v, segTree, 2 * k + 1, mid + 1, right);

    segTree[k] = segTree[2 * k] + segTree[2 * k + 1];
}
void updateTree(vector<int> &segTree, int k, int left, int right, int changed_pos, int new_val)
{
    if(left == right)
    {
        segTree[k] = new_val;
        return;
    }

    int mid = (left + right) / 2;
    if(changed_pos <= mid)// bitan je <= znak
        updateTree(segTree, 2 * k, left, mid, changed_pos, new_val);
    else
        updateTree(segTree, 2 * k + 1, mid + 1, right, changed_pos, new_val);

    segTree[k] = segTree[2 * k] + segTree[2 * k + 1];
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = v.size();

    int update_pos = 1;
    int update_value = 10;

    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<int> segTree(size);
    buildSegTree(v, segTree, 1, 0, n-1);
    updateTree(segTree, 1, 0, n-1, update_pos, update_value);

    for(int e : segTree)
        cout << e <<  " ";
    cout << endl;
}