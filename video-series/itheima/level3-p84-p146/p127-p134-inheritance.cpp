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
public:
    void content() {
        cout << "base content" << endl; // inheritable code with public access right, test for same name member in child classes
    }

public:
    static int num;
};
int BasePage::num = 0;

class BasePage2 {
public:
    string s;
};

// implementation with inheritance: cpp
class Cppi: public BasePage {
public:
    void content() {                    // class specific code
        cout << "cpp content" << endl;
    }

    void inheritance_type_tester() {
        header();       // public header() with public inheritance,         public (child & inside), accessible
        footer();       // protected footer() with public inheritance,      protected (child & inside), accessible
        //sidebar();    // private sidebar() with public inheritance,       private (child & hidden), inaccessible
    }

public:
    static int num;
};
int Cppi::num = 11;

// implementation with inheritance: python
class Pythoni: protected BasePage {
public:
    void content() {                    // class specific code
        cout << "python content" << endl;
    }

    void inheritance_type_tester() {
        header();       // public header() with protected inheritance,      protected (child & inside), accessible
        footer();       // protected footer() with protected inheritance,   protected (child & inside), accessible
        //sidebar();    // private sidebar() with protected inheritance,    private (child & hidden), inaccessible
    }

public:
    static int num;
};
int Pythoni::num = 12;


// implementation with inheritance: js
class Jsi: private BasePage {
public:
    void content() {
        cout << "js content" << endl;
    }

    void inheritance_type_tester() {
        header();       // public header() with private inheritance,        private (child & inside), accessible
        footer();       // protected footer() with private inheritance,     private (child & inside), accessible
        //sidebar();    // private sidebar() with private inheritance,      private (child & hidden), inaccessible
    }

public:
    static int num;
};
int Jsi::num = 13;

class Javai: public BasePage, public BasePage2 {
public:
    int n;
};

// p127-p134, inheritance
int main() {

    cout << "inheritance" << endl;

    /*
        inheritance

        1.  grammar
            class parent_class_name {
                ...
            };
            class child_class_name: inheritance_type parent_class_name {
                ...
            };

        2.  inheritance type
            0.  3 types: public, protected and private
            1.  all public/protected/private non-static member of parent class can be inherited from parent class to child class
                -> but private member of parent class is hidden by compiler (so inaccessible) for child class, no matter which inheritance type is used
            2.  the inheritance type follows minimum access right rule, which means:
                public inheritance:     child class member has the same access right as parent class (public/protected/private(hidden))
                                        explain:    protected parent class member access right overrides the public inheritance type
                protected inheritance:  child class member will have all inheritable (public/protected/private(hidden)) parent class member changed to protected
                                        explain:    protected inheritance type overrides the public parent class member access right
                private inheritance:    child class member will have all inheritable (public/protected/private(hidden)) parent class member changed to private
                                        explain:    private inheritance type overrides the public/protected parent class member access right

        3.  constructor & destructor
            construction sequence:  parent constructed before child
            destruction sequence:   child destructed before parent
        
        4.  access same-name-member (just need the name to be the same (including override)) in both parent & child class
                for child member:   access directly                -> child_object_name.child_class_member_name
                for parent member:  access with scope (parent)     -> child_object_name.parent_class_name::parent_class_member_name
                child same-name-member will hide all same-name-member in parent class, including overrode functions in parent class
            access same-name-static-member
                same as above

        5.  multiple inheritance
            class parent_class_name1 {
                ...
            };
            class parent_class_name2 {
                ...
            };
            ...
            class child_class_name: inheritance_type parent_class_name1, inheritance_type parent_class_name2, ... {
                ...
            };
    */

    // implementation without/with inheritance
    //implementation_without_inheritance();
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
    c.header();                 // public header() with public inheritance,                 public (child & outside), accessible
    //c.footer();               // protected footer() with public inheritance,              protected (child & outside), inaccessible
    //c.sidebar();              // private sidebar() with public inheritance,               private (child & hidden & outside), inaccessible
    c.BasePage::content();      // public BasePage::content() with public inheritance,      public (parent & outside), accessible
    c.content();                // class specific member
    c.inheritance_type_tester();

    cout << "\nPython Page" << endl;
    Pythoni p;
    //p.header();               // public header() with protected inheritance,              protected (child & outside), inaccessible
    //p.footer();               // protected footer() with protected inheritance,           protected (child & outside), inaccessible
    //p.sidebar();              // private sidebar() with protected inheritance,            private (child & hidden & outside), inaccessible
    //p.BasePage::content();    // public BasePage::content() with protected inheritance,   protected (parent & outside), inaccessible
    p.content();                // class specific member
    p.inheritance_type_tester();

    cout << "\nJs Page" << endl;
    Jsi j;
    //j.header();               // public header() with private inheritance,                private (child & outside), inaccessible
    //j.footer();               // protected footer() with private inheritance,             private (child & outside), inaccessible
    //j.sidebar();              // private sidebar() with private inheritance,              private (child & hidden & outside), inaccessible
    //j.BasePage::content();    // public BasePage::content() with private inheritance,     private (parent & outside), inaccessible
    j.content();                // class specific member
    j.inheritance_type_tester();

    // static member access
    cout << c.num << endl;                  // child object access 
    cout << c.BasePage::num << endl;        // child object & parent scope access
    cout << Cppi::num << endl;              // child class direct access
    cout << Cppi::BasePage::num << endl;    // child class & parent scope direct access

    // multiple inheritance
    Javai ja;
    ja.content();
    cout << ja.num << " " << ja.n << endl;
}
