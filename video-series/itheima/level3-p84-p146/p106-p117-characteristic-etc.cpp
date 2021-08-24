#include <iostream>

using namespace std;

class Phone {
public:
    // default constructor
    // Phone() {
    //     brand = "";
    //     cout << "default constructor, Phone constructed" << endl;
    // }

    // parameterized constructor
    Phone(string brand) {
        this->brand = brand;
        cout << "parameterized constructor, Phone constructed" << endl;
    }

    // destructor
    ~Phone() {
        cout << "Phone destructed" << endl;
    }

    string brand;
};

class Person {
public:

    /*   
        we have to use initializer list to explicitly tell the compiler to use a specific Phone constructor
        thus we can avoid the "no default constructor exists for class "Phone"" problem
        https://en.cppreference.com/w/cpp/language/constructor 
    */

    // default constructor
    // Person() {
    //     age = 0;
    //     p_height = new int(0);
    //     phone = Phone("");
    //     cout << "default constructor, Person constructed" << endl;
    // }
    Person(): age(0), p_height(new int(0)), phone("") {
        cout << "default constructor, Person constructed" << endl;
    }

    // parameterized constructor
    // Person(int a, int height, string phone_name) {
    //     age = a;
    //     p_height = new int(height);
    //     phone = Phone(phone_name);
    //     cout << "parameterized constructor, Person constructed" << endl;
    // }
    Person(int a, int height, string phone_name): age(a), p_height(new int(height)), phone(phone_name) {
        cout << "parameterized constructor, Person constructed" << endl;
    }

    // copy constructor, deep copy
    // Person(const Person &p) {
    //     age = p.age;
    //     //p_height = p.p_height;            // shallow copy
    //     p_height = new int(*p.p_height);    // deep copy
    //     phone = Phone(p.phone);
    //     cout << "deep copy constructor, Person constructed" << endl;
    // }
    Person(const Person &p): age(p.age), p_height(new int(*p.p_height)), phone(Phone(p.phone)) {
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

    // static member function
    static string getSex() {
        //age = 0;                  // static function is not allowed to access non-static variable
        sex = "what sex?";
        return sex;
    }

    // return *this
    // if Person addAge(...) {...} is used here, a copy of the object returned by *this will be created by copy constructor
    // this we need to return a reference of the object here using Person& addAge(...) {...}
    Person& addAge(Person &p) {
        this->age += p.age;
        return *this;
    }

    int age;
    int *p_height;  // pointer
    Phone phone;

    static string species;          // public static class member, declared inside of class

private: 
    static string sex;              // private static class member, declared inside of class
};

string Person::species = "human";   // public static class member, initialized outside of class
string Person::sex = "none";        // private static class member, initialized outside of class

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
        
        standard destructor code:
            if (p_pointer != NULL) {    // standard move here
                delete p_pointer;       // delete the memory in heap pool
                p_pointer = NULL;       // re-direct the pointer to NULL
            }

        object member instantiation
            ex:     class A {};
                    class B {A a};
            seq:    object A will be instantiate before B when we instantiate B
            rule:   we have to use initializer list to explicitly tell the compiler to use a specific A constructor
                    thus we can avoid the "no default constructor exists for class "A"" problem
                    https://en.cppreference.com/w/cpp/language/constructor 

        static class member (variable & function)
            static variable:    shared variable by all same-class objects
                                memory allocated in static pool during compiling phase 
                                declared inside of class, initialized outside of class
            static function:    shared function by all same-class objects
                                have access to static variable only 
            access methods:     access through specific object, like p1.species; p1.getEtc();
                                access through class, like Person::species; Person::getEtc();
            
        object member memory allocation
            empty object (class with no variable nor function) takes 1 bytes in order to distinguish it from other empty objects
            memory of non-static class variable is allocated with each object
            memory of non-static/static class function and static class variable is not allocated with each object, they are shared among all objects

        this
            points to:      the caller object, like p1
            is used when:   distinguish parameter and argument, like this->name = name;
                            return the object itself, like return *this;
    */

    // func1
    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {

    // p1 instantiation
    Person p1(1, 160, "Apple");
    cout << p1.age << " " << *p1.p_height << " " << p1.phone.brand << " " << p1.species << endl;

    // p2 instantiation
    Person p2(p1);
    p2.species = "human2.0";   // modify class-level static variable
    cout << p2.age << " " << *p2.p_height << " " << p2.phone.brand << " " << p2.species << endl;

    // check back to p1 to see the static variable is modified
    cout << p1.age << " " << *p1.p_height << " " << p1.phone.brand << " " << p1.species << endl;

    // static variable/function access way 1: through object
    cout << p1.species << " ";
    cout << p1.getSex() << endl;
    // static variable/function access way 2: class direct
    cout << Person::species << " ";
    cout << Person::getSex() << endl;
    //cout << Person::sex << endl;      // inaccessible ouside of class because it is private

    // this, chaining
    p2.addAge(p1).addAge(p1).addAge(p1);
    cout << p2.age << " " << *p2.p_height << " " << p2.phone.brand << " " << p2.species << endl;

}
