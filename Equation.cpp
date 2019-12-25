#include "Equation.h"
#include <algorithm>
using namespace std;

Equation::Equation(string eq)
{
    terms = parseEquation(eq);
    // Move the constant to the RHS
    terms[""] = -terms[""];
}

Equation::Equation(const map<string, double, greater<string>> &other)
{
    terms = other;
}

void Equation::addTerm(Term term)
{
    terms[term.symbol] = terms[term.symbol] + term.coff;
}

void clearSpaces(string &s)
{
    string t = "";
    for (auto c : s)
    {
        if (c != ' ')
            t += c;
    }
    s = t;
}

map<string, double, greater<string>> Equation::parseEquation(string eq)
{
    if (eq[0] != '+' && eq[0] != '-')
        eq = "+" + eq;
    map<string, double, greater<string>> res;
    size_t equalSignPos = eq.find_first_of("=");
    if (eq[equalSignPos + 1] != '+' && eq[equalSignPos + 1] != '-')
        eq.insert(equalSignPos + 1, "+");

    for (int i = equalSignPos + 1; i < eq.size(); ++i)
    {
        if (eq[i] == '+')
            eq[i] = '-';
        else if (eq[i] == '-')
            eq[i] = '+';
    }
    eq.erase(equalSignPos, 1);
    int st = 0;
    while (st < eq.size())
    {
        string termString = getNextTermString(eq, st);
        Term term = stringToTerm(termString);
        res[term.symbol] += term.coff;
    }

    return res;
}

string Equation::getNextTermString(string seq, int &st)
{
    for (int i = st + 1; i < seq.size(); ++i)
    {
        if (seq[i] == '+' || seq[i] == '-')
        {
            int _st = st;
            st = i;
            return seq.substr(_st, i - _st);
        }
    }
    int _st = st;
    st = seq.size();
    return seq.substr(_st);
}

Term Equation::stringToTerm(string term)
{
    int sign = (term[0] == '-' ? -1 : 1);
    for (int i = 1; i < term.size(); ++i)
    {
        if (term[i] != '.' && !isdigit(term[i]))
        {
            string symbol = term.substr(i);
            double coff = i == 1 ? sign : sign * stod(term.substr(1, i - 1));

            return Term(symbol, coff);
        }
    }
    double coff = sign * stod(term.substr(1));
    return Term("", coff);
}

void Equation::unifyEquation(Equation &other)
{
    for (auto it : terms)
    {
        other.addTerm(Term(it.first, 0));
    }

    for (auto it : other.terms)
    {
        this->addTerm(Term(it.first, 0));
    }
}

Equation operator*(double coff, Equation A)
{
    map<string, double, greater<string>> newTerms(A.terms);
    for (auto &term : newTerms)
    {
        term.second *= coff;
    }
    return Equation(newTerms);
}

Equation operator+(Equation A, Equation B)
{
    A.unifyEquation(B);
    for (auto &it : A.terms)
    {
        it.second += B.terms[it.first];
    }
    return A;
}

Equation operator-(Equation A, Equation B)
{
    A.unifyEquation(B);
    for (auto &it : A.terms)
    {
        it.second -= B.terms[it.first];
    }
    return A;
}

ostream &operator<<(ostream &out, const Equation &Eq)
{
    bool firstTerm = true;
    for (auto it : Eq.terms)
    {
        if (it.first != "")
        {
            if (!firstTerm)
            {
                out << (it.second > 0 ? "+ " : "- ");
            }
            out << it.second << it.first << " ";
            firstTerm = false;
        }
    }

    out << "= " << Eq.terms.find("")->second << endl;
    return out;
}

Equation::~Equation()
{
}