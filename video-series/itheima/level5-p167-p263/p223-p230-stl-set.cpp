# include <iostream>
# include <set>

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

class mydes {
public:
    bool operator()(int v1, int v2) const {
        return v1 > v2;
    }
};

class mydesp {
public:
    bool operator()(const Person &p1, const Person &p2) const {
        if (p1.age == p2.age)
            return p1.height > p2.height;
        return p1.age > p2.age;
    }
};

void func1();
void setPrinter(const set<int> s);
void setPrinter2(const set<int, mydes> s);
void personPrinter(const set<Person, mydesp> &s);
void multisetPrinter(const multiset<int> s);

// p223-p230, stl set
int main() {

    cout << "stl set" << endl;

    /*
        stl set

        0.  background
            1.  auto sort for insert (binary tree implementation)
            2.  set: not-allow for duplicates (duplicates omitted?)
                multiset: allow for duplicates
        1.  constructor & assignment
            1.  set<T> s;                       // default constructor
            2.  set(const set &s);              // copy constructor
            3.  set& operator=(const set &s);   // operator= overload
        2.  size & swap
            1.  empty();                        // is empty?
            2.  size();                         // current size
            3.  swap(s);                        // swap two sets
        3.  insert & delete
            1.  insert(element);                // insert a element
            2.  erase(position);                // delete element at position p
            3.  erase(s.begin(), s.end());      // delete closed-open range elements
            4.  erase(element);                 // delete specific element
            5.  clear();                        // delete all
        4.  find & count
            1.  find(element);                  // find specific element, return a iterator if exists, otherwise return set.end()
            2.  count(element);                 // count element
        5.  multiset
            1.  multiset<T> ms;
        6.  pair
            1.  pair<type, type> p (value1, value2);
            2.  pair<type, type> p = make_pair(value1, value2);
        7.  sort & functor
            1.  sort
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // constructor & assignment
    set<int> s1;
    for (int i = 0; i < 5; i++) s1.insert(i);   setPrinter(s1);     // using insert to add element to set, auto-sort, no-duplicates (duplicates ommited?)
    set<int> s2(s1);                            setPrinter(s2);     // copy constructor
    set<int> s3; s3 = s1;                       setPrinter(s3);     // operator= overload

    // size & swap
    cout << s1.empty() << " " << s1.size() << endl;
    set<int> s4; for (int i = 0; i < 5; i++) s4.insert(i);  setPrinter(s4);
    set<int> s5; for (int i = 5; i < 9; i++) s5.insert(i);  setPrinter(s5);
    s4.swap(s5); setPrinter(s4); setPrinter(s5);
    
    // insert & delete
    set<int> s6; for (int i = 0; i < 9; i++) s6.insert(i);  setPrinter(s6);
    set<int>::iterator it1 = s6.begin(); it1++; it1++;
    s6.erase(it1);  setPrinter(s6);                 // 2 (position 2) deleted
    s6.erase(6);    setPrinter(s6);                 // 6 deleted
    set<int>::iterator it21 = s6.begin(); it21++; it21++;
    set<int>::iterator it22 = s6.end(); it22--; it22--;
    s6.erase(it21, it22); setPrinter(s6);           // range position [2-5) deleted
    s6.clear();     setPrinter(s6);                 // delete all

    // find & count
    set<int> s7; for (int i = 0; i < 9; i++) s7.insert(i);  setPrinter(s7);
    set<int>::iterator pos = s7.find(7);
    pos != s7.end() ? cout << "found: " << *pos << "; count " << *pos << ": " << s7.count(*pos) << endl : cout << "not exist" << endl;

    // multiset
    set<int> s8; 
    pair<set<int>::iterator, bool> ret1 = s8.insert(0);
    ret1.second ? cout << "insert successful" << endl : cout << "insert unsuccessful" << endl;
    pair<set<int>::iterator, bool> ret2 = s8.insert(0);
    ret2.second ? cout << "insert successful" << endl : cout << "insert unsuccessful" << endl;

    multiset<int> s9; for (int i = 0; i < 9; i++) s9.insert(7);  multisetPrinter(s9);

    // pair
    pair<string, int> pa1 ("Ada", 1);
    cout << pa1.first << " " << pa1.second << endl;
    pair<string, int> pa2 = make_pair("Bob", 2);
    cout << pa2.first << " " << pa2.second << endl;

    // sort & functor
    // https://stackoverflow.com/questions/51235355/comparison-object-being-invocable-as-const 
    set<int> s10; for (int i = 0; i < 10; i++) s10.insert(i);           setPrinter(s10);
    set<int, mydes> s11; for (int i = 0; i < 10; i++) s11.insert(i);    setPrinter2(s11);
    set<Person, mydesp> s12;
    Person p1("a", 35, 175); s12.insert(p1);
    Person p2("b", 45, 180); s12.insert(p2);
    Person p3("c", 40, 170); s12.insert(p3);
    Person p4("d", 25, 190); s12.insert(p4);
    Person p5("e", 35, 160); s12.insert(p5);
    Person p6("g", 35, 200); s12.insert(p6);
    personPrinter(s12);
}

void setPrinter(const set<int> s) {
    for (set<int>::const_iterator it = s.begin(); it != s.end(); it++) 
        cout << *it << " ";
    cout << endl;
}

void setPrinter2(const set<int, mydes> s) {
    for (set<int, mydes>::const_iterator it = s.begin(); it != s.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void personPrinter(const set<Person, mydesp> &s) {
    for (set<Person, mydesp>::const_iterator it = s.begin(); it != s.end(); it++)
        cout << (*it).name << " " << (*it).age << " " << (*it).height << endl;
}

void multisetPrinter(const multiset<int> s) {
    for (multiset<int>::const_iterator it = s.begin(); it != s.end(); it++) 
        cout << *it << " ";
    cout << endl;
}
