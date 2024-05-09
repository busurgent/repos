#include <iostream>
#include "matrixx.h"
#include "indices.h"
using namespace std;
int main()
{
   matrix a(2,2);
   indices ind;
   for(ind.x=0;ind.x<2;ind.x++)
   {
       for(ind.y=0;ind.y<2;ind.y++)
       {
           cin>>a[ind];
       }
   }
    matrix b(2,2);
   for(ind.x=0;ind.x<2;ind.x++)
   {
       for(ind.y=0;ind.y<2;ind.y++)
       {
           cin>>b[ind];
       }
   }
   matrix c;
   c=a+b;
   cout<<c;
   c=a*b;
   cout<<c;
}