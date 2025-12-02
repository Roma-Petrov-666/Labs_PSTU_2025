#include <iostream>

int main() {
    int n, s;
    bool is_included = false;
    std::cin>>n>>s;
    
    while (n > 0) {
        if (n%10 == s) {
            is_included = true;
        }
        n /= 10;
    }
    
    if (is_included) {
        std::cout<<"Входит";
    } else {
        std::cout<<"Не входит";
    }
 
    return 0;
}