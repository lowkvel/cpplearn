#include <iostream>

using namespace std;

class Calculator {
public:
    int num1;
    int num2;

    int getResult(string ope) {
        if (ope == "+")
            return num1 + num2;
        else if (ope == "-")
            return num1 - num2;
        else if (ope == "*")
            return num1 * num2;
        else if (ope == "/" && num2 != 0)
            return num1 / num2;
        else
            return 0;
        
        // when we need to add more functionalities here, we have to modify the source code
        // this violates the Open Closed Principle (open to expansion, close to modification)
    }
};

void func1();

// p135-p142, polymorphism ex1
int main() {

    cout << "polymorphism ex1" << endl;

    /*
        polymorphism ex1
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    Calculator c;
    c.num1 = 10;
    c.num2 = 2;
    cout << c.getResult("+") << endl;
    cout << c.getResult("-") << endl;
    cout << c.getResult("*") << endl;
    cout << c.getResult("/") << endl;
}