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

vector<double> GaussianElimination(vector<vector<double>>& a, int m, int n)
{
    vector<vector<double>> a_copy = a;
    for (int i = 0; i < m; i++) {
        double max = 0;
        int index = 0;
        for (int j = i; j < m; j++) {
            if (max <= abs(a[j][i])) {
                index = j;
                max = abs(a[j][i]);
            }
        }
        swap(a[i], a[index]);

        //print(a, m, n);
        //cout << endl;
        for (int j = i; j < m; j++) {
            double del = a[j][i];
            for (int k = i; k < n; k++) {
                a[j][k] /= del;
            }
        }

        for (int j = m - 1; j > i; j--) {
            for (int k = i; k < n; k++) {
                a[j][k] -= a[i][k];
            }
        }

        print(a, m, n);
        cout << endl;
    }
    /*k++;
    if (k != m)
    {
        GaussianElimination(a, a_copy, m, n, k);
    }
    else*/
    //{
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

    return { x1, x2, x3 };
}


int main()
{
    vector<vector<double>> a
    {
        {2.31, 31.49, 1.52, 40.95},
        {4.21, 22.42, 3.85, 30.24},
        {3.49, 4.85, 28.72, 42.81}
    };

    for (int i = 0; i < 3; i++) {
        assert(!(a[i][i] == 0));
    }

    vector<double> solution = GaussianElimination(a, 3, 4);

    vector<vector<double>> Ax{
        {2.31, 31.49, 1.52, 2.31 * solution[0] + 31.49 * solution[1] + 1.52 * solution[2]},
        {4.21, 22.42, 3.85, 4.21 * solution[0] + 22.42 * solution[1] + 3.85 * solution[2]},
        {3.49, 4.85, 28.72, 3.49 * solution[0] + 4.85 * solution[1] + 28.72 * solution[2]}
    };

    vector<double> Ax_tild = GaussianElimination(Ax, 3, 4);
    double max1 = 0;
    for (int i = 0; i < 3; i++) {
        if (max1 <= abs(Ax_tild[i] - solution[i])) {
            max1 = abs(Ax_tild[i] - solution[i]);
        }
    }

    double max2 = 0;
    for (int i = 0; i < 3; i++) {
        if (max2 <= abs(solution[i])) {
            max2 = abs(solution[i]);
        }
    }
    cout << "max1 = " << max1 << "  " << "max2 = " << max2 << endl;
    cout << "Relative fault: " << max1 / max2;

    return 0;
}