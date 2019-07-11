#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Tacka
{
public:

    int x;
    int y;

    Tacka(){};
    
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

int nadjiDoleLevo(vector<Tacka> sveTacke)
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

    int d = (ABx * ACy) - (ABy * ACx);

    if(d > 0)
        return 1;
    if(d < 0)
        return -1;
    if(d == 0)
        return 0;
}

int kvadratRastojanja(Tacka A, Tacka B)
{
    int d = (A.x - B.x) * (A.x - B.x) - (A.y - B.y) * (A.y - B.y);
    return d;
}


bool cmp(Tacka A, Tacka B)
{
    int o = orijent(pivot, A, B);
    
    if(o == 1)
        return false;
    
    if(o == -1)
        return true;
    
    return (kvadratRastojanja(pivot, A) <= kvadratRastojanja(pivot, B));
}

vector<Tacka> convexHull(vector<Tacka> sveTacke)
{
    int ekstrem = nadjiDoleLevo(sveTacke);
    swap(sveTacke[0], sveTacke[ekstrem]);
    pivot = sveTacke[0];
    cout << "Skroz leva tacka" << endl;
    pivot.toString();

    sort(sveTacke.begin() + 1,  sveTacke.end(), cmp);

    cout << "SORTIRANE TACKE" << endl;
    for(Tacka t : sveTacke)
        t.toString();
    // return {};

    vector<Tacka> poligon;
    poligon.push_back(sveTacke[0]);
    poligon.push_back(sveTacke[1]);
    poligon.push_back(sveTacke[2]);

    int m = 2;

    for(int i = 3; i < sveTacke.size(); i++)
    {
        while(orijent(poligon[m - 1], poligon[m], sveTacke[i]) == 1)
        {
            poligon.pop_back();
            m--;
        }
        poligon.push_back(sveTacke[i]);
        m++;
    }
    return poligon;

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
    
    cout << "Poligon: " << endl;
    for(Tacka t : poligon)
    {
        t.toString();
    }
}