#include <iostream>
#include <cmath>

int main() {
    int n;
    double s;
    bool finish = false;
    std::cin>>n>>s;
    
    for (double i=0; i < n; i++) {
        if (abs(s - sin(n + i/n)) < 0.00001) {
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
