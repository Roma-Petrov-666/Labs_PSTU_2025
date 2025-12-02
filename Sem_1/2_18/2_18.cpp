#include <iostream>

int main() {
    int n, s=0;
    std::cin>>n;
    
    while (n > 0) {
        s = s*10 + n%10;
        n /= 10;
    }
    
    std::cout<<s;
 
    return 0;
}