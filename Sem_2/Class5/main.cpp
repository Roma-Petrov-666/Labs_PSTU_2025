#include <iostream>

#include "Pair.h"
#include "Long.h"
#include "Vector.h"

int main() {
    Vector v(5);
    PAIR a;
    LONG b;

    std::cout << "Enter PAIR object:" << std::endl;
    a.Input();
    std::cout << std::endl << "Enter LONG object:" << std::endl;
    b.Input();

    Object* p = &a;
    v.Add(p);
    p = &b;
    v.Add(p);

    std::cout << std::endl << "Vector contents (polymorphic Show):" << std::endl;
    std::cout << v;

    return 0;
}