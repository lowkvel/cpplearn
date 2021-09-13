#include <iostream>
#include <fstream>

using namespace std;

class Person {
public:
    char name[64];
    int age;
};

void func1();
void in_normal();
void in_binary();
void out_normal();
void out_binary();

// p143-p146, file
int main() {

    cout << "file" << endl;

    /*
        file

        1.  file format
            1.  plain text file, stored as ASCII, readalbe 
            2.  binary file, stored as binary stream, not readable

        2.  stream for r/w/rw
            ifstream:   read operation (input)
            ofstream:   write operation (output)
            ffstream:   read/write operation (in/output)

        3.  process
            1.  #include <fstream>
            2.  ofstream ofs;
            3.  ofs.open("file_path", open_mode);     // open mode here
            4.  ofs << "data to write";
            5.  ofs.close();

        4.  open mode
            1.  ios::in         // open file for reading
            2.  ios::out        // open file for writing
            3.  ios::ate        // open file at the end of the file
            4.  ios::app        // open file at the end of the file for appending
            5.  ios::trunc      // open file after deleted existing same name file
            6.  ios::binary     // open file as binary format
            7.  etc...
            0.  ios::out | ios::binary      // if need to use multiple open options
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    in_normal();
    in_binary();
    //out_normal();
    //out_binary();
}

void in_normal() {
    // create ifstream object
    ifstream ifs;

    // open file and check if opened successful
    ifs.open("temp.txt", ios::in);
    if (!ifs.is_open()) {
        cout << "file opened failed" << endl;
        return;
    } else
        cout << "file opened successful" << endl;

    // read file 1, word-wise
    //char buf1[1024] = {0};
    //while (ifs >> buf1) cout << buf1 << endl;

    // read file 2, line-wise
    //char buf2[1024] = {0};
    //while (ifs.getline(buf2, sizeof(buf2))) cout << buf2 << endl;

    // read file 3, line-wise
    string buf3;
    while (getline(ifs, buf3)) cout << buf3 << endl;

    // read file 4, character-wise, not recommemded
    //char c;
    //while ((c = ifs.get()) != EOF) cout << c <<endl;

    // close ifstream
    ifs.close();
}

void in_binary() {
    // create ifstream object
    ifstream ifs;

    // open file and check if opened successful
    ifs.open("tempb.txt", ios::in | ios::binary);
    if (!ifs.is_open()) {
        cout << "file opened failed" << endl;
        return;
    } else
        cout << "file opened successful" << endl;

    // read file
    Person p;
    ifs.read((char *)&p, sizeof(Person));
    cout << p.name << " " << p.age << endl;

    // close ifstream
    ifs.close();
}

void out_normal() {
    // create ofstream object
    ofstream ofs;

    // open file
    ofs.open("temp.txt", ios::out);

    // write data
    ofs << "temp normal";

    // close ofstream
    ofs.close();
}

void out_binary() {
    // create ofstream object
    ofstream ofs;

    // open file
    ofs.open("tempb.txt", ios::out | ios::binary);

    // write data
    Person p = {"Bob", 18};
    ofs.write((const char *)&p, sizeof(Person));

    // close ofstream
    ofs.close();
}
