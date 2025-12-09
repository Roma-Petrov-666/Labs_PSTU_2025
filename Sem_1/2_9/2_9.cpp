#include <iostream>

int main() {
	int n, d;
    std::cin>>n;
    d = n/2;

    // Заднняя грань
    for (int i=0; i < d; i++) {
        std::cout<<" ";
    }
    for (int i=0; i < n; i++) {
        std::cout<<"* ";
    }
    std::cout<<std::endl;

    // Верхние диагонали
    for (int i=0; i < d-1; i++) {
        for (int j=1; j < d-i; j++) {
            std::cout<<" ";
        }
        std::cout<<"* ";
        for (int j=0; j < n-2; j++) {
            std::cout<<"  ";
        }
        std::cout<<"*";
        for (int j=1; j < i; j++) {
            std::cout << " ";
        }
        std::cout<<"*"<<std::endl;
    }

    // Передняя верхняя грань + кусочек задней грани
    for (int i=0; i < n; i++) {
        std::cout<<"* ";
    }
    for (int i=0; i < d-2; i++) {
        std::cout<<" ";
    }
    std::cout<<"*"<<std::endl;

    // Боковые грани (без диагоналей, прямые)
    for (int i=0; i < n-d-1; i++) {
        std::cout<<"* ";
        for (int j=0; j < n-2; j++) {
            std::cout<<"  ";
        }
        std::cout<<"* ";
        for (int j=0; j < d-2; j++) {
            std::cout<<" ";
        }
        std::cout<<"*"<<std::endl;
    }
    
    // Нижние диагонали
    for (int i=0; i < d-1; i++) {
        std::cout<<"* ";
        for (int j=0; j < n-2; j++) {
            std::cout<<"  ";
        }
        std::cout<<"*";
        for (int j=1; j < d-i-1; j++) {
            std::cout<<" ";
        }
        std::cout<<"*"<<std::endl;
    }
    
    // Нижняя грань
    for (int i=0; i < n; i++) {
        std::cout<<"* ";
    }
    std::cout<<std::endl;

    return 0;
}
