#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <numeric>

// Вспомогательные шаблонные функции для конвертации
template <class T>
std::vector<T> stack_to_vector(std::stack<T> s) {
    std::vector<T> v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }
    return v;
}

template <class T>
std::stack<T> vector_to_stack(const std::vector<T>& v) {
    std::stack<T> s;
    for (int i = v.size() - 1; i >= 0; --i)
        s.push(v[i]);
    return s;
}

template <class T>
class SetStack {
public:
    SetStack() {}

    void Add(const T& el) {
        // Проверка уникальности: преобразуем стек в вектор, ищем el
        std::vector<T> v = stack_to_vector(data);
        if (std::find(v.begin(), v.end(), el) == v.end()) {
            data.push(el);
        }
    }

    SetStack operator+(const SetStack& other) const {
        SetStack res = *this;
        std::vector<T> otherVec = stack_to_vector(other.data);
        for (const auto& x : otherVec)
            res.Add(x);
        return res;
    }

    int size() const {
        return data.size();
    }

    void Print() const {
        std::stack<T> s = data; // копия
        std::vector<T> v = stack_to_vector(s);
        for (const auto& x : v)
            std::cout << x << " ";
        std::cout << std::endl;
    }

    // Задание 3 – добавить максимальный элемент в начало (вершину стека)
    void AddMaxToBegin() {
        if (data.empty()) return;
        std::vector<T> v = stack_to_vector(data);
        auto it = std::max_element(v.begin(), v.end());
        T max_val = *it;
        v.insert(v.begin(), max_val);
        data = vector_to_stack(v);
    }

    // Задание 4 – удалить минимальный элемент
    void DelMin() {
        if (data.empty()) return;
        std::vector<T> v = stack_to_vector(data);
        auto it = std::min_element(v.begin(), v.end());
        v.erase(it);
        data = vector_to_stack(v);
    }

    // Задание 5 – ко всем элементам прибавить среднее арифметическое
    void AddSrednee() {
        if (data.empty()) return;
        std::vector<T> v = stack_to_vector(data);
        T sum = std::accumulate(v.begin(), v.end(), T());
        T avg = sum / (int)v.size();
        for (auto& x : v)
            x = x + avg;
        data = vector_to_stack(v);
    }

private:
    std::stack<T> data;
};