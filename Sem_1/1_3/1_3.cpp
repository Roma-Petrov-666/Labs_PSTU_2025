#include <iostream>

int main () {
    double a;
    std::cin>>a;

    if (a < 5) {
        a *= 3;
    }
    else if (a > 7){
        a += 3;
    }
    else {
        a /= 10;
    }

    std::cout<<a<<std::endl;

    return 0;
}