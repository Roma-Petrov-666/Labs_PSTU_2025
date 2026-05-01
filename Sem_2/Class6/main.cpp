#include <iostream>
#include "Set.h"

int main() {
    Set a(3);
    std::cout << "Изначальное множество a: " << a;

    std::cout << "Введите элементы множества a:" << std::endl;
    std::cin >> a;
    std::cout << "После ввода a = " << a;

    Set b(2);
    std::cout << "Введите элементы множества b (размер 2):" << std::endl;
    std::cin >> b;
    std::cout << "b = " << b;

    // Операция присваивания
    Set c;
    c = a;
    std::cout << "c = a : " << c;

    // Доступ по индексу
    std::cout << "a[1] = " << a[1] << std::endl;

    // Операция () – размер
    std::cout << "Размер a: " << a() << std::endl;

    // Объединение множеств
    Set d = a + b;
    std::cout << "Объединение a + b = " << d;

    // Проверка размера объединения
    std::cout << "Размер объединения: " << d() << std::endl;

    // Последовательный обход с итератором
    std::cout << "Элементы d через итератор:" << std::endl;
    for (Iterator it = d.first(); it != d.last(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Копирование конструктором
    Set e = d;
    std::cout << "Копия e = d: " << e;

    return 0;
}