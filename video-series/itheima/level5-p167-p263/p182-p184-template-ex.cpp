# include <iostream>

# include "p182-p184-template-ex-myarray.hpp"

using namespace std;

class Person {
public:
    string name;
    int age;

public:
    Person() { }
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }
};

void func1();

// p167-p173, template ex
int main() {

    cout << "template ex" << endl;

    /*
        template ex
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // copy constructor
    Myarray <int> arr1(5);
    Myarray <int> arr2(arr1);

    // operator= overload
    Myarray <int> arr3(100);
    arr3 = arr1;                // problem here, if arr1 = arr1, then arr1 got emptied

    // insert, delete, overator[] overload, getSize()
    Myarray <int> arr4(5);
    for (int i = 0; i < 5; i++) 
        arr4.ins(i);
    arr4.del();
    for (int i = 0; i < arr4.getSize(); i++) 
        cout << arr4[i] << " "; 
    cout << endl << arr4.getCapacity() << " " << arr4.getSize() << endl;

    // test
    Myarray <Person> arr5(10);
    Person p1("Ada", 1);    arr5.ins(p1);
    Person p2("Bob", 2);    arr5.ins(p2);
    Person p3("Clara", 3);  arr5.ins(p3);
    Person p4("David", 4);  arr5.ins(p4);
    Person p5("Erick", 5);  arr5.ins(p5);
    for (int i = 0; i < arr5.getSize(); i++) 
        cout << arr5[i].name << " " << arr5[i].age << endl;
    cout << arr5.getCapacity() << " " << arr5.getSize() << endl;
}
