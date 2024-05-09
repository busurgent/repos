#include <iostream>
#include "indices.h"
using namespace std;

class matrix
{
private:
int Nx, Ny;
double **A;
public:
matrix();
matrix(int, int);
matrix(const matrix&);
~matrix();
matrix& operator=(const matrix&);
double& operator[] (const indices&);
friend ostream& operator<<(ostream&, const matrix&);
matrix operator*(const matrix&);
matrix operator+(const matrix&);
};