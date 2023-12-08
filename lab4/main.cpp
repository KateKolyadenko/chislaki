#include <iostream>
#include <cmath>
#include "approximation.h"
#include <fstream>


using namespace std;

int main(int argc, char** argv) {
    ifstream datafile = ifstream("data.txt");
    int n;
    datafile >> n;
    double* X = new double[n];
    for (int i = 0; i < n; i++) {
        datafile >> X[i];
    }

    double* Y = new double[n];
    for (int i = 0; i < n; i++) {
        datafile >> Y[i];
    }

    double* coeffs = approx_wrapped(X, Y, n);

    double a = coeffs[0];
    double b = coeffs[1];
    double c = coeffs[2];

    cout << a << " " << b << " " << c << endl;

    cout << c << "x^2  " << b << "x  " << a << endl;

    delete[] X;
    delete[] Y;
    delete[] coeffs;
    return 0;
}