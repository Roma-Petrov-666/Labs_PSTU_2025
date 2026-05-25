#include <iostream>

#include "IndexedSet.h"
#include "Money.h"

int main() {
    try {
        std::cout << "===== IndexedSet<double> =====" << std::endl;
        IndexedSet<double> doubleSet;
        std::cin >> doubleSet;
        std::cout << "Исходный контейнер:\n" << doubleSet << std::endl;

        doubleSet.addMaxToBegin();
        std::cout << "После добавления max в начало:\n" << doubleSet << std::endl;

        doubleSet.delMin();
        std::cout << "После удаления min:\n" << doubleSet << std::endl;

        doubleSet.addSrednee();
        std::cout << "После прибавления среднего:\n" << doubleSet << std::endl;

        std::cout << "\n===== IndexedSet<Money> =====" << std::endl;
        IndexedSet<Money> moneySet;
        std::cin >> moneySet;
        std::cout << "Исходный контейнер:\n" << moneySet << std::endl;

        moneySet.addMaxToBegin();
        std::cout << "После добавления max в начало:\n" << moneySet << std::endl;

        moneySet.delMin();
        std::cout << "После удаления min:\n" << moneySet << std::endl;

        moneySet.addSrednee();
        std::cout << "После прибавления среднего:\n" << moneySet << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}