#include <iostream>

int main () {
    int n;
    std::cin>>n;

    if (n < 0) {
        std::cout<<"Ошибка"<<std::endl;
    } else {

        std::cout<<(n*(n+1))/2<<std::endl;
    }

    return 0;
}