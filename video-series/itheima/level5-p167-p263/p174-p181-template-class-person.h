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