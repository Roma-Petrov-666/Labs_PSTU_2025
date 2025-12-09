#include <iostream>

int main() {
    int n, fact=1;
    std::cin>>n;
    
    int *ptr_fact = &fact;
    
    for (int i=1; i < n+1; i++) {
        *ptr_fact *= i;
    }
    
    std::cout<<*ptr_fact;
 
    return 0;
}