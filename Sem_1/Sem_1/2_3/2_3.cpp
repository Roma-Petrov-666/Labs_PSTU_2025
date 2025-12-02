#include <iostream>

int main () {
    int n, sum, k;
    std::cin>>n;
    
    if (n <= 0) {
        std::cout<<"Ошибка"<<std::endl;
    } else {

        for (int i=1; i <= n; i++) {
            k = 1;
            for (int j=i; j <= 2*i; j++) {
                k *= j;
            }
            sum += k;
        }

        std::cout<<sum<<std::endl;
    }

    return 0;
}