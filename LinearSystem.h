#ifndef LINSYS_H
#define LINSYS_H

#include <vector> 
#include <string>
#include <map>
#include <cmath>
#include "Equation.h"

using namespace std;

class LinearSystem
{
private:
    vector<Equation> AugMat;
    void partialPivot(int st);
    int echelonReduce();
    void unifyVariables();
    void backSub();
public:
    LinearSystem(vector<Equation> _AugMat);
    map<string, double> solve();
    ~LinearSystem();
};




#endif