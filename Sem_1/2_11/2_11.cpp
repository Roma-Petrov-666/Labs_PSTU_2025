#include <iostream>

int main() {
    int n, a;
    bool plusFirst = false;
    bool minusFirst = false;
    std::cin>>n;

    for (int i=0; i < n; i++) {
        std::cin>>a;
        if (!plusFirst && !minusFirst) {
            if (a > 0) {
                plusFirst = true;
            } else if (a < 0) {
                minusFirst = true;
            }
        }
    }
    
    if (plusFirst) {
        std::cout<<"Первые положительные";
    } else if (minusFirst) {
        std::cout<<"Первые отрицательные";
    } else {
        std::cout<<"Все 0";
    }
 
    return 0;

}
