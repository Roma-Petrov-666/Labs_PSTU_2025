#include <iostream>
#include <cmath>

int main() {
    double x1, x2, a, b, c, D;
    std::cin>>a>>b>>c;
    
    D = sqrt(b*b - 4*a*c);
    
    x1 = (-b + D) / (2*a);
    x2 = (-b - D) / (2*a);

    std::cout<<x1<<std::endl<<x2;
 
    return 0;
}
