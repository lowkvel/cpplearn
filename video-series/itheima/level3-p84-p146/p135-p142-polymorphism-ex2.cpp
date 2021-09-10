#include <iostream>

using namespace std;

// abstract class AbstractBeverage
class AbstractBeverage {
public:
    // pure virtual functions
    virtual void boil() = 0;
    virtual void brew() = 0;
    virtual void pour() = 0;
    virtual void addons() = 0;

    // virtual destructor
    virtual ~AbstractBeverage() {}

    void makeBeverage() {
        boil();
        brew();
        pour();
        addons();
    }
};

// coffee
class Coffee: public AbstractBeverage {
public:
    virtual void boil() { cout << "boil coffee" << endl; }
    virtual void brew() { cout << "brew coffee" << endl; }
    virtual void pour() { cout << "pour coffee" << endl; }
    virtual void addons() { cout << "addons coffee" << endl; }
};

// tea
class Tea: public AbstractBeverage {
public:
    virtual void boil() { cout << "boil tea" << endl; }
    virtual void brew() { cout << "brew tea" << endl; }
    virtual void pour() { cout << "pour tea" << endl; }
    virtual void addons() { cout << "addons tea" << endl; }
};

void make(AbstractBeverage *absb);
void func1();

// p135-p142, polymorphism ex2
int main() {

    cout << "polymorphism ex2" << endl;

    /*
        polymorphism ex2
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void make(AbstractBeverage *absb) { 
    absb->makeBeverage(); 
    delete absb;
}

void func1() {
    AbstractBeverage *absb = new Coffee;
    absb->makeBeverage();
    delete absb;

    make(new Tea);
}