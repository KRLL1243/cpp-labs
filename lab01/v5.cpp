#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    double epsilon;
    double term;
    double sum = 0.0;
    double x;
    int n;
    int k;

    cout << "Input x = ";
    if (!(cin >> x) || x <= -1 || x > 1)
    {
        cout << "Error: x must be in (-1; 1].\n";
        return 1;
    }

    cout << "\nInput number of digits after decimal point = ";
    if (!(cin >> k) || k <= 1 || k > 15)
    {
        cout << "Error: enter an integer from 2 to 15.\n";
        return 1;
    }

    epsilon = pow(10.0, -k);
    term = x;
    n = 1;

    while (fabs(term) >= epsilon)
    {
        sum += term;
        term = -term * x * n / (n + 1);
        ++n;
    }

    cout << fixed << setprecision(k);
    cout << "ln(1 + x) = " << log(1 + x) << "\tS = " << sum << "\n";

    return 0;
}
