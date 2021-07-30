#include <iostream>

using namespace std;

// p16-p23, operator
int main() {

    cout << "operator" << endl;

    /*
        https://en.cppreference.com/w/cpp/language/operators 

        Arithmetic      + - * / % ++ --
        Assignment      = += -= *= /= %= <<= >>= &= ^= |=
        Relational      < <= == => > !=
        Logical         && || !
        Bitwise         & | ^ ~ << >> 
        Misc            sizeof() ? 
    */
    
    // arithmetic
    // + - * pass
    // / %
    int a = 3; int b = 2; 
    int c = a / b;                          // c = 1            int / int = int, b cannot be 0, discard the remainder
    int d = a % b;                          // d = 1            int % int = int, b cannot be 0, can only do % on int
    // ++
    int a1 = 2; int b1 = ++a1;              // a = 3, b = 3     first a = a + 1,    then b = a
    int a2 = 2; int b2 = a2++;              // a = 3, b = 2     first b = a,        then a = a + 1
    // --
    int a3 = 2; int b3 = --a3;              // a = 1, b = 1     first a = a - 1,    then b = a
    int a4 = 2; int b4 = a4--;              // a = 1, b = 2     first b = a,        then a = a - 1

    // assignment
    // pass

    // relational
    // pass

    // logical
    // pass
    
    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;

}
