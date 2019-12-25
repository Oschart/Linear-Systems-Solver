#include <iostream>
#include <string>
#include "Equation.h"

using namespace std;

int main()
{
    string s;
    cin >> s;
    Equation A(s);
    Equation B = 2*A;
    cout << B;
    cout << B + A;
    cout << A;
}