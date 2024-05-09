#include <iostream>
#include <map>
#include <string>
#include "matrixx.h"
#include "indices.h"
using namespace std;

void createMatrix(map<string,matrix*>& mapa)
{
    int n,m;
    string matrixName;
    cout << "Input matrix name: ";
    cin >> matrixName;
    cout << "Input matrix size: ";
    cin >> n >> m;
    matrix* newMatrix = new matrix(n,m);
    indices ind;
    cout << "Input matrix" << endl;
    for(ind.x=0;ind.x<n;ind.x++)
    {
        for(ind.y=0;ind.y<m;ind.y++)
        {
            cin >> (*newMatrix)[ind];
        }
    }
    mapa[matrixName] = newMatrix;
}

void callExpression(map<string,matrix*>& mapa)
{
    if (mapa.size() < 2)
        cout << "Storage too small" << endl;

    else{
        string expr, correction;
        cout << "Write the expression with available variables" << endl;
        getline(cin >> ws, expr);

        for(int i = 0; i < expr.size(); i++){
            if (expr[i] != ' ')
                correction.push_back(expr[i]);
        }
        expr.clear();

        for (int i = 0; i < correction.size(); i++)
            if (correction[i] == '+' || correction[i] == '-' || correction[i] == '*'){
                expr.push_back(correction[i]);
                break;
            }

        if (expr.size() == 1){
            size_t found = correction.find(expr);
            string firstName = correction.substr(0, found), secondName = correction.substr(found+1);
            cout << firstName << endl << secondName << endl;
            if (expr == "+"){
                matrix c;
                c = *(mapa[firstName]) + *(mapa[secondName]);
                cout << c << endl;
            }
            if (expr == "*"){
                matrix c;
                c = (*(mapa[firstName])) * (*(mapa[secondName]));
                cout << c << endl;
            }
        }
    }
}

int main()
{
    string inp, mode;
    map<string, matrix*> matrixMap;
    cout << "Hello, this is my simple matrix calculator!" << endl << "Do you want to continue [y/n]?" << endl;
    
    cin >> inp;

    while(true)
    {
        if (inp != "y"){
            for (auto& pair : matrixMap)
            delete pair.second;
            return 0;
        }
        
        cout << "Chose mode: Create matrix - 1, Calculator - 2, Show available names - 3: ";
        cin >> mode;
        if (mode == "1")
            createMatrix(matrixMap);

        else if (mode == "2")
            callExpression(matrixMap);
        else if(mode == "3"){
            for (const auto& pair : matrixMap)
                cout << pair.first << " :" << endl << *(pair.second) <<endl << "#################" << endl;
        }
        else{
            cout << "Incorrect input" << endl;
            return 0;
        }

        cout << "Do you want to continue [y/n]?" << endl;
        cin >> inp;
    }




}