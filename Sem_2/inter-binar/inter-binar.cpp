#include <iostream>
#include <string>

int linearSubstringSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return 0;
    if (m > n) return -1;

    for (int i=0; i <= n-m; ++i) {
        bool found = true;
        for (int j=0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

bool issufLess(const std::string& text, int next, int cur) {
    int n = text.length();
    while (next < n && cur < n) {
        if (text[next] != text[cur]) {
            return text[next] < text[cur];
        }
        ++next;
        ++cur;
    }
    return next == n && cur < n;
}

void bubleSort(int* sufArray, int n, const std::string& text) {
    for (int i=0; i < n-1; ++i) {
        for (int j=0; j < n-i-1; ++j) {
            if (issufLess(text, sufArray[j+1], sufArray[j])) {
                int temp = sufArray[j];
                sufArray[j] = sufArray[j+1];
                sufArray[j+1] = temp;
            }
        }
    }
}

int binarySubstringSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return 0;
    if (m > n) return -1;

    int* sufArray = new int[n];
    for (int i=0; i < n; ++i) {
        sufArray[i] = i;
    }
    bubleSort(sufArray, n, text);

    int left = 0;
    int right = n-1;

    while (left <= right) {
        int mid = (left + right)/2;
        int sufIdx = sufArray[mid];

        bool equal = true;
        bool less = false;

        for (int j=0; j < m; ++j) {
            if (sufIdx + j >= n) {
                equal = false;
                less = true;
                break;
            }
            if (pattern[j] != text[sufIdx + j]) {
                equal = false;
                if (pattern[j] < text[sufIdx + j]) {
                    less = true;
                }
                break;
            }
        }

        if (equal) {
            delete[] sufArray;
            return sufIdx;
        }

        if (less) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    delete[] sufArray;
    return -1;
}

int interpolationSearch(const int* arr, int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            return (arr[low] == target) ? low : -1;
        }

        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        if (pos < low || pos > high) return -1;

        if (arr[pos] == target) {
            return pos;
        }
        if (arr[pos] < target) {
            low = pos+1;
        } else {
            high = pos-1;
        }
    }
    return -1;
}

int main() {
    std::string text = "hello wrld, helo world, gello world, hello world";

    std::cout << "Линейный поиск 'world': " << linearSubstringSearch(text, "world") << std::endl;
    std::cout << "Бинарный поиск 'hello': " << binarySubstringSearch(text, "hello") << std::endl;

    const int size = 10;
    int numbers[size] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << "Интерполяционный поиск 2: " << interpolationSearch(numbers, size, 2) << std::endl;

    return 0;
}