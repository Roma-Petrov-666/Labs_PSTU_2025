#include <iostream>

int main () {
    int n, sum;
    std::cin>>n;

    if (n <= 0) {
        std::cout<<"Ошибка"<<std::endl;
    } else {

    	for (int i=1; i <= n; i++) {
     	  sum += i;
    	}

    	std::cout<<sum<<std::endl;
	}

    return 0;
}