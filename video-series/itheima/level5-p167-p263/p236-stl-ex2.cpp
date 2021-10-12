# include <iostream>
# include <vector>
# include <map>
# include <ctime>

using namespace std;

class Worker {
public:
    string name;
    int wage;
};

void func1();
void printWorkers(const vector<Worker> &vw);
void workerCreation(vector<Worker> &vw);
void workerPlacement(const vector<Worker> &vw, multimap<int, Worker> &mw);
void workerDisplayByPlacement(const multimap<int, Worker> &mw);

// p236, stl ex2
int main() {

    cout << "stl ex2" << endl;

    /*
        stl ex2
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // srand
    srand((unsigned int) time (NULL));
    
    // create 10 workerss
    vector<Worker> vw;
    workerCreation(vw);
    
    // worker placement
    multimap<int, Worker> mw;
    workerPlacement(vw, mw);

    // worker display by placement
    workerDisplayByPlacement(mw);
}

void printWorkers(const vector<Worker> &vw) {
    for (vector<Worker>::const_iterator it = vw.begin(); it != vw.end(); it++)
        cout << it->name << " " << it->wage << endl;
}

void workerCreation(vector<Worker> &vw) {
    string nameSeed = "ABCDEFGHIJKLMN";
    for (int i = 0; i < 10; i++) {
        Worker w;
        w.name = "wk";
        w.name += nameSeed[i];
        w.wage = rand() % 10000 + 10000;    // 10000-19999

        vw.push_back(w);
    }
}

void workerPlacement(const vector<Worker> &vw, multimap<int, Worker> &mw) {
    for (vector<Worker>::const_iterator it = vw.begin(); it != vw.end(); it++) {
        int deptid = rand() % 3;            // 0, 1, 2
        mw.insert(make_pair(deptid, *it));
    }
}

void workerDisplayByPlacement(const multimap<int, Worker> &mw) {
    for (int i = 0; i < 3; i++) {
        // get the iterator of first occurence of key i
        // count how many got outputed, compare with how many needs to output
        int outputed = 0;
        for (multimap<int, Worker>::const_iterator pos = mw.find(i); pos != mw.end() && outputed < mw.count(i); pos++, outputed++) 
            cout << (*pos).first << " " << (*pos).second.name << " " << (*pos).second.wage << endl;
    }
}
