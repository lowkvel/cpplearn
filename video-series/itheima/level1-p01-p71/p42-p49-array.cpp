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
    
    // 1d declaration 1:   int score[10];
    // automatically assign all 0s into the array with size 5, PROBLEM HERE, THE LAST ELEMENT GOT ASSIGNED WITH RANDOM VALUE!
    int score1[5];
    score1[0] = 1;
    cout << endl << score1 << endl;
    for (int i = 0; i < 5; i++)
        cout << score1[i] << " ";
    cout << endl;

    // 1d declaration 2:   int score[10] = {0, 1, 2, ...}; 
    // automatically assign 1 and 1 into the first two blocks, then fill the rest blocks with 0s
    int score2[5] = {1, 1};
    cout << endl << score2 << endl;
    for (int i = 0; i < (end(score2) - begin(score2)); i++)
        cout << score2[i] << " ";
    cout << endl;

    // 1d declaration 3:   int score[] = {0, 1, 2, ...};
    // array initialized with 2 blocks, given by the element number which is 2
    int score3[] = {1, 1}; 
    cout << endl << score3 << endl;     
    for (int i = 0; i < (sizeof(score3) / sizeof(score3[0])); i++)
        cout << score3[i] << " ";
    cout << endl;

    cout << endl << begin(score3) << " " << end(score3) << endl;
    cout << &score3[0] << " " << &score3[1] << endl;

    // 2d declaration 1:
    // automatically assign all 0s into the array with size 6, PROBLEM HERE, THE LAST ELEMENT GOT ASSIGNED WITH RANDOM VALUE!
    int score4[2][3];
    score4[0][0] = 1;
    score4[1][1] = 1;
    cout << endl << score4 << endl;
    for (int i = 0; i < (sizeof(score4) / sizeof(score4[0])); i++) {
        for (int j = 0; j < (sizeof(score4[0]) / sizeof(score4[0][0])); j++)
            cout << score4[i][j] << " ";
        cout << endl;
    }
    
    // 2d declaration 2:
    // automatically assign {1, 1, 1} into the first row, then fill the rest rows with 0s
    int score5[2][3] = {{1, 1, 1}};
    cout << endl << score5 << endl;
    for (int i = 0; i < (sizeof(score5) / sizeof(score5[0])); i++) {
        for (int j = 0; j < (sizeof(score5[0]) / sizeof(score5[0][0])); j++)
            cout << score5[i][j] << " ";
        cout << endl;
    }

    // 2d declaration 3:
    // automatically assign four 1s into the first 4 blocks, then fill the rest blocks with 0s
    int score6[2][3] = {1, 1, 1, 1};
    cout << endl << score6 << endl;
    for (int i = 0; i < (sizeof(score6) / sizeof(score6[0])); i++) {
        for (int j = 0; j < (sizeof(score6[0]) / sizeof(score6[0][0])); j++)
            cout << score6[i][j] << " ";
        cout << endl;
    }

    // 2d declaration 4:
    // automatically assign random number of 1s into the array, then fill the rest blocks of the last row with 0s
    int score7[][3] = {1, 1, 1, 1, 1, 1, 1};
    cout << endl << score7 << endl;
    for (int i = 0; i < (sizeof(score7) / sizeof(score7[0])); i++) {
        for (int j = 0; j < (sizeof(score7[0]) / sizeof(score7[0][0])); j++)
            cout << score7[i][j] << " ";
        cout << endl;
    }

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;

}
