# include <iostream>

# include "speechManager.h"

using namespace std;

void main_func();

// build command:
// /usr/bin/clang++ -std=c++11 -g speechContestManagementSystem.cpp speechManager.cpp -o speechContestManagementSystem
/*
speechContestManagementSystem.cpp speechManager.cpp
*/

int main() {

    SpeechManager sm;
    
    sm.showMenu();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}
