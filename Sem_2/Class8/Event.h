#pragma once

const int evNothing = 0;   // пустое событие
const int evMessage = 100; // событие-сообщение

const int cmAdd = 1;        // добавить объект
const int cmDel = 2;        // удалить объект
const int cmGetElement = 3; // показать элемент по номеру
const int cmShow = 4;       // показать всю группу
const int cmMake = 6;       // создать группу
const int cmQuit = 101;     // выход

struct TEvent {
    int what;       // тип события
    union {
        int command; // код команды
        struct {
            int message;
            int a;   // параметр команды
        };
    };
};