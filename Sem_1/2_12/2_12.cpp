#include <iostream>

int main() {
    int n, a, max, min;
    std::cin>>n;
    std::cin>>max;
    min = max;

    for (int i=0; i < n-1; i++) {
        std::cin>>a;
        if (a > max) {
            max = a;
        } else if (a < min) {
            min = a;
        }
    }
    
    std::cout<<max<<std::endl<<min;
 
    return 0;
}
