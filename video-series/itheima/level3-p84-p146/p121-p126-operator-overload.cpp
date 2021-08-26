#include <iostream>

using namespace std;

// used for overloading +, <<, =
class Person {
public:
    int a;
    int b;
    int *age;

    // constructor
    Person() {              // default
        // a = b = 0;
        age = new int(0);
    }
    Person(int i) {         // parameterized
        // a = b = 0;
        age = new int(i);
    }

    // destructor
    ~Person() {
        if (age != NULL) {
            delete age;
            age = NULL;
        }
        cout << "Person destructed" << endl;
    }

    // operator+ overload with class member function
    Person operator+(Person &p) {
        Person temp;
        temp.a = this->a + p.a;
        temp.b = this->b + p.b;
        return temp;
    }

    // operator<< overload with class member function, we tend not to use it, 
    // reason: the desired form cout << p will become p.operator<<(cout) -> p << cout, which is not what we want
    void operator<<(ostream &cout) {
        cout << this->a << " " << this->b << endl;
    }

    // operator= overload with class member function, turn shallow copy into deep copy
    Person& operator=(Person &p) {
        // delete the memory if already allocated
        if (age != NULL) {
            delete age;
            age = NULL;
        }
        
        // deep copy for heap storage
        age = new int(*p.age);

        // shallow copy for the rest
        a = p.a;
        b = p.b;

        return *this;
    }
};

// used for overloading ++
class Myint {
private:
    int num;

friend ostream& operator<<(ostream& cout, Myint i);

public:
    Myint() {
        num = 0;
    }

    // operator++ overload with class member function, pre-increment
    // return reference of Myint here is because 
    // we want to increment the value of the same Myint object, like: ++(++(++i))
    // instead of incrementing the copied value everytime
    Myint& operator++() {
        num++;                  // increment the value
        return *this;           // return a reference for chaining capability
    }

    // operator++ overload with class member function, post-increment
    // int here is used as placeholder parameter, can be used to distinguish pre- and post- increment
    // pay attention to the copied value returned here compared to above pre-increment implementation
    Myint operator++(int) {
        Myint temp = *this;     // record current value, copy constructor involved here
        num++;                  // increment the value
        return temp;            // return a copy of recorded value instead of reference 
                                // because it is a local variable which will be deleted when this function ends
    }
};

void func1();
Person operator+(Person &p1, Person &p2);
//void operator<<(ostream &cout, Person &p);    // no chaining capabilities
ostream& operator<<(ostream &cout, Person &p);  // with channing capabilities
ostream& operator<<(ostream &cout, Myint i);    // pay attention to the value instead of reference here

// p120-p126, operator overload
int main() {

    cout << "operator overload" << endl;

    /*
        operator overload
            1.  operator overload is allowed to have function overload at the same time based on differenct set of parameters

        operator+ overload
            1.  operator+ overload with class member function               p1.operator+(p2)    ->  p1 + p2
                    return_type operator+(...) {
                        return_type temp;
                        ...
                        return temp;
                    }
            2.  operator+ overload with global function                     operator+(p1, p2)   ->  p1 + p2
                    return_type operator+(..., ...) {
                        return_type temp;
                        ...
                        return temp;
                    }

        operator<< overload
            1.  operator<< overload with class member function              p.operator<<(cout)  ->  p << cout
                    dont use this one 
                    because the desired form         -> cout << p 
                    will become p.operator<<(cout)   -> p << cout
            2.  operator<< overload with global function
                    ostream& operator<<(ostream &cout, return_type &p) {    operator<<(cout, p) ->  cout << p << ...
                        cout << ...;
                        return cout;
                    }

        operator++ overload
            1.  pre-increment
                    Myint& operator++() {       // reference returned
                        num++; 
                        return *this;           // chaining capability
                    }
            2.  post-increment
                    Myint operator++(int) {     // copied value returned
                        Myint temp = *this;
                        num++;
                        return temp;            // local variable
                    }

        operator= overload
            1.  operator= overload with class member function               p1.operator=(p2)    ->  p1 = p2
                    Person& operator=(Person &p) {
                        // delete the memory if already allocated
                        if (age != NULL) {
                            delete age;
                            age = NULL;
                        }
                        age = new int(*p.age);  // deep copy for heap pool
                        ...                     // shallow copy for others
                        return *this;
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

    // operator<< overload with class member function, we tend not to use it, 
    // reason: the desired form cout << p will become p.operator<<(cout) -> p << cout, which is not what we want
    p1.operator<<(cout);            // dont use this one
    // simplified version for p1
    p1 << cout;                     // dont use this one
    // operator<< overload with global function
    operator<<(cout, p2) << endl;
    // simplified version for p2
    cout << p2 << endl;

    // operator++ overload with class member function, including pre-increment and post-increment
    Myint i;                    cout << i << endl;      // instantiate i
    cout << ++(++i) << " ";     cout << i << endl;      // pre-increment
    cout << i++ << " ";         cout << i << endl;      // post-increment, cant do chaining operation here

    // operator= overload with class member function, turn default shallow copy into deep copy
    Person p5 = Person(5);   
    Person p6 = Person(6);
    Person p7 = Person(7);
    cout << *p5.age << " " << *p6.age << " " << *p7.age << endl;
    p5.operator=(p6.operator=(p7));
    //p5 = p6 = p7;   // chain
    cout << *p5.age << " " << *p6.age << " " << *p7.age << endl;  
    
}

Person operator+(Person &p1, Person &p2) {
    Person temp;
    temp.a = p1.a + p2.a;
    temp.b = p1.b + p2.b;
    return temp;
}

// normally this will do, but we need to use the following one because of chaining capabiliteis
// void operator<<(ostream &cout, Person &p) {
//     cout << p.a << " " << p.b << endl;
// }

// this one gives the capabiliteis to output more things (like endl) after the Person object
ostream& operator<<(ostream &cout, Person &p) {
    cout << p.a << " " << p.b;
    return cout;
}
// we use 'Myint i' here instead of 'Myint &i' like above
// because the pre-increment requires chaining capabilities which means we have to use reference
// but the post-increment requires the local variable to be returned which means we have to return a copied value of Myint
// so we combine two requirements into one since a referenced value is also a value
ostream& operator<<(ostream &cout, Myint i) {
    cout << i.num;  // friend is declared within Myint here
    return cout;
}

// todo
// Person& operator=(Person &p) {
//     this->a = p.a;
//     this->b = p.b;
//     this->age = new int(p.age);
// }