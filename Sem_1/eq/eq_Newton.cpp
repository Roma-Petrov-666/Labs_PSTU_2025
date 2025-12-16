#include <cmath>
#include <iostream>

int main() {
    double x, x_prev;
    
    x = 0;
    x_prev = 1;
    double s = 0.000001;
    
    while (abs(x - x_prev) > s) {
        x_prev = x;
        x = x_prev - ( acos(x_prev)-sqrt(1-0.3*pow(x_prev, 3)) )/( (9*pow(x_prev, 2)/(2*sqrt(10)*sqrt(10-3*pow(x_prev, 3)))) - 1/(sqrt(1-pow(x_prev, 2))) );
    }
    
    std::cout<<x;
    
    return 0;
}