#pragma once

#include <iostream>

class Money {
public:
    Money();                           // конструктор без параметров
    Money(long rubles, int kopeks);    // конструктор с параметрами
    Money(const Money& other);         // конструктор копирования
    ~Money();

    // Оператор присваивания
    Money& operator=(const Money& other);

    // Операции сравнения (необходимы для объединения множеств)
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    // Дружественные функции ввода-вывода
    friend std::ostream& operator<<(std::ostream& out, const Money& m);
    friend std::istream& operator>>(std::istream& in, Money& m);

private:
    long rub;
    int  kop;
};