#include <iostream>

using namespace std;

// forward declaration of Building, used for declaration of class Goodguy3
class Building;

// class Goodguy3 is declared without details here 
// because constructor of Goodguy3 and function pri_visit() & pub_visit()
// needs to access a Building's instance which is defined after Goodguy3
class Goodguy3 {
public:
    //constructor, declaration only
    Goodguy3(); 

    // use this function to access Building's public members, declaration only
    void pub_visit();
    // use this function to access Building's private members, declaration only
    void pri_visit();

    Building *building;     // defines below
};

class Building {

// friend declaration here
friend void goodguy1(Building &b);  // global function goodguy1() will have access to class Building's private members
friend class Goodguy2;              // class Goodguy2 will have access to class Building's private members
friend void Goodguy3::pri_visit();  // class member function pri_visit() of class Goodguy3 will have access to class Building's private members

public:
    // constructor
    Building() {
        livingroom = "livingroom";
        bedroom = "bedroom";
    }

public:
    string livingroom;

private:
    string bedroom;
};

// global function goodguy1 declaration
void goodguy1(Building &b);

// class Goodguy2 as friend to class Building
class Goodguy2 {
public:
    // constructor
    Goodguy2() {
        building = new Building();
    }

    // use this function to access Building's public & private members
    void visit() {
        cout << building->livingroom << endl;
        cout << building->bedroom << endl;      // good to go
    }  
    
    Building *building;
};

// class member function of Goodguy3 as friend to class Building are specified here
Goodguy3::Goodguy3() {
    building = new Building();
}
void Goodguy3::pri_visit() {
    cout << building->bedroom << endl;      // good to go
}
void Goodguy3::pub_visit() {
    cout << building->livingroom << endl;   // good to go
}

// p118-p120, friend
int main() {

    cout << "friend" << endl;

    /*
        friend

        1.  global function as friend
                friend return_type global_function_name(...);   // declared inside of desinated class
        2.  class as friend
                friend class class_name;                        // declared inside of desinated class
        3.  class member function as friend

        
    */

    // global function as friend
    Building b1;
    goodguy1(b1);

    // class as friend
    Goodguy2 g2;
    g2.visit();

    // class member function as friend
    Goodguy3 g3;
    g3.pub_visit();
    g3.pri_visit();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

// global function, declared as friend to class Building
void goodguy1(Building &b) {
    cout << b.livingroom << endl;
    cout << b.bedroom << endl;      // good to go
}