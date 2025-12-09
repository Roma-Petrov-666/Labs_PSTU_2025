#include <iostream>

int main() {
    int a, b;
    std::cin>>a>>b;
    int *ptr_a = &a, *ptr_b = &b, *tmp;
    
    tmp = ptr_a;
    ptr_a = ptr_b;
    ptr_b = tmp;
    
    
    std::cout<<*ptr_a<<", "<<*ptr_b;
 
    return 0;
}