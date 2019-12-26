#include <iostream>
#include <string>
#include "LinearSystem.h"

using namespace std;

int main()
{
    cout << "Insert your equations, bruh \n";
    string eq;
    vector<Equation> Eqs;
    while(getline(cin, eq) && !eq.empty())
    {
        Eqs.push_back(Equation(eq));
    }
    LinearSystem system(Eqs);

    map<string, double> sol = system.solve();
    for(auto it: sol)
    {
        cout << it.first << " = " << it.second << endl;
    }
}