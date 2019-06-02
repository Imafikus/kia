#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Geometrija
{
public:

    int skalarniProizvod(vector<double> a, vector<double> b)
    {
        double sp = 0;
        for(int i = 0; i < a.size(); i++)
        {
            sp += a[i] * b[i];
        }
        return sp;
    }
    
    double intenzitet(vector<double> a)
    {
        double it = 0;
        for(int e : a)
        {
            it += e*e;
        }
        return sqrt(it);
    }

    double ugaoIzmedju(vector<double> a, vector<double> b)
    {
        return acos(skalarniProizvod(a, b) / (intenzitet(a) * intenzitet(b)) );
    }

    vector<double> vektorskiProizvod3d(vector<double> a, vector<double> b)
    {
        vector<double> p(3);
        p[0] = a[1] * b[2] - a[2] * b[1];
        p[1] = a[2] * b[0] - a[0] * b[2];
        p[2] = a[0] * b[1] - a[1] * b[0];

        return p;
    }

    void dekartPolarne(vector<double> a, double& r, double& fi)
    {
        r = sqrt(a[0] * a[0] + a[1] * a[1]);
        fi = atan(a[1] / a[0]);
    }

    vector<double> polarneDekart(double r, double fi)
    {
        vector<double> a(2);
        a[0] = r * cos(fi);
        a[1] = r * sin(fi);

        return a;
    }


    double povrsinaTrouglaHeron(vector<double> a, vector<double> b, vector<double> c)
    {
        double _a = intenzitet(a);
        double _b = intenzitet(b);
        double _c = intenzitet(c);

        double s = (_a + _b + _c) / 2;
        
        double p = sqrt(s * (s - _a) * (s - _b) * (s - _c));
        return p;
    }

    double povrsinaTrouglaVektorskiProizvod(vector<double> a, vector<double> c)
    {
        vector<double> ab = {a[0], a[1], 0}; 
        vector<double> ac = {c[0], c[1], 0};

        return intenzitet(vektorskiProizvod3d(ab, ac)) / 2;
    }

    double povrsinaTrouglaPertle(vector<double> a, vector<double> b, vector<double> c)
    {
        double p = (a[0] * b[1] + b[0] * c[1] + c[0] * a[1]) - (a[0] * c[1] + c[0] * b[1] + b[0] * a[1]);
        return p / 2;
    }

    bool kolinearneTacke(vector<double> A, vector<double> B, vector<double> C)
    {
        //? Tacke ce biti jednake ako je k za AB i k za AC jednako
        double kAB = (B[1] - A[1]) / (B[0] - A[0]);
        double kAC = (C[1] - A[1]) / (C[0] - A[0]);

        return (kAB == kAC);
    }

    double orijentacija(vector<double> A, vector<double> B, vector<double> C)
    {
        double ax = A[0]; double ay = A[1];
        double bx = B[0]; double by = B[1];
        double cx = C[0]; double cy = C[1];

        double d = (bx - ax) * (cy - ay) - (cx - ax) * (by - ay);
        return d;
    }
private:

};


void stampajVektor(vector<int> a)
{
    for(int e : a)
    {
        cout << e << " ";
    }
    cout << endl;
}

void stampajVektor(vector<double> a)
{
    for(double e : a)
    {
        cout << e << " ";
    }
    cout << endl;
}


int main()
{
    Geometrija g = Geometrija();
    vector<double> a = {0, 0};
    vector<double> b = {1, 0};
    vector<double> c = {0, 1};

    double d = g.orijentacija(a, b, c);
    cout << d << endl;

    if (d > 0)
    {
        cout << "Pozitivna orijentacija" << endl;
    } 
    else if (d < 0)
    {
        cout << "Negativna orijentacija" << endl;
    }
    else
    {
        cout << "Kolinearne tacke" << endl;
    }
}