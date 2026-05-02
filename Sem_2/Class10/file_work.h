#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Money.h"

// Создание файла и заполнение
int make_file(const char* f_name) {
    std::fstream stream(f_name, std::ios::out | std::ios::trunc);
    if (!stream) return -1;
    int n;
    Money p;
    std::cout << "Количество записей? ";
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> p;
        stream << p << "\n";
    }
    stream.close();
    return n;
}

// Печать содержимого файла
int print_file(const char* f_name) {
    std::fstream stream(f_name, std::ios::in);
    if (!stream) return -1;
    Money p;
    int i = 0;
    while (stream >> p) {
        std::cout << p << "\n";
        ++i;
    }
    stream.close();
    return i;
}

// Удаление всех записей, равных заданному значению
int del_all_equal(const char* f_name, const Money& value) {
    std::fstream temp("temp", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) return -1;
    Money p;
    int deleted = 0, total = 0;
    while (stream >> p) {
        if (stream.eof()) break;
        ++total;
        if (p != value)   // сохраняем только не равные заданному
            temp << p;
        else
            ++deleted;
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp", f_name);
    return deleted;
}

// Увеличение на заданную сумму всех записей, равных значению value
int increase_equal_by(const char* f_name, const Money& value, const Money& inc) {
    std::fstream temp("temp", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) return -1;
    Money p;
    int changed = 0;
    while (stream >> p) {
        if (stream.eof()) break;
        if (p == value) {
            p = p + inc;
            ++changed;
        }
        temp << p;
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp", f_name);
    return changed;
}

// Добавление K записей после элемента с заданным номером
int add_k_after(const char* f_name, int K, int pos, const Money& sample) {
    std::fstream temp("temp", std::ios::out);
    std::fstream stream(f_name, std::ios::in);
    if (!stream) return -1;
    Money p;
    int i = 0, added = 0;
    bool inserted = false;
    while (stream >> p) {
        if (stream.eof()) break;
        temp << p;
        ++i;
        if (i == pos) {
            for (int j = 0; j < K; ++j) {
                temp << sample;
                ++added;
            }
            inserted = true;
        }
    }
    if (!inserted && pos >= i) {
        for (int j = 0; j < K; ++j) {
            temp << sample;
            ++added;
        }
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp", f_name);
    return added;
}