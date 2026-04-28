#include <iostream>
#include "Class3.cpp"

int main() {
    Money a;
    Money b;
    Money c;

    std::cin >> a;
    std::cin >> b;

    ++a;
    std::cout << a << std::endl;

    c = (a++) + b;
    std::cout << "a=" << a << std::endl;
    std::cout << "b=" << b << std::endl;
    std::cout << "c=" << c << std::endl;

    return 0;
}