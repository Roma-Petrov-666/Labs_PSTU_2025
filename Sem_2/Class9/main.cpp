#include <iostream>

#include "Set.h"

int main() {
    try {
        Set a(2);
        std::cin >> a;
        std::cout << "a: " << a << std::endl;

        // доступ к элементам
        std::cout << "a[1] = " << a[1] << std::endl;
        // std::cout << a[-1];   // IndexErrorNegative
        // std::cout << a[5];    // IndexErrorLarge

        std::cout << "size = " << a() << std::endl;

        ++a;
        std::cout << "after ++a: " << a << std::endl;
        a++;
        std::cout << "after a++: " << a << std::endl;

        Set b(2);
        std::cin >> b;
        std::cout << "b: " << b << std::endl;

        Set c = a + b;
        std::cout << "a + b: " << c << std::endl;

        // Set huge(MAX_SIZE + 1);   // MaxSizeError
        // while (true) ++a;         // OverflowError

    } catch (const Error& e) {
        std::cout << "Caught exception: ";
        e.what();
    }
    return 0;
}