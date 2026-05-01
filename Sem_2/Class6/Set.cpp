#include <iostream>
#include "Set.h"

Set::Set() : size(0), data(nullptr) {
    beg.elem = data;
    end.elem = data;
}

Set::Set(int s) : size(s) {
    data = new int[size];
    for (int i=0; i < size; ++i)
        data[i] = 0;
    beg.elem = data;
    end.elem = data + size;
}

Set::Set(const Set& other) : size(other.size) {
    data = new int[size];
    for (int i=0; i < size; ++i)
        data[i] = other.data[i];
    beg.elem = data;
    end.elem = data + size;
}

Set::~Set() {
    delete[] data;
    data = nullptr;
}

Set& Set::operator=(const Set& other) {
    if (this == &other) return *this;
    delete[] data;
    size = other.size;
    data = new int[size];
    for (int i=0; i < size; ++i)
        data[i] = other.data[i];
    beg.elem = data;
    end.elem = data + size;
    return *this;
}

int& Set::operator[](int index) {
    if (index < 0 || index >= size) {
        std::cout << "Ошибка: индекс " << index << " вне диапазона [0.." << size - 1 << "]" << std::endl;
        static int dummy = 0;
        return dummy;
    }
    return data[index];
}

int Set::operator[](int index) const {
    if (index < 0 || index >= size) {
        std::cout << "Ошибка: индекс " << index << " вне диапазона" << std::endl;
        return 0;
    }
    return data[index];
}

int Set::operator()() const {
    return size;
}

Set Set::operator+(const Set& other) const {
    int* temp = new int[size + other.size];
    int uniqueSize = 0;

    for (int i=0; i < size; ++i)
        temp[uniqueSize++] = data[i];

    for (int j = 0; j < other.size; ++j) {
        bool found = false;
        for (int k = 0; k < uniqueSize; ++k) {
            if (temp[k] == other.data[j]) {
                found = true;
                break;
            }
        }
        if (!found)
            temp[uniqueSize++] = other.data[j];
    }

    Set result(uniqueSize);
    for (int i=0; i < uniqueSize; ++i) {
        result.data[i] = temp[i];
    }

    delete[] temp;
    return result;
}

std::ostream& operator<<(std::ostream& out, const Set& s) {
    if (s.size == 0) {
        out << "Пустое множество" << std::endl;
    } else {
        for (int i=0; i < s.size; ++i)
            out << s.data[i] << " ";
        out << std::endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Set& s) {
    std::cout << "Введите " << s.size << " элементов:" << std::endl;
    for (int i=0; i < s.size; ++i) {
        std::cout << "[" << i << "]: ";
        in >> s.data[i];
    }
    return in;
}