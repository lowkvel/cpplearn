# include <deque>
# include <algorithm>
# include <numeric>

# include "speechManager.h"

SpeechManager::SpeechManager() {
    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();
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
    this->fileIsEmpty = true;
    this->record.clear();
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
    cout << "Winners!\n----------------------------" << endl;
    showWinners(winners);
    recordSaving(winners);

    // reinitialize contest
    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();
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

void SpeechManager::recordSaving(const vector<int> &v) {
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);    // appending

    for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
        ofs << *it << "," << this->speakers[*it].score[1] << ",";
    ofs << endl;

    ofs.close();
    this->fileIsEmpty = false;
    cout << "--------------\nresults saved." << endl;
}

void SpeechManager::loadRecord() {
    // open file
    ifstream ifs("speech.csv", ios::in);

    // file not exist
    if (!ifs.is_open()) {
        this->fileIsEmpty = true;
        cout << "file not found." << endl;
        ifs.close();
        return;
    }

    // file is empty, no previous record exist
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        cout << "empty file." << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    // begin here
    this->fileIsEmpty = false;

    // load data
    ifs.putback(ch);    // put the character back read above
    string data;
    int index = 0;
    while (ifs >> data) {
        vector<string> v;

        int pos = -1;   // for posititon of ","
        int start = 0;  // substr use this as start point

        while (true) {
            pos = data.find(",", start);    // find "," from position 0
            if (pos == -1) break;           // break if no "," found

            v.push_back(data.substr(start, pos - start));   // substring
            start = pos + 1;                                // update start point
        }

        this->record.insert(make_pair(index, v));           // insert into record
        index++;
    }

    // close ifs
    ifs.close();
}

void SpeechManager::showRecord() {
    if (this->fileIsEmpty) cout << "no record yet." << endl;

    for (map<int, vector<string> >::iterator it = this->record.begin(); it != this->record.end(); it++)
        cout << "Contest " << it->first + 1 << ": "
            << it->second[0] << " " << it->second[1] << ", "
            << it->second[2] << " " << it->second[3] << ", "
            << it->second[4] << " " << it->second[5] << endl;
}
