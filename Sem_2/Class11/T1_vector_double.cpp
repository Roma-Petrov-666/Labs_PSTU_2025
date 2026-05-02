#include <iostream>
#include <vector>

typedef std::vector<double> Vec;

Vec make_vector(int n) {
    Vec v;
    for (int i = 0; i < n; ++i) {
        double a;
        std::cout << "?";
        std::cin >> a;
        v.push_back(a);
    }
    return v;
}

void print_vector(const Vec& v) {
    for (int i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

double srednee(const Vec& v) {
    double sum = 0.0;
    for (int i = 0; i < v.size(); ++i)
        sum += v[i];
    return sum / v.size();
}

int max_index(const Vec& v) {
    int imax = 0;
    for (int i = 1; i < v.size(); ++i)
        if (v[i] > v[imax]) imax = i;
    return imax;
}

int min_index(const Vec& v) {
    int imin = 0;
    for (int i = 1; i < v.size(); ++i)
        if (v[i] < v[imin]) imin = i;
    return imin;
}

void add_max_to_begin(Vec& v) {
    if (v.empty()) return;
    int imax = max_index(v);
    double max_val = v[imax];
    v.insert(v.begin(), max_val);
}

void del_min(Vec& v) {
    if (v.empty()) return;
    int imin = min_index(v);
    v.erase(v.begin() + imin);
}

void add_srednee(Vec& v) {
    if (v.empty()) return;
    double sr = srednee(v);
    for (int i = 0; i < v.size(); ++i)
        v[i] += sr;
}

int main() {
    try {
        Vec v;
        int n;
        std::cout << "N?";
        std::cin >> n;
        v = make_vector(n);
        print_vector(v);

        add_max_to_begin(v);
        std::cout << "После добавления максимального в начало:\n";
        print_vector(v);

        del_min(v);
        std::cout << "После удаления минимального:\n";
        print_vector(v);

        add_srednee(v);
        std::cout << "После прибавления среднего арифметического:\n";
        print_vector(v);

    } catch (...) {
        std::cout << "Ошибка!" << std::endl;
    }
    return 0;
}