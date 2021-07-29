#include <iostream>
#include <limits>

using namespace std;

// p08-p15, datatype
int main() {

    cout << "datatype" << endl;

    /*
        integer

        short               2 bytes     [-2^15, 2^15-1]
        unsigned short      2 bytes     [0, 2^16-1]
    
        int                 4 bytes     [-2^31, 2^31-1]
        unsigned int        4 bytes     [0, 2^32-1]

        long                4-8 bytes   [-2^31, 2^31-1]
        unsigned long       4-8 bytes   [0, 2^32-1]

        long long           8 bytes     [-2^63, 2^63-1]
        unsigned long long  8 bytes     [0, 2^64-1]
    */
    
    cout << "\nshort & int & long & long long" << endl;

    short a = 10;
    unsigned short au = 10;
    cout << "short a = " << a 
        << "\t\t\tsizeof(short) = " << sizeof(short) << " bytes" 
        << "\t\t\trangeof(short) = [" << (numeric_limits<short>::min)() << ", " << (numeric_limits<short>::max)() << "]" << endl;
    cout << "unsigned short au = " << au 
        << "\t\tsizeof(unsigned short) = " << sizeof(unsigned short) << " bytes" 
        << "\trangeof(unsigned short) = [" << (numeric_limits<unsigned short>::min)() << ", " << (numeric_limits<unsigned short>::max)() << "]" << endl;

    int b = 10;
    unsigned int bu = 10u;
    cout << "int b = " << b 
        << "\t\t\tsizeof(int) = " << sizeof(int) << " bytes" 
        << "\t\t\trangeof(int) = [" << (numeric_limits<int>::min)() << ", " << (numeric_limits<int>::max)() << "]" << endl;
    cout << "unsigned int bu = " << bu 
        << "\t\tsizeof(unsigned int) = " << sizeof(unsigned int) << " bytes" 
        << "\t\trangeof(unsigned int) = [" << (numeric_limits<unsigned int>::min)() << ", " << (numeric_limits<unsigned int>::max)() << "]" << endl;
    
    long c = 10l;
    unsigned long cu = 10ul;
    cout << "long c = " << c 
        << "\t\t\tsizeof(long) = " << sizeof(long) << " bytes" 
        << "\t\t\trangeof(long) = [" << (numeric_limits<long>::min)() << ", " << (numeric_limits<long>::max)() << "]" << endl;
    cout << "unsigned long cu = " << cu 
        << "\t\tsizeof(unsigned long) = " << sizeof(unsigned long) << " bytes" 
        << "\t\trangeof(unsigned long) = [" << (numeric_limits<unsigned long>::min)() << ", " << (numeric_limits<unsigned long>::max)() << "]" << endl;
    
    long long d = 10ll;
    unsigned long long du = 10ull;
    cout << "long long d = " << d 
        << "\t\tsizeof(long long) = " << sizeof(long long) << " bytes" 
        << "\t\trangeof(long long) = [" << (numeric_limits<long long>::min)() << ", " << (numeric_limits<long long>::max)() << "]" << endl;
    cout << "unsigned long long du = " << du 
        << "\tsizeof(unsigned long long) = " << sizeof(long long) << " bytes" 
        << "\trangeof(unsigned long long) = [" << (numeric_limits<unsigned long long>::min)() << ", " << (numeric_limits<unsigned long long>::max)() << "]" << endl;
    
    /*
        float       4 bytes     7 significant figues        +/- 3.4e +/- 38
        double      8 bytes     15-16 significant figues    +/- 1.7e +/- 308
    */

    cout << "\nfloat & double" << endl;
    
    float e = 10.111111f;
    cout << "float e = " << e 
        << "\t\tsizeof(float) = " << sizeof(float) << " bytes"
        << "\t\t\trangeof(float) = [" << (numeric_limits<float>::min)() << ", " << (numeric_limits<float>::max)() << "]" << endl;

    double f = 10.111111;
    cout << "double f = " << f 
        << "\t\tsizeof(double) = " << sizeof(double) << " bytes"
        << "\t\trangeof(double) = [" << (numeric_limits<double>::min)() << ", " << (numeric_limits<double>::max)() << "]" << endl;

    /*
        char                1 bytes     [-2^7, 2^7-1]
        unsigned char       1 bytes     [0, 2^8-1]
    */

    cout << "\nchar" << endl;

    char ch1 = 'a';             // the ASCII code 97 of 'a' is stored in char variable, not the 'a' itself
    unsigned char ch1u = 'a';
    cout << "char '" << ch1 << "' with ASCII code " << (int)ch1 
        << "\t\tsizeof(char) = " << sizeof(char) << " bytes" 
        << "\t\t\trangeof(char) = [" << CHAR_MIN << ", " << CHAR_MAX << "]" << endl;
    cout << "unsigned char '" << ch1u << "' with ASCII code " << (int)ch1u 
        << "\tsizeof(unsigned char) = " << sizeof(unsigned char) << " bytes" 
        << "\t\trangeof(unsigned char) = [" << 0 << ", " << UCHAR_MAX << "]" << endl;
    char ch2 = 98;              // the stored ASCII code 97 automatically transformed into 'a' in cout from iostream
    cout << "char '" << ch2 << "' with ASCII code " << (int)ch2 
        << "\t\tsizeof(char) = " << sizeof(char) << " bytes" 
        << "\t\t\trangeof(char) = [" << CHAR_MIN << ", " << CHAR_MAX << "]" << endl;  




    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;

}
