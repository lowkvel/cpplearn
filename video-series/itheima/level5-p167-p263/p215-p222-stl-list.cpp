# include <iostream>

# include <list>

using namespace std;

class Person {
public:
    string name;
    int age;
    int height;

public:
    Person(string name, int age, int height) {
        this->name = name;
        this->age = age;
        this->height = height;
    }
};

void func1();
bool myasc(int v1, int v2);
bool mydes(int v1, int v2);
bool personSortRule(Person p1, Person p2);
void listPrinter(const list<int> &l);
void personPrinter(const list<Person> &l);

// p215-p222, stl list
int main() {

    cout << "stl list" << endl;

    /*
        stl list

        1.  constructor
            1.  list<T> l;                  // default constructor
            2.  list(l.begin(), l.end)();   // copy [begin, end), closed-open range
            3.  list(n, element);           // construct n * element
            4.  list(const list &l);        // copy constructor
        2.  assign & swap
            1.  list& operator=(const list &l);
            2.  assign(l.begin(), l.end());
            3.  assign(n, element);
            4.  swap(l);
        3.  size & resize
            1.  empty();                        // is empty?
            2.  size();                         // current size
            3.  resize(int n);                  // resize size into n, delete the oversized element at the end or fill with default value
            4.  resize(int n, element);         // resize size into n, delete the oversized element at the end or fill with given value element
        4.  insert & delete
            1.  push_front(e);                                      // add element e at the head
            2.  push_back(e);                                       // add element e at the end
            3.  pop_front();                                        // delete the first element
            4.  pop_back();                                         // delete the last element
            5.  insert(const_iterator p, e)                         // insert element e at position p
            6.  insert(const_iterator p, int n, e);                 // insert n * element e at position p
            7.  insert(p, begin, end);                              // insert [d.begin(), d.end()) at position p
            8.  erase(const_iterator p);                            // delete element where iterator points
            9.  erase(const_iterator start, const_iterator end);    // delete elements from start to end
            10. remove(e);                                          // delete all elements matching e
            11. clear();                                            // delete all
        5.  get element
            1.  front();        // get the first element
            2.  back);          // get the last element
        6.  reverse & sort
            1.  reverse();      // reverse the list
            2.  sort();         // sort the list
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // constructor
    list<int> l1;
    for (int i = 0; i < 10; i++) l1.push_back(i);   listPrinter(l1);    // default
    list<int> l2(l1.begin(), l1.end());             listPrinter(l2);    // closed-open range copy
    list<int> l3(10, 1);                            listPrinter(l3);    // n element
    list<int> l4(l3);                               listPrinter(l4);    // pure copy

    // assign & swap
    list<int> l5 = l1;                              listPrinter(l5);    // operator= overload
    list<int> l6; l6.assign(l1.begin(), l1.end());  listPrinter(l6);    // closed-open range assign
    list<int> l7; l7.assign(10, 1);                 listPrinter(l7);    // n element
    l7.swap(l6); listPrinter(l6); listPrinter(l7);                      // swap

    // size & resize
    list<int> l8 = l1;
    cout << l8.empty() << " " << l8.size() << endl;     // empty, size
    l8.resize(15);      listPrinter(l8);                // expansion with default value 0
    l8.resize(20, 1);   listPrinter(l8);                // expansion with given value 1
    l8.resize(5);       listPrinter(l8);                // shrinking
    l8.resize(10);      listPrinter(l8);                // re-expansion with default value 0

    // insert & delete
    list<int> l9 = l1;                              listPrinter(l9);
    l9.push_front(7);                               listPrinter(l9);    // push_front
    l9.push_back(7);                                listPrinter(l9);    // push_back
    l9.pop_front();                                 listPrinter(l9);    // pop_front
    l9.pop_back();                                  listPrinter(l9);    // pop_back
    list<int>::iterator it1 = l9.begin(); it1++; 
    l9.insert(it1, 7);                              listPrinter(l9);    // insert
    list<int>::iterator it2 = l9.begin(); it2++;
    l9.insert(it2, 5, 7);                           listPrinter(l9);    // insert
    l9.erase(--it1);                                listPrinter(l9);    // erase
    list<int>::iterator it31 = l9.begin(); it31++;
    list<int>::iterator it32 = l9.end(); it32--;
    l9.erase(it31, it32);                           listPrinter(l9);    // erase
    l9.push_back(99); l9.push_front(99);            listPrinter(l9);
    l9.remove(99);                                  listPrinter(l9);    // remove
    l9.clear();                                     listPrinter(l9);    // clear
    
    // get element
    list<int> l10 = l1; listPrinter(l10);
    cout << l10.front() << " " << l10.back() << endl;

    // reverse & sort
    list<int> l11 = l1;     listPrinter(l11);
    l11.reverse();          listPrinter(l11);   // reverse
    l11.sort();             listPrinter(l11);   // sort
    l11.sort(myasc);        listPrinter(l11);   // sort ascending
    l11.sort(mydes);        listPrinter(l11);   // sort descending
    
    // sort example
    list<Person> l12;
    Person p1("a", 35, 175); l12.push_back(p1);
    Person p2("b", 45, 180); l12.push_back(p2);
    Person p3("c", 40, 170); l12.push_back(p3);
    Person p4("d", 25, 190); l12.push_back(p4);
    Person p5("e", 35, 160); l12.push_back(p5);
    Person p6("g", 35, 200); l12.push_back(p6);
    personPrinter(l12);
    l12.sort(personSortRule);
    personPrinter(l12);
}

bool myasc(int v1, int v2) {return v1 < v2;}    // ascending
bool mydes(int v1, int v2) {return v1 > v2;}    // descending
bool personSortRule(Person p1, Person p2) {
    if (p1.age == p2.age)
        return p1.height > p2.height;
    return p1.age < p2.age;
}

void listPrinter(const list<int> &l) {
    for (list<int>::const_iterator it = l.begin(); it != l.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void personPrinter(const list<Person> &l) {
    for (list<Person>::const_iterator it = l.begin(); it != l.end(); it++)
        cout << (*it).name << " " << (*it).age << " " << (*it).height << endl;
}