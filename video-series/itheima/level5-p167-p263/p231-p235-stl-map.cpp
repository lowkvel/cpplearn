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
        2.  size & swap
            1.  empty();
            2.  size();
            3.  swap(m);
        3.  insert & delete
            1.  insert(element);                // insert, 4 ways, shown below
            2.  erase(position);
            3.  erase(m.begin(), m.end());
            4.  erase(key);
            5.  clear();
        4.  find & count
            1.  find(key);                      // find specific pair, return a iterator if exists, otherwise return map.end()
            2.  count(key);                     // count element
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

    // size & swap
    cout << m1.empty() << " " << m1.size() << endl;
    map<int, int> m4; for (int i = 0; i < 3; i++) m4.insert(pair<int, int>(i, i));    
    map<int, int> m5; for (int i = 0; i < 5; i++) m5.insert(pair<int, int>(i, i));    
    mapPrinter(m4); mapPrinter(m5);
    m4.swap(m5);
    mapPrinter(m4); mapPrinter(m5);

    // insert & delete
    map<int, int> m6;
    for (int i = 0; i < 3; i++) m6.insert(pair<int, int>(i, i));                // way 1
    for (int i = 3; i < 6; i++) m6.insert(make_pair(i, i));                     // way 2
    for (int i = 6; i < 9; i++) m6.insert(map<int, int>::value_type(i, i));     // way 3
    m6[9] = 9;                                                                  // way 4, not recommended for insertion
    mapPrinter(m6);
    map<int, int>::iterator it1 = m6.begin(); it1++; it1++;
    m6.erase(m6.begin());   mapPrinter(m6);
    map<int, int>::iterator it21 = m6.begin(); it21++; it21++;
    map<int, int>::iterator it22 = m6.end(); it22--; it22--;
    m6.erase(it21, it22);   mapPrinter(m6);
    m6.erase(8);            mapPrinter(m6);
    m6.clear();             mapPrinter(m6);

    // find & count
    map<int, int> m7;
    for (int i = 0; i < 9; i++) m7.insert(pair<int, int>(i, i));    mapPrinter(m7);
    map<int, int>::iterator pos = m7.find(3);
    pos != m7.end() ? cout << "found key: " << (*pos).first << "; count " << (*pos).first << ", " << (*pos).second << ": " << m7.count((*pos).first) << endl : cout << "not exist" << endl;

}

void mapPrinter(const map<int, int> &m) {
    for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
        cout << (*it).first << ", " << (*it).second << "; ";
    cout << endl;
}
