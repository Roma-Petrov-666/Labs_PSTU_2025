#include <iostream>
#include <cmath>

int main() {
    int n, counter=0;
    double max=-1, a;
    std::cin>>n;
    
    for (double i=0; i < n; i++) {
        a = sin(n + i/n);
        if (a > max) {
            max = a;
            counter = 1;
        } else if (max - a < 0.00001) {
            counter++;
        }
    }
    
    std::cout<<counter;
 
    return 0;
}