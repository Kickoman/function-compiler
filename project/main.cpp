#include <iostream>
#include "Function.h"

using namespace std;

int main()
{
    Function f;
    string raw;
    getline(cin, raw);
    f = raw;
    double xval;
    cin >> xval;
    cout << f(xval);
    return 0;
}
