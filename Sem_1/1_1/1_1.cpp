#include <iostream>

int main () {
    int a, b, c, max;
    std::cin>>a>>b>>c;

    if (a >= b) {
        if (a >= c) {
            max = a;
        }
        else {
            max = c;
        }
    }
    else {
        if (b >= c) {
            max = b;
        }
        else {
            max = c;
        }
    }

    std::cout<<max<<std::endl;

    return 0;
}