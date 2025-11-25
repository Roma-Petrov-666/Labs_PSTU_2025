#include <iostream>

int main () {
    int n;
    std::cin>>n;
    
    int spaces = n/2;
    int stars = 1;

    for (int i=0; i < (n+1)/2; i++)
    {
        for (int j=0; j < spaces; j++) 
        {  
            std::cout << " ";  
        }
        spaces--;
        for (int j=0; j < stars; j++)
        {
            std::cout << "*";
        }
        stars += 2;
        std::cout << std::endl;  
    }  

    return 0;
}
