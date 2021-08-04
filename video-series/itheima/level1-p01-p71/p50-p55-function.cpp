#include <iostream>

using namespace std;

#include "p50-p55-function-minus.h"

// build command:
// /usr/bin/clang++ -std=c++11 -g p50-p55-function.cpp p50-p55-function-minus.cpp -o p50-p55-function

// function declaration, no specs needed
int add(int n1, int n2);
void swap(int n1, int n2);

// p50-p55, function
int main() {

    cout << "function" << endl;

    /*
        function

        // function declaration
        return_type function_name(parameter list);

        // function definition
        return_type function_name(parameter list) {

            // statements

            // return something;
        }

        // pull out the declaration and definition into different files from main.cpp
        1. declare the add functions in add.h file
            #include <iostream>         // include this because the add function itself need it
            using namespace std;        // same as above
            int add(int n1, int n2);
        2. define the add functions in add.cpp cile
            #include "add.h"            // include the declaration from add.h
            int add(int n1, int n2) {   // then define it in add.cpp
                // statements;
            }
        3.  include add.h and use the add function
            #include <iostream>         // include this because the main function need it
            using namespace std;        // same as above
            #include "add.h"            // then include the specific add function into the main file from add.h
            int main() {
                // add(1, 2);
            }
    */

    int a = 1; int b = 2;
    cout << "a + b = " << add(a, b) << endl;
    cout << "a - b = " << minuss(a, b) << endl;
    cout << "original a b:\t" << a << " " << b << endl; // original a&b
    swap(a, b);                                         // swap function wont affect the original a&b
    cout << "original a b:\t" << a << " " << b << endl; // original a&b not affected
    
    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

// function definition, need specs

int add(int n1, int n2) {
    int sum = n1 + n2;
    return sum;
}

void swap(int n1, int n2) {
    int temp = n1;
    n1 = n2;
    n2 = temp;
    cout <<"swapped a b:\t" << n1 << " " << n2 << endl;
}
