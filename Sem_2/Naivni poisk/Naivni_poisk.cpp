#include <iostream>
#include <string>

int naivniSubstringSearch(std::string text, std::string pattern) {
    int n = text.length(); 
    int m = pattern.length();

    if (m == 0) return 0;
    if (m > n) return -1;
    bool isFound;
    for (int i=0; i <= n - m; i++) {
        isFound = true;

        for (int j=0; j < m; j++) {
            if (text[i+j] != pattern[j]) {
                isFound = false;
                break;
            }
        }

        if (isFound) return i;
    }

    return -1;
}

int main() {
    std::string text = "hello wrld, helo world, gello world, hello world";
    
    std::cout << naivniSubstringSearch(text, "world");
	
    return 0;
}