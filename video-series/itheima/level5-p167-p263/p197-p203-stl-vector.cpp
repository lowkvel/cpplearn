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
            1.  vector<T> v;                   // default constructor
            2.  vector(v.begin(), v.end());     // copy [v.begin(), v.end()), closed-open range
            3.  vector(n, element);             // construct n * element
            4.  vector(const vector &vec);      // copy constructor

    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // constructor
    vector<int> v1;
    for (int i = 0; i < 10; i++) v1.push_back(i);   vectorPrinter(v1);  // default constructor
    vector<int> v2(v1.begin(), v1.end());           vectorPrinter(v2);  // copy [v.begin(), v.end()), closed-open range
    vector<int> v3(10, 1);                          vectorPrinter(v3);  // construct n * element
    vector<int> v4(v3);                             vectorPrinter(v4);  // copy constructor

}

void vectorPrinter(vector <int> &v) {
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;
}
