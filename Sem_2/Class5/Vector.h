#pragma once

#include "Object.h"

class Vector {
public:
    Vector(void);
    Vector(int n);
    virtual ~Vector(void);

    void Add(Object* p);  // добавить указатель на объект

    // Перегруженная операция вывода
    friend std::ostream& operator<<(std::ostream& out, const Vector& v);

private:
    Object** beg;
    int size;      // ёмкость
    int cur;       // текущее количество
};