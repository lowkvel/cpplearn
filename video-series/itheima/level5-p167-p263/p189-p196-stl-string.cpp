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
            1.  string & operator=(const char *s);      // assign string char *s
            2.  string & operator=(const string &s);    // assign string &s
            3.  string & operator=(char c);             // assign char c
            4.  string & assign(const char *s);         // 1 ?
            5.  string & assign(const char *s, int n);  // assign first n characters of string char *s
            6.  string & assign(const string &s);       // 2 ?
            7.  string & assign(int n, char c);         // assign with multiple same characters
        3.  concatenation

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
    const char *str = "s2";
    string s2(str);             // 2.  string(const char* s);      // create a string given const char *str
    cout << s2 << endl;
    string s3(s2);              // 3.  string(const string &str);  // create a string given another string
    cout << s3 << endl;
    string s4(10, 'a');         // 4.  string(int n, char c);      // create a string given multiple same characters
    cout << s4 << endl;
    string s5("s5");            // ? prob 2 ?
    cout << s5 << endl;

    // assignment
    string s6; s6 = "s6";               // 1.  string & operator=(const char *s);      // assign string char *s
    cout << s6 << endl;
    string s7; s7 = s6;                 // 2.  string & operator=(const string &s);    // assign string &s
    cout << s7 << endl;
    string s8; s8 = 'a';                // 3.  string & operator=(char c);             // assign char c
    cout << s8 << endl;
    string s9; s9.assign("s9");         // 4.  string & assign(const char *s);         // 1 above
    cout << s9 << endl;
    string s10; s10.assign("s10", 2);   // 5.  string & assign(const char *s, int n);  // assign first n characters of string char *s
    cout << s10 << endl;
    string s11; s11.assign(s10);        // 6.  string & assign(const string &s);       // 2 above
    cout << s11 << endl;
    string s12; s12.assign(10, 'a');    // 7.  string & assign(int n, char c);         // assign with multiple same characters
    cout << s12 << endl;
    
    

}
