#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>

#include "Money.h"

struct MoneyGreater : public std::binary_function<Money, Money, bool> {
    bool operator()(const Money& a, const Money& b) const { return a > b; }
};

struct MoneyLess : public std::binary_function<Money, Money, bool> {
    bool operator()(const Money& a, const Money& b) const { return a < b; }
};

struct MoneyAdd : public std::binary_function<Money, Money, Money> {
    Money operator()(const Money& a, const Money& b) const { return a + b; }
};

std::vector<Money> stack_to_vector(std::stack<Money> s) {
    std::vector<Money> v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }
    return v;
}

std::stack<Money> vector_to_stack(const std::vector<Money>& v) {
    std::stack<Money> s;
    for (int i = v.size() - 1; i >= 0; --i)
        s.push(v[i]);
    return s;
}

template <typename Cont>
void print_container(const Cont& c, const std::string& name = "") {
    if (!name.empty()) std::cout << name << ": ";
    for (const auto& el : c) std::cout << el << "  ";
    std::cout << std::endl;
}

void print_stack(std::stack<Money> s, const std::string& name = "") {
    std::vector<Money> v = stack_to_vector(s);
    print_container(v, name);
}

// ===================================================================
// ЗАДАЧА 1:
// ===================================================================
void task1_vector() {
    std::cout << "\n========== ЗАДАЧА 1: vector<Money> ==========\n";
    std::vector<Money> vec;
    vec.push_back(Money(10, 50));
    vec.push_back(Money(5, 30));
    vec.push_back(Money(10, 50));
    vec.push_back(Money(20, 0));
    vec.push_back(Money(5, 30));
    vec.push_back(Money(15, 70));

    print_container(vec, "Исходный вектор");

    Money minVal = *std::min_element(vec.begin(), vec.end());
    std::replace_if(vec.begin(), vec.end(),
                    std::bind2nd(MoneyGreater(), Money(15, 0)),
                    minVal);
    std::cout << "После replace_if (>15.00 -> min): ";
    print_container(vec);

    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             std::bind2nd(std::equal_to<Money>(), minVal)),
              vec.end());
    std::cout << "После remove_if (удалены равные min): ";
    print_container(vec);

    std::sort(vec.begin(), vec.end(), MoneyLess());
    std::cout << "По возрастанию: ";
    print_container(vec);

    std::sort(vec.begin(), vec.end(), MoneyGreater());
    std::cout << "По убыванию: ";
    print_container(vec);

    Money searchVal(10, 50);
    auto it = std::find_if(vec.begin(), vec.end(),
                           std::bind2nd(std::equal_to<Money>(), searchVal));
    if (it != vec.end())
        std::cout << "Элемент " << searchVal << " найден (find_if).\n";
    else
        std::cout << "Элемент " << searchVal << " не найден.\n";

    int cnt = std::count_if(vec.begin(), vec.end(),
                            std::bind2nd(MoneyLess(), Money(10, 0)));
    std::cout << "Количество элементов < 10.00 (count_if): " << cnt << "\n";

    auto maxIt = std::max_element(vec.begin(), vec.end());
    if (maxIt != vec.end()) {
        Money maxVal = *maxIt;
        vec.insert(vec.begin(), maxVal);
        std::cout << "Максимальный (" << maxVal << ") добавлен в начало.\n";
        print_container(vec);
    }

    auto minIt = std::min_element(vec.begin(), vec.end());
    if (minIt != vec.end()) {
        vec.erase(minIt);
        std::cout << "Минимальный удалён.\n";
        print_container(vec);
    }

    if (!vec.empty()) {
        Money sum = std::accumulate(vec.begin(), vec.end(), Money(0, 0));
        Money avg = sum / static_cast<int>(vec.size());
        std::for_each(vec.begin(), vec.end(), [&](Money& m) { m = m + avg; });
        std::cout << "Прибавлено среднее (" << avg << ") ко всем элементам:\n";
        print_container(vec);
    }
}

// ===================================================================
// ЗАДАЧА 2:
// ===================================================================
void task2_stack() {
    std::cout << "\n========== ЗАДАЧА 2: stack<Money> ==========\n";
    std::stack<Money> st;
    st.push(Money(3, 20));
    st.push(Money(7, 80));
    st.push(Money(3, 20));
    st.push(Money(12, 40));
    st.push(Money(7, 80));
    st.push(Money(5, 0));

    print_stack(st, "Исходный стек");

    std::vector<Money> v = stack_to_vector(st);

    Money minVal = *std::min_element(v.begin(), v.end());
    std::replace_if(v.begin(), v.end(),
                    std::bind2nd(MoneyGreater(), Money(7, 0)),
                    minVal);
    st = vector_to_stack(v);
    std::cout << "После замены (>7.00 -> min): ";
    print_stack(st);

    v = stack_to_vector(st);
    v.erase(std::remove_if(v.begin(), v.end(),
                           std::bind2nd(std::equal_to<Money>(), minVal)),
            v.end());
    st = vector_to_stack(v);
    std::cout << "После удаления равных min: ";
    print_stack(st);

    v = stack_to_vector(st);
    std::sort(v.begin(), v.end(), MoneyLess());
    st = vector_to_stack(v);
    std::cout << "Отсортированный стек (вершина – наибольший):\n";
    print_stack(st, "Стек");

    v = stack_to_vector(st);
    Money searchVal(3, 20);
    auto it = std::find_if(v.begin(), v.end(),
                           std::bind2nd(std::equal_to<Money>(), searchVal));
    std::cout << (it != v.end() ? "Элемент найден.\n" : "Элемент не найден.\n");
    int cnt = std::count_if(v.begin(), v.end(),
                            std::bind2nd(MoneyLess(), Money(4, 0)));
    std::cout << "Элементов < 4.00: " << cnt << "\n";

    if (!v.empty()) {
        Money maxVal = *std::max_element(v.begin(), v.end());
        v.insert(v.begin(), maxVal);
        st = vector_to_stack(v);
        std::cout << "Максимальный (" << maxVal << ") добавлен в вершину.\n";
        print_stack(st);
    }

    v = stack_to_vector(st);
    auto minIt = std::min_element(v.begin(), v.end());
    if (minIt != v.end()) {
        v.erase(minIt);
        st = vector_to_stack(v);
        std::cout << "Минимальный удалён.\n";
        print_stack(st);
    }

    v = stack_to_vector(st);
    if (!v.empty()) {
        Money sum = std::accumulate(v.begin(), v.end(), Money(0, 0));
        Money avg = sum / static_cast<int>(v.size());
        std::for_each(v.begin(), v.end(), [&](Money& m) { m = m + avg; });
        st = vector_to_stack(v);
        std::cout << "Прибавлено среднее (" << avg << "):\n";
        print_stack(st);
    }
}

// ===================================================================
// ЗАДАЧА 3:
// ===================================================================
void task3_multiset() {
    std::cout << "\n========== ЗАДАЧА 3: multiset<Money> ==========\n";
    std::multiset<Money> ms;
    ms.insert(Money(4, 40));
    ms.insert(Money(9, 10));
    ms.insert(Money(4, 40));
    ms.insert(Money(2, 30));
    ms.insert(Money(9, 10));

    print_container(ms, "Исходный multiset");

    Money oldVal(9, 10), newVal(8, 80);
    auto pos = ms.find(oldVal);
    while (pos != ms.end()) {
        ms.erase(pos);
        pos = ms.find(oldVal);
    }
    ms.insert(newVal);
    ms.insert(newVal);
    std::cout << "После замены 9.10 -> 8.80:\n";
    print_container(ms);

    ms.erase(Money(4, 40));
    std::cout << "После удаления всех 4.40:\n";
    print_container(ms);

    std::cout << "Прямой обход: ";
    for (auto it = ms.begin(); it != ms.end(); ++it) std::cout << *it << " ";
    std::cout << "\nОбратный обход: ";
    for (auto it = ms.rbegin(); it != ms.rend(); ++it) std::cout << *it << " ";
    std::cout << "\n";

    Money searchVal(2, 30);
    auto found = ms.find(searchVal);
    std::cout << (found != ms.end() ? "Найден 2.30\n" : "Не найден 2.30\n");
    std::cout << "Количество 8.80 = " << ms.count(Money(8, 80)) << "\n";

    if (!ms.empty()) {
        auto maxIt = ms.rbegin();
        Money maxVal = *maxIt;
        ms.insert(maxVal);
        std::cout << "Максимальный (" << maxVal << ") добавлен (multiset::insert).\n";
        print_container(ms);
    }

    if (!ms.empty()) {
        ms.erase(ms.begin());
        std::cout << "Минимальный удалён.\n";
        print_container(ms);
    }

    if (!ms.empty()) {
        Money sum = std::accumulate(ms.begin(), ms.end(), Money(0, 0));
        Money avg = sum / static_cast<int>(ms.size());
        std::multiset<Money> newMs;
        std::for_each(ms.begin(), ms.end(), [&](const Money& m) {
            newMs.insert(m + avg);
        });
        ms.swap(newMs);
        std::cout << "Прибавлено среднее (" << avg << "):\n";
        print_container(ms);
    }
}

// ===================================================================
int main() {
    std::cout << "Лабораторная работа №13. Вариант 6.\n";
    std::cout << "Использование стандартных обобщённых алгоритмов.\n\n";

    task1_vector();
    task2_stack();
    task3_multiset();

    return 0;
}