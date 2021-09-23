# pragma once

# include <iostream>

using namespace std;

template <typename NameType, typename AgeType = int>
class Person {
public:
    NameType name;
    AgeType age;

public:
    Person() { }
    Person(NameType name, AgeType age);
    
    void showPerson();
    void showTypeName();
};

// outside class member function implementation
template <typename NameType, typename AgeType>
Person<NameType, AgeType>::Person(NameType name, AgeType age) {
    this->name = name;
    this->age = age;
}

// outside class member function implementation
template <typename NameType, typename AgeType>
void Person<NameType, AgeType>::showPerson() {
    cout << this->name << " " << this->age << endl;
}
