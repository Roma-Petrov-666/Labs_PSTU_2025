#include <iostream>

int main() {
    int n;
    double x, y=1, y_i=1;
    std::cin>>n>>x;
    
    for (int i=1; i < n+1; i++) {
        y_i *= x/i;
        y += y_i;
    }
    
    std::cout<<y;
 
    return 0;
}