# include <iostream>
# include <stack>
# include <queue>

using namespace std;

void func1();

// p104-p209, stl stack & queue
int main() {

    cout << "stl stack & queue" << endl;

    /*
        stl stack & queue

        1.  stack:  FILO
            1.  constructor
                1.  stack<T> s;
                2.  stack(const stack &s);
            2.  assignment
                1.  stack& operator=(const stack &s);
            3.  get/save element
                1.  push(e);
                2.  pop();
                3.  top();
            4.  size
                1.  empty();
                2.  size();
        2.  queue:  FIFO
            1.  constructor
                1.  queue<T> q;
                2.  queue(const queue &q);
            2.  assignment
                1.  queue& operator=(const queue &q);
            3.  get/save element
                1.  push(e);
                2.  pop();
                3.  front();
                4.  back();
            4.  size
                1.  empty();
                2.  size();
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // stack:   FILO
    stack<int> s1; s1.push(1); s1.push(2); s1.push(3); s1.push(4);
    stack<int> s2(s1);          // copied s1
    stack<int> s3 = s1;         // copied s1
    cout << s1.size() << endl;
    while (!s1.empty()) {
        cout << s1.top() << " ";
        s1.pop();
    }
    cout << endl;
    cout << s1.size() << endl;
    cout << s2.size() << endl;
    cout << s3.size() << endl;

    // queue:   FIFO
    queue<int> q1; q1.push(1); q1.push(2); q1.push(3); q1.push(4);
    queue<int> q2(q1);          // copied q1
    queue<int> q3 = q1;         // copied q1
    cout << q1.size() << endl;
    while (!q1.empty()) {
        cout << q1.front() << " ";
        q1.pop();
    }
    cout << endl;
    cout << q1.size() << endl;
    cout << q2.size() << endl;
    cout << q3.size() << endl;
}

