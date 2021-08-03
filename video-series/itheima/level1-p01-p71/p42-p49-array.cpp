#include <iostream>

using namespace std;

// p42-p49, array
int main() {

    cout << "array" << endl;

    /*
        array
    */

    /*
        two ways to get array's element number:
            sizeof(arr) / sizeof(arr[0])
            end(arr) - begin(arr)
    */
    
    // declaration 1:   int score[10];
    // automatically assign all 0s into the array with size 5, PROBLEM HERE!
    int score1[5];
    score1[0] = 1;
    cout << endl << score1 << endl;
    for (int i = 0; i < 5; i++)
        cout << score1[i] << " ";
    cout << endl;

    // declaration 2:   int score[10] = {0, 1, 2, ...}; 
    // automatically assign 0 and 1 into the first two blocks, then fill the rest blocks with 0s
    int score2[5] = {1, 1};
    cout << endl << score2 << endl;
    for (int i = 0; i < (end(score2) - begin(score2)); i++)
        cout << score2[i] << " ";
    cout << endl;

    // declaration 3:   int score[] = {0, 1, 2, ...};
    // array initialized with 2 blocks, given by the element number which is 2
    int score3[] = {1, 1}; 
    cout << endl << score3 << endl;     
    for (int i = 0; i < (sizeof(score3) / sizeof(score3[0])); i++)
        cout << score3[i] << " ";
    cout << endl;

    cout << endl << begin(score3) << " " << end(score3) << endl;
    cout << &score3[0] << " " << &score3[1] << endl;

    


    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;

}
