#pragma once

#include <iostream>

// Предварительное объявление класса Set для использования в Iterator
class Set;

class Iterator {
    friend class Set;

public:
    Iterator() : elem(nullptr) {}
    Iterator(const Iterator& it) : elem(it.elem) {}

    bool operator==(const Iterator& it) const { return elem == it.elem; }
    bool operator!=(const Iterator& it) const { return elem != it.elem; }

    // Префиксный инкремент – переход к следующему элементу
    void operator++() { ++elem; }

    // Разыменование – получение значения текущего элемента
    int& operator*() const { return *elem; }

private:
    int* elem;   // указатель на элемент типа int
};


class Set {
    friend class Iterator;
    friend std::ostream& operator<<(std::ostream& out, const Set& s);
    friend std::istream& operator>>(std::istream& in, Set& s);

public:
    Set();                                  // пустое множество
    Set(int s);                             // множество заданного размера
    Set(const Set& other);                  // копирование
    ~Set();

    // Операция присваивания
    Set& operator=(const Set& other);

    // Доступ по индексу (чтение и запись)
    int& operator[](int index);
    int  operator[](int index) const;

    // Размер множества
    int operator()() const;

    // Объединение множеств
    Set operator+(const Set& other) const;

    // Итераторы
    Iterator first() const { return beg; }
    Iterator last()  const { return end; }

private:
    int size;        // текущее количество элементов
    int* data;       // динамический массив элементов
    Iterator beg;    // указатель на первый элемент
    Iterator end;    // указатель на элемент за последним
};