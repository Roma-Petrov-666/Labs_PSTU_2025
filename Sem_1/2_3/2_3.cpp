#include <iostream>

int main () {
    int n, sum, k;
    std::cin>>n;
    
    if (n <= 0) {
        std::cout<<"Ошибка"<<std::endl;
    } else {

        for (int i=1; i < n+1; i++) {
            k = 1;
            for (int j=i; j < 2*i+1; j++) {
                k *= j;
            }
            sum += k;
        }

        std::cout<<sum<<std::endl;
    }

    return 0;
}