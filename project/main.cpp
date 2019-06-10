#include <iostream>
#include "Function.h"

using namespace std;

int main()
{
    Function f;
    string raw;
    getline(cin, raw);
    f.set_function(raw);
    double xval;
    cin >> xval;
    cout << f.run(xval);
    return 0;
}
