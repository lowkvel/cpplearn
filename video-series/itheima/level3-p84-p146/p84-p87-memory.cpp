#include <iostream>
#include <limits>

using namespace std;

int* func();
int* funca();

// global variable here
int ga = 10;
int gb = 10;
// global constant here
const int cga = 10;
const int cgb = 10;

// p84-p87, memory
int main() {

    cout << "memory" << endl;

    /*
        pools of memory in cpp: 

        code:   binary code storage, managed by operation system, 
                allocated before running, 
                read only, same code stored here is shared by duplicated runs of the same program

        static: global/static/constant (partial) variable storage, permanent for the entire run of the program
                allocated before running, freed by operation system after the program finished running

        stack:  local/parameter variable storage (automatic allocated by compiler, continuous memory)
                allocated after running, managed (allocation & free) by compiler
                do NOT return the address (&) of a local parameter

        heap:   dynamic storage (large pool of memory allocated by programmer in discontiguous order)
                allocated after running, allocated by programmer and freed by operation system if not released by programmer before the program terminated

    */

    // code, pass

    // static:  global, static, constant (string, global)
    // global variable, static variable tends to stay together in static storage
    cout << "global variable:\t" << &ga << " \t" << &gb << endl;
    static int sa = 10;     // this is a static variable
    static int sb = 10;     // same as above
    cout << "static variable:\t" << &sa << " \t" << &sb << endl;

    // global constant, string constant tends to stay together in static storage, but it is not stored next to above area
    cout << "global constant:\t" << &cga << " \t" << &cgb << endl;      // this is a global constant
    cout << "string constant:\t" << &"string" << endl;                  // this is a string constant
    
    // local constant and local variable stays together
    const int cla = 10;      // this is a local constant
    const int clb = 10;      // same as above
    cout << "local constant:\t\t" << &cla << " \t" << &clb << endl;
    int a = 10;     // this is a local variable
    int b = 10;     // same as above
    cout << "local variable:\t\t" << &a << " \t" << &b << endl;

    // stack:   local/parameter
    // dont return address of local parameter, the variable is allocated in stack pool and will be freed after excution of func()

    // heap:    dynamic storage
    int* p = func();
    cout << p << endl;      // address in heap pool
    cout << *p << endl;     // value in address from heap pool
    delete p;               // frees the memory allocated in heap pool

    int* parr = funca();
    for (int i = 0; i < 10; i++)
        cout << parr[i];
    cout << endl;
    delete[] parr;          // frees the memory of array nees [] after delete

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

int* func() {
    // new returns the address (in heap pool) of the variable created, 
    // then the address of the variable is stored in p in stack pool
    int* p = new int(10); 
    cout << &p << endl;     // stores p's address, in stack pool, will be freed after func() ends, cannot be returned
    return p;               // stores address of new int created, in heap pool, can be returned
}

int* funca() {
    int * parr = new int[10];
    for (int i = 0; i < 10; i++)
        parr[i] = i;
    return parr;
}
