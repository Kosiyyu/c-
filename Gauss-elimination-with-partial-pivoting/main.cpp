#include <iostream>
#include <fstream>

using namespace std;

int n = 0;
double** tab;
double* X;

static void getData()
{
    ifstream indata;
    indata.open("data2.txt");
    if (!indata)
    {
        exit(1);
    }
    indata >> n;
    tab = new double* [n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        tab[i] = new double[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            indata >> tab[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        X = new double[n];
    }
    indata.close();
}

void swapRow(int y1, int y2)
{
    for (int i = 0; i < n + 1; i++)
    {
        swap(tab[y1][i], tab[y2][i]);
    }
}

void killNegativeZero()
{
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n + 1; i++) {
            if (tab[i][j] == 0) {
                tab[i][j] = 0.0;
            }
        }
    }
}

void printTab()
{
    killNegativeZero();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++)
        {
            cout << tab[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

void makeTriangularMatrix()
{
    for (int i = 0; i < n; i++)
    {
        int maxi = i;
        int y = tab[i][i];
        for (int j = i + 1; j < n; j++)
        {
            if (abs(tab[j][i]) > y)
            {
                y = tab[j][i];
                maxi = j;
            }
        }
        swapRow(maxi, i);
        for (int j = i + 1; j < n; j++)
        {
            double m = tab[j][i] / tab[i][i];
            for (int k = i + 1; k < n + 1; k++)
            {
                tab[j][k] = tab[j][k] - tab[i][k] * m;
            }
            tab[j][i] = 0;
        }
    }
}

void calculateSolution()
{
    for (int i = n - 1; i >= 0; i--)
    {
        X[i] = tab[i][n];
        for (int j = i + 1; j < n; j++)
        {
            X[i] = X[i] - tab[i][j] * X[j];
        }
        X[i] = X[i] / tab[i][i];
    }
}

void printX()
{
    for (int i = n - 1; i >= 0; i--)
    {
        cout << "x" << i << " = " << X[i] << endl;
    }
}

int main()
{
    getData();
    cout << "MACIERZ PRZED ROZSZERZONA PRZED OBLICZANIEM => " << endl;
    printTab();
    makeTriangularMatrix();
    cout << "MACIERZ ROZSZERZONA PO OBLICZANIU => " << endl;
    printTab();
    calculateSolution();
    cout << "ROZWIAZANIA DLA PODANEJ MACIERZY => " << endl;
    printX();

    return 0;
}
