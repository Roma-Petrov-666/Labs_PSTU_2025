#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template <class T>
class Set {
public:
    Set() {}
    Set(int n, T val = T()) : data(n, val) {}

    void Add(const T& el) {
        if (std::find(data.begin(), data.end(), el) == data.end())
            data.push_back(el);
    }

    Set operator+(const Set& other) const {
        Set res = *this;
        for (const auto& x : other.data)
            res.Add(x);
        return res;
    }

    T& operator[](int index) { return data[index]; }
    const T& operator[](int index) const { return data[index]; }
    int size() const { return data.size(); }

    void Print() const {
        for (const auto& x : data)
            std::cout << x << " ";
        std::cout << std::endl;
    }

    // Задание 3 – добавить максимальный элемент в начало
    void AddMaxToBegin() {
        if (data.empty()) return;
        auto it = std::max_element(data.begin(), data.end());
        T max_val = *it;
        data.insert(data.begin(), max_val);
    }

    // Задание 4 – удалить минимальный элемент
    void DelMin() {
        if (data.empty()) return;
        auto it = std::min_element(data.begin(), data.end());
        data.erase(it);
    }

    // Задание 5 – ко всем элементам прибавить среднее арифметическое
    void AddSrednee() {
        if (data.empty()) return;
        T sum = std::accumulate(data.begin(), data.end(), T());
        T avg = sum / (int)data.size();
        for (auto& x : data)
            x = x + avg;
    }

private:
    std::vector<T> data;
};