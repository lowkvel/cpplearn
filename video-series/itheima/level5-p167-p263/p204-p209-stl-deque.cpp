# include <iostream>
# include <deque>
# include <algorithm>

using namespace std;

void func1();
void dequePrinter(const deque<int> &d);

// p104-p209, stl deque
int main() {

    cout << "stl deque" << endl;

    /*
        stl deque (double-ended queue)
        0.  difference with vector and its mechanism
            1.  difference
                1.  double-ended vector: insert/delete at both head and tail end 
                2.  faster insert/detele time at head compared to vecter
                3.  slower accessing time compared to vector
            2.  mechanism
                1.  deque has a bookkeeper, which stores a series of pointers points to multiple buffer area
                2.  each buffer has limited capacity, and new buffer area will get allocated if current buffer area is filled
        1.  constructor
            1.  deque<T> d;                         // default constructor
            2.  deque(d.begin(), d.end());          // copy [d.begin(), d.end()), closed-open range
            3.  deque(n, element);                  // construct n * element
            4.  deque(const deque &d);              // copy constructor
        2.  assignment
            1.  deque& operator=(const deque &d);   // overload =
            2.  assign(begin, end);                 // assign [d.begin(), d.end()), closed-open range
            3.  assign(n, element);                 // assign n * element
        3.  capacity & size
            1.  empty();                        // is empty?
            2.  size();                         // current size
            3.  resize(int n);                  // resize size into n (capacity stays untouched), delete the oversized element at the end or fill with default value
            4.  resize(int n, element);         // resize size into n (capacity stays untouched), delete the oversized element at the end or fill with given value element
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
            10. clear();                                            // delete all
        5.  get element
            1.  at(int p);      // get element at position p
            2.  operator[];     // get element through []
            3.  front();        // get the first element
            4.  back);          // get the last element
        6.  sort
            1.  sort(iterator begin, iterator end);
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // constructor
    deque<int> d1;                                                      // default constructor
    for (int i = 0; i < 10; i++) d1.push_back(i);   dequePrinter(d1);
    deque<int> d2(d1.begin(), d1.end());            dequePrinter(d2);   // copy [d.begin(), d.end()), closed-open range
    deque<int> d3(10, 7);                           dequePrinter(d3);   // construct n * element
    deque<int> d4(d3);                              dequePrinter(d4);   // copy constructor

    // assignment
    deque<int> d5 = d1;                             dequePrinter(d5);   // overload =
    deque<int> d6; d6.assign(d5.begin(), d5.end()); dequePrinter(d6);   // assign [d.begin(), d.end()), closed-open range
    deque<int> d7; d7.assign(10, 7);                dequePrinter(d7);   // assign n * element

    // capacity & size
    deque<int> d8 = d1; 
    cout << d8.empty() << endl;
    cout << d8.size() << ": "; dequePrinter(d8);
    d8.resize(20); cout <<  d8.size() << ": ";      dequePrinter(d8);   // expansion with default int value 0
    d8.resize(14); cout << d8.size() << ": ";       dequePrinter(d8);   // shrinking and delete the oversized element at the end
    d8.resize(18, 3); cout << d8.size() << ": ";    dequePrinter(d8);   // expansion with given int value 1

    // insert & delete
    deque<int> d9 = d1;
    d9.push_front(999);                             dequePrinter(d9);   // add element e at the end
    d9.push_back(999);                              dequePrinter(d9);   // add element e at the end
    d9.pop_front();                                 dequePrinter(d9);   // delete the first element
    d9.pop_back();                                  dequePrinter(d9);   // delete the last element
    d9.insert(d9.begin(), 999);                     dequePrinter(d9);   // insert element e at position p
    d9.insert(d9.begin(), 2, 999);                  dequePrinter(d9);   // insert n * element e at position p
    d9.insert(d9.begin(), d1.begin(), d1.end());    dequePrinter(d9);   // insert [d.begin(), d.end()) at position p
    deque<int>::iterator it1 = d9.begin(); it1++;
    d9.erase(it1);                                  dequePrinter(d9);   // delete element where iterator points
    deque<int>::iterator it21 = d9.begin(); it21++;
    deque<int>::iterator it22 = d9.end(); it22--; 
    d9.erase(it21, it22);                           dequePrinter(d9);   // delete elements from start to end
    d9.clear();                                     dequePrinter(d9);   // delete all

    // get element
    deque<int> d10 = d1;    dequePrinter(d10);
    cout << d10.at(7) << " " << d10[7] << " " << d10.front() << " " << d10.back() << endl;

    // sort
    deque<int> d11;
    d11.push_back(1);   d11.push_back(2);   d11.push_back(3);
    d11.push_front(9);  d11.push_front(8);  d11.push_front(7);
    dequePrinter(d11);
    sort(d11.begin(), d11.end());
    dequePrinter(d11);
}

void dequePrinter(const deque<int> &d) {
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
        cout << *it << " ";
    cout << endl;
}
