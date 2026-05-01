#include <iostream>

#include "List.h"

List::List() : head(nullptr), tail(nullptr), cur(0), maxSize(0) {}

List::~List() {
    Node* p = head;
    while (p) {
        Node* t = p;
        p = p->next;
        delete t;    // удаляем только узел, объекты не удаляются
    }
}

void List::Add(Object* p) {
    if (maxSize > 0 && cur >= maxSize) {
        std::cout << "Группа заполнена (макс. " << maxSize << " элементов)." << std::endl;
        return;
    }
    Node* n = new Node(p);
    if (!head) {
        head = tail = n;
    } else {
        tail->next = n;
        tail = n;
    }
    cur++;
}

void List::Del() {
    if (!head) {
        std::cout << "Список пуст, удаление невозможно." << std::endl;
        return;
    }
    if (head == tail) {   // один элемент
        delete head;
        head = tail = nullptr;
    } else {
        Node* p = head;
        while (p->next != tail) p = p->next;
        delete tail;
        tail = p;
        tail->next = nullptr;
    }
    cur--;
}

void List::Show() {
    if (!head) {
        std::cout << "Группа пуста." << std::endl;
        return;
    }
    Node* p = head;
    int i = 1;
    while (p) {
        std::cout << "Элемент " << i++ << ": ";
        p->data->Show();
        p = p->next;
    }
}

Object* List::Get(int index) {
    if (index < 0 || index >= cur) return nullptr;
    Node* p = head;
    for (int i=0; i < index; i++) p = p->next;
    return p->data;
}

void List::HandleEvent(const TEvent& e) {
    if (e.what == evMessage) {
        Node* p = head;
        while (p) {
            p->data->HandleEvent(e);
            p = p->next;
        }
    }
}