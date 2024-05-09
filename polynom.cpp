#include "polynom.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

int i,j;

array::array()
{
    A = NULL;
    N = 0;
}
array::array(int n)
{
    A = new double[n];
    N = n;
}
array::array(string s) {
    string buff;
    j = 0;

    for(i = 0; i < s.length(); i++)
        if (s[i] != ' ')
            buff.push_back(s[i]);
    for(i = 0; i < buff.length(); i++)
        if (buff[i] == 'x' && buff[i+1] != '^')
            buff.insert(i+1, "^1");

    if (buff[0] != '-')
        buff = "+" + buff;

    vector<string> memb;
    string bf;

    for (i = 0; i < buff.length(); i++)
    {
        bf.push_back(buff[i]);
        if (buff[i+1] == '+' || buff[i+1] == '-' || i == buff.length() - 1)
        {
            memb.push_back(bf);
            bf.clear();
        }
    } 

    int max_degree = 0;
    int degree;
    for (string term : memb){
        size_t found_pow = term.find("^");
        if (found_pow != string::npos){
            degree = stoi(term.substr(found_pow + 1));
            if (degree > max_degree){
                max_degree = degree;
            }
        }
    }
    int array_size = max_degree + 1;
    A = new double[array_size]();
    N = array_size;
    int coeff;
    for (string term : memb){
        size_t found_x = term.find("x");
        size_t found_pow = term.find("^");
        if (found_pow != string::npos)
            degree = stoi(term.substr(found_pow + 1));
        else 
            degree = 0;

        if (found_x != 1){
            if (found_x != string::npos && term[0] == '+')
                coeff = stoi(term.substr(1,found_x));
            else if (found_x != string::npos && term[0] == '-')
                coeff = stoi(term.substr(0,found_x));
            else
                coeff = stoi(term);
        }
        else
            coeff = 1;

        A[degree] = coeff;
    }
}
array::array(const array &other)
{
    A = new double[other.N];
    this -> N = other.N;
    for (i = 0; i < other.N; i++)
        this->A[i] = other.A[i];
}
array::~array()
{
    delete[] A;
}
array& array::operator=(const array &other)
{
    if(this->A!=other.A)
    {
        delete[] this -> A;
        this->N = other.N;
        A = new double[other.N];
        for(i=0;i<this->N;i++)
            this->A[i] = other.A[i];
    }
    return *this;
}
double& array::operator[] (int n)
{
        return A[n];
}

polynomial::polynomial(int n) : array(n)
{
}
polynomial::polynomial() : array()
{
}
polynomial::polynomial(const polynomial &arr) : array(arr)
{
}

polynomial::polynomial(string s) : array(s)
{
}

polynomial::~polynomial()
{
}
polynomial polynomial::operator+(const polynomial &other)
{
    polynomial temp(0);
    temp.N = (this -> N > other.N) ? this -> N : other.N;
    temp.A = new double[temp.N];
    for(i=0;i<temp.N;i++)
    {
        if(i<this -> N && i<other.N)
        temp.A[i] = this -> A[i] + other.A[i];
        if(i>=this -> N && i<other.N)
        temp.A[i] = other.A[i];
        if(i<this -> N && i>=other.N)
        temp.A[i] = this -> A[i];
    }
    return temp;
}

polynomial polynomial::operator*(const polynomial &other)
{
    polynomial temp(0);
    temp.N = this -> N + other.N - 1;
    temp.A = new double[temp.N];

    for (i=0; i < temp.N; i++)
    temp.A[i] = 0;

for (i = this->N-1; i >= 0; i--)
for (j = other.N-1; j >= 0; j--)
    temp.A[i + j] += this -> A[i] * other.A[j];
    return temp;
}

ostream& operator<<(ostream &os, const polynomial &p)
{
    for (i = p.N-1; i >= 0; i--)
    {
        if(p.A[i]!=0)
        {
            if(p.A[i]!=1&&p.A[i]!=-1||i==0)
                os << p.A[i];

            if(i>=2)
                os << "x^" << i;

            if(i==1)
                os << "x";
        }

        if(p.A[i-1]>0&&i!=0)
            os << "+";
        if(p.A[i-1]==-1&&i-1!=0)
            os << "-";
    }
    return os;
}