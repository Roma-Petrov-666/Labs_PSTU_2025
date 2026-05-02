#include "Money.h"

// Конструктор без параметров
Money::Money() : rub(0), kop(0) {}

// Конструктор с параметрами
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

// Конструктор копирования
Money::Money(const Money& other) : rub(other.rub), kop(other.kop) {}

// Деструктор
Money::~Money() {}

// Операция присваивания
Money& Money::operator=(const Money& other) {
    if (this != &other) {
        rub = other.rub;
        kop = other.kop;
    }
    return *this;
}

// Сложение
Money Money::operator+(const Money& other) const {
    long totalRub = rub + other.rub;
    int  totalKop = kop + other.kop;
    if (totalKop >= 100) {
        totalRub += totalKop / 100;
        totalKop %= 100;
    }
    return Money(totalRub, totalKop);
}

// Вычитание
Money Money::operator-(const Money& other) const {
    long totalRub = rub - other.rub;
    int  totalKop = kop - other.kop;
    if (totalKop < 0) {
        totalKop += 100;
        --totalRub;
    }
    return Money(totalRub, totalKop);
}

// Операции сравнения
bool Money::operator==(const Money& other) const {
    return rub == other.rub && kop == other.kop;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

// Вывод в стандартный поток
std::ostream& operator<<(std::ostream& out, const Money& m) {
    out << m.rub << ",";
    if (m.kop < 10) out << "0";
    out << m.kop;
    return out;
}

// Ввод из стандартного потока
std::istream& operator>>(std::istream& in, Money& m) {
    std::cout << "Рубли: ";
    in >> m.rub;
    std::cout << "Копейки (0..99): ";
    in >> m.kop;
    // Нормализация
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

// Чтение из файлового потока
std::fstream& operator>>(std::fstream& fin, Money& m) {
    fin >> m.rub;
    fin >> m.kop;
    return fin;
}

// Запись в файловый поток
std::fstream& operator<<(std::fstream& fout, const Money& m) {
    fout << m.rub << "\n" << m.kop << "\n";
    return fout;
}