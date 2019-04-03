#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

void napraviSegmentnoStablo(vector<int> pocetniNiz, vector<int> &segmentnoStablo, int levo, int desno, int k)
{
    //? Ovo je ako smo zaboli skroz do listova
    if(levo == desno)
    {
        //? moze da bude i desno, nebitno
        segmentnoStablo[k] = pocetniNiz[levo];
        return;
    }

    int mid = (levo + desno) / 2;

    napraviSegmentnoStablo(pocetniNiz, segmentnoStablo, levo, mid, 2 * k);
    napraviSegmentnoStablo(pocetniNiz, segmentnoStablo, mid + 1, desno, 2 * k + 1);

    segmentnoStablo[k] = segmentnoStablo[2 * k] + segmentnoStablo[2 * k + 1];
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    int brojElemenataNiza = v.size();

    int visinaStabla = ceil(log2(brojElemenataNiza));

    int velicinaStabla = 2 * pow(2, visinaStabla);
    vector<int> segmentnoStablo(velicinaStabla);

    napraviSegmentnoStablo(v, segmentnoStablo, 0, brojElemenataNiza-1, 1);

    for(int e : segmentnoStablo)
        cout << e << " ";
    cout << endl;
}