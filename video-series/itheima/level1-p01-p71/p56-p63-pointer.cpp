#include <iostream>

using namespace std;

void swap1(int a, int b);
void swap2(int* pa, int* pb);

// p56-p63, pointer
int main() {

    cout << "pointer" << endl;

    /*
        pointer

        // normal pointer
        int a = 10;         // initialize int a with value 10
        int* p = &a;        // int* p means p is a int pointer, stores a's address given by &a, takes 4/8 bytes in 32/64 bits operation system
        *p = 20;            // *p accesses the value stored at a's address (stored in p), which is a itself

        // null pointer, not accessible (0x0 - 0xff) by user since it locked by operation system
        int* p = NULL;      // p points to 0x0, which is locked by operation system

        // wild pointer, pointer assigned with address which is not allocated by operation system
        int* p = 0xfff;     // p points to assigned address, which is not allocated by operation system

        // const pointer
        int a = 10;
        const int* p = &a;          // address p is modifible, value *p is const,   const(*p)
        int* const p = &a;          // address p is const, value *p is modifible,   const(p)
        const int* const p = &a;    // address p is const, value *p is const,       const(*p) & const(p)

    */

    // normal pointer
    int a = 10;
    int* p = &a;
    cout << "p takes " << sizeof(p) << " bytes" << endl;
    cout << "a = " << a << "\tp = " << p << "\t&a = " << &a << "\t*p = " << *p << "\t\toriginal value" << endl;
    *p = 25;
    cout << "a = " << a << "\tp = " << p << "\t&a = " << &a << "\t*p = " << *p << "\t\tmodified *p means a got modified" << endl;
    p = p + 10;
    cout << "a = " << a << "\tp = " << p << "\t&a = " << &a << "\t*p = " << *p << "\t\tmodified p gives fault in *p" << endl;

    // null pointer
    int* pn = NULL;
    cout << "null pointer pn = " << pn << ", \t\t*pn is not accessible (0x0 - 0xff) by user since it is locked by operation system" << endl;

    // wild pointer
    int* pw = (int*)0xfff;
    cout << "wild pointer pw = " << pw << ", \t*pw is not assessible since the memory address is not allocated by operation system" << endl;

    // const pointer
    int b = 20;
    const int* p1 = &a;         p1 = &b;    // okay, but *p1 = 20 is not okay
    int* const p2 = &a;         *p2 = 20;   // okay, but p2 = &b is not okay
    const int* const p3 = &a;               // both of *p3 = 20 and p3 = &b are not okay

    // pointer and array
    int arr[5] = {0, 1, 2, 3, 4};
    int* parr = arr;
    cout << "arr[0] = " << arr[0] << ",\t*parr = " << *parr << endl;
    cout << "arr[1] = " << arr[1] << ",\t*(parr+1) = " << *(parr+1) << endl;

    // pointer and function
    int c = 1; int d = 2;
    cout << "before swap1(int c, int d):     c = " << c << "\td = " << d << endl;
    swap1(c, d);
    cout << "after swap1(int c, int d):      c = " << c << "\td = " << d << endl;
    cout << "before swap2(int* pc, int* pd): c = " << c << "\td = " << d << endl;
    swap2(&c, &d);
    cout << "after swap2(int* pc, int* pd):  c = " << c << "\td = " << d << endl;

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
