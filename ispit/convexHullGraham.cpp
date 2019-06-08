#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>


using namespace std;

pair<double, double> pivot;

int nadjiSkrozLevuTacku(vector<pair<double, double>> skupTacaka)
{
    pair<double, double> skrozLevo = skupTacaka[0];

    int idx;

    for(int i = 0; i < skupTacaka.size(); i++)
    {
        if(skupTacaka[i].first < skrozLevo.first || (skupTacaka[i].first == skrozLevo.first && skupTacaka[i].second < skrozLevo.second))
        {
            skrozLevo = skupTacaka[i];
            idx = i;
        }
    }
    return idx;
}

void stampajTacke(vector<pair<double, double>> tacke)
{
    for(auto t : tacke)
        cout << t.first << " " << t.second << endl;
}

double orijentacija(pair<double, double> A, pair<double, double> B, pair<double, double> C)
{
    double orijent = (B.first - A.first) * (C.second - A.second) - (C.first - A.first) * (B.second - A.second);
    return orijent;
}

double orijentacija1(pair<double, double> A, pair<double, double> B, pair<double, double> C)
    {
        double ax = A.first; double ay = A.second;
        double bx = B.first; double by = B.second;
        double cx = C.first; double cy = C.second;

        double d = (bx - ax) * (cy - ay) - (cx - ax) * (by - ay);
        return d;
    }

pair<double, double> drugiSaVrhaSteka(stack<pair<double, double>> tacke)
{
    tacke.pop();
    return tacke.top();
}


bool cmp(pair<double, double> p1, pair<double, double> p2)
{
    if(orijentacija1(pivot, p1, p2) > 0)
    {
        return true;
    }
    else if(orijentacija1(pivot, p1, p2) < 0)
    {
        return false;
    }
    else
    {
        double rastojanjeP1 = (p1.first - pivot.first) * (p1.first - pivot.first) - (p1.second - pivot.second) * (p1.second - pivot.second);
        double rastojanjeP2 = (p2.first - pivot.first) * (p2.first - pivot.first) - (p2.second - pivot.second) * (p2.second - pivot.second);
        
        return(rastojanjeP1 <= rastojanjeP2);
    }
}

vector<pair<double, double>> graham(vector<pair<double, double>> skupTacaka)
{
    int indexSkrozLeveTacke = nadjiSkrozLevuTacku(skupTacaka);
    
    cout << "Skroz levo: " <<  indexSkrozLeveTacke << endl;
    swap(skupTacaka[0], skupTacaka[indexSkrozLeveTacke]);
    pivot = skupTacaka[0];
    
    sort(skupTacaka.begin() + 1, skupTacaka.end(), cmp);
    stampajTacke(skupTacaka);

    stack<pair<double, double>> poligon;

    poligon.push(skupTacaka[0]);
    poligon.push(skupTacaka[1]);
    poligon.push(skupTacaka[2]);


    cout << "Dosao do for" << endl;
    for(int i = 3; i < skupTacaka.size(); i++)
    {
        while(orijentacija(drugiSaVrhaSteka(poligon), poligon.top(), skupTacaka[i]) <= 0)
        {
            poligon.pop();
        }
        poligon.push(skupTacaka[i]);
    }

    cout << "Prosao for" << endl;

    vector<pair<double, double>> res;
    while(!poligon.empty())
    {
        res.push_back(poligon.top());
        poligon.pop();
    }

    return res;
}

int main()
{
    vector<pair<double, double>> tacke = { {1, 1}, {0, 0}, {1, 0}, {0, 1}, {0.2, 0.2}, {0.7, 0.7} };

    vector<pair<double, double>> poligon = graham(tacke);

    for(pair<double, double> p : poligon)
        cout << p.first << " " << p.second << endl;


}