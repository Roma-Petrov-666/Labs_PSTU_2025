#include <iostream>
#include <cmath>

int main() {
    int n;
    double s;
    bool finish = false;
    std::cin>>n>>s;
    
    for (double i=1; i < n+1; i++) {
        if (s - sin(i + 1/i) < 0.00001) {
            finish = true;
        }
    }
    
    if (finish) {
        std::cout<<"Содержит";
    } else {
        std::cout<<"Не содержит";
    }
 
    return 0;
}