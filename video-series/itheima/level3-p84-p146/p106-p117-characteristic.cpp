#include <iostream>

using namespace std;

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

void func1();
void test1(Person p);
Person test2();

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
                                            used in     1. copy a object
                                                        2. pass value (copy) into function as parameter
                                                        3. return object as value in function
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
    cout << p1.age << endl;
    Person p2(2);   // parameterized constructor
    cout << p2.age << endl;
    Person p3(p2);  // copy constructor
    cout << p3.age << endl;

    // = 
    Person p4 = Person();
    cout << p4.age << endl;
    Person p5 = Person(5);      //Person(...) is a anonymous object
    cout << p5.age << endl;
    Person p6 = Person(p5);
    cout << p6.age << endl;
    
    // {}
    Person p7 = 7;              // equivalent to Person p7 = Person(10); variant: Person p7 = {10}; <-- array
    cout << p7.age << endl;
    Person p8 = p7;             // equivalent to Person p8 = Person(p7);
    cout << p8.age << endl;

    // when to use copy constructor
    // 1. copy a object
    Person p11 = Person(11);
    cout << p11.age << endl;
    Person p12 = Person(p11);
    cout << p12.age << endl;
    // 2. pass value into function
    Person p13 = Person(13);
    cout << p13.age << endl;
    test1(p13);
    // 3. return object as value
    /*  Copy elision
        normally, return will call a copy constructor (before c++11)
        but return value optimization is used in this case (after c++11), so the original object is returned 
        in order to verify the object without RVO, use '-fno-elide-constructors' in build
        https://en.cppreference.com/w/cpp/language/copy_elision
    */
    Person p14 = test2();
    cout << p14.age << endl;
}

void test1(Person p) {
    cout << p.age << endl;
}

Person test2() {
    /*  Copy elision
        normally, return will call a copy constructor (before c++11)
        but return value optimization is used in this case (after c++11), so the original object is returned 
        in order to verify the object without RVO, use '-fno-elide-constructors' in build
        https://en.cppreference.com/w/cpp/language/copy_elision
    */
    Person p = Person(14);
    return p;
}
