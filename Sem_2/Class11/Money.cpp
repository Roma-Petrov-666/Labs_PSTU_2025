#include <stdexcept>

#include "Money.h"

Money::Money() : rub(0), kop(0) {}

Money::Money(long rubles, int kopeks) : rub(rubles), kop(kopeks) {
    if (kop < 0 || kop > 99) {
        rub += kop / 100;
        kop %= 100;
        if (kop < 0) {
            kop += 100;
            --rub;
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

Money Money::operator+(const Money& other) const {
    long totalRub = rub + other.rub;
    int  totalKop = kop + other.kop;
    if (totalKop >= 100) {
        totalRub += totalKop / 100;
        totalKop %= 100;
    }
    return Money(totalRub, totalKop);
}

Money Money::operator-(const Money& other) const {
    long totalRub = rub - other.rub;
    int  totalKop = kop - other.kop;
    if (totalKop < 0) {
        totalKop += 100;
        --totalRub;
    }
    return Money(totalRub, totalKop);
}

Money Money::operator/(int divisor) const {
    if (divisor == 0) throw std::runtime_error("Division by zero in Money");
    long long totalKop = static_cast<long long>(rub) * 100 + kop;
    long long resKop = totalKop / divisor;
    long newRub = static_cast<long>(resKop / 100);
    int  newKop = static_cast<int>(resKop % 100);
    return Money(newRub, newKop);
}

bool Money::operator==(const Money& other) const {
    return rub == other.rub && kop == other.kop;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator>(const Money& other) const {
    return (rub * 100 + kop) > (other.rub * 100 + other.kop);
}

bool Money::operator<(const Money& other) const {
    return (rub * 100 + kop) < (other.rub * 100 + other.kop);
}

std::ostream& operator<<(std::ostream& out, const Money& m) {
    out << m.rub << ",";
    if (m.kop < 10) out << "0";
    out << m.kop;
    return out;
}

std::istream& operator>>(std::istream& in, Money& m) {
    std::cout << "Рубли: ";
    in >> m.rub;
    std::cout << "Копейки: ";
    in >> m.kop;
    if (m.kop < 0 || m.kop > 99) {
        m.rub += m.kop / 100;
        m.kop %= 100;
        if (m.kop < 0) {
            m.kop += 100;
            --m.rub;
        }
    }
    return in;
}

std::fstream& operator>>(std::fstream& fin, Money& m) {
    fin >> m.rub >> m.kop;
    return fin;
}

std::fstream& operator<<(std::fstream& fout, const Money& m) {
    fout << m.rub << "\n" << m.kop << "\n";
    return fout;
}