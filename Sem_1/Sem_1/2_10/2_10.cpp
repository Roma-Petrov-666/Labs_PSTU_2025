#include <iostream>

int main() {
    int n, a, max;
    std::cin>>n;
    std::cin>>max;

    for (int i=0; i < n-1; i++) {
        std::cin>>a;
        if (a > max) {
            max = a;
        }
    }
    
    std::cout<<max;
 
    return 0;
}