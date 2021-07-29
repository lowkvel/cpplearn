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
    
    cout << "integer" << endl;
    
    short a = 10;
    unsigned short au = 10;
    cout << "short a = " << a 
        << "\t\t\tsizeof(short) = " << sizeof(short) << " bytes" 
        << "\t\t\trangeof(short) = [" << (numeric_limits<short>::min)() << ", " << (numeric_limits<short>::max)() << "]" << endl;
    cout << "unsigned short au = " << au 
        << "\t\tsizeof(unsigned short) = " << sizeof(unsigned short) << " bytes" 
        << "\trangeof(unsigned short) = [" << (numeric_limits<unsigned short>::min)() << ", " << (numeric_limits<unsigned short>::max)() << "]" << endl;

    int b = 10;
    unsigned int bu = 10;
    cout << "int b = " << b 
        << "\t\t\tsizeof(int) = " << sizeof(int) << " bytes" 
        << "\t\t\trangeof(int) = [" << (numeric_limits<int>::min)() << ", " << (numeric_limits<int>::max)() << "]" << endl;
    cout << "unsigned int bu = " << bu 
        << "\t\tsizeof(unsigned int) = " << sizeof(unsigned int) << " bytes" 
        << "\t\trangeof(unsigned int) = [" << (numeric_limits<unsigned int>::min)() << ", " << (numeric_limits<unsigned int>::max)() << "]" << endl;
    
    long c = 10;
    unsigned long cu = 10;
    cout << "long c = " << c 
        << "\t\t\tsizeof(long) = " << sizeof(long) << " bytes" 
        << "\t\t\trangeof(long) = [" << (numeric_limits<long>::min)() << ", " << (numeric_limits<long>::max)() << "]" << endl;
    cout << "unsigned long cu = " << cu 
        << "\t\tsizeof(unsigned long) = " << sizeof(unsigned long) << " bytes" 
        << "\t\trangeof(unsigned long) = [" << (numeric_limits<unsigned long>::min)() << ", " << (numeric_limits<unsigned long>::max)() << "]" << endl;
    
    long long d = 10;
    unsigned long long du = 10;
    cout << "long long d = " << d 
        << "\t\tsizeof(long long) = " << sizeof(long long) << " bytes" 
        << "\t\trangeof(long long) = [" << (numeric_limits<long long>::min)() << ", " << (numeric_limits<long long>::max)() << "]" << endl;
    cout << "unsigned long long du = " << du 
        << "\tsizeof(unsigned long long) = " << sizeof(long long) << " bytes" 
        << "\trangeof(unsigned long long) = [" << (numeric_limits<unsigned long long>::min)() << ", " << (numeric_limits<unsigned long long>::max)() << "]" << endl;
    


    
    

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;

}
