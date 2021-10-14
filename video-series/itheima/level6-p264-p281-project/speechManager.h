# pragma once

# include <iostream>
# include <vector>
# include <map>

# include "speaker.h"

using namespace std;

class SpeechManager {
public:
    vector<int> round1s;            // initial speakers, 12
    vector<int> round2s;            // second round speakers, 6
    vector<int> winners;            // winner speakers, 3
    map<int, Speaker> speakers;     // map
    int speechCount;                // speech rounds count

public:
    SpeechManager();    // constructor
    
    ~SpeechManager();   // destructor
    
    void showMenu();    // show menu

    void quitSystem();  // quit

    void initSpeech();  // speech container initialization

};
