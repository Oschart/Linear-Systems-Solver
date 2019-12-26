#include "LinearSystem.h"

LinearSystem::LinearSystem(vector<Equation> _AugMat)
{
    AugMat = _AugMat;
    unifyVariables();
}

void LinearSystem::partialPivot(int st)
{
    sort(AugMat.begin() + st, AugMat.end(), comp);
}

bool comp(Equation &x, Equation &y)
{
    return abs(x.getPivot().coff) > abs(y.getPivot().coff);
}

int LinearSystem::echelonReduce()
{

    for (int i = 0; i < AugMat.size(); ++i)
    {
        partialPivot(i);
        Equation &A = AugMat[i];
        double pivotA = A.getPivot().coff;
        if (pivotA == 0)
        {
            cout << "System has infinitely many solutions\n";
            return 0;
        }
        for (int j = i + 1; j < AugMat.size(); ++j)
        {
            Equation &B = AugMat[j];
            double pivotB = B.getPivot().coff;
            B = B - (pivotB / pivotA) * A;
        }
    }
    return 1;
}

void LinearSystem::backSub()
{

    map<string, double> subList;
    for (int i = AugMat.size() - 1; i >= 1; --i)
    {
        Equation &E = AugMat[i];
        Term pivot = E.getPivot();
        subList[pivot.symbol] = E.getConst() / pivot.coff;
        for (int j = i - 1; j >= 0; --j)
        {
            AugMat[j].substitute(subList);
        }
    }
}

map<string, double> LinearSystem::solve()
{
    map<string, double> sol;
    int res = echelonReduce();
    if (res == 1)
    {
        backSub();

        for (auto it : AugMat)
        {
            Term pivot = it.getPivot();
            sol[pivot.symbol] = it.getConst()/pivot.coff;
        }
    }

    return sol;
}

void LinearSystem::unifyVariables()
{
    if (AugMat.size() < 2)
        return;
    for (int i = 1; i < AugMat.size(); ++i)
    {
        AugMat[i].unifyEquation(AugMat[i - 1]);
    }
}

LinearSystem::~LinearSystem()
{
}