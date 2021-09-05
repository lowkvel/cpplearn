#include <iostream>

using namespace std;

void implementation_without_inheritance();
void implementation_with_inheritance();

// implementation without inheritance
class Cpp {
public:
    void header() {
        cout << "header" << endl;
    }
    void footer() {
        cout << "footer" << endl;
    }
    void sidebar() {
        cout << "sidebar" << endl;
    }
    void content() {                    // class specific code
        cout << "cpp content" << endl;
    }
};

// implementation without inheritance
class Python {
public:
    void header() {                     // inheritable code
        cout << "header" << endl;
    }
    void footer() {                     // inheritable code
        cout << "footer" << endl;
    }
    void sidebar() {                    // inheritable code
        cout << "sidebar" << endl;
    }
    void content() {                    // class specific code
        cout << "python content" << endl;
    }
};

// implementation with inheritance: base
class BasePage {
public:
    void header() {                     // inheritable code
        cout << "header" << endl;
    }
    void footer() {                     // inheritable code
        cout << "footer" << endl;
    }
    void sidebar() {                    // inheritable code
        cout << "sidebar" << endl;
    }
};

// implementation with inheritance: cpp
class Cppi: public BasePage {
public:
    void content() {                    // class specific code
        cout << "cpp content" << endl;
    }
};

// implementation with inheritance: python
class Pythoni: public BasePage {
public:
    void content() {                    // class specific code
        cout << "python content" << endl;
    }
};

// p127-p134, inheritance
int main() {

    cout << "inheritance" << endl;

    /*
        inheritance

        1.  grammar
            class parent_class {
                ...
            };
            class child_class: inheritance_type parent_class {
                ...
            };

        


    */

    // implementation without/with inheritance
    implementation_without_inheritance();
    implementation_with_inheritance();


    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void implementation_without_inheritance() {
    cout << "\nimplementation without inheritance" << endl;

    cout << "\nCpp Page" << endl;
    Cpp c;
    c.header();
    c.footer();
    c.sidebar();
    c.content();

    cout << "\nPython Page" << endl;
    Python p;
    p.header();
    p.footer();
    p.sidebar();
    p.content();
}

void implementation_with_inheritance() {
    cout << "\nimplementation with inheritance" << endl;

    cout << "\nCpp Page" << endl;
    Cppi c;
    c.header();
    c.footer();
    c.sidebar();
    c.content();

    cout << "\nPython Page" << endl;
    Pythoni p;
    p.header();
    p.footer();
    p.sidebar();
    p.content();
}