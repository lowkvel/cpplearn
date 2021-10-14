# include <deque>
# include <algorithm>
# include <numeric>

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
    this->speechCount = 0;
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
    cout << "-------------------------------------------" << endl;
    // contesting
    for (int i = 1; i <= 2; i++) {
        this->speechCount++;    // round i
        speechSpeakersDraw();   // i round speaker draw
        speechContest();        // i round speaker contest
    }

    // show & save result
    cout << "Winners!\n--------------" << endl;
    showWinners(winners);
}

void SpeechManager::speechSpeakersDraw() {
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

void SpeechManager::speechContest() {
    // current round
    vector<int> currentRound;
    this->speechCount == 1 ? currentRound = round1s : currentRound = round2s;

    multimap<double, int, greater<double> > groupScore;     // multimap used to auto-sort score and its' speaker
    int num = 0;                                            // halving
    for (vector<int>::iterator it = currentRound.begin(); it != currentRound.end(); it++) {
        num ++;     // increment every speaker processed

        // get 10 scores from 10 evaluators, 60.0 - 100.0
        deque<double> scores;
        for (int i = 0; i < 10; i++) 
            scores.push_back((rand() % 401 + 600) / 10.f);
        // tester
        // for (deque<double>::iterator itscores = scores.begin(); itscores != scores.end(); itscores++)
        //     cout << *itscores << " ";
        // cout << endl;

        // score preprocessing, sort, pop highest & lowest
        sort(scores.begin(), scores.end(), greater<double>());  // sort descending
        scores.pop_back();  // lowest popped
        scores.pop_front(); // highest popped

        // avg calculation & storage
        double sum = accumulate(scores.begin(), scores.end(), 0.0f);
        double avg = sum / (double)scores.size();
        this->speakers[*it].score[this->speechCount - 1] = avg;

        // temp multimap used to auto-sort avg score along with associated id
        groupScore.insert(make_pair(avg, *it));
        // output every 6 speakers
        if (num % 6 == 0) {
            cout << "----------------------" << endl;
            cout << num / 6 << " half result.\n--------------" << endl;
            for (multimap<double, int, greater<double> >::iterator it = groupScore.begin(); it != groupScore.end(); it++)
                cout << it->second << " " << this->speakers[it->second].name << " " << this->speakers[it->second].score[this->speechCount - 1] << endl;
            
            // take the first 3 speakers into next round
            int count = 0;
            for (multimap<double, int, greater<double> >::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
                this->speechCount == 1 ? round2s.push_back((*it).second) : winners.push_back((*it).second);

            // clear temp multimap for next 6 speakers to use
            groupScore.clear();
        }
    }
    cout << "-------------------------------------------" << endl;
}

void SpeechManager::showWinners(const vector<int> &v) {
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
        cout << *it << " " << this->speakers[*it].name << " " << this->speakers[*it].score[0] << " " << this->speakers[*it].score[1] << endl;
}