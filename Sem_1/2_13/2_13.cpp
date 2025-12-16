#include <cmath>
#include <iostream>

int main() {
    float a, b, c, d, x1, x2;
    std::cin>>a>>b>>c;
    d = b*b - 4*a*c;
    
    if (d > 0) {
        x1 = (-b + sqrt(d)) / (2*a);
        x2 = (-b - sqrt(d)) / (2*a);
        std::cout<<"x1="<<x1<<"; x2="<<x2;
    } else if (d == 0) {
        x1 = (-b) / (2*a);
        std::cout<<"x1=x2="<<x1;
    } else {
        std::cout<<"Корней нет";
    }

}