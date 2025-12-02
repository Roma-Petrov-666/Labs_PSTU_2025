#include <iostream>

int main () {
    int n, prod=1;
    std::cin>>n;
 
    if (n <= 0) {
        std::cout<<"Ошибка"<<std::endl;
    } else {

        for (int i=1; i <= n; i++) {
            prod *= i;
        }

        std::cout<<prod<<std::endl;
    }

    return 0;
}