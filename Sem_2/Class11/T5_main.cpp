#include <iostream>

#include "SetStack.h"
#include "Money.h"

int main() {
    SetStack<double> ds;
    int n;
    std::cout << "Сколько double-элементов добавить? ";
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        double val;
        std::cout << "?";
        std::cin >> val;
        ds.Add(val);
    }
    ds.Print();

    ds.AddMaxToBegin();
    std::cout << "После AddMaxToBegin: ";
    ds.Print();

    ds.DelMin();
    std::cout << "После DelMin: ";
    ds.Print();

    ds.AddSrednee();
    std::cout << "После AddSrednee: ";
    ds.Print();

    SetStack<Money> ms;
    std::cout << "Сколько денежных сумм добавить? ";
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        Money m;
        std::cin >> m;
        ms.Add(m);
    }
    ms.Print();

    ms.AddMaxToBegin();
    std::cout << "После AddMaxToBegin: ";
    ms.Print();

    ms.DelMin();
    std::cout << "После DelMin: ";
    ms.Print();

    ms.AddSrednee();
    std::cout << "После AddSrednee: ";
    ms.Print();

    return 0;
}