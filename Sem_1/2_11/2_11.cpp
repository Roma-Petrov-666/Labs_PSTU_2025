#include <iostream>

int main() {
    int n, a, sign=0;
    std::cin>>n;

    for (int i=0; i < n; i++) {
        std::cin>>a;
        if (a > 0) {
            sign = 1;
            break;
        } else if (a < 0) {
            sign = -1;
            break;
        }
    }
    
    if (sign == 1) {
        std::cout<<"Первые положительные";
    } else if (sign == -1) {
        std::cout<<"Первые отрицательные";
    } else {
        std::cout<<"Все 0";
    }
 
    return 0;
}