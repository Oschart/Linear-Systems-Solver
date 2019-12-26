#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "LinearSystem.h"

using namespace std;

int main()
{
    cout << "Insert your equations, bruh \n";
    //freopen("13-equations.txt", "r", stdin);
    ifstream in("13-equations.txt");
    string eq;
    vector<Equation> Eqs;
    while(getline(in, eq) && !eq.empty())
    {
        Eqs.push_back(Equation(eq));
    }
    LinearSystem system(Eqs);

    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    map<string, double> sol = system.solve();
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    for(auto it: sol)
    {
        cout << it.first << " = " << it.second << endl;
    }
    cout << "==================================\n";
    cout << "Time taken = " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000.0 << " milliseconds" << std::endl;
    cout << "==================================\n";
}