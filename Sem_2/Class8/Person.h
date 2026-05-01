#pragma once

#include <string>
#include <iostream>

#include "Object.h"

class Person : public Object {
public:
    Person(void);
    virtual ~Person(void);
    Person(std::string, int);
    Person(const Person&);

    std::string Get_name() const { return name; }
    int Get_age() const { return age; }
    void Set_name(std::string);
    void Set_age(int);

    Person& operator=(const Person&);

    void Show() override;
    void Input() override;
    void HandleEvent(const TEvent& e) override;

protected:
    std::string name;
    int age;
};