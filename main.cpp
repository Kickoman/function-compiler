#include <iostream>
#include "kfunction.h"

using namespace std;

int main()
{
    Function<double> f;
    string raw;
    getline(cin, raw);
    f = raw;
    double xval;
    cin >> xval;
    cout << f(xval);
    return 0;
}
