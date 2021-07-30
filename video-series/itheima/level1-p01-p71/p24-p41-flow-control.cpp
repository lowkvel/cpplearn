#include <iostream>

using namespace std;

// p24-p41, flow control
int main() {

    cout << "flow control" << endl;

    /*
        Selection
            if
            ?
            switch

        Iteration
            while
            do - while
            for
            range for

        Jump
            return
            goto
            continue
            break
    */
    
    // if ... else if ... else
    int a = 2; int b = 4;
    if (a == 2 && b == 3) {
        cout << "yes" << endl;
    } else {
        if (a == 2) {
            cout << "partialy yes a" << endl;
        } else if (b == 3) {
            cout << "partialy yes b" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    // ? : 
    int c = 2; int d = 3;
    int max = c > d ? c : d;    // d is returned here as variable, then got assigned to another variable
    cout << max << endl;

    c > d ? c : d = 9;          // d is returned here as variable, thus can do assignment to it
    cout << c << " " << d << endl;

    // switch ... case ... break ... default
    int e = 2;
    switch (e) {
        case 0: 
            cout << "0" << endl; 
            break;
        case 1: 
            cout << "1" << endl; 
            break;
        case 2: 
            cout << "2" << endl; 
            break;
        default: 
            cout << "cannot decide" << endl; 
            break;
    }

    // while
    int f = 0;
    while (f < 10) {
        cout << f << endl;
        f++;
    }
    while (1) {
        cout << f << endl;
        f--;
        if (f <= 0) break;
    }

    // do - while
    do {
        cout << f << endl;
        f++;
    } while (f < 10);

    // for
    for (int i = 0; i < 10; i++)
        cout << i << endl;

    int i = 0;
    for (;;) {
        if (i >= 10) break;
        cout << i << endl;
        i++;
    }


    
    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;

}
