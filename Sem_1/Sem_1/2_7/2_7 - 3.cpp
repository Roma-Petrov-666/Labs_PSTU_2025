#include <iostream>

int main () {
    int n;
    std::cin>>n;

    if (n <= 0) {
        std::cout<<"Ошибка";
    } else {
        for (int i=0; i < n; i++) {
            std::cout<<"*";
        }
        std::cout<<std::endl;
        
        for (int i=0; i < n-2; i++) {
            std::cout<<"*";
            for (int j=0; j < n-2; j++) {
                std::cout<<" ";
            }
            std::cout<<"*"<<std::endl;
        }
        
        for (int i=0; i < n; i++) {
            std::cout<<"*";
        }
	std::cout<<std::endl;
    }

    return 0;
}