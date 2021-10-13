# include <iostream>
# include <algorithm>
# include <functional>
# include <numeric>
# include <vector>

using namespace std;

class printIntc { public: void operator()(int v) { cout << v << " "; } };
class Mirror { public: int operator()(int v) { return -v; } };

void func1();   // traverse algorithms
void printInt(int v);

// p243-p263, algorithms
int main() {

    cout << "algorithms" << endl;

    /*
        algorithms

        0.  stl library
            1.  <algorithm>     // the most used one
            2.  <functional>    // templates
            3.  <numeric>       // simple numeric operations
        1.  traverse algorithms
            1.  for_each
            2.  transform
    */

    func1();    // traverse algorithms

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // traverse algorithm, for_each
    vector<int> v1; for (int i = 0; i < 9; i++) v1.push_back(i);
    for_each(v1.begin(), v1.end(), printInt);       cout << endl;   // normal function printInc
    for_each(v1.begin(), v1.end(), printIntc());    cout << endl;   // functor printIntc()

    // traverse algorithm, transform
    vector<int> v2; for (int i = 0; i < 9; i++) v2.push_back(i);
    vector<int> v3; v3.resize(v2.size());                           // resize here is mandatory
    transform(v2.begin(), v2.end(), v3.begin(), Mirror());          // functor Mirror()
    for_each(v2.begin(), v2.end(), printIntc());    cout << endl;   // functor printIntc()
    for_each(v3.begin(), v3.end(), printIntc());    cout << endl;   // functor printIntc()
}

void printInt(int v) { cout << v << " "; }
