#include "Person.h"
#include "Event.h"

Person::Person(void) : name(""), age(0) {}
Person::~Person(void) {}
Person::Person(std::string N, int A) : name(N), age(A) {}
Person::Person(const Person& p) : name(p.name), age(p.age) {}

void Person::Set_name(std::string N) { name = N; }
void Person::Set_age(int A) { age = A; }

Person& Person::operator=(const Person& p) {
    if (&p == this) return *this;
    name = p.name;
    age = p.age;
    return *this;
}

void Person::Show() {
    std::cout << "Имя: " << name << ", возраст: " << age << std::endl;
}

void Person::Input() {
    std::cout << "Имя: ";
	std::cin >> name;
    std::cout << "Возраст: ";
	std::cin >> age;
}

void Person::HandleEvent(const TEvent& e) {
	
}