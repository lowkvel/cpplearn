# include <iostream>
# include <algorithm>
# include <functional>
# include <numeric>
# include <vector>
# include <ctime>

using namespace std;

class Person {
public:
    string name;
    int age;

public:
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }

    bool operator==(const Person &p) { return this->name == p.name && this->age == p.age; }
};

class printIntc { public: void operator()(int v) { cout << v << " "; } };
class Mirror { public: int operator()(int v) { return -v; } };
class greaterFive { public: bool operator()(int v) { return v > 5; } };
class greaterFivep { public: bool operator()(Person &p) { return p.age > 5; } };

void func1();   // traverse algorithms
void func2();   // search algorithms
void func3();   // sort algorithms
void printInt(int v);
void printVector(const vector<int> &v);

// p243-p263, algorithms
int main() {

    cout << "algorithms" << endl;

    /*
        algorithms

        0.  stl library
            1.  <algorithm>     // the most used one
            2.  <functional>    // templates
            3.  <numeric>       // simple numeric operations
        1.  traverse algorithms
            1.  for_each
            2.  transform
        2.  search algorithms
            1.  find(iterator_begin, iterator_end, value);              // operator== overload required if item is not built-in datatype
            2.  find_if(iterator_begin, iterator_end, _Predicate);
            3.  adjacent_find(iterator_begin, iterator_end);
            4.  binary_search(iterator_begin, iterator_end, value); 
            5.  count(iterator_begin, iterator_end, value); 
            6.  count_if(iterator_begin, iterator_end, _Predicate);
        3.  sort algorithms
            1.  sort(iterator_begin, iterator_end, _Predicate);
            2.  random_shuffle(iterator_begin, iterator_end);
            3.  merge(iterator1_begin, iterator1_end, iterator2_begin, iterator2_end, iterator_dest_begin);
            4.  reverse(iterator_begin, iterator_end);
    */

    func1();    // traverse algorithms
    func2();    // search algorithms
    func3();    // sort algorithms

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // traverse algorithm, for_each
    vector<int> v1; for (int i = 0; i < 9; i++) v1.push_back(i);
    for_each(v1.begin(), v1.end(), printInt);       cout << endl;   // normal function printInc
    for_each(v1.begin(), v1.end(), printIntc());    cout << endl;   // functor printIntc()

    // traverse algorithm, transform
    vector<int> v2; for (int i = 0; i < 9; i++) v2.push_back(i);
    vector<int> v3; v3.resize(v2.size());                           // resize here is mandatory
    transform(v2.begin(), v2.end(), v3.begin(), Mirror());          // functor Mirror()
    for_each(v2.begin(), v2.end(), printIntc());    cout << endl;   // functor printIntc()
    for_each(v3.begin(), v3.end(), printIntc());    cout << endl;   // functor printIntc()
}

void func2() {
    vector<int> v1; for (int i = 0; i < 9; i++) v1.push_back(i); v1.push_back(8);
    vector<Person> v2;
    Person p1("a", 1); v2.push_back(p1);
    Person p2("b", 2); v2.push_back(p2);
    Person p3("c", 3); v2.push_back(p3); v2.push_back(p3);
    Person p4("d", 4);

    // search algorithm, find
    vector<int>::iterator it11 = find(v1.begin(), v1.end(), 7);
    it11 == v1.end() ? cout << "7 not found" << endl : cout << "7 found" << endl;
    // operator== overload required because of user-defined Person data type
    vector<Person>::iterator it22 = find(v2.begin(), v2.end(), p4);
    it22 == v2.end() ? cout << "p4 not found" << endl : cout << "p4 found" << endl;

    // search algorithm, find_if
    vector<int>::iterator it31 = find_if(v1.begin(), v1.end(), greaterFive());
    it31 == v1.end() ? cout << ">5 not found" << endl : cout << ">5 found" << endl;
    vector<Person>::iterator it32 = find_if(v2.begin(), v2.end(), greaterFivep());
    it31 == v1.end() ? cout << ">5p not found" << endl : cout << ">5p found" << endl;

    // search algorithm, adjacent_find
    vector<int>::iterator it41 = adjacent_find(v1.begin(), v1.end());
    it31 == v1.end() ? cout << "adjacent duplicates not found" << endl : cout << "adjacent duplicates found" << endl;
    //vector<int>::iterator it42 = adjacent_find(v2.begin(), v2.end());

    // search algorithm, binary_search
    cout << binary_search(v1.begin(), v1.end(), 7) << endl;
    //cout << binary_search(v2.begin(), v2.end(), p2) << endl;

    // search algorithm, count
    cout << count(v1.begin(), v1.end(), 8) << endl;
    cout << count(v2.begin(), v2.end(), p3) << endl;

    // search algorithm, count_if
    cout << count_if(v1.begin(), v1.end(), greaterFive()) << endl;
    cout << count_if(v2.begin(), v2.end(), greaterFivep()) << endl;
}

void func3() {
    vector<int> v1; for (int i = 0; i < 9; i++) v1.push_back(i); v1.push_back(8);
    vector<Person> v2;
    Person p1("a", 1); v2.push_back(p1);
    Person p2("b", 2); v2.push_back(p2);
    Person p3("c", 3); v2.push_back(p3); v2.push_back(p3);
    Person p4("d", 4);

    srand((unsigned int) time (NULL));

    // sort algorithm, sort
    vector<int> v3 = v1;
    sort(v3.begin(), v3.end(), greater<int>());     printVector(v3);

    // sort algorithm, random_shuffle
    vector<int> v4 = v1;
    random_shuffle(v4.begin(), v4.end());           printVector(v4);

    // sort algorithm, merge
    vector<int> v5 = v1;
    vector<int> v6 = v1;
    vector<int> v7; v7.resize(v5.size() + v6.size());       // resize here is required
    merge(v5.begin(), v5.end(), v6.begin(), v6.end(), v7.begin());  printVector(v7);

    // sort algorithm, reverse
    vector<int> v8 = v1;
    reverse(v8.begin(), v8.end());                  printVector(v8);
}

void printInt(int v) { cout << v << " "; }

void printVector(const vector<int> &v) {
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;
}
