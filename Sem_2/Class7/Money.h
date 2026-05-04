#pragma once

#include <iostream>

class Money {
public:
    Money(void);
    Money(long rubles, int kopeks);
    Money(const Money& other);
    ~Money(void);

    long Get_rub() const { return rub; }
    int  Get_kop() const { return kop; }

    void Set_rub(long r) { rub = r; }
    void Set_kop(int k);

    // Операция присваивания
    Money& operator=(const Money& other);

    // Арифметические операции
    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;

    // Операции сравнения
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    // Дружественные функции ввода/вывода
    friend std::ostream& operator<<(std::ostream& out, const Money& m);
    friend std::istream& operator>>(std::istream& in, Money& m);

private:
    long rub;
    int  kop;
};
