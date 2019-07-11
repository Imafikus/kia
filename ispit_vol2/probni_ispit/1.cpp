#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Tacka
{
public:
    double x;
    double y;

    Tacka(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};

int orijent(Tacka A, Tacka B, Tacka C)
{
    double ABx = (B.x - A.x);
    double ABy = (B.y - A.y);

    double CAx = (C.x - A.x);
    double CAy = (C.y - A.y);

    int det = (ABx * CAy) - (ABy * CAx);

    if(det > 0)
        return 1;
    if(det < 0)
        return -1;
    if(det == 0)
        return 0;
}

bool praveMnogougao(vector<Tacka> sveTacke)
{
    int brojTacaka = sveTacke.size();

    for(int i = 0; i < brojTacaka; i++)
    {
        int prva = i % brojTacaka;
        int druga = (i + 1) % brojTacaka;
        int treca = (i + 2) % brojTacaka;
        if(orijent(sveTacke[prva], sveTacke[druga], sveTacke[treca]) == -1)
            return false;
    }
    return true;
}

int main()
{
    int brojTacaka = 5;
    vector<Tacka> sveTacke;
    for(int i = 0; i < brojTacaka; i++)
    {
        double x, y;
        cin >> x >> y;
        sveTacke.push_back(Tacka(x, y));
    }

    if(praveMnogougao(sveTacke))
        cout << "DA" << endl;
    else 
        cout << "NE" << endl;
    

}