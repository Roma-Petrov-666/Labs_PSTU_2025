#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Money {
public:
    Money();
    Money(long rubles, int kopeks);
    Money(const Money& other);
    ~Money();

    Money& operator=(const Money& other);

    // Арифметические операции
    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;

    // Сравнение (необходимо для удаления равных записей)
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    // Дружественные функции для работы со стандартными и файловыми потоками
    friend std::ostream& operator<<(std::ostream& out, const Money& m);
    friend std::istream& operator>>(std::istream& in, Money& m);
    friend std::fstream& operator>>(std::fstream& fin, Money& m);
    friend std::fstream& operator<<(std::fstream& fout, const Money& m);

private:
    long rub;   // рубли
    int  kop;   // копейки
};