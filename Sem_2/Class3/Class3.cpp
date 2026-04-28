#pragma once

#include <iostream>

#include "Class3.h"

// перегрузка операции присваивания
Money& Money::operator=(const Money& t) {
    if (&t == this) return *this;
    rubel = t.rubel;
    kop = t.kop;
    return *this;
}

// перегрузка префиксной операции инкремент
Money& Money::operator++() {
    int temp = rubel * 100 + kop;
    ++temp;
    rubel = temp / 100;
    kop = temp % 100;
    return *this;
}

// перегрузка постфиксной операции инкремент
Money Money::operator++(int) {
    int temp = rubel * 100 + kop;
    ++temp;
    Money t(rubel, kop);
    rubel = temp / 100;
    kop = temp % 100;
    return t;
}

// перегрузка бинарной операции сложения
Money Money::operator+(const Money& t) {
    int temp1 = rubel * 100 + kop;
    int temp2 = t.rubel * 100 + t.kop;
    Money p;
    p.rubel = (temp1 + temp2) / 100;
    p.kop = (temp1 + temp2) % 100;
    return p;
}

// перегрузка глобальной функции-операции ввода
std::istream& operator>>(std::istream& in, Money& t) {
    std::cout << "rubel: ";   // добавили std::
    in >> t.rubel;
    std::cout << "kop: ";
    in >> t.kop;
    return in;
}

// перегрузка глобальной функции-операции вывода
std::ostream& operator<<(std::ostream& out, const Money& t) {
    return out << t.rubel << "," << t.kop;
}