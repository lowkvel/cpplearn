# include <iostream>

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

void func1();
void doPrint(myPrint &mp, string s);

// p237-p242, functors & predicates
int main() {

    cout << "functors & predicates" << endl;

    /*
        functors & predicates

        1.  characteristics
            1.  use it like normal function, it can have parameter or return value
            2.  functors can have its own (internal) states
            3.  functors can get passed as parameters into other functions

    */

    // 1.   characteristics
    func1();

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
