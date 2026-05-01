#include "Student.h"

Student::Student(void) : Person(), rating(0.0) {}
Student::Student(std::string N, int A, float R) : Person(N, A), rating(R) {}
Student::Student(const Student& s) : Person(s), rating(s.rating) {}
Student::~Student(void) {}

void Student::Set_rating(float R) { rating = R; }

Student& Student::operator=(const Student& s) {
    if (&s == this) return *this;
    Person::operator=(s);
    rating = s.rating;
    return *this;
}

void Student::Show() {
    std::cout << "--- СТУДЕНТ ---" << std::endl;
    Person::Show();
    std::cout << "Рейтинг: " << rating << std::endl;
}

void Student::Input() {
    Person::Input();
    std::cout << "Рейтинг: ";
	std::cin >> rating;
}

void Student::HandleEvent(const TEvent& e) {
    Person::HandleEvent(e);
}