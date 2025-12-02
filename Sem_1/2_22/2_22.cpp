#include <iostream>
#include <cmath>

int main() {
    int n, n_max;
    double max=-1, a;
    std::cin>>n;
    
    for (double i=0; i < n; i++) {
        a = sin(n + i/n);
        if (a > max) {
            max = a;
            n_max = i;
        }
    }
    
    std::cout<<max<<", "<<n_max;
 
    return 0;
}