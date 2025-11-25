#include <iostream>

int main () {
    double a, b;
    std::cin>>a>>b;

    if (b == 0) {
        std::cout<<"Ошибка"<<std::endl;
    }
    else {
        std::cout<<a/b<<std::endl;
    }

    return 0;
}