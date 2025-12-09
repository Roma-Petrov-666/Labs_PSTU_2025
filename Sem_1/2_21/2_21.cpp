#include <iostream>

int main() {
	int a, a_pred;
	bool is_ordered = true, is_increases = true;
	std::cin>>a_pred>>a;
	
	if (a_pred != 0) {
	    if (a < a_pred) {
	        is_increases = false;
	    }
	    
	    while (a != 0) {
	        if ((a < a_pred && is_increases) || (a > a_pred && !is_increases)) {
	            is_ordered = false;
            }
        
            a_pred = a;
	        std::cin>>a;
	    }
	}
	
	if (is_ordered) {
	    std::cout<<"Упорядоченны";
	} else {
	    std::cout<<"Не упорядоченны";
	}

    return 0;
}