#pragma once

#include "Object.h"

class PAIR : public Object {
public:
    PAIR(void);
    virtual ~PAIR(void);
    PAIR(int, int);
    PAIR(const PAIR&);

    // Селекторы
    int Get_first() const { return first; }
    int Get_second() const { return second; }

    // Модификаторы
    void Set_first(int);
    void Set_second(int);

    // Операция присваивания
    PAIR& operator=(const PAIR&);

    // Покомпонентное сложение
    PAIR operator+(const PAIR&) const;

    // Реализация виртуальных методов
    void Show() override;
    void Input() override;

protected:
    int first;
    int second;
};