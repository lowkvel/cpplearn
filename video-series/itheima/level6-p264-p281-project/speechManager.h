# pragma once

# include <iostream>
# include <vector>
# include <map>
# include <fstream>

# include "speaker.h"

using namespace std;

class SpeechManager {
public:
    vector<int> round1s;            // initial speakers, 12
    vector<int> round2s;            // second round speakers, 6
    vector<int> winners;            // winner speakers, 3
    map<int, Speaker> speakers;     // map
    int speechCount;                // speech rounds count
    bool fileIsEmpty;
    map<int, vector<string> > record;   // past result

public:
    SpeechManager();    // constructor
    
    ~SpeechManager();   // destructor
    
    void showMenu();    // show menu

    void quitSystem();  // quit

    void initSpeech();  // speech container initialization

    void createSpeaker();       // speaker creation

    void speechContesting();    // speech contesting

    void speechSpeakersDraw();  // draw speakers

    void speechContest();       // speech contest

    void showWinners(const vector<int> &v);     // show winners

    void recordSaving(const vector<int> &v);    // record saving

    void loadRecord();

    void showRecord();
};
