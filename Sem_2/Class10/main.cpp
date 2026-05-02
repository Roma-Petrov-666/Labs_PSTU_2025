#include <iostream>
#include <cstdlib>

#include "Money.h"
#include "file_work.h"

int main() {
    Money value;
    int choice;
    char file_name[30];
    do {
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "Имя файла: ";
            std::cin >> file_name;
            if (make_file(file_name) < 0)
                std::cout << "Ошибка создания файла\n";
            break;
        case 2:
            std::cout << "Имя файла: ";
            std::cin >> file_name;
            {
                int cnt = print_file(file_name);
                if (cnt < 0)
                    std::cout << "Ошибка чтения файла\n";
                else if (cnt == 0)
                    std::cout << "Файл пуст\n";
            }
            break;
        case 3:
            std::cout << "Имя файла: ";
            std::cin >> file_name;
            std::cout << "Задайте значение для удаления:\n";
            std::cin >> value;
            {
                int del = del_all_equal(file_name, value);
                if (del < 0)
                    std::cout << "Ошибка при обработке файла\n";
                else
                    std::cout << "Удалено записей: " << del << std::endl;
            }
            break;
        case 4:
			std::cout << "Имя файла: ";
			std::cin >> file_name;
			std::cout << "Задайте значение, которое нужно увеличить:\n";
			std::cin >> value;
			{
				Money increment(1, 50);  // сумма, на которую увеличиваем
				int ch = increase_equal_by(file_name, value, increment);
				if (ch < 0)
					std::cout << "Ошибка при обработке файла\n";
				else
					std::cout << "Изменено записей: " << ch << std::endl;
			}
			break;
        case 5:
            std::cout << "Имя файла: ";
            std::cin >> file_name;
            {
                int K, pos;
                Money sample;
                std::cout << "Введите K (количество добавляемых записей): ";
                std::cin >> K;
                std::cout << "Введите номер элемента, после которого добавить: ";
                std::cin >> pos;
                std::cout << "Введите образец записи:\n";
                std::cin >> sample;
                int add = add_k_after(file_name, K, pos, sample);
                if (add < 0)
                    std::cout << "Ошибка при обработке файла\n";
                else
                    std::cout << "Добавлено записей: " << add << std::endl;
            }
            break;
        case 0:
            std::cout << "Завершение работы.\n";
            break;
        default:
            std::cout << "Неверный пункт меню.\n";
        }
    } while (choice != 0);
    return 0;
}