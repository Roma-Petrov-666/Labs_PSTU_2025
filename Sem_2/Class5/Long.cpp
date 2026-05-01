#include "Long.h"

LONG::LONG() : PAIR(0, 0) {}

LONG::LONG(int high, int low) : PAIR(high, low) {
    // Нормализация младшей части
    if (low >= BASE || low < 0) {
        second = low % BASE;
        first = high + low / BASE;
        if (second < 0) {
            second += BASE;
            first--;
        }
    }
}

LONG::LONG(const LONG& other) : PAIR(other) {}

LONG LONG::operator+(const LONG& other) const {
    int lowSum = second + other.second;
    int carry = lowSum / BASE;
    int newLow = lowSum % BASE;
    int newHigh = first + other.first + carry;
    return LONG(newHigh, newLow);
}

LONG LONG::operator-(const LONG& other) const {
    int newLow = second - other.second;
    int borrow = 0;
    if (newLow < 0) {
        newLow += BASE;
        borrow = 1;
    }
    int newHigh = first - other.first - borrow;
    return LONG(newHigh, newLow);
}

LONG LONG::operator*(const LONG& other) const {
    long long a = static_cast<long long>(first) * BASE + second;
    long long b = static_cast<long long>(other.first) * BASE + other.second;
    long long product = a * b;

    int newLow  = static_cast<int>(product % BASE);
    int newHigh = static_cast<int>(product / BASE);
    return LONG(newHigh, newLow);
}

void LONG::Show() {
    std::cout << "High = " << first << ", Low = " << second
              << "  (value = " << first * BASE + second << ")" << std::endl;
}

void LONG::Input() {
    std::cout << "High part: ";
    std::cin >> first;
    std::cout << "Low part (0.." << BASE - 1 << "): ";
    std::cin >> second;
    // Нормализация
    if (second >= BASE || second < 0) {
        first += second / BASE;
        second %= BASE;
        if (second < 0) { second += BASE; first--; }
    }
}