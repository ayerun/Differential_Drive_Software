#include "rigid2d.hpp"
#include <iostream>

int main()
{
    using namespace rigid2d;
    using namespace std;

    Transform2D Tab;
    Transform2D Tbc;
    Transform2D Tac;
    Transform2D Tba;
    Transform2D Tcb;
    Transform2D Tca;
    Vector2D v;
    Vector2D va;
    Vector2D vb;
    Vector2D vc;
    char sys;

    //get transformations
    cout << "Enter a Transformation (Tab): ";
    cin >> Tab;
    cout << "Enter a Transformation (Tbc): ";
    cin >> Tbc;
    cout << endl;

    //compute transformations
    Tba = Tab.inv();
    Tcb = Tbc.inv();
    Tac = Tab*Tbc;
    Tca = Tac.inv();

    //output results
    cout << "Tab: " << endl;
    cout << Tab << endl;
    cout << "Tbc: " << endl;
    cout << Tbc << endl;
    cout << "Tba: " << endl;
    cout << Tba << endl;
    cout << "Tcb: " << endl;
    cout << Tcb << endl;
    cout << "Tac: " << endl;
    cout << Tac << endl;
    cout << "Tca: " << endl;
    cout << Tca << endl;

    //get vector and coordinate system
    cout << "Enter a Vector (v): ";
    cin >> v;
    cout << v << endl;
    cout << "Enter a coordinate system (a, b, or c): ";
    cin >> sys;

    //compute transformations
    if (sys == 'a')
    {
        va = v;
        vb = Tba(va);
        vc = Tca(va);
    }
    else if (sys == 'b')
    {
        vb = v;
        va = Tab(vb);
        vc = Tcb(vb);
    }
    else if (sys == 'c')
    {
        vc = v;
        va = Tac(vc);
        vb = Tbc(vc);
    }

    //output results
    cout << "va: " << va << endl;
    cout << "vb: " << vb << endl;
    cout << "vc: " << vc << endl;



    // cout << v;
}