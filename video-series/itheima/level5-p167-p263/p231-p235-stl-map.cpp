# include <iostream>
# include <map>

using namespace std;

void func1();
void mapPrinter(const map<int, int> &m);

// p231-p235, stl map
int main() {

    cout << "stl map" << endl;

    /*
        stl map

        0.  background
            1.  auto sort for inserted key (binary tree implementation)
            2.  map: not-allow for duplicates (duplicates omitted?)
                multimap: allow for duplicates
        1.  constructor & assignment
            1.  map<T1, T2> m;                  // default constructor
            2.  map(const map &m);              // copy constructor
            3.  map& operator=(const map &m);   // operator= overload
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // constructor & assignment
    map<int, int> m1;
    for (int i = 0; i < 3; i++) m1.insert(pair<int, int>(i, i));    mapPrinter(m1);
    map<int, int> m2(m1);                                           mapPrinter(m2);
    map<int, int> m3; m3 = m1;                                      mapPrinter(m3);
}

void mapPrinter(const map<int, int> &m) {
    for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
        cout << (*it).first << ", " << (*it).second << "; ";
    cout << endl;
}
