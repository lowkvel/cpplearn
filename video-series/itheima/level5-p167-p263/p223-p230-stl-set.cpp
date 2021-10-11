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
}

void setPrinter(const set<int> s) {
    for (set<int>::const_iterator it = s.begin(); it != s.end(); it++) 
        cout << *it << " ";
    cout << endl;
}
