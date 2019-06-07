#include <vector>
#include <iostream>

using namespace std;

double orijentacija(pair<double, double> A, pair<double, double> B, pair<double, double> C)
{
    double orijent = (B.first - A.first) * (C.second - A.second) - (C.first - A.first) * (B.second - A.second);
    return orijent;
}

bool pripadaTrouglu(pair<double, double> A, pair<double, double> B, pair<double, double> C, pair<double, double> T)
{
    double orACT = orijentacija(A, C, T);
    double orCBT = orijentacija(C, B, T);
    double orBAT = orijentacija(B, A, T);

    bool sviNegativni = (orACT <= 0 && orCBT <= 0 && orBAT <= 0);
    bool sviPozitivni = (orACT >= 0 && orCBT >= 0 && orBAT >= 0);

    return(sviNegativni || sviPozitivni);
}

bool pripadaKonveksnomPoligonu(pair<double, double> T, vector<pair<double, double>> konveksniPoligon)
{
    pair<double, double> pivot = konveksniPoligon[0];

    int l = konveksniPoligon.size() - 1;
    int d = 1;

    while(abs(l - d) > 1)
    {
        int mid = (l + d) / 2;

        if(orijentacija(pivot, konveksniPoligon[mid], T) > 0)
            l = mid;
        else
            d = mid;
    }

    return pripadaTrouglu(pivot, konveksniPoligon[l], konveksniPoligon[d], T);

}

template <typename T>
void proveriPripadnost(T tacka, vector<T> konveksniPoligon)
{
    if(pripadaKonveksnomPoligonu(tacka, konveksniPoligon))

        cout << "Tacka pripada nekonveksnom poligonu" << endl;
    else
        cout << "Tacka ne pripada nekonveksnom poligonu" << endl;
}

int main()
{
    pair<double, double> tacka1 = {5, 8};
    pair<double, double> tacka2 = {0.5, 0.5};

    vector<pair<double, double>> konveksniPoligon = {
        {0, 0}, 
        {1, 0}, 
        {1, 1}, 
        {0, 1}
    };

    proveriPripadnost(tacka1, konveksniPoligon);
    proveriPripadnost(tacka2, konveksniPoligon);
}