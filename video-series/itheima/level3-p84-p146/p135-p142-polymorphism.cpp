#include <iostream>

using namespace std;

class Animal {
public:
    // static polymorphism
    // the address of function speak() is determined in compiling phase 
    //void speak() { cout << "animal speak" << endl; }

    // dynamic polymorphism, virtual function
    // the address of function speak() is determined in running phase
    // the virtual means that a vfptr (virtual function (table) pointer) is stored here, similar to vbptr
    // and vfptr points to a vftable (virtual function table), which stores the address: &Animal::speak()
    virtual void speak() { cout << "animal speak" << endl; }
};

class Cat: public Animal {
public:
    // if the child Cat overrode the parent Animal's virtual function speak(), like below
    // the vfptr inherited (a copied one) from parent Animal will points to a new vftable
    // but the address stored inside of that vftable is overrode with &Cat::speak() instead of the original &Animal::speak()
    virtual void speak() {              // the "virtual" keyword can be omitted here
        cout << "cat speak" << endl;
    }
};

class Dog: public Animal {
public:
    void speak() {                      // the "virtual" keyword is omitted here
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
                including:          function overload & operator overload
            
        2.  dynamic polymorphism:   function address deretmined in running phase
                including:          derived class (child class) with virtual function override and virtual inheritance class
                requirement:        derived class needs to override parent virtual same-return_type/name/para_list function

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
    Animal a;   doSpeak(a);     // original
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
