#include <iostream>

using namespace std;

class Animal {
public:
    // static polymorphism
    // the address of function speak() is determined in compiling phase 
    //void speak() { cout << "animal speak" << endl; }

    // dynamic polymorphism, virtual function
    // the address of function speak() is determined in running phase
    virtual void speak() { cout << "animal speak" << endl; }
};

class Cat: public Animal {
public:
    void speak() {
        cout << "cat speak" << endl;
    }
};

class Dog: public Animal {
public:
    void speak() {
        cout << "dog speak" << endl;
    }
};

void func1();
void doSpeak(Animal &animal);

// p135-p142, polymorphism
int main() {

    cout << "polymorphism" << endl;

    /*
        polymorphism

        1.  static polymorphism:    function address determined in compiling phase
            including:      function overload & operator overload
            
        2.  dynamic polymorphism:   function address deretmined in running phase
            including:      derived class (child class) and virtual inheritance class
            requirement:    derived class needs to override parent virtual same-return_type/name/para_list function

    */

    // func1()
    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {

    // we want the cat/dog to speak, but we will get animal speaking if speak() in Animal is not virtual
    // because the address of function speak() in Animal is determined in compiling phase if it is not virtual, this is static polymorphism
    // after we change function speak() in Animal to virtual, cat/dog will get their speak()
    Animal a;   doSpeak(a);     // 
    Cat c;      doSpeak(c);     // dynamic polymophism
    Dog d;      doSpeak(d);     // dynamic polymophism

}


// accepts a reference of a object from parent class Animal
// speak() from Animal (parent) or Cat (child) will be called depending on whether it is virtual in parent or not
// if speak() in Animal is not virtual, then speak() in Animal will be called no matter what child class object of Animal class is passed in
// if speak() in Animal is virtual, then speak() in child class will be called depending on what child class object of Animal class is passed in
void doSpeak(Animal &animal) {
    animal.speak();
}
