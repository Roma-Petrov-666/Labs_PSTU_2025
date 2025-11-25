#include <iostream>

int main () {
    int n;
    std::cin>>n;

    for (int i=0; i < (n-1)/2; i++) {
        for (int j=0; j*2+1 < n; j++) {
            std::cout<<" ";
        }
        std::cout<<"*"<<std::endl;
    }

    return 0;
}