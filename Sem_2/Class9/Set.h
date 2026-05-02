#pragma once

#include <iostream>

#include "Error.h"

const int MAX_SIZE = 30;

class Set {
public:
    Set();
    Set(int s);                  // может бросить MaxSizeError
    Set(const Set& other);
    ~Set();

    Set& operator=(const Set& other);

    int& operator[](int index);          // бросает IndexErrorNegative / IndexErrorLarge
    int  operator()() const;

    Set  operator+(const Set& other) const; // бросает UnionOverflowError

    Set& operator++();        // бросает OverflowError
    Set  operator++(int);      // бросает OverflowError

    friend std::ostream& operator<<(std::ostream& out, const Set& s);
    friend std::istream& operator>>(std::istream& in, Set& s);

private:
    int size;
    int* data;
    bool contains(int val) const;
    void add(int val);        // бросает OverflowError, если size == MAX_SIZE
};