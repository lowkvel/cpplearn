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
}

void listPrinter(const list<int> &l) {
    for (list<int>::const_iterator it = l.begin(); it != l.end(); it++)
        cout << *it << " ";
    cout << endl;
}
