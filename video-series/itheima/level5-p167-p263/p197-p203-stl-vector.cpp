# include <iostream>
# include <vector>

using namespace std;

void func1();
void vectorPrinter(vector <int> &v);

// p197-p203, stl vector
int main() {

    cout << "stl vector" << endl;

    /*
        stl vector
        
        1.  constructor
            1.  vector<T> v;                    // default constructor
            2.  vector(v.begin(), v.end());     // copy [v.begin(), v.end()), closed-open range
            3.  vector(n, element);             // construct n * element
            4.  vector(const vector &vec);      // copy constructor
        2.  assignment
            1.  vector& operator=(const vector &vec);   // overload =
            2.  assign(begin, end);                     // assign [v.begin(), v.end()), closed-open range
            3.  assign(n, element);                     // assign n * element
        3.  capacity & size
            1.  empty();                        // is empty?
            2.  capacity();                     // max size
            3.  size();                         // current size
            4.  resize(int n);                  // resize size into n (capacity stays untouched), delete the oversized element at the end or fill with default value
            5.  resize(int n, element);         // resize size into n (capacity stays untouched), delete the oversized element at the end or fill with given value element
        4.  insert & delete
            1.  push_back(e);                                       // add element e at the end
            2.  pop_back();                                         // delete the last element
            3.  insert(const_iterator p, e)                         // insert element e at position p
            4.  insert(const_iterator p, int n, e);                 // insert n * element e at position p
            5.  erase(const_iterator p);                            // delete element where iterator points
            6.  erase(const_iterator start, const_iterator end);    // delete elements from start to end
            7.  clear();                                            // delete all
        5.  get element
            1.  at(int p);      // get element at position p
            2.  operator[];     // get element through []
            3.  front();        // get the first element
            4.  back);          // get the last element
        6.  swap
            1.  swap(v);        // swap two vectors
            
            vector<int>(v13) is a anonymous object [missing the variable name between ">("] created by vector copy constructor 
            however vector copy constructor uses the to-be-copied vector's size() as new vector's capacity(), 
            this reduces memory requirement for the newly copied vector
                vector<int> v14(100,1);     // this gives v14 with capacity()=100 and size()=100
                v14.resize(10);             // this reduces v14's size()=10, but capacity()=100 stay untouched
                vector<int> v15(v14);       // copy constructor copys v14's size()=10 to v15 as its both capacity()=10 and size()=10
            then .swap() swaps the pointers direction, so swapped v13's capacity() reduces to the resize() capacity
            and because the .swap() swapped the original vector and the anonymous vector object, 
            makes the huge original vector become anonymous, so the compiler will delete it after this line of code executed (automatically freed)
        7.  reserve
            1.  reserve(int n);     // vector container reserve n capacity (reduce future expansion times), but it is inaccessible if not initialized already
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // constructor
    vector<int> v1;                                                     // default constructor
    for (int i = 0; i < 10; i++) v1.push_back(i);   vectorPrinter(v1);
    vector<int> v2(v1.begin(), v1.end());           vectorPrinter(v2);  // copy [v.begin(), v.end()), closed-open range
    vector<int> v3(10, 1);                          vectorPrinter(v3);  // construct n * element
    vector<int> v4(v3);                             vectorPrinter(v4);  // copy constructor

    // assignment
    vector<int> v5 = v1;                                vectorPrinter(v5);  // overload =
    vector<int> v6; v6.assign(v5.begin(), v5.end());    vectorPrinter(v6);  // assign [v.begin(), v.end()), closed-open range
    vector<int> v7; v7.assign(10, 1);                   vectorPrinter(v7);  // assign n * element

    // capacity & size
    vector<int> v8 = v1; 
    cout << v8.empty() << endl;
    cout << v8.capacity() << " " << v8.size() << ": "; vectorPrinter(v8);
    v8.resize(20); cout << v8.capacity() << " " << v8.size() << ": "; vectorPrinter(v8);    // expansion with default int value 0
    v8.resize(14); cout << v8.capacity() << " " << v8.size() << ": "; vectorPrinter(v8);    // shrinking and delete the oversized element at the end
    v8.resize(18, 3); cout << v8.capacity() << " " << v8.size() << ": "; vectorPrinter(v8); // expansion with given int value 1

    // insert & delete
    vector<int> v9 = v1;
    v9.push_back(999); vectorPrinter(v9);               // add element e at the end
    v9.pop_back(); vectorPrinter(v9);                   // delete the last element
    v9.insert(v9.begin(), 999); vectorPrinter(v9);      // insert element e at position p
    v9.insert(v9.begin(), 2, 999); vectorPrinter(v9);   // insert n * element e at position p
    v9.erase(v9.begin()); vectorPrinter(v9);            // delete element where iterator points
    v9.erase(v9.begin(), v9.end()); vectorPrinter(v9);  // delete elements from start to end
    v9.clear(); vectorPrinter(v9);                      // delete all

    // get element
    vector<int> v10 = v1;
    cout << v10.at(7) << " " << v10[7] << " " << v10.front() << " " << v10.back() << endl;

    // swap
    vector<int> v11 = v1; vectorPrinter(v11);
    vector<int> v12 = v8; vectorPrinter(v12);
    v11.swap(v12);                                      // swap two vectors
    vectorPrinter(v11);
    vectorPrinter(v12);

    /*  the purpose of swap

        vector<int>(v13) is a anonymous object [missing the variable name between ">("] created by vector copy constructor 
        however vector copy constructor uses the to-be-copied vector's size() as new vector's capacity(), 
        this reduces memory requirement for the newly copied vector
            vector<int> v14(100,1);     // this gives v14 with capacity()=100 and size()=100
            v14.resize(10);             // this reduces v14's size()=10, but capacity()=100 stay untouched
            vector<int> v15(v14);       // copy constructor copys v14's size()=10 to v15 as its both capacity()=10 and size()=10
        then .swap() swaps the pointers direction, so swapped v13's capacity() reduces to the resize() capacity
        and because the .swap() swapped the original vector and the anonymous vector object, 
        makes the huge original vector become anonymous, so the compiler will delete it after this line of code executed (automatically freed)
    */
    vector<int> v13(10000, 1);  cout << "v13\t" << v13.capacity() << "\t" << v13.size() << endl;
    v13.resize(100);            cout << "v13r\t" << v13.capacity() << "\t" << v13.size() << endl;
    vector<int>(v13).swap(v13); cout << "v13rs\t" << v13.capacity() << "\t" << v13.size() << endl;

    // reserve
    vector<int> v16;
    int n1 = 0; 
    int *p1 = NULL;
    for (int i = 0; i< 10000; i++) {
        v16.push_back(i);
        if (p1 != &v16[0]) {        // if p1 does not points to v16[0] which is the vector's first address
            p1 = &v16[0];           // that means the vector got expanded or first initialized
            n1++;
        }
    }
    cout << n1 << endl;             // for 10000 element, 18 expansion (copy and paste) happens, time wasting

    vector<int> v17;
    v17.reserve(10000);             // this reserves 10000 capacity for v17
    int n2 = 0; 
    int *p2 = NULL;
    for (int i = 0; i< 10000; i++) {
        v17.push_back(i);
        if (p2 != &v17[0]) {        // if p2 does not points to v17[0] which is the vector's first address
            p2 = &v17[0];           // that means the vector got expanded or first initialized
            n2++;
        }
    }
    cout << n2 << endl;             // for 10000 element, only 1 initialization happens, time saving
}

void vectorPrinter(vector <int> &v) {
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;
}
