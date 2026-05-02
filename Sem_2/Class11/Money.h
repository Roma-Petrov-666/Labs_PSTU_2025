#pragma once

#include <iostream>
#include <fstream>

class Money {
public:
    Money();
    Money(long rubles, int kopeks);
    Money(const Money& other);
    ~Money();

    Money& operator=(const Money& other);

    // Арифметика
    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;
    Money operator/(int divisor) const;

    // Сравнения
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator>(const Money& other) const;
    bool operator<(const Money& other) const;

    // Ввод/вывод
    friend std::ostream& operator<<(std::ostream& out, const Money& m);
    friend std::istream& operator>>(std::istream& in, Money& m);
    friend std::fstream& operator>>(std::fstream& fin, Money& m);
    friend std::fstream& operator<<(std::fstream& fout, const Money& m);

private:
    long rub;
    int  kop;
};