# include <iostream>

# include <list>

using namespace std;

void func1();
void listPrinter(const list<int> &l);

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
    
}

void listPrinter(const list<int> &l) {
    for (list<int>::const_iterator it = l.begin(); it != l.end(); it++)
        cout << *it << " ";
    cout << endl;
}
