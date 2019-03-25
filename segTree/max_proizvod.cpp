#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

struct Node
{
    int largest;
    int second_largest;
};

void buildSegTree(vector<int> v, vector<Node> &segTree, int k, int left, int right)
{
    if(left == right)
    {
        segTree[k].largest = v[left];
        segTree[k].second_largest = INT_MIN;
        return;
    }

    int mid = (left + right) / 2;

    buildSegTree(v, segTree, 2 * k, left, mid);
    buildSegTree(v, segTree, 2 * k + 1, mid + 1, right);

    segTree[k].largest = max(segTree[2 * k].largest, segTree[2 * k + 1].largest);
    segTree[k].second_largest = min( max(segTree[2 * k].largest, segTree[2 * k + 1].second_largest),
                                     max(segTree[2 * k].second_largest, segTree[2 * k + 1].largest));
}
int main() 
{

}