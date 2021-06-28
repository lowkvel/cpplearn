#include <iostream>

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





    return 0;

}


