#pragma once
#include <iostream>
#include <string>
using namespace std;
class array
{
    protected:
        double *A;
        int N;

    public:
        array();
        array(int);
        array(const array&);
        array(string s);
        ~array();
        array& operator=(const array&);
        double& operator[] (int);
};

class polynomial : public array
{
    public:
        polynomial();  
        polynomial(int);
        polynomial(const polynomial&);
        polynomial(string s);
        ~polynomial();
        polynomial operator*(const polynomial&);
        polynomial operator+(const polynomial&);
        friend ostream& operator<<(ostream&, const polynomial&);
};