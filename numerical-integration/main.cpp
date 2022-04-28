#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double func_sin(double x)
{
    return sin(x);
}

double func_polynomial(double x)
{
    return (x * x + 2 * x + 5);
}

double func_exp(double x)
{
    return exp(x);
}

double func_text(double x)
{
    return 3 * log(x);
}

class integral {
    double s;
    int n;
    double lower_boundary;
    double upper_boundary;
public:
    integral() {
        s = 0;
        n = 0;
        lower_boundary = 0;
        upper_boundary = 0;
    }

    integral(int n, double lower_boundary, double upper_boundary) {
        s = (upper_boundary - lower_boundary) / n;
        this->n = n;
        this->lower_boundary = lower_boundary;
        this->upper_boundary = upper_boundary;
    }

    double rectangle(double (*func)(double)) {
        double ret = 0;
        double x = lower_boundary + s / 2;
        for (int i = 0; i < n; i++) {
            ret += func(x);
            x += s;
        }
        return s * ret;
    }

    double trapeze(double (*func)(double)) {
        double ret = 0;
        double x = lower_boundary;
        for (int i = 0; i < n; i++) {
            ret += func(x + s) + func(x);
            x += s;
        }
        return (s * ret) / 2;
    }

    double simpsonComposite(double (*func)(double))
    {
        double ret = func(upper_boundary) + func(lower_boundary);
        double x = 0.0;
        for (int i = 1; i <= n - 1; i++)
        {
            x = lower_boundary + i * s;
            if (i % 2 == 0)
            {
                ret += 2 * (func(x));
            }
            else
            {
                ret += 4 * (func(x));
            }
        }
        ret *= s / 3;
        return ret;
    }
    double simpson(double (*func)(double))
    {
        double ret = 0.0;
        double x = 0.0;
        for (int i = 0; i <= n - 1; i++)
        {
            x = lower_boundary + i * s;
            ret += (s / 6) * (func(x) + 4 * func((x + x + s) / 2) + func(x + s));
        }
        return ret;
    }

    double gaussLagendre(double (*func)(double))
    {
        double ret = 0.0;
        if (n == 2) {
            double quadrature[] = { -0.57735,+0.57735 };
            double A[] = { 1, 1 };
            double t[] = { 0, 0 ,0 ,0 };
            for (int i = 0; i < n; i++) {
                t[i] = ((upper_boundary + lower_boundary) / 2) + ((upper_boundary - lower_boundary) / 2) * quadrature[i];
            }
            for (int i = 0; i < n; i++) {
                ret += (A[i] * func(t[i]));
            }
        }
        else if (n == 4) {
            double quadrature[] = { -0.861136,  -0.339981, 0.339981, 0.861136 };
            double A[] = { 0.347855, 0.652145 , 0.652145,0.347855 };
            double t[] = { 0, 0 ,0 ,0 };
            for (int i = 0; i < n; i++) {
                t[i] = ((upper_boundary + lower_boundary) / 2) + ((upper_boundary - lower_boundary) / 2) * quadrature[i];
            }
            for (int i = 0; i < n; i++) {
                ret += (A[i] * func(t[i]));
            }
        }
        return ((upper_boundary - lower_boundary) / 2) * ret;
    }

};

int main()
{
    int n = 4;
    integral* integralObj = new integral(n, 0.5, 2.5);
    integral* integralObj1 = new integral(n, 0.5, 5);
    cout << "-----------------------------------------------------------" << endl;

    cout << "For number of intervals n: " << n << endl;
    cout << endl;
    cout << "RECTANGULAR RULE { " << endl;
    cout << "functon: sin(x)" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 2.5 << endl;
    cout << "result: " << integralObj->rectangle(func_sin) << endl;
    cout << endl;
    cout << "functon: x^2 + 2x + 5" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj1->rectangle(func_polynomial) << endl;
    cout << endl;
    cout << "functon: e^x" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj1->rectangle(func_exp) << endl;
    cout << "}" << endl;

    cout << "-----------------------------------------------------------" << endl;

    cout << "For number of intervals n: " << n << endl;
    cout << endl;
    cout << "TRAPEZOIDAL RULE { " << endl;
    cout << "functon: sin(x)" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 2.5 << endl;
    cout << "result: " << integralObj->trapeze(func_sin) << endl;
    cout << endl;
    cout << "functon: x^2 + 2x + 5" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj1->trapeze(func_polynomial) << endl;
    cout << endl;
    cout << "functon: e^x" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj1->trapeze(func_exp) << endl;
    cout << "}" << endl;

    cout << "-----------------------------------------------------------" << endl;

    cout << "For number of intervals n: " << n << endl;
    cout << endl;
    cout << "SIMPSON'S RULE { " << endl;
    cout << "functon: sin(x)" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 2.5 << endl;
    cout << "result: " << integralObj->simpson(func_sin) << endl;
    cout << endl;
    cout << "functon: x^2 + 2x + 5" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj1->simpson(func_polynomial) << endl;
    cout << endl;
    cout << "functon: e^x" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj1->simpson(func_exp) << endl;
    cout << "}" << endl;

    cout << "-----------------------------------------------------------" << endl;

    int newN = 2;
    integral* integralObj2 = new integral(newN, 0.5,2.5);
    integral* integralObj3 = new integral(newN, 0.5, 5);

    cout << "For number of intervals n: " << newN << endl;
    cout << endl;
    cout << "GAUSS-LEGENDRE QUADRATURE { " << endl;
    cout << "functon: sin(x)" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 2.5 << endl;
    cout << "result: " << integralObj2->gaussLagendre(func_sin) << endl;
    cout << endl;
    cout << "functon: x^2 + 2x + 5" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj3->gaussLagendre(func_polynomial) << endl;
    cout << endl;
    cout << "functon: e^x" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj3->gaussLagendre(func_exp) << endl;
    cout << "}" << endl;

    cout << "-----------------------------------------------------------" << endl;

    integral* integralObj4 = new integral(n, 0.5, 2.5);
    integral* integralObj5 = new integral(n, 0.5, 5);

    cout << "For number of intervals n: " << n << endl;
    cout << endl;
    cout << "GAUSS-LEGENDRE QUADRATURE { " << endl;
    cout << "functon: sin(x)" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 2.5 << endl;
    cout << "result: " << integralObj4->gaussLagendre(func_sin) << endl;
    cout << endl;
    cout << "functon: x^2 + 2x + 5" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj5->gaussLagendre(func_polynomial) << endl;
    cout << endl;
    cout << "functon: e^x" << endl;
    cout << "integration range from to: " << 0.5 << " - " << 5 << endl;
    cout << "result: " << integralObj5->gaussLagendre(func_exp) << endl;
    cout << "}" << endl;
}
