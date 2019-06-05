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
    
    bool pripadaTrouglu(vector<double> A, vector<double> B, vector<double> C, vector<double> P)
    {
        double ABP = orijentacija(A, B, P);
        double BCP = orijentacija(B, C, P);
        double CAP = orijentacija(C, A, P);

        if(ABP >= 0 && BCP >= 0 && CAP >= 0)
            return true;
        
        if(ABP <= 0 && BCP <= 0 && CAP <= 0)
            return true;
        
        return false;
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
            
            //? Kako gledamo polupravu koja ide na dole, interesuju nas samo tacke poligona koje su sigurno na istoj ili manjoj visini od A
            //? Ako imamo tacku koja je iznad M1 i M2 po Y i koja je izmedju njih po X onda ona sigurno sece duz M1M2
            if(izmedjuTacaka && A[1] >= max(M1[1], M2[1]))
            {
                brojPreseka++;
            }
        }
        cout << "Broj preseka: " << brojPreseka << endl;
        if(brojPreseka % 2 == 0)
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    bool tackaUnutarKonveksnogPoligona(vector<pair<double, double>> poligon, vector<double> A)
    {
        //? Zakucamo start na neku tacku, prva je najlaksa
        vector<double> start = {poligon[0].first, poligon[0].second};

        //? Pocetne granice su levo i desno od starta (n-1 i 1 tacka)
        //? Binarnom pretragom cemo da smanjujemo na pola nas poligon svaki put
        //? U zavisnosti od orijentacije trougla koji prave start, srednja tacka i A
        int l = poligon.size() - 1;
        int d = 1;

        vector<double> levaTacka = {poligon[l].first, poligon[l].second};
        vector<double> desnaTacka = {poligon[d].first, poligon[d].second};

        while(abs(l - d) > 1)
        {
            int s = (l + d) / 2;
            vector<double> sredina = {poligon[s].first, poligon[s].second};

            //? ako je orijentacija veca od 0, znaci da je tacka desno od [start, sredina] duzi
            if(orijentacija(start, sredina, A) > 0)
            {
                levaTacka = {poligon[s].first, poligon[s].second};
                l = s;
            }
            else
            {
                desnaTacka = {poligon[s].first, poligon[s].second};
                d = s;
            }
        }
        //? Kada zavrsimo sa pretragom imamo start, l i d, i treba da proverimo
        //? da li je nasa tacka unutar tog trougla
        return (pripadaTrouglu(start, levaTacka, desnaTacka, A));

    }

    vector<double> nadjiSkrozLevuTacku(vector<pair<double, double>> skupTacaka)
    {
        pair<double, double> skrozLevo = skupTacaka[0];
        
        for(int i = 1; i < skupTacaka.size(); i++)
        {
            if(skupTacaka[i].first < skrozLevo.first)
            {
                skrozLevo = skupTacaka[i];
            }
            else
            {
                if(skupTacaka[i].first == skrozLevo.first && skupTacaka[i].second < skrozLevo.second)
                skrozLevo = skupTacaka[i];
            }
        }
        return {skrozLevo.first, skrozLevo.second};
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

    vector<double> A = {0.5, 1.5};
  
    std::vector<pair<double, double>> poligon = { {1, 1}, {0, 0}, {0, -1}, {0, 1} };
    
    cout << "Skroz leva tacka" << endl;
    stampajVektor(g.nadjiSkrozLevuTacku(poligon));
    
    // if(g.tackaUnutarNekonveksnogPoligona(poligon, A))
    // {
    //     cout << "Tacka pripada" << endl;
    // }
    // else
    // {
    //     cout << "Tacka ne pripada" << endl;
    // }
}