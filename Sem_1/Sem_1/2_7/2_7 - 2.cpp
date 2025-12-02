#include <iostream>

int main () {
    int n;
    std::cin>>n;

    if (n <= 0) {
        std::cout<<"Ошибка";
    } else {
        for (int i=0; i < n; i++) {
            for (int j=0; j < n; j++) {
                std::cout<<"*";
            }
            std::cout<<std::endl;
        }
    }

    return 0;
}