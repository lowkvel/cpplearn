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
    Person(int a, int height) {
        age = a;
        p_height = new int(height);
        cout << "parameterized constructor, Person constructed" << endl;
    }

    // copy constructor, deep copy
    Person(const Person &p) {
        age = p.age;
        //p_height = p.p_height;            // shallow copy
        p_height = new int(*p.p_height);    // deep copy
        cout << "deep copy constructor, Person constructed" << endl;
    }

    // destructor
    ~Person() {
        // we need to delete memory space allocated in heap pool in order to save memory
        // so we dont need to wait for operation system to free this memory after the whole program terminated
        if (p_height != NULL) { // standard move here
            delete p_height;    // delete the memory in heap pool
            p_height = NULL;    // re-direct the pointer to NULL
        }
        cout << "Person destructed" << endl;
    }

    int age;
    int *p_height;
};

void func1();

// p106-p117, characteristics
int main() {

    cout << "characteristics" << endl;

    /*
        characteristics

        shallow & deep copy
            lets say:                   p1: int age=18,     int* pheight=0x0011,    int 0x0011->160 
                                                            created using 'new int(160)', allocated in heap pool
            after shallow copy:         p2: int age=18,     int* pheight=0x0011,    int 0x0011->160
                first destruction p2:   p2: int age=NULL,   int* pheight=NULL,      int 0x0011->NULL
                second destruction p1:  p1: int age=18,     int* pheight=0x0011,    int 0x0011 has not allocated yet (freed already in p2's destruction), 
                                                                                    exception happens here, cant release same memory location more than once
            after deep copy:            p2: int age=18,     int* pheight=0x0022,    int 0x0011->160
                first destruction p2:   p2: int age=NULL,   int* pheight=NULL,      int 0x0011->NULL
                second destruction p1:  p1: int age=NULL,   int* pheight=NULL,      int 0x0011->NULL
                                                                                    problem solved using deep copy
        standard destructor move:
            if (p_pointer != NULL) {    // standard move here
                delete p_pointer;       // delete the memory in heap pool
                p_pointer = NULL;       // re-direct the pointer to NULL
            }


    */

    // test for shallow and deep copy
    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    Person p1(1, 160);
    cout << p1.age << " " << *p1.p_height << endl;
    Person p2(p1);
    cout << p2.age << " " << *p2.p_height << endl;
}
