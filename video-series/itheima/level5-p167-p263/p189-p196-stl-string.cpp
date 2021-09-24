# include <iostream>

using namespace std;


void func1();

// p189-p196, stl string
int main() {

    cout << "stl string" << endl;

    /*
        stl string

        1.  constructor
            1.  string();                   // create a empty string
            2.  string(const char* s);      // create a string given const char *str
            3.  string(const string &str);  // create a string given another string
            4.  string(int n, char c);      // create a string given multiple same characters

        2.  assignment

        3.  concat

        4.  find & replace

        5.  compare

        6.  set & get

        7.  insert & delete

        8.  substring

    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // string constructor
    string s1;                  // 1.  string();                   // create a empty string
    cout << s1 << endl;
    const char *str = "str";
    string s2(str);             // 2.  string(const char* s);      // create a string given const char *str
    cout << s2 << endl;
    string s3(s2);              // 3.  string(const string &str);  // create a string given another string
    cout << s3 << endl;
    string s4(10, 'a');         // 4.  string(int n, char c);      // create a string given multiple same characters
    cout << s4 << endl;
    string s5("str");           // ? prob 2 ?
    cout << s5 << endl;
}
