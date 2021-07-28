#include <iostream>

#define week 7

using namespace std;

// p05, constant
int main() {

    cout << "constant" << endl;

    // constant declaration 1: #define constant_name constant_value
    // 
    cout << "int week = " << week << endl;

    // constant declaration 2: const constant_type constant_name = constant_value;
    const int b = 100;
    cout << "int b = " << b << endl;
    
    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;

}
