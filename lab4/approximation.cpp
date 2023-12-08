#include "approximation.h"
#include <cmath>

#define M 3

double* approx(double* X, double* Y, int n) {
    double** a = new double* [M];
    for (int i = 0; i < M; i++) {
        a[i] = new double[M];
        for (int j = 0; j < M; j++) {
            double sumx = 0;
            for (int xind = 0; xind < n; xind++) {
                sumx += pow(X[xind], i + j);
            }
            a[i][j] = sumx;
        }
    }

    double* b = new double[M];

    for (int i = 0; i < M; i++) {
        double sumxy = 0;
        for (int j = 0; j < n; j++) {
            sumxy += Y[j] * pow(X[j], i);
        }
        b[i] = sumxy;
    }

    double* solutions = new double[M];

    gauss(a, b, solutions, M);
    return solutions;
}

double* approx_wrapped(double* X, double* Y, int n) {
    double* solutions = approx(X, Y, n);
    return solutions;
}