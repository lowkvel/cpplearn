#include <iostream>

using namespace std;

void swap1(int a, int b);
void swap2(int* pa, int* pb);
void swap3(int &a, int &b);
//int& test01();
int& test02();

// p89-p94, reference
int main() {

    cout << "reference" << endl;

    /*
        reference

        int a = 10;
        int &b = a;     // initialization is mandatory, cannot change after initialization
        
        int c = 20;
        b = c;          // this is assignment, not re-reference

        the nature of reference is a const pointer, this explains why reference cannot change after initialization
        int& ref = a        --> int* const ref = &a

        const reference
        further extends the restriction of reference
        const int& ref = 10 --> int temp = 10; const int& ref = temp;   // variable temp is not accessible, but ref is accessible
        const int& ref = a  --> const int* const ref = &a               // double const in pointer, mostly used in function
            func f(const int& v) {
                v = 1000;   // cannot do that
            }

    */

    int a = 10;
    int &b = a;         // initialization is mandatory, cannot change after initialization
    cout << a << " " << b << endl;
    int t = 99;
    b = t;              // this is assignment, not re-reference
    cout << a << " " << b << endl;

    int c = 1; int d = 2;
    // in value
    cout << "before swap1(int c, int d):     c = " << c << "\td = " << d << endl;
    swap1(c, d);
    cout << "after swap1(int c, int d):      c = " << c << "\td = " << d << endl;
    // in pointer
    cout << "before swap2(int* pc, int* pd): c = " << c << "\td = " << d << endl;
    swap2(&c, &d);
    cout << "after swap2(int* pc, int* pd):  c = " << c << "\td = " << d << endl;
    // in reference
    cout << "before swap3(int* pc, int* pd): c = " << c << "\td = " << d << endl;
    swap3(c, d);
    cout << "before swap3(int* pc, int* pd): c = " << c << "\td = " << d << endl;

    // dont return reference of local parameter, the variable is allocated in stack pool and will be freed after excution of func()
    //int &ref = test01();
    // reference of a static parameter can be returned
    int &ref = test02();    // ref is a reference of a
    cout << ref << endl;
    // function used as left value because a reference [ref] of a static parameter [a] was returned by the function
    test02() = 99;          // equivalent to a = 99; this gives ref = 99;
    cout << ref << endl;

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void swap1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap2(int* pa, int* pb) {
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void swap3(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/*
// dont return reference of local parameter, the variable is allocated in stack pool and will be freed after excution of func()
int& test01() {
    int a = 10;
    return a;
}
*/

int& test02() {
    static int a = 10;  // static parameter stored in static pool, can be returned 
    return a;
}