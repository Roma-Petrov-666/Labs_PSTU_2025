#include "Pair.h"

PAIR::PAIR(void) : first(0), second(0) {}
PAIR::~PAIR(void) {}
PAIR::PAIR(int F, int S) : first(F), second(S) {}
PAIR::PAIR(const PAIR& other) : first(other.first), second(other.second) {}

void PAIR::Set_first(int F) { first = F; }
void PAIR::Set_second(int S) { second = S; }

PAIR& PAIR::operator=(const PAIR& c) {
    if (&c == this) return *this;
    first = c.first;
    second = c.second;
    return *this;
}

PAIR PAIR::operator+(const PAIR& other) const {
    return PAIR(first + other.first, second + other.second);
}

void PAIR::Show() {
    std::cout << "first = " << first << ", second = " << second << std::endl;
}

void PAIR::Input() {
    std::cout << "first: ";
    std::cin >> first;
    std::cout << "second: ";
    std::cin >> second;
}