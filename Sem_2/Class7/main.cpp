#include <iostream>

#include "Set.h"
#include "Money.h"

int main() {
    // ==================================================
    // 1. Тестирование шаблона на стандартных типах
    // ==================================================
    std::cout << "===== Testing Set<int> =====" << std::endl;
    Set<int> intSet(3, 0);                 // три элемента, инициализированы нулём
    std::cin >> intSet;
    std::cout << "intSet = " << intSet << std::endl;

    Set<int> intSet2(2, 0);
    std::cin >> intSet2;
    std::cout << "intSet2 = " << intSet2 << std::endl;

    Set<int> unionInt = intSet + intSet2;
    std::cout << "Union: " << unionInt << std::endl;
    std::cout << "Union size = " << unionInt() << std::endl;

    std::cout << "\n===== Testing Set<float> =====" << std::endl;
    Set<float> floatSet(2, 0.0f);
    std::cin >> floatSet;
    std::cout << "floatSet = " << floatSet << std::endl;

    Set<float> floatSet2(2, 0.0f);
    std::cin >> floatSet2;
    std::cout << "Union: " << (floatSet + floatSet2) << std::endl;

    std::cout << "\n===== Testing Set<double> =====" << std::endl;
    Set<double> doubleSet(2, 0.0);
    std::cin >> doubleSet;
    Set<double> doubleSet2(1, 1.0);
    std::cin >> doubleSet2;
    std::cout << "Union: " << (doubleSet + doubleSet2) << std::endl;

    // ==================================================
    // 2. Тестирование шаблона на пользовательском классе Money
    // ==================================================
    std::cout << "\n===== Testing Set<Money> =====" << std::endl;
    Set<Money> moneySet(2);                // два элемента, начальное значение 0,00
    std::cin >> moneySet;
    std::cout << "moneySet = " << moneySet << std::endl;

    Set<Money> moneySet2(2);
    std::cin >> moneySet2;
    std::cout << "moneySet2 = " << moneySet2 << std::endl;

    Set<Money> unionMoney = moneySet + moneySet2;
    std::cout << "Union: " << unionMoney << std::endl;
    std::cout << "Union size = " << unionMoney() << std::endl;

    // Доступ по индексу
    std::cout << "First element of union: " << unionMoney[0] << std::endl;

    return 0;
}