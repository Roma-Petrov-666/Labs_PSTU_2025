#include <iostream>

int main() {
    int a=10;
    int *ptr_a = &a;
    
    *ptr_a = 100;
    
    std::cout<<*ptr_a;
 
    return 0;
}