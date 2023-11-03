#include <iostream>
#include <vector>
#include <iomanip>
#include <assert.h>
using namespace std;

void print(const vector<vector<double>>& matrix, int m, int n) 
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

void GaussianElimination(vector<vector<double>>& a, vector<vector<double>>& a_copy, int m, int n, int k) 
{
    double max = 1;
    int index = 0;
    for (int i = k; i < m; i++) {
        if (max <= abs(a[i][k])) {
            index = i;
            max = abs(a[i][k]);
        }
    }
    if (index != 0) {
        swap(a[k], a[index]);

        print(a, m, n);
    }
    cout << endl;
    for (int i = k; i < m; i++) {
        double del = a[i][k];
        for (int j = k; j < n; j++) {
            a[i][j] /= del;
        }
    }

    for (int i = m - 1; i > k; i--) {
        for (int j = k; j < n; j++) {
            a[i][j] -= a[k][j];
        }
    }

    print(a, m, n);
    cout << endl;
    k++;
    if (k != m)
    {
        GaussianElimination(a, a_copy, m, n, k);
    }
    else 
    {
        double x3 = a[m - 1][n - 1] / a[m - 1][n - 2];
        double x2 = (a[m - 2][n - 1] - x3 * a[m - 2][n - 2]) / a[m - 2][n - 3];
        double x1 = (a[m - 3][n - 1] - x2 * a[m - 3][n - 3] - x3 * a[m - 3][n - 2]) / a[m - 3][n - 4];

        cout << "Solution (x): " << x1 << ' ' << x2 << ' ' << x3 << endl;

        double x4 = x1 * a_copy[m - 3][n - 4] + x2 * a_copy[m - 3][n - 3] + x3 * a_copy[m - 3][n - 2];
        double x5 = x1 * a_copy[m - 2][n - 4] + x2 * a_copy[m - 2][n - 3] + x3 * a_copy[m - 2][n - 2];
        double x6 = x1 * a_copy[m - 1][n - 4] + x2 * a_copy[m - 1][n - 3] + x3 * a_copy[m - 1][n - 2];

        cout << "Check: " << x5 << ' ' << x4 << ' ' << x6 << endl;

        double x7 = a_copy[m - 3][n - 1] - x4;
        double x8 = a_copy[m - 2][n - 1] - x5;
        double x9 = a_copy[m - 1][n - 1] - x6;
        cout << "Residual vectors: " << x7 << ' ' << x8 << ' ' << x9 << endl;

        double norm = abs(x7);
        if (abs(x8) > norm)
        {
            norm = abs(x8);
        }
        if (abs(x9) > norm)
        {
            norm = abs(x9);
        }
        cout << "Norm of the residual vector: " << norm << endl;
       
    }
}


int main() 
{
    vector<vector<double>> a
    {
        {2.31, 31.49, 1.52, 40.95},
        {4.21, 22.42, 3.85, 30.24},
        {3.49, 4.85, 28.72, 42.81}
    };
    vector<vector<double>> a_copy
    {
        {2.31, 31.49, 1.52, 40.95},
        {4.21, 22.42, 3.85, 30.24},
        {3.49, 4.85, 28.72, 42.81}
    };

    for (int i = 0; i < 3; i++) {
        assert(!(a[i][i] == 0));
    }

    GaussianElimination(a, a_copy, 3, 4, 0);
    return 0;
}