#include <iostream>

using namespace std;

class Cube {
private:
    int height;
    int width;
    int length;

public:
    void setHeight(int i) {
        height = i;
    }
    int getHeight() {
        return height;
    }
    void setWidth(int i) {
        width = i;
    }
    int getWidth() {
        return width;
    }
    void setLength(int i) {
        length = i;
    }
    int getLength() {
        return length;
    }

    int calculateArea() {
        return (height * width + width * length + length * height) * 2;
    }
    int calculateVolume() {
        return height * width * length;
    }

    bool isSame(Cube &c) {
        return c.getHeight() == height && c.getLength() == length && c.getWidth() == width;
    }

    bool isSame(Cube* c) {
        return c->getHeight() == height && c->getLength() == length && c->getWidth() == width;
    }
};

bool isSame(Cube &c1, Cube &c2);
bool isSame(Cube* c1, Cube* c2);

// p99-p105, object encapsulation ex1
int main() {

    cout << "object encapsulation ex1" << endl;

    /*
        object encapsulation
    */

    Cube c1;
    c1.setHeight(1);
    c1.setLength(2);
    c1.setWidth(3);
    cout << c1.calculateArea() << " " << c1.calculateVolume() << endl;

    Cube c2;
    c2.setHeight(1);
    c2.setLength(2);
    c2.setWidth(3);
    cout << c1.calculateArea() << " " << c1.calculateVolume() << endl;

    cout << isSame(c1, c2) << " " << isSame(&c1, &c2) << endl;
    cout << c1.isSame(c2) << " " << c1.isSame(&c2) << endl;

    //system("pause");    // use it in windows, effect [press any key to continue], no such command in linux/mac

    return 0;
}

bool isSame(Cube &c1, Cube &c2) {
    return c1.getHeight() == c2.getHeight() && c1.getLength() == c2.getLength() && c1.getWidth() == c2.getWidth();
}

bool isSame(Cube* pc1, Cube* pc2) {
    return pc1->getHeight() == pc2->getHeight() && pc1->getLength() == pc2->getLength() && pc1->getWidth() == pc2->getWidth();
}