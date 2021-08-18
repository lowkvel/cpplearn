#include <iostream>

using namespace std;

void func1(int a, int b, int c);
//void func2(int a, int b, int c);
//void func3(int a, int b = 10, int c = 10);
void func4(int a, int b = 10, int c = 10);

// p95-p98, function adv
int main() {

    cout << "function adv" << endl;

    /*
        function adv

        default argument of parameter
            1.  void func(int a, int b, int c);
                void func(int a, int b = 10, int c = 10){   // all parameters [b, c] after the first parameter [b] with default argument requires default arguments 
                    ...
                }
            2.  void func(int a, int b = 10, int c = 10);
                void func(int a, int b, int c){             // do not redefine default argument defined in declaration
                    ...
                }

    */

    // default argument of parameter
    //func1(10);    // ?
    func1(10, 20, 30);  // default argument overrode
    func4(10, 20, 30);

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1(int a, int b = 10, int c = 10) {
    cout << (a + b + c) << endl;
}

/*
// starting from b, all parameters need default argument
void func2(int a, int b = 10, int c) {
    cout << (a + b + c) << endl;
}
*/

/*
// cannot redefine dufault arguments defined in declaration
void func3(int a, int b = 10, int c = 10) {
    cout << (a + b + c) << endl;
}
*/

void func4(int a, int b, int c) {
    cout << (a + b + c) << endl;
}