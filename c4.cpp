#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    int tlist[3];
    tlist[0] = 0;
    tlist[1] = 1;
    tlist[2] = 2;
    int tlist2[3] = {0, 1, 2};
    cout << sizeof(tlist) << endl;
    cout << sizeof(tlist[0]) << endl;
    cout << tlist[0] << " " << tlist[1] << " " << tlist[2] << endl;

    char clist[] = "Hey";
    cout << clist << " " << clist[0] << endl;
    cout << strlen(clist) << " " << sizeof(clist) << endl;


    return 0;

}


