#include <iostream>

using namespace std;

class Person {

public:
    int a;
    int b;

    // operator+ overload with class member function
    Person operator+(Person &p) {
        Person temp;
        temp.a = this->a + p.a;
        temp.b = this->b + p.b;
        return temp;
    }
};

void func1();
Person operator+(Person &p1, Person &p2);

// p120-p126, operator overload
int main() {

    cout << "operator overload" << endl;

    /*
        operator overload
            1.  operator overload is allowed to have function overload at the same time based on differenct set of parameters

        operator+ overload
            1.  class member function operator overload
                return_type operator+(...) {
                    return_type temp;
                    ...
                    return temp;
                }
            2.  global function operator overload
                return_type operator+(..., ...) {
                    return_type temp;
                    ...
                    return temp;
                }

        
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {

    Person p1; p1.a = 1; p1.b = 1;  cout << p1.a << " " << p1.b << endl;
    Person p2; p2.a = 2; p2.b = 2;  cout << p2.a << " " << p2.b << endl;
    
    // operator+ overload with class member function
    Person p3 = p1.operator+(p2);   cout << p3.a << " " << p3.b << endl;
    // operator+ overload with global function
    Person p4 = operator+(p1, p2);  cout << p4.a << " " << p4.b << endl;
    // simplified version for p3 & p4
    //Person p5 = p1 + p2;            cout << p3.a << " " << p3.b << endl;

}

Person operator+(Person &p1, Person &p2) {
    Person temp;
    temp.a = p1.a + p2.a;
    temp.b = p1.b + p2.b;
    return temp;
}