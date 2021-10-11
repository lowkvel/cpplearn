# include <iostream>
# include <set>

using namespace std;

void func1();
void setPrinter(const set<int> s);

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
            1.  empty();        // is empty?
            2.  size();         // current size
            3.  swap(s);        // swap two sets
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
    
}

void setPrinter(const set<int> s) {
    for (set<int>::const_iterator it = s.begin(); it != s.end(); it++) 
        cout << *it << " ";
    cout << endl;
}
