#pragma once

#include <iostream>

template <class T>
class Set {
public:
    // Конструктор без параметров – пустое множество
    Set();
    // Конструктор с параметрами: выделяет память под s элементов,
    // инициализирует их значением val (по умолчанию T())
    Set(int s, T val = T());
    // Конструктор копирования
    Set(const Set<T>& other);
    // Деструктор
    ~Set();

    // Оператор присваивания
    Set<T>& operator=(const Set<T>& other);

    // Доступ по индексу (чтение и запись)
    T& operator[](int index);
    const T& operator[](int index) const;

    // Определение размера множества
    int operator()() const;

    // Объединение множеств (без повторений)
    Set<T> operator+(const Set<T>& other) const;

    // Глобальные операторы ввода-вывода
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const Set<U>& s);
    template <class U>
    friend std::istream& operator>>(std::istream& in, Set<U>& s);

private:
    int size;   // текущее количество элементов
    T* data;    // динамический массив элементов
};

// ========== Реализация методов ==========

template <class T>
Set<T>::Set() : size(0), data(nullptr) {}

template <class T>
Set<T>::Set(int s, T val) : size(s) {
    data = new T[size];
    for (int i = 0; i < size; ++i)
        data[i] = val;
}

template <class T>
Set<T>::Set(const Set<T>& other) : size(other.size) {
    data = new T[size];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
}

template <class T>
Set<T>::~Set() {
    delete[] data;
    data = nullptr;
}

template <class T>
Set<T>& Set<T>::operator=(const Set<T>& other) {
    if (this == &other) return *this;
    delete[] data;
    size = other.size;
    data = new T[size];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
    return *this;
}

template <class T>
T& Set<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        std::cout << "\nError! Index out of range" << std::endl;
        static T dummy = T(); // фиктивная переменная для возврата
        return dummy;
    }
    return data[index];
}

template <class T>
const T& Set<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        std::cout << "\nError! Index out of range" << std::endl;
        static T dummy = T();
        return dummy;
    }
    return data[index];
}

template <class T>
int Set<T>::operator()() const {
    return size;
}

template <class T>
Set<T> Set<T>::operator+(const Set<T>& other) const {
    // Временный массив максимально возможного размера
    int maxSize = size + other.size;
    T* temp = new T[maxSize];
    int newSize = 0;

    // Копируем все элементы первого множества
    for (int i = 0; i < size; ++i)
        temp[newSize++] = data[i];

    // Добавляем элементы второго, которых ещё нет
    for (int j = 0; j < other.size; ++j) {
        bool found = false;
        for (int k = 0; k < newSize; ++k) {
            if (temp[k] == other.data[j]) {
                found = true;
                break;
            }
        }
        if (!found)
            temp[newSize++] = other.data[j];
    }

    // Создаём результирующее множество точного размера
    Set<T> result(newSize);
    for (int i = 0; i < newSize; ++i)
        result.data[i] = temp[i];

    delete[] temp;
    return result;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Set<T>& s) {
    if (s.size == 0) {
        out << "Empty";
    } else {
        for (int i = 0; i < s.size; ++i) {
            out << s.data[i];
            if (i != s.size - 1) out << " ";
        }
    }
    return out;
}

template <class T>
std::istream& operator>>(std::istream& in, Set<T>& s) {
    std::cout << "Enter " << s.size << " elements:" << std::endl;
    for (int i = 0; i < s.size; ++i) {
        std::cout << "[" << i << "]: ";
        in >> s.data[i];
    }
    return in;
}