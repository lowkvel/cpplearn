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
    //virtual void speak() { cout << "animal speak" << endl; }

    // dynamic polymorphism, pure virtual function -> abstract class Animal
    virtual void speak() = 0;

    // constructor
    Animal() { cout << "animal constructed" << endl; }

    // destructor, virtual
    virtual ~Animal() { cout << "animal destructed" << endl; }
    // destructor, pure virtual, specific implememtation is mandatory
    //virtual ~Animal() = 0;
};

// pure virtual destructor needs a implementation
//Animal::~Animal() { cout << "animal destructed" << endl; }

class Cat: public Animal {
public:
    string *name;

    // constructor, override
    Cat(string name) { 
        this->name = new string(name);
        cout << *this->name << " cat constructed" << endl; 
    }

    // destructor, override
    ~Cat() {
        if (name != NULL) {
            cout << *name << " cat destructed" << endl;
            delete name;
            name = NULL;
        }
    }

    // if the child Cat overrode the parent Animal's virtual function speak(), like below
    // the vfptr inherited (a copied one) from parent Animal will points to a new vftable
    // but the address stored inside of that vftable is overrode with &Cat::speak() instead of the original &Animal::speak()
    virtual void speak() {              // the "virtual" keyword can be omitted here
        cout << *name << " cat speak" << endl;
    }
};

class Dog: public Animal {
public:
    string *name;

    // constructor, override
    Dog(string name) { 
        this->name = new string(name);
        cout << *this->name << " dog constructed" << endl; 
    }

    // destructor, override
    ~Dog() {
        if (name != NULL) {
            cout << *name << " dog destructed" << endl;
            delete name;
            name = NULL;
        }
    }   

    // dynamic polymorphism
    void speak() {                      // the "virtual" keyword is omitted here
        cout << *name << " dog speak" << endl;
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

        3.  virtual function
                grammar:            virtual return_type function_name(parameter_list) {...}

        4.  pure virtual function
                grammar:            virtual return_type function_name(parameter_list) = 0;
                if a class has pure virtual function, it is also called abstract class, which cannot be instantiated
                if a class inherited from a abstract class and wants to get instantiated
                it needs to override all pure virtual functions from the parent to become a concrete class, otherwise it remains abstract

        5.  virtual destructor
            1.  normal virtual destructor
                implememted in child class
            2.  pure virtual destructor
                pure virtual destructor must be implememted, otherwise the compiler wont find the implememted destructor for parent class 
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
    //Animal a;   doSpeak(a);     // original, it is a abstract class now, cannot be instantiated
    Cat c = Cat("slim");    // dynamic polymophism
    doSpeak(c);
    //delete &c; 
    // You must not delete an object that was not allocated with new. 
    // If the object was allocated on the stack pool, your compiler has already generated a call to its destructor at the end of its scope. 
    // This means you will call the destructor twice, with potentially very bad effects.
    // https://stackoverflow.com/questions/4355468/is-it-possible-to-delete-a-non-new-object 

    Dog d = Dog("blue");    // dynamic polymophism    
    doSpeak(d);
    //delete &d; 
    // You must not delete an object that was not allocated with new. 
    // If the object was allocated on the stack pool, your compiler has already generated a call to its destructor at the end of its scope. 
    // This means you will call the destructor twice, with potentially very bad effects.  
    // https://stackoverflow.com/questions/4355468/is-it-possible-to-delete-a-non-new-object 

    Animal *cp = new Cat("fat");   
    cp->speak();    
    delete cp; 
    cp = NULL;

    Animal *dp = new Dog("cool");   
    dp->speak();
    delete dp; 
    dp = NULL;
}

// accepts a reference of a object from parent class Animal
// speak() from Animal (parent) or Cat (child) will be called depending on whether it is virtual in parent or not
// if speak() in Animal is not virtual, then speak() in Animal will be called no matter what child class object of Animal class is passed in
// if speak() in Animal is virtual, then speak() in child class will be called depending on what child class object of Animal class is passed in
void doSpeak(Animal &animal) {
    animal.speak();
}
