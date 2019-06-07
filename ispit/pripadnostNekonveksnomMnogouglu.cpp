#include <vector>
#include <iostream>

using namespace std;

template <typename Tacka>
bool pripadaNekonveksnomPoligonu(Tacka T, vector<Tacka> nekonveksniPoligon)
{
    int brojPreseka = 0;
    int brojTacaka = nekonveksniPoligon.size();

    for(int i = 0; i < brojTacaka; i++)
    {
        int j = (i + 1) % brojTacaka;

        Tacka P1 = nekonveksniPoligon[i];
        Tacka P2 = nekonveksniPoligon[j];

        if(
            T.first > min(P1.first, P2.first) && T.first < max(P1.first, P2.first)
            && T.second >= max(P1.second, P2.second)
        )
        {
            brojPreseka++;
        }
    }
    cout << "Broj preseka: " << brojPreseka << endl;
    return (brojPreseka % 2 != 0);
}
template <typename T>
void proveriPripadnost(T tacka, vector<T> nekonveksniPoligon)
{
    if(pripadaNekonveksnomPoligonu(tacka, nekonveksniPoligon))

        cout << "Tacka pripada nekonveksnom poligonu" << endl;
    else
        cout << "Tacka ne pripada nekonveksnom poligonu" << endl;
}

int main()
{
    pair<double, double> tacka1 = {5, 8};
    pair<double, double> tacka2 = {-5, -8};

    vector<pair<double, double>> nekonveksniPoligon = {
        {0, 0}, 
        {10, 1}, 
        {12, 12}, 
        {2, 10}
    };

    proveriPripadnost(tacka1, nekonveksniPoligon);
    proveriPripadnost(tacka2, nekonveksniPoligon);
}