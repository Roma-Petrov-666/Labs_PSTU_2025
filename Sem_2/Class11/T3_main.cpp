#include <iostream>

#include "Set.h"
#include "Money.h"

int main() {
    Set<int> intSet(3, 0);
    std::cout << "Введите " << 3 << " целых числа:\n";
    for (int i = 0; i < 3; ++i) {
        int val;
        std::cin >> val;
        intSet[i] = val;  // прямая запись по индексу
    }
    intSet.Print();

    intSet.AddMaxToBegin();
    std::cout << "После AddMaxToBegin: ";
    intSet.Print();

    intSet.DelMin();
    std::cout << "После DelMin: ";
    intSet.Print();

    intSet.AddSrednee();
    std::cout << "После AddSrednee: ";
    intSet.Print();

    // Тест с Money
    std::cout << "\n==== Set<Money> ====" << std::endl;
    Set<Money> moneySet(2);
    std::cout << "Введите 2 денежные суммы:\n";
    for (int i = 0; i < 2; ++i) {
        Money m;
        std::cin >> m;
        moneySet.Add(m);   // автоматически проверит уникальность
    }
    moneySet.Print();

    moneySet.AddMaxToBegin();
    std::cout << "После AddMaxToBegin: ";
    moneySet.Print();

    moneySet.DelMin();
    std::cout << "После DelMin: ";
    moneySet.Print();

    moneySet.AddSrednee();
    std::cout << "После AddSrednee: ";
    moneySet.Print();

    return 0;
}