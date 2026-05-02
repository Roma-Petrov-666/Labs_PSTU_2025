#include <iostream>

#include "Set.h"

Set::Set() : size(0), data(nullptr) {}

Set::Set(int s) : size(s) {
    if (s > MAX_SIZE) throw MaxSizeError();
    data = new int[size];
    for (int i=0; i < size; ++i)
        data[i] = 0;
}

Set::Set(const Set& other) : size(other.size) {
    data = new int[size];
    for (int i=0; i < size; ++i)
        data[i] = other.data[i];
}

Set::~Set() {
    delete[] data;
}

Set& Set::operator=(const Set& other) {
    if (this == &other) return *this;
    delete[] data;
    size = other.size;
    data = new int[size];
    for (int i=0; i < size; ++i)
        data[i] = other.data[i];
    return *this;
}

int& Set::operator[](int index) {
    if (index < 0) throw IndexErrorNegative();
    if (index >= size) throw IndexErrorLarge();
    return data[index];
}

int Set::operator()() const {
    return size;
}

bool Set::contains(int val) const {
    for (int i = 0; i < size; ++i)
        if (data[i] == val) return true;
    return false;
}

void Set::add(int val) {
    if (contains(val)) return;
    if (size >= MAX_SIZE) throw OverflowError();
    int* newData = new int[size + 1];
    for (int i=0; i < size; ++i)
        newData[i] = data[i];
    newData[size] = val;
    delete[] data;
    data = newData;
    ++size;
}

Set& Set::operator++() {
    add(0);
    return *this;
}

Set Set::operator++(int) {
    Set temp = *this;
    add(0);
    return temp;
}

Set Set::operator+(const Set& other) const {
    int uniqueCount = size;
    for (int i=0; i < other.size; ++i)
        if (!contains(other.data[i]))
            ++uniqueCount;
    if (uniqueCount > MAX_SIZE) throw UnionOverflowError();

    Set result(0);
    for (int i=0; i < size; ++i)
        if (!result.contains(data[i]))
            result.add(data[i]);
    for (int i=0; i < other.size; ++i)
        if (!result.contains(other.data[i]))
            result.add(other.data[i]);
    return result;
}

std::ostream& operator<<(std::ostream& out, const Set& s) {
    if (s.size == 0) {
        out << "Empty";
    } else {
        for (int i=0; i < s.size; ++i)
            out << s.data[i] << " ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Set& s) {
    std::cout << "Enter " << s.size << " elements:\n";
    for (int i=0; i < s.size; ++i) {
        std::cout << "[" << i << "]: ";
        in >> s.data[i];
    }
    return in;
}