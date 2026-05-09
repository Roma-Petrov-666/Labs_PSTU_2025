#pragma once

#include <iostream>
#include <map>
#include <stdexcept>

template <class T>
class IndexedSet {
private:
    std::map<int, T> data;
    int lastKey;

public:
    IndexedSet() : lastKey(-1) {}
    IndexedSet(int n);
    IndexedSet(const IndexedSet& other) : data(other.data), lastKey(other.lastKey) {}
    ~IndexedSet() {}

    IndexedSet& operator=(const IndexedSet& other);

    T& operator[](int key);
    const T& operator[](int key) const;

    int size() const { return data.size(); }

    // Вывод содержимого
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const IndexedSet<U>& s);
    template <class U>
    friend std::istream& operator>>(std::istream& in, IndexedSet<U>& s);

    void addMaxToBegin();     // добавить максимальный элемент в начало
    void delMin();            // удалить минимальный элемент
    void addSrednee();        // ко всем элементам прибавить среднее арифметическое

private:
    T maxValue() const;
    T minValue() const;
    T average() const;
};



template <class T>
IndexedSet<T>::IndexedSet(int n) : lastKey(n - 1) {
    T val;
    for (int i = 0; i < n; ++i) {
        std::cin >> val;
        data[i] = val;
    }
}

template <class T>
IndexedSet<T>& IndexedSet<T>::operator=(const IndexedSet<T>& other) {
    if (this != &other) {
        data = other.data;
        lastKey = other.lastKey;
    }
    return *this;
}

template <class T>
T& IndexedSet<T>::operator[](int key) {
    auto it = data.find(key);
    if (it == data.end())
        throw std::out_of_range("Key not found");
    return it->second;
}

template <class T>
const T& IndexedSet<T>::operator[](int key) const {
    auto it = data.find(key);
    if (it == data.end())
        throw std::out_of_range("Key not found");
    return it->second;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const IndexedSet<T>& s) {
    if (s.data.empty()) {
        out << "Empty" << std::endl;
    } else {
        for (const auto& kv : s.data)
            out << kv.first << " : " << kv.second << std::endl;
    }
    return out;
}

template <class T>
std::istream& operator>>(std::istream& in, IndexedSet<T>& s) {
    int n;
    std::cout << "Введите количество элементов: ";
    in >> n;
    s.data.clear();
    s.lastKey = n - 1;
    T val;
    for (int i = 0; i < n; ++i) {
        std::cout << "[" << i << "]: ";
        in >> val;
        s.data[i] = val;
    }
    return in;
}


template <class T>
T IndexedSet<T>::maxValue() const {
    if (data.empty()) throw std::logic_error("empty container");
    auto it = data.begin();
    T mx = it->second;
    for (++it; it != data.end(); ++it)
        if (it->second > mx) mx = it->second;
    return mx;
}

template <class T>
T IndexedSet<T>::minValue() const {
    if (data.empty()) throw std::logic_error("empty container");
    auto it = data.begin();
    T mn = it->second;
    for (++it; it != data.end(); ++it)
        if (it->second < mn) mn = it->second;
    return mn;
}

template <class T>
T IndexedSet<T>::average() const {
    if (data.empty()) throw std::logic_error("empty container");
    T sum = data.begin()->second;
    for (auto it = ++data.begin(); it != data.end(); ++it)
        sum = sum + it->second;
    return sum / static_cast<int>(data.size());
}


template <class T>
void IndexedSet<T>::addMaxToBegin() {
    if (data.empty()) return;
    T mx = maxValue();
    int minKey = data.begin()->first;
    int newKey = minKey - 1;
    data.insert(std::make_pair(newKey, mx));
}

template <class T>
void IndexedSet<T>::delMin() {
    if (data.empty()) return;
    T mn = minValue();
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it->second == mn) {
            data.erase(it);
            break;
        }
    }
}

template <class T>
void IndexedSet<T>::addSrednee() {
    if (data.empty()) return;
    T avg = average();
    for (auto& kv : data)
        kv.second = kv.second + avg;
}