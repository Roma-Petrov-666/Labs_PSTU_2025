#include <cstdlib>    // atoi

#include "Dialog.h"
#include "Student.h"

Dialog::Dialog(void) : List(), EndState(0) {}
Dialog::~Dialog(void) {}

void Dialog::GetEvent(TEvent& event) {
    std::string opInt = "+-s?mql";   // допустимые первые символы команд
    std::string s;
    std::cout << "> ";
    std::cin >> s;
    char code = s[0];
    if (opInt.find(code) != std::string::npos) {
        event.what = evMessage;
        switch (code) {
            case 'm': event.command = cmMake;   break;
            case '+': event.command = cmAdd;    break;
            case '-': event.command = cmDel;    break;
            case 's': event.command = cmShow;   break;
            case '?': event.command = cmGetElement; break;
            case 'q': event.command = cmQuit;   break;
        }
        // параметр команды, если есть
        if (s.length() > 1) {
            std::string param = s.substr(1, s.length()-1);
            event.a = atoi(param.c_str());
        } else {
            event.a = 0;
        }
    } else {
        event.what = evNothing;
    }
}

int Dialog::Execute() {
    TEvent event;
    do {
        EndState = 0;
        GetEvent(event);
        HandleEvent(event);
    } while (!Valid());
    return EndState;
}

int Dialog::Valid() {
    return (EndState == 0) ? 0 : 1;
}

void Dialog::ClearEvent(TEvent& event) {
    event.what = evNothing;
}

void Dialog::EndExec() {
    EndState = 1;
}

void Dialog::HandleEvent(TEvent& event) {
    if (event.what != evMessage) return;

    switch (event.command) {
        case cmMake:   // создать группу с заданной вместимостью
            maxSize = event.a;
            // очистка существующего списка
            while (cur > 0) Del();
            std::cout << "Создана группа вместимостью " << maxSize << std::endl;
            ClearEvent(event);
            break;

        case cmAdd:    // добавить нового СТУДЕНТА
            {
                Student* st = new Student;
                st->Input();
                Add(st);
                std::cout << "Студент добавлен. Текущий размер: " << cur;
                if (maxSize > 0) std::cout << "/" << maxSize;
                std::cout << std::endl;
                ClearEvent(event);
            }
            break;

        case cmDel:    // удалить последний элемент
            Del();
            ClearEvent(event);
            break;

        case cmShow:   // показать всю группу
            Show();
            ClearEvent(event);
            break;

        case cmGetElement: {   // показать элемент с номером (параметр a)
            int idx = event.a - 1;   // пользователь вводит номер, начиная с 1
            Object* obj = Get(idx);
            if (obj) {
                std::cout << "Элемент с номером " << event.a << ":" << std::endl;
                obj->Show();
            } else {
                std::cout << "Элемента с номером " << event.a << " не существует." << std::endl;
            }
            ClearEvent(event);
            break;
        }

        case cmQuit:   // завершение работы
            EndExec();
            ClearEvent(event);
            break;

        default:       // событие не обработано – передаём элементам
            List::HandleEvent(event);
            break;
    }
}