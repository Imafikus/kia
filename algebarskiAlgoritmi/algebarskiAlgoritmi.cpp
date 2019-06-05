#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

const int MAX = 1000;

void stampajVektor(vector<int> v);


vector<int> rastaviNaProsteCinioce(int n)
{
    vector<int> p;
    
    //? sve parne mozemo da izbacimo tako sto delimo sa 2
    while(n % 2 == 0)
    {
        p.push_back(2);
        n = n / 2;
    }

    //? Proveravamo sve neparne
    for(int i = 3; i < sqrt(n); i+= 2)
    {
        while(n % i == 0)
        {
            p.push_back(i);
            n = n / i;
        }
    }

    //? Ako imamo nesto vece od 2, to je sigurno prosto
    if(n > 2)
    {
        p.push_back(n);
    }

    return p;
}

vector<int> rastaviNaProsteCinioceEratosten(int n)
{
    vector<int> najmanjiCinilac(MAX);
    for(int i = 1; i < MAX; i++)
    {
        najmanjiCinilac[i] = i;
    }

    for(int d = 2; d*d < MAX; d++)
    {
        //? Ovo znaci da je d prost, i da hocemo da azuriramo sve umnoske ovog broja tako da im najmanji cinilac bude upravo d
        if(najmanjiCinilac[d] == d)
        {
            for(int i = d + d; i <= MAX; i += d)
            {
                //? Ako nismo pre ovoga dirali najmanji cinilac nekog broja, hocemo da menjamo
                if(najmanjiCinilac[i] == i)
                {
                    najmanjiCinilac[i] = d;
                }
            }
        }
    }
    cout << "Izasao iz velike petlje" << endl;
    vector<int> prostiCinioci;
    while(n != 1)
    {
        prostiCinioci.push_back(najmanjiCinilac[n]);
        n = n / najmanjiCinilac[n];
    }
    return prostiCinioci;
}

int nzdProsireni(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;

    int nzd = nzdProsireni(b, a%b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return nzd;
}

int main()
{
    vector<int> prostiCinioci1 = rastaviNaProsteCinioce(140);
    stampajVektor(prostiCinioci1);

    vector<int> prostiCinioci2 = rastaviNaProsteCinioceEratosten(140);
    stampajVektor(prostiCinioci2);

    int a = 30;
    int b = 12;

    int x;
    int y;

    int d = nzdProsireni(a, b, x, y);
    cout << d << " = "<< x << " * "<< a << " + " << y << " * " << b << endl;;

}

void stampajVektor(vector<int> v)
{
    for(int e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}