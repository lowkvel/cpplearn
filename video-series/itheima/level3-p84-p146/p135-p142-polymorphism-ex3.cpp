#include <iostream>

using namespace std;

class Cpu {
public:
    // declare a virtual destructor for base class
    virtual ~Cpu() {}

    virtual void calculate() = 0;
};

class IntelCpu: public Cpu {
public:
    virtual ~IntelCpu() {
        cout << "Intel cpu destructed" << endl;
    }

    virtual void calculate() {
        cout << "Intel cpu calculates" << endl;
    }
};

class AmdCpu: public Cpu {
public:
    virtual ~AmdCpu() {
        cout << "Amd cpu destructed" << endl;
    }

    virtual void calculate() {
        cout << "Amd cpu calculates" << endl;
    }
};

class VideoCard {
public:
    // declare a virtual destructor for base class
    virtual ~VideoCard() {}

    virtual void display() = 0;
};

class IntelVideoCard: public VideoCard {
public:
    virtual ~IntelVideoCard() {
        cout << "Intel video card destructed" << endl;
    }

    virtual void display() {
        cout << "Intel video card displays" << endl;
    }
};

class AmdVideoCard: public VideoCard {
public:
    virtual ~AmdVideoCard() {
        cout << "Amd video card destructed" << endl;
    }

    virtual void display() {
        cout << "Amd video card displays" << endl;
    }
};

class MemoryCard {
public:
    // declare a virtual destructor for base class
    virtual ~MemoryCard() {}

    virtual void storage() = 0;
};

class IntelMemoryCard: public MemoryCard {
public:
    virtual ~IntelMemoryCard() {
        cout << "Intel memory card destructed" << endl;
    }

    virtual void storage() {
        cout << "Intel memory card storages" << endl;
    }
};

class AmdMemoryCard: public MemoryCard {
public:
    virtual ~AmdMemoryCard() {
        cout << "Amd memory card destructed" << endl;
    }

    virtual void storage() {
        cout << "Amd memory card storages" << endl;
    }
};

class Computer {
private:
    Cpu *c;
    VideoCard *vc;
    MemoryCard *mc;

public:
    Computer(Cpu *c, VideoCard *vc, MemoryCard *mc) {
        this->c = c;
        this->vc = vc;
        this->mc = mc;
    }

    ~Computer() {
        if (c != NULL) { delete c; c = NULL; }
        if (vc != NULL) { delete vc; vc = NULL; }
        if (mc != NULL) { delete mc; mc = NULL; }
    }

    void work() {
        c->calculate();
        vc->display();
        mc->storage();
    }
};

void func1();

// p135-p142, polymorphism ex3
int main() {

    cout << "polymorphism ex3" << endl;

    /*
        polymorphism ex3

        the use of virtual destructor
            https://stackoverflow.com/questions/270917/why-should-i-declare-a-virtual-destructor-for-an-abstract-class-in-c 
    */

    func1();

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

void func1() {
    // intel computer
    Cpu *ic = new IntelCpu;
    VideoCard *ivc = new IntelVideoCard;
    MemoryCard *imc = new IntelMemoryCard;
    Computer *c1 = new Computer(ic, ivc, imc);
    c1->work();
    delete c1; c1 = NULL;

    // amd computer
    Computer *c2 = new Computer(new AmdCpu, new AmdVideoCard, new AmdMemoryCard);
    c2->work();
    delete c2; c2 = NULL;
}
