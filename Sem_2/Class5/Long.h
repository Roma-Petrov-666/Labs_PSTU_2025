#pragma once

#include "Pair.h"

class LONG : public PAIR {
public:
    static const int BASE = 10;

    LONG();
    LONG(int high, int low);
    LONG(const LONG&);

    // Переопределённые операции
    LONG operator+(const LONG&) const;
    LONG operator-(const LONG&) const;
    LONG operator*(const LONG&) const;

    void Show() override;
    void Input() override;
};