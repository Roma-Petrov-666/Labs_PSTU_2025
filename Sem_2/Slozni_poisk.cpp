#include <iostream>
#include <string>

int* buildPrefixFunction(const std::string& pattern) {
    int m = pattern.size();
    int* pi = new int[m];
    pi[0] = 0;
    for (int i=1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
		}
        if (pattern[i] == pattern[j]) {
            ++j;
		}
        pi[i] = j;
    }
    return pi;
}

int Search(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0;
    if (n < m) return -1;

    int* pi = buildPrefixFunction(pattern);

    int j = 0;
    for (int i=0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
		}
        if (text[i] == pattern[j]) { ++j; }
        if (j == m) {
            delete[] pi;
            return i-m+1;
        }
    }

    delete[] pi;
    return -1;
}

int main() {
    std::string str = "abcabceabcabcd";
    std::string substr = "abcabcd";

    int pos = Search(str, substr);
    if (pos != -1)
        std::cout << "Найдено по интексу: " << pos << std::endl;
    else
        std::cout << "Не найдено" << std::endl;

    return 0;
}