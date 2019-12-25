#ifndef EQUATION_H
#define EQUATION_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>

using namespace std;

struct Term{
    string symbol;
    double coff;

    Term(string _sym, double _coff): symbol(_sym), coff(_coff) {}
};

class Equation
{
private:
    map<string, double, greater<string>> terms;
    static map<string, double, greater<string>> parseEquation(string eq);
    static string getNextTermString(string seq, int &st);
    static Term stringToTerm(string term);
public:
    Equation(string eq);
    Equation(const map<string, double, greater<string>> &other);
    void addTerm(Term term);
    void unifyEquation(Equation &other);
    friend Equation operator * (double coff, Equation A);
    friend Equation operator + (Equation A, Equation B);
    friend Equation operator - (Equation A, Equation B);

    friend ostream& operator<< (ostream& out, const Equation &Eq);
    ~Equation();
};


#include "Equation.cpp"

#endif