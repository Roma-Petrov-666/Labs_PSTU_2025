#include <cmath>
#include <iostream>

int main() {
    double a, b, c;
    double fa, fb, fc;
    double s = 0.000001;
    
    a = 0;
    b = 1;
    
    while (b-a > s) {
        c = (a+b)/2;
        fa = acos(a) - sqrt(1 - 0.3*pow(a, 3));
        fb = acos(b) - sqrt(1 - 0.3*pow(b, 3));
        fc = acos(c) - sqrt(1 - 0.3*pow(c, 3));
        
        if (fa*fc < 0) {
            b = c;
        } else if (fb*fc < 0) {
            a = c;
        }
    }
    
    std::cout<<a<<"; "<<b;
    
    return 0;
}