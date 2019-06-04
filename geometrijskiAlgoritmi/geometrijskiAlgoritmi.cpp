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

    bool tackaUnutarNekonveksnogPoligona(vector<pair<double, double>> poligon, vector<double> A)
    {
        int brojPreseka = 0;

        int n = poligon.size();
        for(int i = 0; i < n; i++)
        {
            //? ovo se radi da, umesto da odemo van niza da, se vratimo na 0ti element
            int j = (i + 1) % n;

            vector<double> M1 = {poligon[i].first, poligon[i].second};
            vector<double> M2 = {poligon[j].first, poligon[j].second};

            //? proveravamo da li je A izmedju M1 i M2 u odnosu na X osu
            bool izmedjuTacaka = (A[0] > min(M1[0], M2[0]) && A[0] < max(M1[0], M2[0]));
            
            // cout << "izmedjuTacaka: " << izmedjuTacaka << endl;
            // cout << "Tacke: " << M1[0] << " " << M1[1] << "   " << M2[0] << " " << M2[1] << endl;
            // cout << endl;
            //? Ovo je tacka koja je na istoj X kkordinati kao A, ali je sigurno ispod M1 i M2
            if(izmedjuTacaka && A[1] > max(M1[1], M2[1]))
            {
                //? uzimamo A1 tako da ima X koordinatu kao A, a da joj Y koordinata sigurno bude manja od manje koordinate M1 i M2
                vector<double> A1 = {A[0], min(M1[1], M2[1]) - 1};
                // cout << "A1: " << A1[0] << " " << A1[1] << endl;
                
                double orM1 = orijentacija(A, A1, M1);
                double orM2 = orijentacija(A, A1, M2);
            
                // cout << "orM1: " << orM1 << endl;
                // cout << "orM2: " << orM2 << endl; 
                // cout << endl;

                //? ako ovo vazi znamo da su tacke sa razlicitih strana duzi koja ce, te ovo znaci da imamo presek sa tom duzi
                if(orM1 != orM2)
                    brojPreseka++;
            }
        }
        // cout << "Broj preseka: " << brojPreseka << endl;
        if(brojPreseka % 2 == 0)
        {
            return false;
        }
        else 
        {
            return true;
        }
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
    vector<pair<double, double>> Poligon = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
    vector<double> A = {2, 2};
    
    
    if(g.tackaUnutarNekonveksnogPoligona(Poligon, A))
    {
        cout << "Tacka unutar poligona" << endl;
    }
    else
    {
        cout << "Tacka nije unutar poligona" << endl;
    }
}