#pragma once

#include "Object.h"
#include "Event.h"

class List {
protected:
    struct Node {
        Object* data;
        Node* next;
        Node(Object* d = nullptr) : data(d), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int cur;          // текущее количество элементов
    int maxSize;      // максимально допустимое количество (0 – без ограничения)

public:
    List();
    virtual ~List();

    void Add(Object* p);          // добавить в конец
    void Del();                   // удалить с конца
    virtual void Show();          // показать все элементы
    int operator()() const { return cur; }
    void SetMaxSize(int s) { maxSize = s; }
    int GetMaxSize() const { return maxSize; }
    Object* Get(int index);       // получить элемент по индексу (0‑based)
    virtual void HandleEvent(const TEvent& e); // передать событие всем элементам
};