#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void makeSegmentTree(vector<int> &startingVector, vector<int> &segmentTree, int startingSize)
{
    copy_n(startingVector.begin(), startingSize, segmentTree.begin() + startingSize);

    for(int k = startingSize - 1; k >= 1; k--)
        segmentTree[k] = segmentTree[2 * k] + segmentTree[2 * k + 1];
}

void makeSegmentTreeRec(vector<int> &startingVector, vector<int> &segmentTree, int pos, int left, int right)
{
    if(left == right)
    {
        segmentTree[pos] = startingVector[left];
        return;
    }

    int mid = (left + right) / 2;

    makeSegmentTreeRec(startingVector, segmentTree, 2 * pos, left, mid);
    makeSegmentTreeRec(startingVector, segmentTree, 2 * pos + 1, mid + 1, right);

    segmentTree[pos] = segmentTree[2 * pos] + segmentTree[2 * pos + 1];
}

int sumOfSegment(vector<int> &segmentTree, int x, int y, int start, int end, int k)
{
    if(x > end || y < start)
        return 0;
    
    if(x >= start && y <= end)
        return segmentTree[k];
    
    int mid = (x + y) / 2;

    return sumOfSegment(segmentTree, x, mid, start, end, 2 * k) + sumOfSegment(segmentTree, mid + 1, y, start, end, 2 * k + 1); 

}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = v.size();

    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<int> segmentTree(size);
    vector<int> segmentTreeRec(size);
    
    makeSegmentTreeRec(v, segmentTreeRec, 1, 0, n-1);

    cout << sumOfSegment(segmentTreeRec, 0, n-1, 0, 7, 1) << endl;
}