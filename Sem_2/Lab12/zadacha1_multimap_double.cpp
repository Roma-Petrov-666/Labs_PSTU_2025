#include <iostream>
#include <map>
#include <algorithm>

typedef std::multimap<int, double> TMultimap;

TMultimap make_multimap(int n) {
    TMultimap m;
    double val;
    for (int i = 0; i < n; ++i) {
        std::cout << "? ";
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

double max_value(const TMultimap& m) {
    auto it = std::max_element(m.begin(), m.end(),
        [](const std::pair<int,double>& a, const std::pair<int,double>& b) {
            return a.second < b.second;
        });
    return it->second;
}

double min_value(const TMultimap& m) {
    auto it = std::min_element(m.begin(), m.end(),
        [](const std::pair<int,double>& a, const std::pair<int,double>& b) {
            return a.second < b.second;
        });
    return it->second;
}

double average(const TMultimap& m) {
    double sum = 0.0;
    for (const auto& kv : m) sum += kv.second;
    return sum / m.size();
}

// Добавить максимальный элемент в начало (ключ на 1 меньше минимального ключа)
void add_max_to_begin(TMultimap& m) {
    if (m.empty()) return;
    double mx = max_value(m);
    int min_key = m.begin()->first;
    m.insert(std::make_pair(min_key - 1, mx));
}

// Удалить минимальный элемент (первое вхождение)
void remove_min(TMultimap& m) {
    if (m.empty()) return;
    double mn = min_value(m);
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it->second == mn) {
            m.erase(it);
            break;
        }
    }
}

// Прибавить среднее арифметическое ко всем элементам
void add_average(TMultimap& m) {
    if (m.empty()) return;
    double avg = average(m);
    for (auto& kv : m)
        kv.second += avg;
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