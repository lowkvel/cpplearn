#include <iostream>

using namespace std;

// abstract calculator
class AbstractCalculator {
public:
    int num1;
    int num2;
    virtual int getResult() { return 0; }
    // the original code is untouched here, follows open closed principle
};

// open to expansion, add calculator inherited from abstract calculator
class AddCalculator: public AbstractCalculator {
public:
    virtual int getResult() {
        return num1 + num2;
    }
};

// open to expansion, minus calculator inherited from abstract calculator
class MinusCalculator: public AbstractCalculator {
public:
    virtual int getResult() {
        return num1 - num2;
    }
};

// open to expansion, ...

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
    // create a add calculator
    AbstractCalculator *absc = new AddCalculator;
    absc->num1 = 10;
    absc->num2 = 2;
    cout << absc->getResult() << endl;
    delete absc;                    // frees the memory allocated in heap pool, but the absc pointer stays untouched

    // redirect to a minus calculator
    absc = new MinusCalculator;     // redirect to a new heap memory using the untouched absc pointer from above
    absc->num1 = 10;
    absc->num2 = 2;
    cout << absc->getResult() << endl;
    delete absc;

    // ...
}