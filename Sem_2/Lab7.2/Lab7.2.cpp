#include <iostream>
#include <string>

using namespace std;

int gcd(int a, int b) {
    int t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int nok(int a) {
    return a;
}

int nok(int a, int b) {
    return (a * b)/gcd(a, b);
}

template<typename... Args>
int nok(int first, int second, Args... rest) {
    int nok_two = nok(first, second);
    return nok(nok_two, rest...);
}

int main() {
	cout<<nok(4, 6, 8)<<endl;
	cout<<nok(3, 5, 7, 11, 13)<<endl;
	cout<<nok(42, 20, 6, 7, 18, 1)<<endl;
    
    return 0;
}
