#include <iostream>

int lomutoSplit(int *arr, int low, int high) {
    int i = low - 1;
    int pivot = arr[high];

    for (int j=low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
	
    std::swap(arr[i+1], arr[high]);
    return i + 1;
}

void lomutoSort(int *arr, int low, int high) {
    if (low < high) {
        int p_idx = lomutoSplit(arr, low, high);
        lomutoSort(arr, low, p_idx - 1);
        lomutoSort(arr, p_idx + 1, high);
    }
}

int main() {
    int size = 10;
    int arr[size] = {5, 6, 8, 7, 1, 3, 4, 2, 9, 0};

    lomutoSort(arr, 0, size - 1);

    for (int i=0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}