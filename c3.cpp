#include <iostream>
#include <climits>

using namespace std;

int main()
{
    short n_short = SHRT_MAX;
    int n_int = INT_MAX;
    long n_long = LONG_MAX;
    long long n_llong = LLONG_MAX;

    cout << "short is " << sizeof(short) << " bytes"
         << " with a min of " << SHRT_MIN << " and with a max of " << SHRT_MAX << endl;
    cout << "int is " << sizeof(int) << " bytes"
         << " with a min of " << INT_MIN << " and with a max of " << INT_MAX << endl;
    cout << "long is " << sizeof(long) << " bytes"
         << " with a min of " << LONG_MIN << " and with a max of " << LONG_MAX << endl;
    cout << "long long is " << sizeof(long long) << " bytes"
         << " with a min of " << LLONG_MIN << " and with a max of " << LLONG_MAX << endl;

    int temp0 = 233;
    int temp1(233);
    int temp2{233};
    int temp3 = {233};
    cout << "init 4 ways: " << temp0 << " " << temp1 << " " << temp2 << " " << temp3 << endl;

    int ten = 233;
    int eight = 0233;
    int sixteen = 0x233;
    cout << "233 in decimal equals " << ten << " in decimal" << endl;
    cout << "0233 in octal equals " << eight << " in decimal" << endl;
    cout << "0x233 in hexadecimal equals " << sixteen << " in decimal" << endl;
    //cout << hex; // base cout changing

    char ch = 'M';
    int chi = ch;
    cout << "char " << ch << " in ASCII is " << chi << endl;
    cout.put(ch);
    cout.put(chi+1);
    cout << '\n';

    //cout.setf(ios_base::fixed, ios_base::floatfield);
    float f = 10.0 / 3.0;
    double d = 10.0 / 3.0;
    const float mils = 1.0e6;
    cout << "f: " << f << " " << f * mils << " " << 10 * f * mils << endl;
    cout << "d: " << d << " " << d * mils << " " << 10 * d * mils << endl;
    float f1 = 2.34e+22f;
    float f2 = f1 + 1.0f;
    cout << f1 << " " << f2 << " " << f2 - f1 << endl;  // f2 - f1 should be 1.0f

    return 0;
}
