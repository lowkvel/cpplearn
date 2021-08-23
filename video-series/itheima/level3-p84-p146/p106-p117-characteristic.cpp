#include <iostream>

using namespace std;

void func1();

class Person {
public:
    // default constructor
    Person() {
        age = 0;
        cout << "default constructor, Person constructed" << endl;
    }

    // parameterized constructor
    Person(int a) {
        age = a;
        cout << "parameterized constructor, Person constructed" << endl;
    }

    // copy constructor
    Person(const Person &p) {
        age = p.age;
        cout << "copy constructor, Person constructed" << endl;
    }

    // destructor
    ~Person() {
        cout << "Person destructed" << endl;
    }

    int age;

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
                        classfication:  default constructor (without parameter)
                                        parameterized constructor (with parameter)
                                        copy constructor (with another same class object as parameter)
                        call:           ():      Person p1(...); or Person p1;
                                        =:       Person p1 = Person(...); Person(...) is a anonymous object
                                        {}       Person p1 = {...};
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
    // ()
    Person p1;      // default constructor, dont use () in it, otherwize compiler will treat it as function declaration
    Person p2(10);  // parameterized constructor
    Person p3(p2);  // copy constructor

    // = 
    Person p4 = Person();
    Person p5 = Person(10);     //Person(...) is a anonymous object
    Person p6 = Person(p5);
    
    // {}
    Person p7 = 10;             // equivalent to Person p7 = Person(10); variant: Person p7 = {10}; <-- array
    Person p8 = p7;             // equivalent to Person p8 = Person(p7);
}

