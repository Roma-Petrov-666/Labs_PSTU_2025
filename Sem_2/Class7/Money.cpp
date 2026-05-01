#include "Money.h"

Money::Money() : rub(0), kop(0) {}

Money::Money(long rubles, int kopeks) : rub(rubles), kop(kopeks) {
    // Нормализация копеек (диапазон 0..99)
    if (kop < 0 || kop > 99) {
        rub += kop / 100;
        kop %= 100;
        if (kop < 0) {
            kop += 100;
            rub--;
        }
    }
}

Money::Money(const Money& other) : rub(other.rub), kop(other.kop) {}

Money::~Money() {}

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        rub = other.rub;
        kop = other.kop;
    }
    return *this;
}

bool Money::operator==(const Money& other) const {
    return rub == other.rub && kop == other.kop;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Money& m) {
    out << m.rub << ",";
    // Добавляем ведущий ноль для копеек, если нужно
    if (m.kop < 10) out << "0";
    out << m.kop;
    return out;
}

std::istream& operator>>(std::istream& in, Money& m) {
    std::cout << "Rubles: ";
    in >> m.rub;
    std::cout << "Kopeks (0..99): ";
    in >> m.kop;
    // Нормализация
    if (m.kop < 0 || m.kop > 99) {
        m.rub += m.kop / 100;
        m.kop %= 100;
        if (m.kop < 0) {
            m.kop += 100;
            m.rub--;
        }
    }
    return in;
}