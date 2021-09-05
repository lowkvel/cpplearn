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
    void header() {                     // inheritable code with public access right
        cout << "header" << endl;
    }
protected:
    void footer() {                     // inheritable code with protected access right
        cout << "footer" << endl;
    }
private:
    void sidebar() {                    // inheritable code with private access right
        cout << "sidebar" << endl;
    }
};

// implementation with inheritance: cpp
class Cppi: public BasePage {
public:
    void content() {                    // class specific code
        cout << "cpp content" << endl;
    }

    void inheritance_type_tester() {
        header();       // public header() with public inheritance,         public, accessible
        footer();       // protected footer() with public inheritance,      protected (child & inside), accessible
        //sidebar();    // private sidebar() with public inheritance,       private (parent), inaccessible
    }
};

// implementation with inheritance: python
class Pythoni: protected BasePage {
public:
    void content() {                    // class specific code
        cout << "python content" << endl;
    }

    void inheritance_type_tester() {
        header();       // public header() with protected inheritance,      protected (child & inside), accessible
        footer();       // protected footer() with protected inheritance,   protected (child & inside), accessible
        //sidebar();    // private sidebar() with protected inheritance,    private (parent), inaccessible
    }
};

// implementation with inheritance: js
class Jsi: private BasePage {
public:
    void content() {
        cout << "js content" << endl;
    }

    void inheritance_type_tester() {
        header();       // public header() with private inheritance,        private (child & inside), accessible
        footer();       // protected footer() with private inheritance,     private (child & inside), accessible
        //sidebar();    // private sidebar() with private inheritance,      private (parent), inaccessible
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

        2.  inheritance type
            0.  3 types: public, protected and private
            1.  public/protected member of parent class can be inherited from parent class to child class
                -> but private member of parent class is inaccessible for child class, no matter which inheritance type is used
            2.  the inheritance type follows minimum access right rule, which means:
                public inheritance:     child class member has the same access right as parent class (public/protected)
                                        explain:    protected parent class member access right overrides the public inheritance type
                protected inheritance:  child class member will have all inheritable (public/protected) parent class member changed to protected
                                        explain:    protected inheritance type overrides the public parent class member access right
                private inheritance:    child class member will have all inheritable (public/protected) parent class member changed to private
                                        explain:    private inheritance type overrides the public/protected parent class member access right

        


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
    c.header();         // public header() with public inheritance,         public, accessible
    //c.footer();       // protected footer() with public inheritance,      protected (child & outside), inaccessible
    //c.sidebar();      // private sidebar() with public inheritance,       private (parent & outside), inaccessible
    c.content();        // class specific member
    c.inheritance_type_tester();

    cout << "\nPython Page" << endl;
    Pythoni p;
    //p.header();       // public header() with protected inheritance,      protected (child & outside), inaccessible
    //p.footer();       // protected footer() with protected inheritance,   protected (child & outside), inaccessible
    //p.sidebar();      // private sidebar() with protected inheritance,    private (parent & outside), inaccessible
    p.content();        // class specific member
    p.inheritance_type_tester();

    cout << "\nJs Page" << endl;
    Jsi j;
    //j.header();       // public header() with private inheritance,        private (child & outside), inaccessible
    //j.footer();       // protected footer() with private inheritance,     private (child & outside), inaccessible
    //j.sidebar();      // private sidebar() with private inheritance,      private (parent & outside), inaccessible
    j.content();        // class specific member
    j.inheritance_type_tester();
}