# include <iostream>
# include <vector>
# include <deque>
# include <algorithm>

using namespace std;

class Person {
public:
    string name;
    int score;

public:
    Person(string name, int score) {
        this->name = name;
        this->score = score;
    }
};

void func1();

// p210, stl ex1
int main() {

    cout << "stl ex1" << endl;

    /*
        stl ex1
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // set random seed
    srand((unsigned int)time(NULL));

    // initialize vector of Person
    vector<Person> v;
    string nameSeed = "abcde";
    for (int i = 0; i < 5; i++) {
        string name = "p";
        name = name + nameSeed[i];

        //Person p(name, 0);
        v.push_back(Person(name, 0));
    }

    // printer
    // for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    //     cout << (*it).name << " " << (*it).score << endl;

    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {     
        // generate random 10 scores
        deque<int> d;
        for (int i = 0; i < 10; i++)
            d.push_back(rand() % 41 + 60);  // (60, 100]
        
        // sort
        sort(d.begin(), d.end());   

        // delete min & max
        d.pop_front();
        d.pop_back();

        // calculate avg & assignment
        int sum = 0;
        for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++) 
            sum = sum + *dit;
        (*it).score = sum / d.size();
    }

    //printer
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
        cout << (*it).name << " " << (*it).score << endl;
}
