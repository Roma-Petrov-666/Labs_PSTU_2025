#include <iostream>
#include <stack>
#include <vector>

#include "Money.h"

typedef std::stack<Money> St;
typedef std::vector<Money> Vec;

Vec stack_to_vector(St s) {
    Vec v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }
    return v;
}

St vector_to_stack(const Vec& v) {
    St s;
    for (int i = v.size() - 1; i >= 0; --i)
        s.push(v[i]);
    return s;
}

St make_stack(int n) {
    St s;
    for (int i = 0; i < n; ++i) {
        Money m;
        std::cin >> m;
        s.push(m);
    }
    return s;
}

void print_stack(St s) {
    Vec v = stack_to_vector(s);
    for (int i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

Money max_element(St s) {
    Vec v = stack_to_vector(s);
    Money max_val = v[0];
    for (int i = 1; i < v.size(); ++i)
        if (v[i] > max_val) max_val = v[i];
    return max_val;
}

Money min_element(St s) {
    Vec v = stack_to_vector(s);
    Money min_val = v[0];
    for (int i = 1; i < v.size(); ++i)
        if (v[i] < min_val) min_val = v[i];
    return min_val;
}

Money srednee(St s) {
    Vec v = stack_to_vector(s);
    Money sum;
    for (int i = 0; i < v.size(); ++i)
        sum = sum + v[i];
    return sum / (int)v.size();
}

void add_max_to_begin(St& s) {
    if (s.empty()) return;
    Money max_val = max_element(s);
    Vec v = stack_to_vector(s);
    v.insert(v.begin(), max_val);
    s = vector_to_stack(v);
}

void del_min(St& s) {
    if (s.empty()) return;
    Money min_val = min_element(s);
    Vec v = stack_to_vector(s);
    Vec new_v;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == min_val) continue;
        new_v.push_back(v[i]);
    }
    s = vector_to_stack(new_v);
}

void add_srednee(St& s) {
    if (s.empty()) return;
    Money sr = srednee(s);
    Vec v = stack_to_vector(s);
    for (int i = 0; i < v.size(); ++i)
        v[i] = v[i] + sr;
    s = vector_to_stack(v);
}

int main() {
    St s;
    int n;
    std::cout << "Количество элементов в стеке: ";
    std::cin >> n;
    s = make_stack(n);
    std::cout << "Исходный стек:\n";
    print_stack(s);

    add_max_to_begin(s);
    std::cout << "После добавления максимального в начало (вершину):\n";
    print_stack(s);

    del_min(s);
    std::cout << "После удаления минимального:\n";
    print_stack(s);

    add_srednee(s);
    std::cout << "После прибавления среднего арифметического:\n";
    print_stack(s);

    return 0;
}