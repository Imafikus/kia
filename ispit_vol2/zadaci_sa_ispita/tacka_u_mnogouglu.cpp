#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Tacka
{
public:
    
    int x;
    int y;

    Tacka(){}

    Tacka(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void toString()
    {
        cout << x << " " << y << endl;
    }
};

Tacka pivot;

int nadjiSkrozLevuTacku(vector<Tacka> sveTacke)
{
    int idx = 0;
    int min_x = sveTacke[0].x;
    int min_y = sveTacke[0].y;

    for(int i = 1; i < sveTacke.size(); i++)
    {
        if(sveTacke[i].x < min_x)
        {
            min_x = sveTacke[i].x;
            min_y = sveTacke[i].y;
            idx = i;
        }
        else if(sveTacke[i].x == min_x && sveTacke[i].y < min_y)
        {
            min_x = sveTacke[i].x;
            min_y = sveTacke[i].y;
            idx = i;
        }
    }
    return idx;
}

int orijent(Tacka A, Tacka B, Tacka C)
{
    int ABx = B.x - A.x;
    int ABy = B.y - A.y;

    int ACx = C.x - A.x;
    int ACy = C.y - A.y;

    int det = (ABx * ACy) - (ABy * ACx);

    if(det > 0)
        return 1;
    
    if(det < 0)
        return -1;
    
    if(det == 0)
        return 0;
}

int kvadratRastojanja(Tacka A, Tacka B)
{
    int d = (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
    return d;
}

bool cmp(Tacka A, Tacka B)
{
    int o = orijent(pivot, A, B);

    if(o == 1)
        return true;
    if(o == -1)
        return false;
    
    return (kvadratRastojanja(pivot, A) <= kvadratRastojanja(pivot, B));
}

vector<Tacka> convexHull(vector<Tacka> sveTacke)
{
    int ex = nadjiSkrozLevuTacku(sveTacke);
    swap(sveTacke[0], sveTacke[ex]);
    
    pivot = sveTacke[0];
    cout << "Skroz leva tacka" << endl;
    pivot.toString();

    sort(sveTacke.begin() + 1, sveTacke.end(), cmp);
    cout << "Sortiranje tacke" << endl;
    for(Tacka t : sveTacke)
        t.toString();
    

    vector<Tacka> poligon;
    poligon.push_back(sveTacke[0]);
    poligon.push_back(sveTacke[1]);
    poligon.push_back(sveTacke[2]);

    int m = 2;
    for(int i = 3; i < sveTacke.size(); i++)
    {
        while(orijent(poligon[m - 1], poligon[m], sveTacke[i]) == -1)
        {
            poligon.pop_back();
            m--;
        }
        m++;
        poligon.push_back(sveTacke[i]);
    }

    return poligon;

}

bool pripadaTrouglu(Tacka A, Tacka B, Tacka C, Tacka T)
{
    int o1 = orijent(A, B, T);
    int o2 = orijent(B, C, T);
    int o3 = orijent(C, A, T);

    if(o1 >= 0 && o2 >= 0 && o3 >= 0)
        return true;

    if(o1 <= 0 && o2 <= 0 && o3 <= 0)
        return true;
    
    return false;
}

bool tackaPripada(Tacka t, vector<Tacka> poligon)
{
    Tacka pivot = poligon[0];
    int l = poligon.size() - 1;
    int d = 1;

    while(abs(l - d) > 1)
    {
        int mid = (l + d) / 2;
        if(orijent(pivot, poligon[mid], t) == 1)
            d = mid;
        else
            l = mid;
    }

    return pripadaTrouglu(pivot, poligon[l] , poligon[d], t);
}

bool pripadaNekonveksom(Tacka T, vector<Tacka> sveTacke)
{
    int brojPreseka = 0;
    for(int i = 0; i < sveTacke.size(); i++)
    {
        int j = (i + 1) % sveTacke.size();

        Tacka A = sveTacke[i];
        Tacka B = sveTacke[j];

        bool izmedjuX = (min(A.x, B.x) <= T.x && T.x <= max(A.x, B.x));
        bool iznadPoY = (T.y > max(A.y, B.y));

        if(izmedjuX && iznadPoY)
            brojPreseka++;
    }
    return (brojPreseka % 2 == 1);
}

int main()
{
    int brojTacaka;
    cin >> brojTacaka;

    vector<Tacka> sveTacke;

    for(int i = 0; i < brojTacaka; i++)
    {
        int x, y;
        cin >> x >> y;

        sveTacke.push_back(Tacka(x, y));
    }

    vector<Tacka> poligon = convexHull(sveTacke);
    cout << " poligon " << endl;
    for(Tacka t : poligon)
        t.toString();
    

    int x, y;
    cin >> x >> y;

    if(tackaPripada(Tacka(x, y), poligon))
        cout << "Tacka pripada konveksnom poligonu" << endl;
    else 
        cout << "Tacka ne pripada konveksnom poligonu" << endl;

    if(pripadaNekonveksom(Tacka(x, y), sveTacke))
        cout << "Tacka pripada nekonveksnom poligonu" << endl;
    else 
        cout << "Tacka ne pripada nekonveksnom poligonu" << endl;

    
}