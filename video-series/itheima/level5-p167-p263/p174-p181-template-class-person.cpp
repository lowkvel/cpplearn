# include "p174-p181-template-class-person.h"

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