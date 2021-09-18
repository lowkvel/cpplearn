# include <iostream>

using namespace std;

template <typename NameType, typename AgeType>
class Person {
public:
    NameType name;
    AgeType age;

public:
    Person(NameType name, AgeType age) {
        this->name = name;
        this->age = age;
    }

    void showPerson() {
        cout << this->name << " " << this->age << endl;
    }
};

void func1();

// p167-p173, template class
int main() {

    cout << "template class" << endl;

    /*
        template class

        0.  purpose
            parameterize typename
        1.  grammar
            1.  declaration/definition: 
                template <typename T>
                class declaration/definition
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    Person<string, int> p1("Ada", 1);
    p1.showPerson();
    
}
