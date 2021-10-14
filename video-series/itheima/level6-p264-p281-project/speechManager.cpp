# include "speechManager.h"

SpeechManager::SpeechManager() {
    this->initSpeech();
    this->createSpeaker();
}

SpeechManager::~SpeechManager() {

}

void SpeechManager::showMenu() {
    cout << "*******************************************" << endl;
    cout << "*** 1. begin contest.                   ***" << endl;
    cout << "*** 2. check previous contests' result. ***" << endl;
    cout << "*** 3. clear all contests' result.      ***" << endl;
    cout << "*** 0. quit system.                     ***" << endl;
    cout << "*******************************************" << endl;
}

void SpeechManager::quitSystem() {
    cout << "quitted" << endl;
    exit(0);
}

void SpeechManager::initSpeech() {
    this->round1s.clear();
    this->round2s.clear();
    this->winners.clear();
    this->speakers.clear();
    this->speechCount = 1;
}

void SpeechManager::createSpeaker() {
    string nameSeed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 12; i++) {
        string name = "speaker_";
        name += nameSeed[i];

        Speaker sp;
        sp.name = name;
        for (int j = 0; j < 2; j++) sp.score[j] = 0;

        this->round1s.push_back(i + 1);
        this->speakers.insert(make_pair(i + 1, sp));
    }
}

void SpeechManager::speechContesting() {
    speechSpeakersDraw();   // step 1.1, first round speaker draw
}

void SpeechManager::speechSpeakersDraw() {
    cout << "-------------------------------------------" << endl;
    if (this->speechCount == 1) {
        cout << this->speechCount << "st round speakers draw." << endl;
        random_shuffle(round1s.begin(), round1s.end());
        for (vector<int>::iterator it = round1s.begin(); it != round1s.end(); it++)
            cout << *it << ". ";
        cout << endl;
    } else {
        cout << this->speechCount << "nd round speakers draw." << endl;
        random_shuffle(round2s.begin(), round2s.end());
        for (vector<int>::iterator it = round2s.begin(); it != round2s.end(); it++)
            cout << *it << ". ";
        cout << endl;
    }
    cout << "-------------------------------------------" << endl;
}
