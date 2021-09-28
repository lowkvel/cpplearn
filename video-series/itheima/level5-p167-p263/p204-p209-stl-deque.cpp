# include <iostream>
# include <deque>

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
}

void dequePrinter(const deque<int> &d) {
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
        cout << *it << " ";
    cout << endl;
}
