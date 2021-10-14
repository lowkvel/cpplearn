# include "speechManager.h"

SpeechManager::SpeechManager() {
    this->initSpeech();
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
