# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

class Person {
public:
    string name;
    int age;

public:
    Person(string name, int age) {
        this->name = name;
        this->age =  age;
    }
};

void func1();
void printval(int val);

// p185-p188, stl basic
int main() {

    cout << "stl basic" << endl;

    /*
        stl basic

        1.  6 core component
            1.  container   data storage
                1.  sequence container      vector, list, deque, etc
                2.  associative container   map, multimap, set, multiset, etc
                3.  container adapter       stack, queue, priority_queue, etc
            2.  algorithm   general algorithm
                1.  read-only               find, count, search, etc
                2.  write-only              fill, generate, copy, etc
                3.  sort                    sort, reverse, etc
            3.  iteractor   iteracte data storage, between container and algorithm
                1.  input                   read-only       ++, ==, !=
                2.  output                  write-only      ++
                3.  forward                 read-write      ++, ==, !=
                4.  bidirectional           read-write      ++, --
                5.  random-access           read-write      ++, --, [n], -n, <, <=, >, >=
            4.  functor     overloaded ()
                1.  arithmetic              plus<T>, minus<T>, etc
                2.  relational              equal_to<T>, less<T>, etc
                3.  logical                 logical_and<T>, etc
            5.  adapter     container transform
            6.  allocator   allocate/free memory
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // create a vector
    vector<int> v1;

    // add elements at the tail
    v1.push_back(1);    // position 0
    v1.push_back(2);    // position 1

    // access data throuth iterator
    vector<int>::iterator itBegin = v1.begin();     // points to the position of the first element, here points to position 0
    vector<int>::iterator itEnd = v1.end();         // points to the next position of the last element, here points to position 1+1=2
    while(itBegin != itEnd) {
        cout << *itBegin << endl;
        itBegin++;
    }

    // access data throuth iterator, simplified version
    for (vector<int>::iterator itb = v1.begin(); itb != v1.end(); itb++)
        cout << *itb << endl;

    // access data throuth iterator, algorithm version
    for_each(v1.begin(), v1.end(), printval);

    /* for_each() implementation */
    // template <class _InputIterator, class _Function>
    // inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
    // _Function
    // for_each(_InputIterator __first, _InputIterator __last, _Function __f)
    // {
    //     for (; __first != __last; ++__first)
    //         __f(*__first);
    //     return __f;
    // }

    // 1-d vector with Person
    vector<Person> p1;
    p1.push_back(Person("Ada", 1));
    p1.push_back(Person("Bob", 2));
    for (vector<Person>::iterator itb = p1.begin(); itb != p1.end(); itb++)
        cout << (*itb).name << " " << itb->age << endl;

    // 1-d vector tiwh Person*
    vector<Person*> p2;
    Person per1("Ada", 1);  p2.push_back(&per1);
    Person per2("Bob", 2);  p2.push_back(&per2);
    for (vector<Person*>::iterator itb = p2.begin(); itb != p2.end(); itb++)
        cout << (**itb).name << " " << (*itb)->age << endl;

    // 2-d vector
    vector< vector<int> > v;
    vector<int> va; va.push_back(1); va.push_back(2); v.push_back(va);
    vector<int> vb; vb.push_back(3); vb.push_back(4); v.push_back(vb);
    for (vector< vector<int> >::iterator itb1 = v.begin(); itb1 != v.end(); itb1++) {
        for (vector<int>::iterator itb2 = (*itb1).begin(); itb2 != (*itb1).end(); itb2++)
            cout << *itb2 << " ";
        cout << endl;
    }
}

void printval(int val) { cout << val << endl; }
