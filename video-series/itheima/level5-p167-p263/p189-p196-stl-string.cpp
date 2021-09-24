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
            3.  string(const string &s);    // create a string given another string
            4.  string(int n, char c);      // create a string given multiple same characters
        2.  assignment
            1.  string & operator=(const char *s);      // assign string char *s
            2.  string & operator=(const string &s);    // assign string &s
            3.  string & operator=(char c);             // assign char c
            4.  string & assign(const char *s);         // 1
            5.  string & assign(const char *s, int n);  // assign first n characters of string char *s
            6.  string & assign(const string &s);       // 2
            7.  string & assign(int n, char c);         // assign with multiple same characters
        3.  concatenation
            1.  string & operator+=(const char *s);                 // append string char *s
            2.  string & operator+=(const string &s);               // append string &s
            3.  string & operator+=(const char c);                  // append char c
            4.  string & append(const char *s);                     // 1 above
            5.  string & append(const char *s, int n);              // append first n characters of string char *s
            6.  string & append(const string &s);                   // 2 above
            7.  string & append(const string &s, int p, int n);     // append first n characters of string &s starting from position p
        4.  find & replace
            1.  int find(const string &s, int p = 0) const;         // find the first position of string s, starting from position p
            2.  int find(const char *s, int p = 0) const;           // find the first position of char *s, starting from position p
            3.  int find(const char *s, int p, int n) const;        // fint the first position of the first n characters of char *s, starting from position p
            4.  int find(const char c, int p = 0) const;            // find the first position of char c, starting from position p
            5.  int rfind(const string &s, int p = np) const;       // 1. last, backwards
            6.  int rfind(const char *s, int p = np) const;         // 2. last, backwards
            7.  int rfind(const char *s, int p, int n) const;       // 3. last, backwards
            8.  int rfind(const char c, int p = 0) const;           // 4. last, backwards
            9.  string & replace(int p, int n, const string &s);    // replace the first n characters starting from position p of original string with string s
            10. string & replace(int p, int n, const char *s);      // replace the first n characters starting from position p of original string with string char *s
            0.  a random number or -1 will be returned if target is not found
                the string s will replace the range [p, p+n-1] from original string, so the length of replaced original may varies after replacement -> length_of(s) != n
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
    
    // concatenation
    string s13 = "s13"; s13 += "s13";           // 1.  string & operator+=(const char *s);     // append string char *s
    cout << s13 << endl;
    string s14 = "s14"; s14 += s13;             // 2.  string & operator+=(const string &s);   // append string &s
    cout << s14 << endl;
    string s15 = "s15"; s15 += 's';             // 3.  string & operator+=(const char c);      // append char c
    cout << s15 << endl;
    string s16 = "s16"; s16.append("s16");      // 4.  string & append(const char *s);         // 1 above
    cout << s16 << endl;
    string s17 = "s17"; s17.append("s17", 2);   // 5.  string & append(const char *s, int n);  // append first n characters of string char *s
    cout << s17 << endl;
    string s18 = "s18"; s18.append(s17);        // 6.  string & append(const string &s);       // 2 above
    cout << s18 << endl;
    string s19 = "s19"; s19.append(s18, 1, 2);  // 7.  string & append(const string &s, int p, int n);      // append first n characters of string s starting from position p
    cout << s19 << endl;
    
    // find & replace
    string s20 = "s20s20s20"; const char *tf = "20";
    cout << s20.find(tf) << " ";            // 1.  int find(const string &s, int p = 0) const;         // find the first position of string s, starting from position p
    cout << s20.find(tf, 3) << endl;
    cout << s20.find("20") << " ";          // 2.  int find(const char *s, int p = 0) const;           // find the first position of char *s, starting from position p
    cout << s20.find("20", 3) << endl;  
    cout << s20.find(tf, 0, 1) << " ";      // 3.  int find(const char *s, int p, int n) const;        // fint the first position of the first n characters of char *s, starting from position p
    cout << s20.find(tf, 3, 1) << endl;
    cout << s20.find('2') << " ";           // 4.  int find(const char c, int p = 0) const;            // find the first position of char c, starting from position p
    cout << s20.find('2', 3) << endl;
    cout << s20.rfind(tf) << " ";           // 5.  int rfind(const string &s, int p = np) const;       // 1. last, backwards
    cout << s20.rfind(tf, 3) << endl;
    cout << s20.rfind("20") << " ";         // 6.  int rfind(const char *s, int p = np) const;         // 2. last, backwards
    cout << s20.rfind("20", 3) << endl;
    cout << s20.rfind(tf, 9, 1) << " ";     // 7.  int rfind(const char *s, int p, int n) const;       // 3. last, backwards
    cout << s20.rfind(tf, 3, 1) << endl;
    cout << s20.rfind('2', 9) << " ";       // 8.  int rfind(const char c, int p = 0) const;           // 4. last, backwards
    cout << s20.rfind('2', 3) << endl;
    cout << s20.replace(2, 4, "aaaa") << endl;  // 9.  string & replace(int p, int n, const string &s);  // replace the first n characters starting from position p of original string with string s
    cout << s20.replace(2, 4, tf) << endl;      // 10. string & replace(int p, int n, const char *s);    // replace the first n characters starting from position p of original string with string char *s

}
