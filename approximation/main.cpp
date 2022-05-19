/*
    Least-squares function approximation

    In order to achieve other values for the given points, you can
    change the value of the variable n + 1, corresponding to the degree
    of the polynomial. Where n + 1 is an integer greater than zero in
    the range of int.

    Program created by Karol Koś
*/

#include <iostream>

#include <cmath>

#include <fstream>

using namespace std;

int n = 1; //degree
int m = 8; //number of points

double* x = new double[m];
double* y = new double[m];
double* a = new double[n + 1];
double* F = new double[n + 1];
double** g = new double* [m];

double w(int index) {
    return 1;
}
double fi(int index, double exponent) {
    return pow(x[index], exponent);
}

double new_y(double* a, double* x, int index) {
    double ret = 0.0;
    for (int i = n; i >= 0; i--) {
        ret += a[i] * pow(x[index], i);
    }
    return ret;
}
void calculate_g() {
    for (int i = 0; i < m; i++) {
        g[i] = new double[m];
    }
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            g[j][i] = 0;
            for (int k = 0; k < m; k++) {
                g[j][i] += fi(k, j) * fi(k, i) * w(k);
            }
        }
    }
    for (int i = 0; i < n + 1; i++) {
        g[i][n + 1] = F[i];
    }
}
void calculate_F() {
    for (int i = 0; i < n + 1; i++) {
        F[i] = 0;
        for (int j = 0; j < m; j++) {
            F[i] += fi(j, i) * y[j] * w(j);
        }
    }
}
void gauss(double** arr, double* X, int n) {
    for (int i = 0; i < n + 1; i++) {
        int maxi = i;
        int y = arr[i][i];
        for (int j = i + 1; j < n + 1; j++) {
            if (abs(arr[j][i]) > y) {
                y = arr[j][i];
                maxi = j;
            }
        }
        for (int j = 0; j < n + 1 + 1; j++) {
            swap(arr[maxi][j], arr[i][j]);
        }
        for (int j = i + 1; j < n + 1; j++) {
            double m = arr[j][i] / arr[i][i];
            for (int k = i + 1; k < n + 1 + 1; k++) {
                arr[j][k] = arr[j][k] - arr[i][k] * m;
            }
            arr[j][i] = 0;
        }
    }

    for (int i = n; i >= 0; i--) {
        X[i] = arr[i][n + 1];
        for (int j = i + 1; j < n + 1; j++) {
            X[i] = X[i] - arr[i][j] * X[j];
        }
        X[i] = X[i] / arr[i][i];
    }

}

void printArr(double** tab, int n) {
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1 + 1; j++) {
            cout << tab[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

static void getData() {
    ifstream indata;
    indata.open("data.txt");
    if (!indata) {
        exit(1);
    }
    for (int i = 0; i < m; i++) {
        indata >> x[i] >> y[i];
    }
    indata.close();
}
int main() {
    getData();
    calculate_F();
    calculate_g();
    //printArr(g, n);
    gauss(g, a, n);
    cout << "Degree: " << n << endl << endl;
    cout << "Number of points: " << m << endl << endl;
    cout << "Points: " << endl;
    for (int i = 0; i < m; i++) {
        cout << x[i] << ", " << y[i] << endl;
    }
    cout << endl;
    cout << "Coefficients:" << endl;
    for (int i = 0; i < n + 1; i++) {
        cout << "a[" << i << "]: " << a[i] << endl;
    }
    cout << endl;
    cout << "Points after approximation: " << endl;
    for (int i = 0; i < m; i++) {
        cout << x[i] << ", " << new_y(a, x, i) << endl;
    }
    cout << endl;

    delete[] x;
    delete[] y;
    delete[] a;
    delete[] F;
    for (int i = 0; i < m; i++) {
        delete[] g[i];
    }
    delete[] g;
}
