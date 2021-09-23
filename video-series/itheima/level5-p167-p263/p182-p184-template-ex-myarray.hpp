# pragma once

# include <iostream>

using namespace std;

template <typename T>
class Myarray {
private:
    T *paddr;           // points to new()ed array in heap pool
    int capacity;       // array element max count
    int size;           // array element current count

public:
    // constructor
    Myarray(int capacity) {
        //cout << "parameterized constructor" << endl;
        this->capacity = capacity;      // max element count set to capacity
        this->size = 0;                 // current element count set to 0
        this->paddr = new T[this->capacity];    // new() this array in heap pool
    }

    // copy constructor
    Myarray(const Myarray &arr) {
        //cout << "copy constructor" << endl;
        this->capacity = arr.capacity;
        this->size = arr.size;

        // deep copy each element 
        this->paddr = new T[arr.capacity];
        for (int i = 0; i < arr.size; i++)
            this->paddr[i] = arr.paddr[i];
    }

    // operator= overload to prevent shallow copy
    Myarray& operator=(const Myarray &arr) {
        //cout << "operator= overload" << endl;
        // release the data exists in paddr if needed
        if (this->paddr != NULL) {
            delete[] this->paddr;
            this->paddr = NULL;
            this->capacity = 0;
            this->size = 0;
        }

        // deep copy
        this->capacity = arr.capacity;
        this->size = arr.size;
        this->paddr = new T[arr.capacity];
        for (int i = 0; i < arr.size; i++)
            this->paddr[i] = arr.paddr[i];

        return *this;
    }

    // insert at the end
    void ins(const T &val) {
        if (this->capacity == this->size)
            return;
        this->paddr[this->size] = val;
        this->size ++;
    }

    // delete at the end
    void del() {
        if (this->size == 0)
            return;
        //delete this->paddr[this->size];     // physical delete, todo
        this->size --;                      // logical delete
    }

    // access from index
    T& operator[](int index) {
        // if (index >= this->size) return NULL;
        return this->paddr[index];
    }

    // get capacity
    int getCapacity() {
        return this->capacity;
    }

    // get size
    int getSize() {
        return this->size;
    }

    // destructor
    ~Myarray() {
        //cout << "desturctor" << endl;
        if (this->paddr != NULL) {
            delete[] this->paddr;
            this->paddr = NULL;
        }
    }
};
