#include <iostream>

using namespace std;

void func1();

class Person {
public:
    // constructor
    Person() {
        cout << "constructed" << endl;
    }

    // destructor
    ~Person() {
        cout << "destructed" << endl;
    }

};

// p106-p117, characteristics
int main() {

    cout << "characteristics" << endl;

    /*
        characteristics

        constructor:    no return type nor void
                        has same class_name
                        overloadable
                        automatically called by program once while instantiating a object (when?), no need for manual calling
            class_name() {
                ...
            }
        
        destructor:     no return type nor void
                        has same class_name but with '~' in front of it
                        non-overloadable because parameters is not allowed
                        automatically called by program once while destructing a object (when?), no need for manual calling
            ~class_name() {
                ...
            }
    */

    func1();


    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    Person p1;
}

