#pragma once

#include "Person.h"

class Student : public Person {
public:
    Student(void);
    Student(std::string, int, float);
    Student(const Student&);
    ~Student(void);

    float Get_rating() const { return rating; }
    void Set_rating(float);

    Student& operator=(const Student&);

    void Show() override;
    void Input() override;
    void HandleEvent(const TEvent& e) override;

protected:
    float rating;
};