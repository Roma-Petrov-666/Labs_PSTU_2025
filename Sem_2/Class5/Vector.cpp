#include "Vector.h"

Vector::Vector(void) : beg(nullptr), size(0), cur(0) {}

Vector::Vector(int n) : size(n), cur(0) {
    beg = new Object*[n];
}

Vector::~Vector(void) {
    if (beg) delete[] beg;
}

void Vector::Add(Object* p) {
    if (cur < size) {
        beg[cur++] = p;
    }
}

std::ostream& operator<<(std::ostream& out, const Vector& v) {
    if (v.cur == 0) {
        out << "Vector is empty." << std::endl;
    } else {
        for (int i = 0; i < v.cur; ++i) {
            out << "Element " << i + 1 << ": ";
            v.beg[i]->Show();
        }
    }
    return out;
}