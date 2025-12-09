#include <iostream>

int main() {
    double a, b;
    std::cin>>a>>b;
    double *ptr_a = &a, *ptr_b = &b;
    
    std::cout<<*ptr_a + *ptr_b;
 
    return 0;
}