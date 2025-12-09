#include <iostream>

int main() {
    int n, a, min, max;
    std::cin>>n;
    std::cin>>max;
    min = max;
    
    int *ptr_min = &min, *ptr_max = &max;
    
    for (int i=1; i < n; i++) {
        std::cin>>a;
        if (a > *ptr_max) {
            *ptr_max = a;
        } else if (a < *ptr_min) {
            *ptr_min = a;
        }
    }
    
    std::cout<<*ptr_min<<", "<<*ptr_max;
 
    return 0;
}