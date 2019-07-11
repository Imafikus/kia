#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;


class Tacka
{
public:
    int x;
    int y;
    bool jeKuca;

    Tacka() {}

    Tacka(int x, int y, bool jeKuca)
    {
        this->x = x;
        this->y = y;
        this->jeKuca = jeKuca;
    }    

    void toString()
    {
        cout << x << " " << y << endl;
    }
};

Tacka pivot = Tacka();

int findExtremePoint(vector<Tacka> sveTacke)
{
    int min_x = sveTacke[0].x;
    int min_y = sveTacke[0].y;

    int idx = 0;

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
            idx = 1;
        }
    }
}

int orijent(Tacka A, Tacka B, Tacka C)
{
    int ABx = B.x - A.x;
    int ABy = B.y - A.y;

    int ACx = C.x - A.x;
    int ACy = C.y - A.y;

    int det = ABx * ACy - ACx * ABy;
    
    if(det > 0)
        return 1;

    if(det < 0)
        return -1;
    
    return det;
}

int udaljenostKvadrat(Tacka A, Tacka B)
{
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

bool cmp(Tacka A, Tacka B)
{
    int o = orijent(pivot, A, B);

    if(o == 1)
        return true;
    
    else if(o == -1)
        return false;
    
    else return (udaljenostKvadrat(pivot, A) <= udaljenostKvadrat(pivot, B));
}

vector<Tacka> convexHull(vector<Tacka> sveTacke)
{
    int indeksEkstremne = findExtremePoint(sveTacke);
    swap(sveTacke[0], sveTacke[indeksEkstremne]);
    pivot = sveTacke[0];
    cout << "Ekstremna tacka: ";
    pivot.toString();

    sort(sveTacke.begin() + 1, sveTacke.end(), cmp);
    cout << "Sve tacke sortirane" << endl;
    for(Tacka t : sveTacke)
    {
        t.toString();
    }

    int m = 2;
    vector<Tacka> res;
    res.push_back(sveTacke[0]);
    res.push_back(sveTacke[1]);
    res.push_back(sveTacke[2]);

    for(int i = 3; i < sveTacke.size(); i++)
    {
        cout << "Tacke koje se trenutno gledaju" << endl;
        res[m-1].toString();
        res[m].toString();
        sveTacke[i].toString();
        cout << endl;

        while(orijent(res[m - 1], res[m], sveTacke[i]) == -1)
        {
            res.pop_back();
            m--;
        }
        m++;
        res.push_back(sveTacke[i]);
    }

    return res;
}

int main()
{
    int brojStubova, brojKuca;
    cin >> brojStubova >> brojKuca;

    vector<Tacka> sveTacke;

    for(int i = 0; i < brojStubova; i++)
    {
        int x, y;
        cin >> x >> y;
        sveTacke.push_back(Tacka(x, y, false));
    }

    for(int i = 0; i < brojKuca; i++)
    {
        int x, y;
        cin >> x >> y;
        sveTacke.push_back(Tacka(x, y, true));
    }

    vector<Tacka> omotac = convexHull(sveTacke);

    cout << "OMOTAC: " << endl;
    for(Tacka t : omotac)
    {
        // t.toString();
        if(t.jeKuca)
        {
            cout << "NE" << endl;
            return 0;
        }
    }
    cout << "DA" << endl;
}
