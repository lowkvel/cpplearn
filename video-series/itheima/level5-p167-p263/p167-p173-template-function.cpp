# include <iostream>

using namespace std;

class Person {
public:
    string name;
    int age;

public:
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }
};

void func1();
void swap1(int &a, int &b);
void swap2(double &a, double &b);
template <typename T> void swapt(T &a, T &b);
template <typename T> void sort(T arr[], int len);
template <typename T> void printarr(T arr[], int len);
int add(int a, int b);
template <typename T> int addt(T a, T b);
void print(int a, int b);
template <typename T> void print(T a, T b);
template <typename T> void print(T a, T b, T c);
template <typename T> bool compare(T &a, T &b);
template <> bool compare(Person &a, Person &b);

// p167-p173, template function
int main() {

    cout << "template function" << endl;

    /*
        template function

        0.  purpose
            parameterize typename
        1.  grammar
            1.  declaration/definition: 
                template <typename T>
                function declaration/definition
            2.  call: 
                func(a, b);         // implicit call
                func<int>(a, b);    // explicit call
        2.  difference between normal function and template function
            1.  normal function can do implicit type conversion
            2.  template function with implicit call cannot do implicit type conversion, because compiler wont know which type to use
            3.  template function with explicit call can do implicit type conversion, because target type is explicitly specified
        3.  priority
            1.  normal function has priority over template function if both are accepted
            2.  template function can be forced to call using empty template parameter list <>
            3.  overload is allowed with template function
            4.  better (more suitable) template function has priority over normal function
        4.  limitation
            1.  template normally works for primitive data types
            2.  template needs overload for self-defined data types like classes
                grammar:    template <> return_type compare(class_type &a, class_type &b)
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // normal/template function basics
    int a = 1; 
    int b = 2;
    swap1(a, b);            // normal function
    swapt(a, b);            // template function, implicit call
    swapt<int>(a, b);       // template function, explicit call
    cout << a << " " << b << endl;

    double c = 1.0; 
    double d = 2.0;
    swap2(c, d);            // normal function
    swapt(c, d);            // template function, implicit call
    swapt<double>(c, d);    // template function, explicit call
    cout << c << " " << d << endl;

    // ex
    char charr[] = "sdgbvcrtgh";
    sort(charr, (sizeof(charr)/sizeof(char)));
    printarr(charr, (sizeof(charr)/sizeof(char)));

    int intarr[] = {5,4,2,3,4,5,7,6,7,6,5,8,1,6,2,7,9,8,4,4};
    sort(intarr, (sizeof(intarr)/sizeof(int)));
    printarr(intarr, (sizeof(intarr)/sizeof(int)));

    // difference between normal and template function
    int e = 1; int f = 2; char g = 'g';
    cout << add(e, f) << endl;          // normal function, int + int call
    cout << add(e, g) << endl;          // normal function, int + char call, implicit type conversion successful (char g -> int g), int + char call -> int + int call
    cout << addt(e, f) << endl;         // template function, int + int call
    //cout << addt(e, g) << endl;       // template function, int + char call, implicit type conversion failed for implicit call
    cout << addt<int>(e, g) << endl;    // template function, int + char call, implicit type conversion successful because of explicit call

    // priority
    int i = 1; int j = 2; 
    char c1 = 'a'; char c2 = 'b';
    print(i, j);        // 1.  normal function has priority over template function if both are accepted
    print<>(i, j);      // 2.  template function can be forced to call using empty template parameter list <>
    print(i, j, 3);     // 3.  overload is allowed with template function
    print(c1, c2);      // 4.  better (more suitable) template function has priority over normal function

    // limitation
    int k = 1; int l = 2;
    Person p1("a", 1); Person p2("b", 2);
    cout << compare(k, l) << endl;      // no problem for primitive data types
    cout << compare(p1, p2) << endl;    // problems for self-defined data types, need to overload
}

// normal/template function
void swap1(int &a, int &b) { int temp = a; a = b; b = temp; }
void swap2(double &a, double &b) { double temp = a; a = b; b = temp; }
template <typename T> void swapt(T &a, T &b) { T temp = a; a = b; b = temp; }

// ex
template <typename T> 
void sort(T arr[], int len) {
    for (int i = 0; i < len; i++) {
        int max = i;
        for(int j = i+1; j < len; j++) 
            if (arr[max] < arr[j]) 
                max = j;
        if (max != i) 
            swapt(arr[max], arr[i]);
    }
}

template <typename T>
void printarr(T arr[], int len) {
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// difference between normal and template function
int add(int a, int b) { return a + b; }
template <typename T> int addt(T a, T b) { return a + b; }

// priority
void print(int a, int b) { cout << "normal ab" << endl; }
template <typename T> void print(T a, T b) { cout << "template ab" << endl; }
template <typename T> void print(T a, T b, T c) { cout << "template abc" << endl; }

// limitation
template <typename T> bool compare(T &a, T &b) { return a == b; }
template <> bool compare(Person &a, Person &b) { return a.age == b.age; }
