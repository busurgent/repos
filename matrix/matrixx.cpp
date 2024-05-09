#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "matrixx.h"
#include "indices.h"
using namespace std;
int i,j,r;

matrix::matrix()
{
    Nx = 0;
    Ny = 0;
    A = NULL;
}
matrix::matrix(int nx,int ny)
{
    Nx = nx;
    Ny = ny;
    A = new double* [Nx];
    for (i=0;i<Nx;i++)
    {
        A[i] = new double [Ny];
    }
    for(i=0;i<Nx;i++)
        for(j=0;j<Ny;j++)
        A[i][j] = 0;
}
matrix::matrix(const matrix &other)
{
    this->Nx = other.Nx;
    this->Ny = other.Ny;
    A = new double* [Nx];
    for (i=0;i<Nx;i++)
    {
        A[i] = new double [Ny];
    }
    for(i=0;i<Nx;i++)
        for(j=0;j<Ny;j++)
        this->A[i][j] = other.A[i][j];
}
matrix::~matrix()
{
    for(i=0;i<Ny;i++)
        delete[] A[i];
        delete[] A;
}
matrix& matrix::operator=(const matrix &other)
{
    for(i=0;i<Ny;i++)
        delete[] A[i];
        delete[] A;
    this->Nx = other.Nx;
    this->Ny = other.Ny;
    A = new double* [Nx];
    for (i=0;i<Nx;i++)
    {
        A[i] = new double [Ny];
    }
    for(i=0;i<Nx;i++)
        for(j=0;j<Ny;j++)
        this->A[i][j] = other.A[i][j];
        return *this;
}
double& matrix::operator[] (const indices &ind)
{
        return A[ind.x][ind.y];
}
ostream& operator<<(ostream &cout, const matrix &other)
{
     for(i=0;i<other.Nx;i++)
     {
         for(j=0;j<other.Ny;j++)
            cout << other.A[i][j] <<" ";
         cout << endl;
     }
     return cout;
}
matrix matrix::operator+(const matrix &other)
{
    matrix temp;
    if(this->Nx==other.Nx&&this->Ny==other.Ny)
    {
        temp.Nx = this->Nx;
        temp.Ny = this->Ny;
        temp.A = new double* [temp.Nx];
        for(i=0;i<temp.Nx;i++)
        temp.A[i] = new double [temp.Ny];
        for(i=0;i<temp.Nx;i++)
            for(j=0;j<temp.Ny;j++)
            temp.A[i][j] = this->A[i][j] + other.A[i][j];
            return temp;
    }
    else
    {
        temp.Nx = 0;
        temp.Ny = 0;
        temp.A = NULL;
        cout<<"IMPOSSIBLE+"<<endl;
        return temp;
    }
}
matrix matrix::operator*(const matrix &other)
{
    matrix temp;
    if(this->Ny==other.Nx)
    {
        temp.Nx = this->Nx;
        temp.Ny = other.Ny;
        temp.A = new double* [temp.Nx];
        for(i=0;i<temp.Nx;i++)
        temp.A[i] = new double [temp.Ny];

        for(i=0;i<Nx;i++)
            for(j=0;j<Ny;j++)
            temp.A[i][j] = 0;

        for(i=0;i<temp.Nx;i++)
            for(j=0;j<temp.Ny;j++)
            {
                for(r=0;r<this->Ny;r++)
                {
                    temp.A[i][j] = temp.A[i][j] + this->A[i][r] * other.A[r][j];
                }
            }
            return temp;
    }
    else
        {
        temp.Nx = 0;
        temp.Ny = 0;
        temp.A = NULL;
        cout<<"IMPOSSIBLE*"<<endl;
        return temp;
    }
}