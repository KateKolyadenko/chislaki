#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdio.h>
using namespace std;
const double eps1 = 0.0001;
const double eps2 = 0.00001;


double function(double x)
{
	return 1/(pow(log10(x), 2) + 1);
}

double function(double x, double y)
{
	return pow(x, 2) / (1 + pow(y, 2));
}

double MethodOfTrapezoid(double a, double b)
{
	double sum = 0; double sum_prev = 0;
	double h = (b - a); 
	int kol_vo = 0; 

	do {
		sum_prev = sum;                               
		sum = 0;                                     
		for (int i = 1; i <= ((b - a) / h) - 1; i++)       
		{
			sum += 2 * function(a + h * i);
		}           
		sum = (function(a) + sum + function(b)) * h / 2;
		h /= 2;                                      
		kol_vo++;
	} while (abs(sum - sum_prev) > eps1);
	cout << "Trapezoid: " << endl << kol_vo << " iter" << endl;
	return sum;
}

double MethodOfSimpson(double a, double b)
{
	double sum = 0; double sum_prev = 0;
	double h = (b - a) / 2;                           
	int kol_vo = 0;

	do {
		sum_prev = sum;
		sum = 0;
		for (int i = 1; i <= ((b - a) / h); i += 2)
		{
			sum += 4 * function(a + h * i);
		}
		for (int i = 2; i <= ((b - a) / h) - 1; i += 2)
		{
			sum += 2 * function(a + h * i);
		}
		sum = (function(a) + sum + function(b)) * h / 3;
		h /= 2;                                     
		kol_vo++;
	} while (abs(sum - sum_prev) > eps2);
	cout << "Simpsson: " << endl << kol_vo << " iter" << endl;
	return sum;
}

double MethodOfCubeSimpson(double a, double b, double c, double d)
{
	int m = 2; int n = m;
	int kol_vo = 0;
	double sum = 0; double sum_prev = 0;

	do {
		sum_prev = sum;
		sum = 0;
		double hx = (b - a) / (2 * n);
		double hy = (d - c) / (2 * m);

		double xi = a;
		double yi = c;

		double* Xi = new double[2 * n + 1];
		Xi[0] = xi;

		for (int i = 1; i <= 2 * n; i++)
			Xi[i] = Xi[i - 1] + hx;

		double* Yi = new double[2 * m + 1];
		Yi[0] = yi;

		for (int j = 1; j <= 2 * m; j++)
			Yi[j] = Yi[j - 1] + hy;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				sum += function(Xi[2 * i], Yi[2 * j]);
				sum += 4 * function(Xi[2 * i + 1], Yi[2 * j]);
				sum += function(Xi[2 * i + 2], Yi[2 * j]);
				sum += 4 * function(Xi[2 * i], Yi[2 * j + 1]);
				sum += 16 * function(Xi[2 * i + 1], Yi[2 * j + 1]);
				sum += 4 * function(Xi[2 * i + 2], Yi[2 * j + 1]);
				sum += function(Xi[2 * i], Yi[2 * j + 2]);
				sum += 4 * function(Xi[2 * i + 1], Yi[2 * j + 2]);
				sum += function(Xi[2 * i + 2], Yi[2 * j + 2]);
			}
		}
		sum *= (hx * hy / 9);
		n *= 2;
		m *= 2;
		kol_vo++;
	} while (abs(sum - sum_prev) > eps2);
	cout << "Cube Simpsson: " << endl << kol_vo << " iter" << endl;
	return sum;
}

int main()
{
	double a = 1.0;
	double b = 2.835;
	double trapp;
	double simp;
	double cube_simp;
	trapp = MethodOfTrapezoid(a, b);
	cout << trapp << endl << endl;
	simp = MethodOfSimpson(a, b);
	cout << simp << endl << endl;

	double a1 = 0.0;
	double b1 = 4;
	double c1 = 1;
	double d1 = 2;
	cube_simp = MethodOfCubeSimpson(a1, b1, c1, d1);
	cout << cube_simp << endl;
	return 0;
}
