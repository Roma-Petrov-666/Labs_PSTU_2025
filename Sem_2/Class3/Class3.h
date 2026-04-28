#pragma once

#include <iostream>

class Money {
private:
    long int rubel;
    int kop;
public:
    Money() : rubel(0), kop(0) {}
    Money(int r, int k) : rubel(r), kop(k) {}
    Money(const Money& m) : rubel(m.rubel), kop(m.kop) {}
    ~Money() {}

    int get_rubel() { return rubel; }
    int get_kop() { return kop; }
    void set_rubel(int r) { rubel = r; }
    void set_kop(int k) { kop = k; }

    // перегруженные операции
    Money& operator=(const Money&);
    Money& operator++();        // префиксный
    Money operator++(int);      // постфиксный
    Money operator+(const Money&);

    // глобальные функции ввода-вывода – теперь с std::
    friend std::istream& operator>>(std::istream& in, Money& t);
    friend std::ostream& operator<<(std::ostream& out, const Money& t);
};