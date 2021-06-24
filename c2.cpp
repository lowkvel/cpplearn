#include <iostream>
#include <cmath>

using namespace std;
//using std::cin;
//using std::cout;
//using std::endl;

void print_lol(int n);
string print_lol2(int n);

int main()
{

    cout << "first line" << endl;

    int temp;
    cin >> temp;
    temp = temp + 2;
    
    double sqrtemp;
    sqrtemp = sqrt(temp);

    cout << temp << " is a number" << endl;
    cout << temp
         << " is a int"
         << endl;
    cout << sqrtemp
         << " is a double"
         << endl;

    print_lol(temp);
    cout << print_lol2(temp) << endl;

    return 0;

}

void print_lol(int n)
{
    cout << "jokes on you " << n << " lol" << endl;
}

string print_lol2(int n)
{
    return "jokes on you " + to_string(n + 2) + " lol";
}
