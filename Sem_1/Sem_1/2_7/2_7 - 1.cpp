#include <iostream>
#include <cmath>

int main () {
    int n, k;
    std::cin>>n;

    if (floor(sqrt(n)) != sqrt(n)) {
        std::cout<<"Ошибка";
    } else {
        k = sqrt(n);
        
        for (int i=0; i < k; i++) {
            for (int j=0; j < k; j++) {
                std::cout<<"*";
            }
            std::cout<<std::endl;
        }
    }
    return 0;
}