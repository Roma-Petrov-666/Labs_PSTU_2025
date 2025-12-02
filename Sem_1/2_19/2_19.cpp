#include <iostream>

int main() {
    int n, sum=0;
    std::cin>>n;
    
    for (int i=1; i < n+1; i++) {
        if (i%3 == 0) {
            sum -= i;
        } else {
            sum += i;
        }
    }
    
    std::cout<<sum;
 
    return 0;
}