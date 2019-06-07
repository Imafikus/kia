#include <cmath>
#include<vector>
#include <iostream>

using namespace std;

void napraviSegmentnoStablo(vector<int> niz, vector<int> &stablo, int l, int d, int k)
{
    if(l == d)
    {
        stablo[k] = niz[l];
        return;
    }

    int mid = (l + d) / 2;
    napraviSegmentnoStablo(niz, stablo, l, mid, 2 * k);
    napraviSegmentnoStablo(niz, stablo, mid + 1, d, 2 * k + 1);

    stablo[k] = stablo[2 * k] + stablo[2 * k + 1];

}

void stampajVektor(vector<int> v)
{
    for(int e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> pocetniNiz = {1, 2, 3, 4, 5, 6, 7, 8};
    int visinaStabla = ceil(log2(pocetniNiz.size())) + 1;

    int velicinStabla = pow(2, visinaStabla);
    vector<int> segmentnoStablo(velicinStabla);

    napraviSegmentnoStablo(pocetniNiz, segmentnoStablo, 0, pocetniNiz.size()-1, 1);

    stampajVektor(segmentnoStablo);

}