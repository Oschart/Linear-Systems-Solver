#include <iostream>
#include <string>
#include "Equation.h"

using namespace std;

int main()
{
    string s;
    cin >> s;
    Equation A(s);
    cout << A*2;
}