#include <iostream>
#include <cmath>
using namespace std;

double Sum_N(double n, double x) {
    double sum=0;
    for (int i=1; i <= n; i++) {
        sum = sum + cos(2*i*x) / (4*i*i - 1);
    }
    
    return sum;
}

double Sum_e(double e, double x) {
    double sum1 = 0;
    double sum2 = Sum_N(1, x);
    int i=2;
    
    while (abs(sum2 - sum1) >= e) {
        sum1 = sum2;
        sum2 += cos(2*i*x) / (4*i*i - 1);
        i++;
    }
    
    return sum2;
}

double Func(double x) {
    return 0.5 - (M_PI/4) * abs(sin(x));
}

int main() {
	double a = 0.1;
	double b = 0.8;
    
    for (double i=a; i < b; i += (b-a)/10) {
        cout<<"Значение: "<<Sum_N(50, i)<<"\t"<<"Погрешность: "<<abs(Func(i) - Sum_N(50, i))<<endl;
    }
    
    cout<<endl;
    
    for (double i=a; i < b; i += (b-a)/10) {
        cout<<"Значение: "<<Sum_e(0.0001, i)<<"\t"<<"Погрешность: "<<abs(Func(i) - Sum_e(0.0001, i))<<endl;
    }
    
    return 0;
}