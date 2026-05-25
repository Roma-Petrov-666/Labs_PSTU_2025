#include <iostream>
#include <map>

#include "Money.h"

typedef std::multimap<int, Money> TMultimap;

TMultimap make_multimap(int n) {
    TMultimap m;
    Money val;
    for (int i = 0; i < n; ++i) {
        std::cin >> val;
        m.insert(std::make_pair(i, val));
    }
    return m;
}

void print_multimap(const TMultimap& m) {
    for (const auto& kv : m)
        std::cout << kv.first << " : " << kv.second << std::endl;
    std::cout << std::endl;
}

Money max_value(const TMultimap& m) {
    auto it = m.begin();
    Money mx = it->second;
    for (++it; it != m.end(); ++it)
        if (it->second > mx) mx = it->second;
    return mx;
}

Money min_value(const TMultimap& m) {
    auto it = m.begin();
    Money mn = it->second;
    for (++it; it != m.end(); ++it)
        if (it->second < mn) mn = it->second;
    return mn;
}

Money average(const TMultimap& m) {
    Money sum;
    for (const auto& kv : m) sum = sum + kv.second;
    return sum / static_cast<int>(m.size());
}

void add_max_to_begin(TMultimap& m) {
    if (m.empty()) return;
    Money mx = max_value(m);
    int min_key = m.begin()->first;
    m.insert(std::make_pair(min_key - 1, mx));
}

void remove_min(TMultimap& m) {
    if (m.empty()) return;
    Money mn = min_value(m);
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it->second == mn) {
            m.erase(it);
            break;
        }
    }
}

void add_average(TMultimap& m) {
    if (m.empty()) return;
    Money avg = average(m);
    for (auto& kv : m)
        kv.second = kv.second + avg;
}

int main() {
    int n;
    std::cout << "N? ";
    std::cin >> n;
    TMultimap mm = make_multimap(n);
    std::cout << "\nИсходный multimap:\n";
    print_multimap(mm);

    add_max_to_begin(mm);
    std::cout << "После добавления максимального в начало:\n";
    print_multimap(mm);

    remove_min(mm);
    std::cout << "После удаления минимального:\n";
    print_multimap(mm);

    add_average(mm);
    std::cout << "После прибавления среднего ко всем элементам:\n";
    print_multimap(mm);

    return 0;
}