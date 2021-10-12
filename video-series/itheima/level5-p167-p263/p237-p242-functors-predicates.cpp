# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

class myAdd {
public:
    int operator()(int v1, int v2) {
        return v1 + v2;
    }
};

class myPrint {
public:
    int count;      // counter

public:
    myPrint() {
        this->count = 0;
    }

    void operator()(string s) {
        cout << s << endl;
        this->count++;
    }
};

// predicate, single parameter
class greaterThanFive { public: bool operator()(int v) { return v > 5; } };
// predicate, double parameters
class myDes { public: bool operator()(int v1, int v2) { return v1 > v2; } };

void func1();
void doPrint(myPrint &mp, string s);
void func2();

// p237-p242, functors & predicates
int main() {

    cout << "functors & predicates" << endl;

    /*
        functors & predicates

        1.  characteristics
            1.  use it like normal function, it can have parameter or return value
            2.  functors can have its own (internal) states
            3.  functors can get passed as parameters into other functions
        2.  predicates
            1.  definition: functor which has bool value type as its returns value
            2.  types:      single/double parameter predicates
    */

    func1();    // 1.   characteristics
    func2();    // 2.   predicates

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // use it like normal function, it can have parameter or return value
    myAdd ma;
    cout << ma(1, 2) << endl;

    // functors can have its own (internal) states
    myPrint mp;
    for (int i = 0; i < 3; i++) mp("functors");
    cout << "functors got printed " << mp.count << " times" << endl;

    // functors can get passed as parameters into other functions
    myPrint mp2;
    doPrint(mp2, "functors2");
    cout << "functors2 got printed " << mp2.count << " times" << endl;
}

void doPrint(myPrint &mp, string s) { mp(s); }

void func2() {
    vector<int> v1; for (int i = 0; i < 10; i++) v1.push_back(i);
    // using anonymous object here, can use normal form (greaterThanFive gtf) if desired
    vector<int>::iterator it = find_if(v1.begin(), v1.end(), greaterThanFive());
    it == v1.end() ? cout << "not found" << endl : cout << "found " << *it << endl;

    vector<int> v2; for (int i = 0; i < 10; i++) v2.push_back(i);
    // using anonymous object here,
    sort(v2.begin(), v2.end(), myDes());
    for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) cout << *it << " ";
    cout << endl;
}
