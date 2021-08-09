#include <iostream>

using namespace std;

void printStudentWithValue(struct student s);
void printStudentWithReference(struct student* ps);
void printStudentWithReferenceAndConst(const struct student* ps);

struct student {
    string name;
    int age;
    int score;
};

struct fullname {
    string first_name;
    string last_name;
};

struct advanced_student {
    struct fullname name;
    int age;
    int score;
};

// p64-p71, struct
int main() {

    cout << "struct" << endl;

    /*
        struct

        struct struct_name {
            variable_type variable_name1;
            variable_type variable_name2;
            ...
        };

    */

    // basic struct 
    struct student s1;
    s1.name = "Alice";
    s1.age = 18;
    s1.score = 99;
    cout << s1.name << " " << s1.age << " " << s1.score << endl;

    struct student s2 = {"Bob", 19, 100};
    cout << s2.name << " " << s2.age << " " << s2.score << endl;

    // array with struct
    struct student stus[3] = {
        {"Alice", 18, 99},
        {"Bob", 19, 100},
    };
    for (int i = 0; i < (sizeof(stus)/sizeof(stus[0])); i++)
        cout << stus[i].name << " " << stus[i].age << " " << stus[i].score << endl;

    // pointer with struct
    struct student s3 = {"Wild", 20, 87};
    struct student *ps3 = &s3;
    cout << ps3->name << " " << ps3->age << " " << ps3->score << endl;

    // struct with struct
    struct advanced_student as1 = {
        {"first name", "last name"},
        28,
        100,
    };
    cout << as1.name.first_name << " " << as1.name.last_name << " " << as1.age << " " << as1.score << endl;

    // struct into function
    struct student s4 = {"Cathy", 23, 93};
    printStudentWithValue(s4);
    printStudentWithReference(&s4);

    // struct with const
    struct student s5 = {"David", 25, 91};
    printStudentWithReferenceAndConst(&s5);

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void printStudentWithValue(struct student s) {
    // attributes' value changed inside here wont affect outside's value
    cout << s.name << " " << s.age << " " << s.score << endl;
}

void printStudentWithReference(struct student* ps) {
    // attributes' value changed inside here affects outside's value
    cout << ps->name << " " << ps->age << " " << ps->score << endl;
}

void printStudentWithReferenceAndConst(const struct student* ps) {
    // attributes' value cannot get changed while const is on
    cout << ps->name << " " << ps->age << " " << ps->score << endl;
}
